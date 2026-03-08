#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-DL-TB-Report-S-H.h"
#include "NR5G-MAC-DL-TB-Report-Record.h"
#include "NR5G-MAC-DL-TB-Report-DL-MCE.h"
#include "host.h"

void convert_S_H_B886(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 12;
}

void convert_Record_B886(uint8_t *hex_data, int *index)
{
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=4;
}

void convert_dl_mce_B886(uint8_t *hex_data, int *index)
{
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=4;
}

void decode_NR5G_MAC_DL_TB_Report_v3(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_DL_TB_Report_S_H_t *t_S_H = 0;
    NR5G_MAC_DL_TB_Report_Record_t *t_Record = 0;
    NR5G_MAC_DL_TB_Report_DL_MCE_t *t_dl_mce = 0;
    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_Record;
    asn_dec_rval_t rval_dl_mce;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B886(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_DL_TB_Report_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_DL_TB_Report_S_H, t_S_H);
    
    int num_record = (hex_data[start_S_H+15]);
    if(num_record > 1)
    {
        printf("num_record > 1: If you read this line, please contact me in github\n");
    }

    /*Record*/
    for (int i = 0; i < num_record; i++)
    {
        int start_Record = *index;
        convert_Record_B886(hex_data, index);
        int Record_length = *index - start_Record;

        rval_Record = uper_decode(0, &asn_DEF_NR5G_MAC_DL_TB_Report_Record, (void **)&t_Record, hex_data + start_Record, Record_length, 0, 0);
        if (rval_Record.code != RC_OK)
        {
            printf("rval_Record decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DL_TB_Report_Record, t_Record);
        
        /*dl-mce*/
        int num_ca = hex_data[start_Record+4];
        if(num_ca > 1)
        {
            printf("num_ca > 1: If you read this line, please contact me in github\n");
        }
        for(int j=0;j<num_ca;j++)
        {
            int start_ca = *index;
            convert_dl_mce_B886(hex_data, index);
            int ca_length = *index - start_ca;

            rval_dl_mce = uper_decode(0, &asn_DEF_NR5G_MAC_DL_TB_Report_DL_MCE, (void **)&t_dl_mce, hex_data + start_ca, ca_length, 0, 0);
            if (rval_dl_mce.code != RC_OK)
            {
                printf("rval_dl_mce decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_DL_TB_Report_DL_MCE, t_dl_mce);
        }
    }
    printf("decode over\n");
}