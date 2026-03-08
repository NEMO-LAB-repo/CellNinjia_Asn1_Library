#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RRC-Serving-Cell-Info-S-H.h"
#include "host.h"

void convert_S_H_B823(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 8);
    convert_endianess(hex_data, index, 2);
    *index += 4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
}

void decode_NR5G_RRC_Serving_Cell_Info_v4(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RRC_Serving_Cell_Info_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B823(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RRC_Serving_Cell_Info_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
        printf("rval_S_H decode error\n");
        exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RRC_Serving_Cell_Info_S_H, t_S_H); 
    printf("decode_B823 over!!!!\n");
}