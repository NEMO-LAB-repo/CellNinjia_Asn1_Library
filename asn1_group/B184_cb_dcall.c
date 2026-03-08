#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-CA-Metrics-Log-Packet-S-H.h"
#include "LTE-ML1-CA-Metrics-Log-Packet-content.h"
#include "LTE-ML1-CA-Metrics-Log-Packet-scells.h"
#include "host.h"

void convert_S_H_B184(uint8_t *hex_data, int *index)
{
    //1-4
    *index+=4;
    //5-6
    convert_endianess(hex_data, index, 2);
    //7-8
    convert_endianess(hex_data, index, 2);
}


void convert_pcell_start_B184(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index+=2;
}

void convert_pcell_only_B184(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    *index+=4;
}

void convert_structure_end_B184(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=4;
}

void convert_total_metrics_B184(uint8_t *hex_data, int *index)
{
    convert_pcell_only_B184(hex_data,index);
    convert_pcell_only_B184(hex_data,index);
    convert_pcell_only_B184(hex_data,index);
    convert_pcell_only_B184(hex_data,index);
    convert_structure_end_B184(hex_data,index);
}

void convert_content_B184(uint8_t *hex_data, int *index)
{
    convert_pcell_start_B184(hex_data,index);
    convert_total_metrics_B184(hex_data,index);
    convert_total_metrics_B184(hex_data,index);
    convert_total_metrics_B184(hex_data,index);
}

void convert_scell_start_B184(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index+=6; 
}

void convert_scell_B184(uint8_t *hex_data, int *index)
{
    convert_scell_start_B184(hex_data,index);
    convert_pcell_only_B184(hex_data,index);
    convert_pcell_only_B184(hex_data,index);
    convert_pcell_only_B184(hex_data,index);
}

void decode_B184(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_CA_Metrics_Log_Packet_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_CA_Metrics_Log_Packet_content_t *t_content = 0;
    asn_dec_rval_t rval_content;
    LTE_ML1_CA_Metrics_Log_Packet_scells_t *t_scells = 0;
    asn_dec_rval_t rval_scells;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B184(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_CA_Metrics_Log_Packet_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_CA_Metrics_Log_Packet_S_H, t_S_H); 

    //get num of scells
    int num_of_scells = hex_data[start_S_H+2];
    printf("num_of_scells=%d\n",num_of_scells);

    /*content*/
    int start_content = *index;
    convert_content_B184(hex_data, index);
    int content_length = *index - start_content;

    rval_content = uper_decode(0, &asn_DEF_LTE_ML1_CA_Metrics_Log_Packet_content, (void **)&t_content, hex_data+start_content, content_length, 0, 0);
    if(rval_content.code != RC_OK) {
      printf("rval_content decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_CA_Metrics_Log_Packet_content, t_content); 

    /*scells*/
    for(int i=0;i<num_of_scells;i++)
    {
        printf("[%d] scells\n",i);
        int start_scells = *index;
        convert_scell_B184(hex_data, index);
        int scells_length = *index - start_scells;

        rval_scells = uper_decode(0, &asn_DEF_LTE_ML1_CA_Metrics_Log_Packet_scells, (void **)&t_scells, hex_data+start_scells, scells_length, 0, 0);
        if(rval_scells.code != RC_OK) {
        printf("rval_scells decode error\n");
        exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_CA_Metrics_Log_Packet_scells, t_scells); 
    }
    printf("decode_B184 over!!!!\n");
}

