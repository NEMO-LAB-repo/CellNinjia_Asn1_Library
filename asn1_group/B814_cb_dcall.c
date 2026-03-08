#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-NAS-Plain-Message-Container-S-H.h"
#include "host.h"

// specific header
void convert_S_H_B814(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=3;
}

void decode_NR5G_NAS_Plain_Message_Container_v1(uint8_t *hex_data, size_t length, int *index, int msg_len)
{
    NR5G_NAS_Plain_Message_Container_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B814(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_NAS_Plain_Message_Container_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_NAS_Plain_Message_Container_S_H, t_S_H); 

    printf("Raw Bytes: \n");
    int start_raw_byte = *index;
    printf("*index = %d \n", start_raw_byte);

    // check format 8Byte -- pkt type 2Byte -- header 14Byte(first 2 are not header last 12 Byte are header)
    // so first 12 Byte included in *index
    while(*index != (msg_len))
    {
        printf("%02X ", hex_data[*index]);
        *index+=1;
    }
    printf("\n");

    printf("decode_B814 over!!!!\n");
    printf("index=%d\n",*index);
}