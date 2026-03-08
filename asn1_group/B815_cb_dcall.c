#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-NAS-MM5G-NSSAI-Info-S-H.h"
#include "NR5G-NAS-MM5G-NSSAI-Info-NSSAI.h"

#include "host.h"

// specific header
void convert_S_H_B815(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=6;
}

void convert_NSSAI_B815(uint8_t *hex_data, int *index)
{
    *index+=5;
}

void decode_NR5G_NAS_MM5G_NSSAI_Info_v1(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_NAS_MM5G_NSSAI_Info_S_H_t *t_S_H = 0;
    NR5G_NAS_MM5G_NSSAI_Info_NSSAI_t *t_NSSAI = 0;
    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_NSSAI;
    

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B815(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_NAS_MM5G_NSSAI_Info_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_NAS_MM5G_NSSAI_Info_S_H, t_S_H); 

    int num_nssai = hex_data[start_S_H+9];

    /* NSSAI */
    for(int i=0;i<num_nssai;i++)
    {
        int start_NSSAI = *index;
        convert_NSSAI_B815(hex_data,index);
        int NSSAI_length = *index - start_NSSAI;

        rval_NSSAI = uper_decode(0, &asn_DEF_NR5G_NAS_MM5G_NSSAI_Info_NSSAI, (void **)&t_NSSAI, hex_data+start_NSSAI, NSSAI_length, 0, 0);
        if(rval_NSSAI.code != RC_OK) {
          printf("rval_NSSAI decode error\n");
          exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_NAS_MM5G_NSSAI_Info_NSSAI, t_NSSAI); 
    }

    printf("decode_B815 over!!!!\n");
    printf("index=%d\n",*index);
}