#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "host.h"
#include "NR5G-L2-DL-Config-S-H.h"
#include "NR5G-L2-DL-Config-RB-Config.h"

void convert_S_H_B84B(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=4;
    //mcg
    *index+=7;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);

    //scg
    *index+=7;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);

    //Tail
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
}

void convert_RB_B84B(uint8_t *hex_data, int *index)
{
    *index+=24;
    convert_endianess(hex_data, index, 2);
    *index+=11;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=1;
}

void decode_NR5G_L2_DL_Config_v5(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_L2_DL_Config_S_H_t *t_S_H = 0;
    NR5G_L2_DL_Config_RB_Config_t *t_RB = 0;

    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_RB;


    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B84B(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_L2_DL_Config_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      // exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_L2_DL_Config_S_H, t_S_H); 

    int num_nrb = (hex_data[start_S_H+6] & 0x0F);

    /* RB Config */
    for(int i=0;i<num_nrb;i++)
    {
        printf("RB Config [%d]\n", i);
        int start_RB = *index;
        convert_RB_B84B(hex_data,index);
        int RB_length = *index - start_RB;

        rval_RB = uper_decode(0, &asn_DEF_NR5G_L2_DL_Config_RB_Config, (void **)&t_RB, hex_data+start_RB, RB_length, 0, 0);
        if(rval_RB.code != RC_OK) {
          printf("rval_RB decode error\n");
          // exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_DL_Config_RB_Config, t_RB); 
    }
    printf("decode_B84B over!!!!\n");
}