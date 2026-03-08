#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-PDCP-DL-Data-PDU-Specific-Header.h"
#include "LTE-PDCP-DL-Data-PDU-Pdcp-State.h"
#include "LTE-PDCP-DL-Data-PDU-Meta-Log-Buffer.h"
#include "host.h"

// specific header
void convert_S_H_B0A1(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 3);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

// PDCP State
void convert_pdcp_state_B0A1(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

//meta log buffer
void convert_meta_log_buffer_B0A1(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 5);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 1);
    convert_endianess(hex_data, index, 3);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

void decode_B0A1(uint8_t *hex_data, size_t length, int *index)
{
    LTE_PDCP_DL_Data_PDU_Specific_Header_t *t_S_H=0;
    asn_dec_rval_t rval_S_H;
    LTE_PDCP_DL_Data_PDU_Pdcp_State_t *t_pdcp_State=0;
    asn_dec_rval_t rval_Pdcp_State;
    LTE_PDCP_DL_Data_PDU_Meta_Log_Buffer_t * t_meta_log_buffer=0;
    asn_dec_rval_t rval_Meta_Log_Buffer;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B0A1(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_PDCP_DL_Data_PDU_Specific_Header, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_PDCP_DL_Data_PDU_Specific_Header, t_S_H);   

    int num_of_Meta = (hex_data[start_S_H+4]<<8)|(hex_data[start_S_H+5]);
    printf("num of meta=%d\n",num_of_Meta);
    int num_of_RB = (hex_data[start_S_H+6]<<8)|(hex_data[start_S_H+7]);
    printf("num_of_RB=%d\n",num_of_RB);
    
    printf("PDCP State\n");
    for(int i=0;i<num_of_RB;i++)
    {
        printf("[%d]\n",i);
        int start_Pdcp = *index;
        convert_pdcp_state_B0A1(hex_data, index);
        int Pdcp_length = *index-start_Pdcp;

        rval_Pdcp_State = uper_decode(0, &asn_DEF_LTE_PDCP_DL_Data_PDU_Pdcp_State, (void **)&t_pdcp_State, hex_data+start_Pdcp, Pdcp_length, 0, 0);
        if(rval_Pdcp_State.code != RC_OK) {
        printf("rval_Pdcp_State decode error\n");
        exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_PDCP_DL_Data_PDU_Pdcp_State, t_pdcp_State); 
    }

    printf("Meta Log Buffer\n");
    for(int i=0;i<num_of_Meta;i++)
    {
        printf("[%d]\n",i);
        int start_Meta = *index;
        convert_meta_log_buffer_B0A1(hex_data, index);
        int Meta_length = *index-start_Meta;

        rval_Meta_Log_Buffer = uper_decode(0, &asn_DEF_LTE_PDCP_DL_Data_PDU_Meta_Log_Buffer, (void **)&t_meta_log_buffer, hex_data+start_Meta, Meta_length, 0, 0);
        if(rval_Meta_Log_Buffer.code != RC_OK) {
        printf("rval_Meta_Log_Buffer decode error\n");
        exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_PDCP_DL_Data_PDU_Meta_Log_Buffer, t_meta_log_buffer); 
    }
    printf("decode_B0A1 over!!!!\n");
}