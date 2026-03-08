#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-NAS-MM5G-State-Content.h"
#include "host.h"

void convert_content_B80C(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=3;
    convert_endianess(hex_data, index, 3);
    *index+=1;
    convert_endianess(hex_data, index, 3);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 4);
    *index+=4;
}

void decode_NR5G_NAS_MM5G_State_v1(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_NAS_MM5G_State_Content_t *t_content = 0;
    asn_dec_rval_t rval_content;

    /*content*/
    int start_content = *index;
    convert_content_B80C(hex_data, index);
    int content_length = *index - start_content;

    rval_content = uper_decode(0, &asn_DEF_NR5G_NAS_MM5G_State_Content, (void **)&t_content, hex_data + start_content, content_length, 0, 0);
    if (rval_content.code != RC_OK)
    {
        printf("rval_content decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_NAS_MM5G_State_Content, t_content);

    printf("decode_B80C over!!!!\n");
    free(t_content);

}