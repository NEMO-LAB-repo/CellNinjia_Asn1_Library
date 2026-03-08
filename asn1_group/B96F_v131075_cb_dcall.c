#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-ML1-Searcher-Conn-Eval-v131075-S-H.h"
#include "NR5G-ML1-Searcher-Conn-Eval-v131075-Cell-Info.h"
#include "host.h"

void convert_S_H_B96F_v131075(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 1; // Skip the next 12 bytes
    convert_endianess(hex_data, index, 3);
    *index += 4; // Skip the next 12 bytes
}

void convert_Cell_Info_B96F_v131075(uint8_t *hex_data, int *index)
{
    *index += 4; // Skip the first 2 bytes
    convert_endianess(hex_data, index, 2); // Convert the next 2 bytes
    convert_endianess(hex_data, index, 2); // Convert the next 2 bytes
}

void decode_NR5G_ML1_Searcher_Conn_Eval_v131075(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_ML1_Searcher_Conn_Eval_v131075_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_ML1_Searcher_Conn_Eval_v131075_Cell_Info_t *t_Cell_Info = 0;
    asn_dec_rval_t rval_Cell_Info;

    // Decode S_H
    int start_S_H = *index;
    convert_S_H_B96F_v131075(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_ML1_Searcher_Conn_Eval_v131075_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_ML1_Searcher_Conn_Eval_v131075_S_H, t_S_H);

    // Decode Cell Info
    int num_cells = (hex_data[start_S_H + 8]);
    for (int i = 0; i < num_cells; i++)
    {
        printf("[%d]\n", i);
        int start_Cell_Info = *index;
        convert_Cell_Info_B96F_v131075(hex_data, index);
        int Cell_Info_length = *index - start_Cell_Info;

        rval_Cell_Info = uper_decode(0, &asn_DEF_NR5G_ML1_Searcher_Conn_Eval_v131075_Cell_Info, (void **)&t_Cell_Info, hex_data + start_Cell_Info, Cell_Info_length, 0, 0);
        if (rval_Cell_Info.code != RC_OK)
        {
            printf("rval_Cell_Info decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_ML1_Searcher_Conn_Eval_v131075_Cell_Info, t_Cell_Info);
    }
    printf("Decode B96F_v131075 complete.\n");
}