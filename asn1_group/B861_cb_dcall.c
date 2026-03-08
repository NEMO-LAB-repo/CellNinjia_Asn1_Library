#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-PDCP-UL-Control-Pdu-S-H.h"
#include "NR5G-PDCP-UL-Control-Pdu-Content.h"
#include "host.h"

void convert_S_H_B861(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=4;
}

void convert_PDU_CONTENT_B861(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=8;
}

void decode_NR5G_PDCP_UL_Control_Pdu_v196609(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_PDCP_UL_Control_Pdu_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_PDCP_UL_Control_Pdu_Content_t *t_PDU_CONTENT = 0;
    asn_dec_rval_t rval_PDU_CONTENT;

    /*S-H*/
    int start_S_H = *index;
    convert_S_H_B861(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_PDCP_UL_Control_Pdu_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        // return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_PDCP_UL_Control_Pdu_S_H, t_S_H);

    int num_control_pdu = (hex_data[start_S_H+4]);

    /*PDU CONTENT*/
    for (int i = 0; i < num_control_pdu; i++)
    {   
        printf("[%d]\n",i);

        int start_PDU_CONTENT = *index;
        convert_PDU_CONTENT_B861(hex_data, index);
        int PDU_CONTENT_length = *index - start_PDU_CONTENT;

        rval_PDU_CONTENT = uper_decode(0, &asn_DEF_NR5G_PDCP_UL_Control_Pdu_Content, (void **)&t_PDU_CONTENT, hex_data + start_PDU_CONTENT, PDU_CONTENT_length, 0, 0);
        if (rval_PDU_CONTENT.code != RC_OK)
        {
            printf("rval_PDU_CONTENT decode error\n");
            // return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_PDCP_UL_Control_Pdu_Content, t_PDU_CONTENT);
    }
    printf("decode over!!!!\n");
}