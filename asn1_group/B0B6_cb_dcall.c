#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-PDCP-UL-Delay-Statistics-S-HEADER.h"
#include "LTE-PDCP-UL-Delay-Statistics-RBs.h"
#include "host.h"


// specific header
void convert_S_H_B0B6(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 3);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
}

//RBs
void convert_RBS_B0B6(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 1);
    //PDCP Delay Pkt Count
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    //PDCP Delay Pkt Count2
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    //PDCP Delay Pkt Count3
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    //other
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    //skip 10 Bytes
    *index+=10;
}

void decode_B0B6(uint8_t *hex_data, size_t length, int *index)
{
    LTE_PDCP_UL_Delay_Statistics_S_HEADER_t *t_S_H=0;
    asn_dec_rval_t rval_S_H;
    LTE_PDCP_UL_Delay_Statistics_RBs_t *t_RBs=0;
    asn_dec_rval_t rval_RBs;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B0B6(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_PDCP_UL_Delay_Statistics_S_HEADER, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_PDCP_UL_Delay_Statistics_S_HEADER, t_S_H); 

    int num_of_RBs =  (hex_data[start_S_H+4]);
    printf("num_of_RBs=%d\n",num_of_RBs);
    int num_of_RST =  (hex_data[start_S_H+5]);
    printf("num_of_RST=%d\n",num_of_RST);

    if(num_of_RST!=0)
    {
        printf("RST Structure unknown!\n");
        printf("record this situation!\n");
    }
    printf("RBs\n");
    for(int i=0;i<num_of_RBs;i++)
    {
        printf("[%d]\n",i);
        int start_rbs = *index;
        convert_RBS_B0B6(hex_data, index);
        int RBS_length = *index-start_rbs;

        rval_RBs = uper_decode(0, &asn_DEF_LTE_PDCP_UL_Delay_Statistics_RBs, (void **)&t_RBs, hex_data+start_rbs, RBS_length, 0, 0);
        if(rval_RBs.code != RC_OK) {
        printf("rval_RBs decode error\n");
        exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_PDCP_UL_Delay_Statistics_RBs, t_RBs); 
    }
    printf("decode_B0B6 over!!!!\n");
}