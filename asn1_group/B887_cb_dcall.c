#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-PDSCH-Status-S-H.h"
#include "NR5G-MAC-PDSCH-Status-R-H.h"
#include "NR5G-MAC-PDSCH-Status-Info.h"
#include "host.h"

void convert_S_H_B887(uint8_t *hex_data, int *index)
{
    *index+=16;
}

void convert_R_H_B887(uint8_t *hex_data, int *index)
{
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=4;
}

void convert_PDSCH_Status_Info_B887(uint8_t *hex_data, int *index)
{
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 3);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=4;
}

void decode_NR5G_MAC_PDSCH_Status_v5(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_PDSCH_Status_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_PDSCH_Status_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_PDSCH_Status_Info_t *t_PDSCH_Status_Info = 0;
    asn_dec_rval_t rval_PDSCH_Status_Info;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B887(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_PDSCH_Status_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_PDSCH_Status_S_H, t_S_H);

    int num_records = hex_data[start_S_H + 15];

    for(int i=0;i<num_records;i++)
    {
        /*R_H*/
        int start_R_H = *index;
        convert_R_H_B887(hex_data, index);
        int R_H_length = *index - start_R_H;
        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_PDSCH_Status_R_H, (void **)&t_R_H, hex_data + start_R_H, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK)
        {
            printf("rval_R_H decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_PDSCH_Status_R_H, t_R_H);

        int num_PDSCH_Status_Info = hex_data[start_R_H + 4];

        for(int j=0;j<num_PDSCH_Status_Info;j++)
        {
            /*PDSCH_Status_Info*/
            int start_PDSCH_Status_Info = *index;
            convert_PDSCH_Status_Info_B887(hex_data, index);
            int PDSCH_Status_Info_length = *index - start_PDSCH_Status_Info;
            rval_PDSCH_Status_Info = uper_decode(0, &asn_DEF_NR5G_MAC_PDSCH_Status_Info, (void **)&t_PDSCH_Status_Info, hex_data + start_PDSCH_Status_Info, PDSCH_Status_Info_length, 0, 0);
            if (rval_PDSCH_Status_Info.code != RC_OK)
            {
                printf("rval_PDSCH_Status_Info decode error\n");
                return;
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_PDSCH_Status_Info, t_PDSCH_Status_Info);
        }
    }
    printf("decode over!!!!\n");
}