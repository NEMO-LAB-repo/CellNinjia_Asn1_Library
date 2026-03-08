#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-RRC-Supported-CA-Combos-S-H.h"
#include "LTE-RRC-Supported-CA-Combos-CA-H.h"
#include "LTE-RRC-Supported-CA-Combos-Bw-Class.h"
#include "host.h"

void convert_S_H_B0CD(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
}

void convert_CA_Combos_H_B0CD(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
}

void convert_BW_Class_B0CD(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
}

void decode_B0CD(uint8_t *hex_data, size_t length, int *index)
{
    LTE_RRC_Supported_CA_Combos_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_RRC_Supported_CA_Combos_CA_H_t *t_CA_H= 0;
    asn_dec_rval_t rval_CA_H;
    LTE_RRC_Supported_CA_Combos_Bw_Class_t *t_BW_Class = 0;
    asn_dec_rval_t rval_bw_class;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B0CD(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_RRC_Supported_CA_Combos_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_RRC_Supported_CA_Combos_S_H, t_S_H); 

    int num_combos = hex_data[start_S_H+1];
    printf("num_combos=%d\n",num_combos);

    for(int i=0;i<num_combos;i++)
    {
        printf("[%d]\n",i);
        //CA Combos header just 1 Byte, not call upderdecode, directly decode it
        int start_CA_Combos = *index;
        convert_CA_Combos_H_B0CD(hex_data, index);
        int num_band = hex_data[start_CA_Combos];
        printf("num_band=%d\n",num_band);

        //BW class
        for(int j=0;j<num_band;j++)
        {
            printf("[%d]\n",j);
            int start_bw_class = *index;
            convert_BW_Class_B0CD(hex_data,index);
            int bw_class_length = *index-start_bw_class;
            rval_bw_class = uper_decode(0, &asn_DEF_LTE_RRC_Supported_CA_Combos_Bw_Class, (void **)&t_BW_Class, hex_data+start_bw_class, bw_class_length, 0, 0);
            if(rval_bw_class.code != RC_OK) {
            printf("rval_bw_class decode error\n");
            exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_RRC_Supported_CA_Combos_Bw_Class, t_BW_Class);
        }
    }
    printf("decode_B0CD over!!!!\n");
    printf("index=%d\n",*index);
}

