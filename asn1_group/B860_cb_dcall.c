#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-PDCP-UL-Stats-S-H.h"
#include "NR5G-PDCP-UL-Stats-Record.h"
#include "host.h"

void convert_S_H_B860(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=16;

    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 2);
    *index+=38;
}

void convert_Record_B860(uint8_t *hex_data, int *index)
{
    *index+=4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    *index+=8;
    convert_endianess(hex_data, index, 2);
    *index+=6;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=12;
    convert_endianess(hex_data, index, 4);
    *index+=12;
    convert_endianess(hex_data, index, 2);
    *index+=6;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=36;
}

void decode_NR5G_PDCP_UL_Stats_v9(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_PDCP_UL_Stats_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_PDCP_UL_Stats_Record_t *t_Record = 0;
    asn_dec_rval_t rval_Record;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B860(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_PDCP_UL_Stats_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_PDCP_UL_Stats_S_H, t_S_H);

    int num_record = (hex_data[start_S_H+5]&0x1F);

    /*Record*/
    for (int i = 0; i < num_record; i++)
    {
        int start_Record = *index;
        convert_Record_B860(hex_data, index);
        int Record_length = *index - start_Record;

        rval_Record = uper_decode(0, &asn_DEF_NR5G_PDCP_UL_Stats_Record, (void **)&t_Record, hex_data + start_Record, Record_length, 0, 0);
        if (rval_Record.code != RC_OK)
        {
            printf("rval_Record decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_PDCP_UL_Stats_Record, t_Record);
    }
    printf("decode over!!!!\n");
    return;
}
