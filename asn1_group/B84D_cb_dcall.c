#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RLC-DL-Stats-S-H.h"
#include "NR5G-RLC-DL-Stats-RB.h"
#include "host.h"

void convert_S_H_B84D(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=2;
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
    *index+=2;
}

void convert_RB_B84D(uint8_t *hex_data, int *index)
{
    *index+=2;
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
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
}

void decode_NR5G_RLC_DL_Stats_v196608(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RLC_DL_Stats_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_RLC_DL_Stats_RB_t *t_RB = 0;
    asn_dec_rval_t rval_RB;

    /*S-H*/
    int start_S_H = *index;
    convert_S_H_B84D(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RLC_DL_Stats_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RLC_DL_Stats_S_H, t_S_H);

    int num_records = (hex_data[start_S_H+4]);

    /*R-H*/
    for (int i = 0; i < num_records; i++)
    {   
        printf("[%d]\n",i);

        int start_RB = *index;
        convert_RB_B84D(hex_data, index);
        int RB_length = *index - start_RB;

        rval_RB = uper_decode(0, &asn_DEF_NR5G_RLC_DL_Stats_RB, (void **)&t_RB, hex_data + start_RB, RB_length, 0, 0);
        if (rval_RB.code != RC_OK)
        {
            printf("rval_RB decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RLC_DL_Stats_RB, t_RB);
    }
    printf("decode_B84D over!!!!\n");
}