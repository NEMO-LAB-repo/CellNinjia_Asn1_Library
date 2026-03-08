#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-L2-UL-Config-S-H.h"
#include "NR5G-L2-UL-Config-RB.h"
#include "host.h"

void convert_S_H_B871(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=32;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);

    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);

    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);

    *index+=12;
}

void convert_RB_B871(uint8_t *hex_data, int *index)
{
    *index+=8;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=4;
}

void decode_NR5G_L2_UL_Config_v5(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_L2_UL_Config_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_L2_UL_Config_RB_t *t_RB = 0;
    asn_dec_rval_t rval_RB;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B871(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_Config_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Config_S_H, t_S_H);

    int num_rb = ((hex_data[start_S_H + 5] &0x3F));

    /*RB*/
    for (int i = 0; i < num_rb; i++)
    {
        printf("RB[%d]\n", i);
        int start_RB = *index;
        convert_RB_B871(hex_data, index);
        int RB_length = *index - start_RB;

        rval_RB = uper_decode(0, &asn_DEF_NR5G_L2_UL_Config_RB, (void **)&t_RB, hex_data + start_RB, RB_length, 0, 0);
        if (rval_RB.code != RC_OK)
        {
            printf("rval_RB decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Config_RB, t_RB);
    }
    printf("decode over!!!!\n");
}