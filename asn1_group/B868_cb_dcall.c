#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RLC-UL-Stats-S-H.h"
#include "NR5G-RLC-UL-Stats-LC.h"
#include "host.h"

void convert_S_H_B868(uint8_t *hex_data, int *index)
{
    *index += 20;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_LC_B868(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 3);
    *index += 27;

    convert_endianess(hex_data, index, 2);
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 2;

    convert_endianess(hex_data, index, 4);
    *index += 4;
    convert_endianess(hex_data, index, 4);
    *index += 4;
    convert_endianess(hex_data, index, 4);
    *index += 4;
    convert_endianess(hex_data, index, 2);
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 2;

    convert_endianess(hex_data, index, 4);
    *index += 4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index += 8;
}

void decode_NR5G_RLC_UL_Stats_v4(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RLC_UL_Stats_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_RLC_UL_Stats_LC_t *t_LC = 0;
    asn_dec_rval_t rval_LC;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B868(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RLC_UL_Stats_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RLC_UL_Stats_S_H, t_S_H);

    int num_stats_lc = hex_data[start_S_H + 5];

    /*LC*/
    for (int i = 0; i < num_stats_lc; i++)
    {
        int start_LC = *index;
        convert_LC_B868(hex_data, index);
        int LC_length = *index - start_LC;

        rval_LC = uper_decode(0, &asn_DEF_NR5G_RLC_UL_Stats_LC, (void **)&t_LC, hex_data + start_LC, LC_length, 0, 0);
        if (rval_LC.code != RC_OK)
        {
            printf("rval_LC decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RLC_UL_Stats_LC, t_LC);
    }
    printf("decode over!!!!\n");
}