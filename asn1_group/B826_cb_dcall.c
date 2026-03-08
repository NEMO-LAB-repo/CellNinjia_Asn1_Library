#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RRC-Supported-CA-Combos-S-H.h"
#include "NR5G-RRC-Supported-CA-Combos-Combo-H.h"
#include "NR5G-RRC-Supported-CA-Combos-BW-Class.h"
#include "host.h"

void convert_S_H_B826(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 1;
}

void convert_Combo_H_B826(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_Bw_Class_B826(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index += 6;
    convert_endianess(hex_data, index, 2);
}

void decode_NR5G_RRC_Supported_CA_Combos_v7(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RRC_Supported_CA_Combos_S_H_t *t_S_H = 0;
    NR5G_RRC_Supported_CA_Combos_Combo_H_t *t_C_H = 0;
    NR5G_RRC_Supported_CA_Combos_BW_Class_t *t_BW = 0;

    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_C_H;
    asn_dec_rval_t rval_BW;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B826(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RRC_Supported_CA_Combos_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error, may caused by diff version\n");
        // exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RRC_Supported_CA_Combos_S_H, t_S_H);

    int num_combos = (hex_data[start_S_H + 8] << 8) | (hex_data[start_S_H + 9]);

    /*CA_Combos*/
    for (int i = 0; i < num_combos; i++)
    {
        int start_Combo_H = *index;
        convert_Combo_H_B826(hex_data, index);
        int Combo_H_length = *index - start_Combo_H;

        rval_C_H = uper_decode(0, &asn_DEF_NR5G_RRC_Supported_CA_Combos_Combo_H, (void **)&t_C_H, hex_data + start_Combo_H, Combo_H_length, 0, 0);
        if (rval_C_H.code != RC_OK)
        {
            printf("rval_C_H decode error, may caused by diff version\n");
            // exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RRC_Supported_CA_Combos_Combo_H, t_C_H);

        /*BW CLASS*/
        int num_bands = (hex_data[start_Combo_H] & 0x0E) >> 1;

        for(int j=0;j<num_bands;j++)
        {
            int start_BW = *index;
            convert_Bw_Class_B826(hex_data, index);
            int BW_length = *index - start_BW;
    
            rval_BW = uper_decode(0, &asn_DEF_NR5G_RRC_Supported_CA_Combos_BW_Class, (void **)&t_BW, hex_data + start_BW, BW_length, 0, 0);
            if (rval_BW.code != RC_OK)
            {
                printf("rval_BW decode error, may caused by diff version\n");
                // exit(65);
            }
            xer_fprint(stdout, &asn_DEF_NR5G_RRC_Supported_CA_Combos_BW_Class, t_BW);
        }
    }

    printf("decode over!!!!\n");
}