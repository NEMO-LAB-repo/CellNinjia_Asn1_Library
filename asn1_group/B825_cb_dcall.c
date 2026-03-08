#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RRC-Configuration-Info-S-H.h"
#include "NR5G-RRC-Configuration-Info-Contiguous-CC-Info.h"
#include "NR5G-RRC-Configuration-Info-Serving-Cell-Info.h"
#include "NR5G-RRC-Configuration-Info-Radio-Bearer-Info.h"
#include "host.h"

void convert_S_H_B825(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 57;
}

void convert_Contiguouse_CC_B825(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index += 2;
}

void convert_Serving_Cell_B825(uint8_t *hex_data, int *index)
{
    *index += 1;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index += 5;
}

void convert_Radio_Bearer_B825(uint8_t *hex_data, int *index)
{
    *index += 18;
}

void decode_NR5G_RRC_Configuration_Info_v8(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RRC_Configuration_Info_S_H_t *t_S_H = 0;
    NR5G_RRC_Configuration_Info_Contiguous_CC_Info_t *t_cc=0; 
    NR5G_RRC_Configuration_Info_Serving_Cell_Info_t *t_serving=0; 
    NR5G_RRC_Configuration_Info_Radio_Bearer_Info_t *t_radio=0; 

    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_cc;
    asn_dec_rval_t rval_serving;
    asn_dec_rval_t rval_radio;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B825(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RRC_Configuration_Info_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RRC_Configuration_Info_S_H, t_S_H);

    int num_contiguous_cc_groups = hex_data[start_S_H+58];
    int num_active_cc = hex_data[start_S_H+59];
    int num_active_rb = hex_data[start_S_H+60];



    /*Contiguous CC Info*/
    for(int i=0;i<num_contiguous_cc_groups;i++)
    {
        int start_cc_group = *index;
        convert_Contiguouse_CC_B825(hex_data, index);
        int CC_group_length = *index - start_cc_group;
    
        rval_cc = uper_decode(0, &asn_DEF_NR5G_RRC_Configuration_Info_Contiguous_CC_Info, (void **)&t_cc, hex_data + start_cc_group, CC_group_length, 0, 0);
        if (rval_cc.code != RC_OK)
        {
            printf("rval_cc decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RRC_Configuration_Info_Contiguous_CC_Info, t_cc);
    }

    /*NR5G Serving Cell Info*/
    for(int i=0;i<num_active_cc;i++)
    {
        int start_cc = *index;
        convert_Serving_Cell_B825(hex_data, index);
        int CC_length = *index - start_cc;
    
        rval_serving = uper_decode(0, &asn_DEF_NR5G_RRC_Configuration_Info_Serving_Cell_Info, (void **)&t_serving, hex_data + start_cc, CC_length, 0, 0);
        if (rval_serving.code != RC_OK)
        {
            printf("rval_serving decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RRC_Configuration_Info_Serving_Cell_Info, t_serving);
    }

    /*Radio Bearer Info*/
    for(int i=0;i<num_active_rb;i++)
    {
        int start_rb = *index;
        convert_Radio_Bearer_B825(hex_data, index);
        int rb_length = *index - start_rb;
    
        rval_radio = uper_decode(0, &asn_DEF_NR5G_RRC_Configuration_Info_Radio_Bearer_Info, (void **)&t_radio, hex_data + start_rb, rb_length, 0, 0);
        if (rval_radio.code != RC_OK)
        {
            printf("rval_radio decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RRC_Configuration_Info_Radio_Bearer_Info, t_radio);
    }
    printf("decode over!!!!\n");
}