#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-NAS-SM5G-Plain-OTA-Outgoing-Msg-S-H.h"
#include "host.h"

void convert_S_H_B801(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=7;
}

void decode_NR5G_NAS_SM5G_Plain_OTA_Outgoing_Msg_v1(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_NAS_SM5G_Plain_OTA_Outgoing_Msg_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B801(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_NAS_SM5G_Plain_OTA_Outgoing_Msg_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_NAS_SM5G_Plain_OTA_Outgoing_Msg_S_H, t_S_H); 

    printf("decode_B801 over!!!!\n");
}
