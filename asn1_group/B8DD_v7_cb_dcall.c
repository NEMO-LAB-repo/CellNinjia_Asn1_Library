#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-LL1-FW-Serving-FTL-v7-S-H.h"
#include "NR5G-LL1-FW-Serving-FTL-v7-SNR.h"
#include "NR5G-LL1-FW-Serving-FTL-v7-Content.h"
#include "host.h"

void convert_S_H_B8DD_v7(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index += 20;
}

void convert_SNR_B8DD_v7(uint8_t *hex_data, int *index)
{
    *index+=64;
}

void convert_Content_B8DD_v7(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4); 
    convert_endianess(hex_data, index, 4); 
    convert_endianess(hex_data, index, 4); 
    convert_endianess(hex_data, index, 4);
}

void decode_NR5G_LL1_FW_Serving_FTL_v7(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_LL1_FW_Serving_FTL_v7_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_LL1_FW_Serving_FTL_v7_SNR_t *t_SNR = 0;
    asn_dec_rval_t rval_SNR;
    NR5G_LL1_FW_Serving_FTL_v7_Content_t *t_Content = 0;
    asn_dec_rval_t rval_Content;

    // Decode S_H
    int start_S_H = *index;
    convert_S_H_B8DD_v7(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_LL1_FW_Serving_FTL_v7_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_LL1_FW_Serving_FTL_v7_S_H, t_S_H);

    // Decode SNR
    int start_SNR = *index;
    convert_SNR_B8DD_v7(hex_data, index);
    int SNR_length = *index - start_SNR;

    rval_SNR = uper_decode(0, &asn_DEF_NR5G_LL1_FW_Serving_FTL_v7_SNR, (void **)&t_SNR, hex_data + start_SNR, SNR_length, 0, 0);
    if (rval_SNR.code != RC_OK)
    {
        printf("rval_SNR decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_LL1_FW_Serving_FTL_v7_SNR, t_SNR);

    // Decode Content
    int start_Content = *index;
    convert_Content_B8DD_v7(hex_data, index);
    int Content_length = *index - start_Content;

    rval_Content = uper_decode(0, &asn_DEF_NR5G_LL1_FW_Serving_FTL_v7_Content, (void **)&t_Content, hex_data + start_Content, Content_length, 0, 0);
    if (rval_Content.code != RC_OK)
    {
        printf("rval_Content decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_LL1_FW_Serving_FTL_v7_Content, t_Content);

    printf("Decode B8DD_v7 complete.\n");
}