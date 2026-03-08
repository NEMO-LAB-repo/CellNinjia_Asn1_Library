#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-GM-TX-Report-S-H.h"
#include "LTE-ML1-GM-TX-Report-R-H.h"
#include "LTE-ML1-GM-TX-Report-R-H-Exd.h"
#include "LTE-ML1-GM-TX-Report-R-H-PUCCH.h"
#include "LTE-ML1-GM-TX-Report-R-H-PUSCH.h"
#include "host.h"

void convert_S_H_B16D(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_R_H_B16D(uint8_t *hex_data, int *index)
{
    *index+=4;
    //5 6 7
    convert_endianess(hex_data, index, 3);
    //8
    *index+=1;
}

void convert_R_H_Exd_B16D(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
}

void convert_PUSCH_B16D(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=4;
    convert_endianess(hex_data, index, 2);
    *index+=2;
}
void convert_PUCCH_B16D(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=4;
    convert_endianess(hex_data, index, 2);
    *index+=2;
}

void decode_B16D(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_GM_TX_Report_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_GM_TX_Report_R_H_t  *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    LTE_ML1_GM_TX_Report_R_H_Exd_t  *t_R_H_Exd = 0;
    asn_dec_rval_t rval_R_H_Exd;
    LTE_ML1_GM_TX_Report_R_H_PUSCH_t  *t_R_H_PUSCH = 0;
    asn_dec_rval_t rval_R_H_PUSCH;
    LTE_ML1_GM_TX_Report_R_H_PUCCH_t  *t_R_H_PUCCH = 0;
    asn_dec_rval_t rval_R_H_PUCCH;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B16D(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_GM_TX_Report_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_GM_TX_Report_S_H, t_S_H); 

    //num of records
    int num_of_records=hex_data[start_S_H+3];
    printf("num_of_records=%d\n",num_of_records);

    /*Record*/
    for(int i=0;i<num_of_records;i++)
    {
        printf("\n[%d] Records\n",i);
        /*R-H*/
        int start_R_H = *index;
        convert_R_H_B16D(hex_data, index);
        int R_H_length = *index - start_R_H;

        rval_R_H = uper_decode(0, &asn_DEF_LTE_ML1_GM_TX_Report_R_H, (void **)&t_R_H, hex_data+start_R_H, R_H_length, 0, 0);
        if(rval_R_H.code != RC_OK) {
        printf("rval_R_H decode error\n");
        exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_GM_TX_Report_R_H, t_R_H);

        //ack/nak to send mask
        int mask_len=hex_data[start_R_H+7]&0x02;
        printf("mask_len=%d\n",mask_len);

        if(mask_len==2)
        {
            *index+=14;
            //printf("ACK/NAK to Send Mask: 0000000000000000000000000000H\n");
        }
        else
        {
            *index+=2;
            //printf("ACK/NAK to Send Mask: 0000H\n");
        }

        /*R-H-Exd*/
        int start_R_H_Exd = *index;
        printf("index=%d\n",*index);
        convert_R_H_Exd_B16D(hex_data, index);
        int R_H_Exd_length = *index - start_R_H_Exd;

        rval_R_H_Exd = uper_decode(0, &asn_DEF_LTE_ML1_GM_TX_Report_R_H_Exd, (void **)&t_R_H_Exd, hex_data+start_R_H_Exd, R_H_Exd_length, 0, 0);
        if(rval_R_H_Exd.code != RC_OK) {
            printf("rval_R_H_Exd decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_GM_TX_Report_R_H_Exd, t_R_H_Exd);

        //Total TX Power
        int Tota_Tx_Power = ((hex_data[start_R_H_Exd]&0x3F)<<2)|((hex_data[start_R_H_Exd+1]&0xC0)>>6);
        if(Tota_Tx_Power>128)
        {
            Tota_Tx_Power-=256;
        }
        printf("Tota_Tx_Power=%d\n",Tota_Tx_Power);

        if(Tota_Tx_Power>=0)
        {
            /*PUSCH*/
            int start_R_H_PUSCH = *index;
            convert_PUSCH_B16D(hex_data, index);
            int R_H_PUSCH_length = *index - start_R_H_PUSCH;

            rval_R_H_PUSCH = uper_decode(0, &asn_DEF_LTE_ML1_GM_TX_Report_R_H_PUSCH, (void **)&t_R_H_PUSCH, hex_data+start_R_H_PUSCH, R_H_PUSCH_length, 0, 0);
            if(rval_R_H_PUSCH.code != RC_OK) {
                printf("rval_R_H_PUSCH decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_ML1_GM_TX_Report_R_H_PUSCH, t_R_H_PUSCH);
        }
        else
        {
            /*PUCCH*/
            int start_R_H_PUCCH = *index;
            convert_PUCCH_B16D(hex_data, index);
            int R_H_PUCCH_length = *index - start_R_H_PUCCH;

            rval_R_H_PUCCH = uper_decode(0, &asn_DEF_LTE_ML1_GM_TX_Report_R_H_PUCCH, (void **)&t_R_H_PUCCH, hex_data+start_R_H_PUCCH, R_H_PUCCH_length, 0, 0);
            if(rval_R_H_PUCCH.code != RC_OK) {
                printf("rval_R_H_PUCCH decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_ML1_GM_TX_Report_R_H_PUCCH, t_R_H_PUCCH);
        }
    }
    printf("decode_B16D over!!!!\n");
}