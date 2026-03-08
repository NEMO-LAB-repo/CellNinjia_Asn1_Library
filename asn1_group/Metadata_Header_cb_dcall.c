#include <stdint.h>
#include <stdio.h>
#include "MetadataHeader.h"
#include "change_byte_sequence.h"
#include "Metadata_Header_cb_dcall.h"

void convert_M_H(uint8_t *hex_data, size_t length, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 8);
}

void decode_metadata_header(uint8_t *hex_data, size_t length, int *index)
{
    printf("index=%d\n",*index);
    MetadataHeader_t *t_M_H =0;
    asn_dec_rval_t rval_M_H; /* Decoder return value  */
    
    /*convert byte sequence*/
    int start_M_H = 0;
    convert_M_H(hex_data,length,index);
    printf("index after M_H=%d\n",*index);
    /*asn1c decode*/
    int M_H_Length = *index-start_M_H;
    printf("M_H_Length=%d\n",M_H_Length);
    // printf("Converted Hex Data: \n");
    rval_M_H = uper_decode(0, &asn_DEF_MetadataHeader, (void **)&t_M_H, hex_data+start_M_H, M_H_Length, 0, 0);
    if(rval_M_H.code != RC_OK) {
        printf("rval_M_H decode error\n");
        exit(65); /* better, EX_DATAERR */
    }
    xer_fprint(stdout, &asn_DEF_MetadataHeader, t_M_H);
}