#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "RLC-DL-AM-CONTROL-PDU-S-HEADER.h"
#include "RLC-DL-AM-CONTROL-PDU-PDU.h"
#include "RLC-DL-AM-Control-PDU-E1.h"
#include "host.h"

// specific header
void convert_S_H_B083(uint8_t *hex_data, int *index)
{
    *index+=8;
}

// pdu structure
void convert_pdu_B083(uint8_t *hex_data, int *index)
{
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=6;

}

// specific header
void convert_E1_B083(uint8_t *hex_data, int *index)
{
    *index+=2;
}


void decode_B083(uint8_t *hex_data, size_t length, int *index)
{
    /*introduce different sub structure*/
    RLC_DL_AM_CONTROL_PDU_S_HEADER_t *t_S_H =0;
    asn_dec_rval_t rval_S_H; /* Decoder return value  */
    RLC_DL_AM_CONTROL_PDU_PDU_t *t_PDU =0;
    asn_dec_rval_t rval_PDU; /* Decoder return value  */
    RLC_DL_AM_Control_PDU_E1_t *t_E1 =0;
    asn_dec_rval_t rval_E1; /* Decoder return value  */


    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B083(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_RLC_DL_AM_CONTROL_PDU_S_HEADER, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_RLC_DL_AM_CONTROL_PDU_S_HEADER, t_S_H);   

    int num_control_pdu = hex_data[start_S_H+4];
    printf("num_control_pdu:%d\n",num_control_pdu);
    for(int i=0;i<num_control_pdu;i++)
    {
        /*PDU*/
        printf("[%d]\n",i);
        int start_PDU = *index;
        convert_pdu_B083(hex_data, index);
        int PDU_length = *index-start_PDU;

        rval_PDU = uper_decode(0, &asn_DEF_RLC_DL_AM_CONTROL_PDU_PDU, (void **)&t_PDU, hex_data+start_PDU, PDU_length, 0, 0);
        if(rval_PDU.code != RC_OK) {
        printf("rval_PDU decode error\n");
        exit(65);
        }
        xer_fprint(stdout, &asn_DEF_RLC_DL_AM_CONTROL_PDU_PDU, t_PDU); 

        //E1 exist flag
        int E1_exist_flag =  ((hex_data[start_PDU+9] & 0x03) >> 1 );
        printf("E1_exist_flag=%d\n", E1_exist_flag);
        int E2_exist_flag =  ((hex_data[start_PDU+9] & 0x01));
        printf("E2_exist_flag=%d\n", E2_exist_flag);

        if(E1_exist_flag==1)
        {
            /*E1*/
            int start_E1 = *index;
            convert_E1_B083(hex_data, index);
            int E1_length = *index-start_E1;

            rval_E1 = uper_decode(0, &asn_DEF_RLC_DL_AM_Control_PDU_E1, (void **)&t_E1, hex_data+start_E1, E1_length, 0, 0);
            if(rval_E1.code != RC_OK) {
                printf("rval_E1 decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_RLC_DL_AM_Control_PDU_E1, t_E1); 
        }

        if(E2_exist_flag)
        {
            printf("warning E2 exist flag=1\n");
        }
    }
    printf("decode_B083 over!!!!\n");
}