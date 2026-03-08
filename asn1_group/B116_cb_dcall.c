#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-LL1-Serving-Cell-Measurement-Results-S-H.h"
#include "host.h"

void convert_S_H_B116(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
    // Digital Rotator Data + Timing Offset Rx + skip2
    *index += 42;
}

void decode_B116(uint8_t *hex_data, size_t length, int *index)
{
    LTE_LL1_Serving_Cell_Measurement_Results_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B116(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_LL1_Serving_Cell_Measurement_Results_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_LL1_Serving_Cell_Measurement_Results_S_H, t_S_H); 
    printf("decode_B116 over!!!!\n");
    printf("index=%d\n",*index);
}