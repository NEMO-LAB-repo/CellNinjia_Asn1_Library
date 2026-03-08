#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-DCI-Info-S-H.h"
#include "NR5G-MAC-DCI-Info-R-H.h"
#include "NR5G-MAC-DCI-Info-DCI-H.h"
#include "NR5G-MAC-DCI-Info-DCI-UL.h"
#include "NR5G-MAC-DCI-Info-DCI-DL.h"
#include "host.h"

void convert_S_H_B885(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 12;
}

void convert_R_H_B885(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 4;
}

void convert_DCI_H_B885(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index += 2;
}

void convert_DCI_UL_B885(uint8_t *hex_data, int *index)
{
    *index += 12;
    convert_endianess(hex_data, index, 3);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 8;
}

void convert_DCI_DL_B885(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index += 6;
}

void decode_NR5G_MAC_DCI_Info_v131077(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_DCI_Info_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_DCI_Info_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_DCI_Info_DCI_H_t *t_DCI_H = 0;
    asn_dec_rval_t rval_DCI_H;
    NR5G_MAC_DCI_Info_DCI_UL_t *t_DCI_UL = 0;
    asn_dec_rval_t rval_DCI_UL;
    NR5G_MAC_DCI_Info_DCI_DL_t *t_DCI_DL = 0;
    asn_dec_rval_t rval_DCI_DL;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B885(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_S_H, t_S_H);


    /*Record*/
    int num_of_record = (hex_data[start_S_H + 15]);
    for(int i=0;i<num_of_record;i++)
    {
        printf("[%d]\n", i);
        int start_record = *index;
        convert_R_H_B885(hex_data, index);
        int R_H_length = *index - start_record;

        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_R_H, (void **)&t_R_H, hex_data + start_record, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK)
        {
            printf("rval_R_H decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_R_H, t_R_H);

        int num_dci = hex_data[start_record + 4];

        /*DCI*/
        for(int j=0;j<num_dci;j++)
        {   
            printf("  [%d]\n", j);
            int start_DCI_H = *index;
            convert_DCI_H_B885(hex_data, index);
            int DCI_H_length = *index - start_DCI_H;

            rval_DCI_H = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_DCI_H, (void **)&t_DCI_H, hex_data + start_DCI_H, DCI_H_length, 0, 0);
            if (rval_DCI_H.code != RC_OK)
            {
                printf("rval_DCI_H decode error\n");
                return;
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_DCI_H, t_DCI_H);

            int dci_format = ((hex_data[start_DCI_H] & 0x01) << 1) | ((hex_data[start_DCI_H + 1] & 0x80) >> 7);
            if(dci_format < 2)
            {
                /*DCI UL*/
                int start_DCI_UL = *index;
                convert_DCI_UL_B885(hex_data, index);
                int DCI_UL_length = *index - start_DCI_UL;

                rval_DCI_UL = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_DCI_UL, (void **)&t_DCI_UL, hex_data + start_DCI_UL, DCI_UL_length, 0, 0);
                if (rval_DCI_UL.code != RC_OK)
                {
                    printf("rval_DCI_UL decode error\n");
                    return;
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_DCI_UL, t_DCI_UL);
            }
            else
            {
                /*DCI DL*/
                int start_DCI_DL = *index;
                convert_DCI_DL_B885(hex_data, index);
                int DCI_DL_length = *index - start_DCI_DL;

                rval_DCI_DL = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_DCI_DL, (void **)&t_DCI_DL, hex_data + start_DCI_DL, DCI_DL_length, 0, 0);
                if (rval_DCI_DL.code != RC_OK)
                {
                    printf("rval_DCI_DL decode error\n");
                    return;
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_DCI_DL, t_DCI_DL);
            }

        }
    }
    printf("decode over!!!!\n");
    return;
}