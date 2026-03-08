#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Serving-Cell-Information-S-H.h"
#include "host.h"

void convert_S_H_B197(uint8_t *hex_data, int *index)
{
    //1 2
    *index+=2;
    //3 4
    convert_endianess(hex_data, index, 2);
    //5 6 7 8
    convert_endianess(hex_data, index, 4);
    //9 10
    convert_endianess(hex_data, index, 2);
    //11 12 13 14 15 16
    *index+=6;
    //17 18
    convert_endianess(hex_data, index, 2);
    //19 20
    *index+=2;
    //21 22 23 24 25 26
    convert_endianess(hex_data, index, 6);
    //27 28 
    *index+=2;
    //29 30 31 32
    convert_endianess(hex_data, index, 4);
    //33 34 35 36
    convert_endianess(hex_data, index, 4);
}

void decode_B197(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_Serving_Cell_Information_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B197(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Serving_Cell_Information_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Serving_Cell_Information_S_H, t_S_H);    

    printf("decode_B197 over!!!!\n");
    printf("index=%d\n",*index);
}