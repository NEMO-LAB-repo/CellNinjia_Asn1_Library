#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-PDCP-DL-Data-PDU-S-H.h"
#include "NR5G-PDCP-DL-Data-PDU-PDCP-State.h"
#include "NR5G-PDCP-DL-Data-PDU-Meta-Log-Buffer.h"
#include "host.h"

void convert_S_H_B840(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

void convert_PDCP_State_B840(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_Meta_Log_Buffer_B840(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index += 7;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void decode_NR5G_PDCP_DL_Data_Pdu_v6(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_PDCP_DL_Data_PDU_S_H_t *t_S_H = 0;
    NR5G_PDCP_DL_Data_PDU_PDCP_State_t *t_PDCP = 0;
    NR5G_PDCP_DL_Data_PDU_Meta_Log_Buffer_t *t_Meta = 0;

    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_PDCP;
    asn_dec_rval_t rval_Meta;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B840(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_PDCP_DL_Data_PDU_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_PDCP_DL_Data_PDU_S_H, t_S_H);

    int number_of_meta = (hex_data[start_S_H + 4] << 8) | (hex_data[start_S_H + 5]);
    int number_of_rb = (hex_data[start_S_H + 6] << 8) | (hex_data[start_S_H+7]);

    /*PDCP State*/
    for (int i = 0; i < number_of_rb; i++)
    {
        int start_PDCP = *index;
        convert_PDCP_State_B840(hex_data, index);
        int PDCP_length = *index - start_PDCP;

        rval_PDCP = uper_decode(0, &asn_DEF_NR5G_PDCP_DL_Data_PDU_PDCP_State, (void **)&t_PDCP, hex_data + start_PDCP, PDCP_length, 0, 0);
        if (rval_PDCP.code != RC_OK)
        {
            printf("rval_PDCP decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_PDCP_DL_Data_PDU_PDCP_State, t_PDCP);
    }

    /*Meta Log Buffer*/
    for(int i=0;i<number_of_meta;i++)
    {
        int start_Meta = *index;
        convert_Meta_Log_Buffer_B840(hex_data, index);
        int Meta_length = *index - start_Meta;
    
        rval_Meta = uper_decode(0, &asn_DEF_NR5G_PDCP_DL_Data_PDU_Meta_Log_Buffer, (void **)&t_Meta, hex_data + start_Meta, Meta_length, 0, 0);
        if (rval_Meta.code != RC_OK)
        {
            printf("rval_Meta decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_PDCP_DL_Data_PDU_Meta_Log_Buffer, t_Meta);
    }

    printf("decode over!!!!\n");
}