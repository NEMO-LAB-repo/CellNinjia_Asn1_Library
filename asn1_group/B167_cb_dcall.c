#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Random-Access-Request-MSG1-Report-S-H.h"
#include "host.h"

void convert_S_H_B167(uint8_t *hex_data, int *index)
{
    //version and skip0
    *index+=4;
    //5 6 7 8
    convert_endianess(hex_data, index, 4);
    //9
    *index+=1;
    //10 11
    convert_endianess(hex_data, index, 2);
    //12 13 14
    *index +=3;
    //15 16
    convert_endianess(hex_data, index, 2);
    //17 18
    convert_endianess(hex_data, index, 2);
    //19 20
    convert_endianess(hex_data, index, 2);
    //21 22 23 24 25 26 27 28
    *index +=8;
    //29 30
    convert_endianess(hex_data, index, 2);
    //31 32
    *index+=2;
}

void decode_B167(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_Random_Access_Request_MSG1_Report_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B167(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Random_Access_Request_MSG1_Report_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Random_Access_Request_MSG1_Report_S_H, t_S_H); 
    printf("decode_B167 over!!!!\n");
    printf("index=%d\n",*index);
}