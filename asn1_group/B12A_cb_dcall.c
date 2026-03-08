#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-LL1-PCFICH-Decoding-Results-S-H.h"
#include "LTE-LL1-PCFICH-Decoding-Results-Record.h"
#include "host.h"

void convert_S_H_B12A(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 3);
    convert_endianess(hex_data, index, 2);
    *index+=10;
}

void convert_Record_B12A(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index += 2;
    convert_endianess(hex_data, index, 4);
}

void decode_B12A(uint8_t *hex_data, size_t length, int *index)
{
    LTE_LL1_PCFICH_Decoding_Results_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_LL1_PCFICH_Decoding_Results_Record_t *t_Record= 0;
    asn_dec_rval_t rval_Record;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B12A(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_LL1_PCFICH_Decoding_Results_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_LL1_PCFICH_Decoding_Results_S_H, t_S_H); 

    int num_Record = ((hex_data[start_S_H+2] & 0x3E) >> 1);
    printf("num_Record=%d\n",num_Record);

    for(int i=0;i<num_Record;i++)
    {
        printf("[%d]\n",i);
        int start_record = *index;
        convert_Record_B12A(hex_data, index);
        int Record_length = *index-start_record;
        rval_Record = uper_decode(0, &asn_DEF_LTE_LL1_PCFICH_Decoding_Results_Record, (void **)&t_Record, hex_data+start_record, Record_length, 0, 0);
        if(rval_Record.code != RC_OK) {
            printf("rval_Record decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_LL1_PCFICH_Decoding_Results_Record, t_Record);   
    }
    printf("decode_B0CD over!!!!\n");
    printf("index=%d\n",*index);
}