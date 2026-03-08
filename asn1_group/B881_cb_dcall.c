#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-UL-TB-Stats-S-H.h"
#include "NR5G-MAC-UL-TB-Stats-Record.h"
#include "host.h"

void convert_S_H_B881(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=8;
}

void convert_Record_B881(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

void decode_NR5G_MAC_UL_TB_Stats_v196609(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_UL_TB_Stats_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_UL_TB_Stats_Record_t *t_Record = 0;
    asn_dec_rval_t rval_Record;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B881(hex_data, index);
    int S_H_length = *index - start_S_H;
    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_UL_TB_Stats_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_TB_Stats_S_H, t_S_H);

    int num_records = (hex_data[start_S_H+7]);

    /*Record*/
    for(int i = 0; i < num_records; i++)
    {   
        printf("[%d]\n",i);
        int start_Record = *index;
        convert_Record_B881(hex_data, index);
        int Record_length = *index - start_Record;
        rval_Record = uper_decode(0, &asn_DEF_NR5G_MAC_UL_TB_Stats_Record, (void **)&t_Record, hex_data + start_Record, Record_length, 0, 0);
        if (rval_Record.code != RC_OK)
        {
            printf("rval_Record decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_TB_Stats_Record, t_Record);
    }

    printf("decode over!!!\n");
}