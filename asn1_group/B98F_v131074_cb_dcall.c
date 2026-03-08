#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-ML1-Antenna-Switch-Diversity-v131074-S-H.h"
#include "NR5G-ML1-Antenna-Switch-Diversity-v131074-CC-Data.h"
#include "host.h"

void convert_S_H_B98F_v131074(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index += 6; // Skip the next 12 bytes
    convert_endianess(hex_data, index, 2);
    *index += 14;
}

void convert_CC_Data_B98F_v131074(uint8_t *hex_data, int *index)
{
    *index += 150;
}

void decode_NR5G_ML1_Antenna_Switch_Diversity_v131074(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_ML1_Antenna_Switch_Diversity_v131074_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_ML1_Antenna_Switch_Diversity_v131074_CC_Data_t *t_CC_Data = 0;
    asn_dec_rval_t rval_CC_Data;

    // Decode S_H
    int start_S_H = *index;
    convert_S_H_B98F_v131074(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_ML1_Antenna_Switch_Diversity_v131074_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_ML1_Antenna_Switch_Diversity_v131074_S_H, t_S_H);


    // Decode CC Data
    int start_CC_Data = *index;
    convert_CC_Data_B98F_v131074(hex_data, index);
    int CC_Data_length = *index - start_CC_Data;

    rval_CC_Data = uper_decode(0, &asn_DEF_NR5G_ML1_Antenna_Switch_Diversity_v131074_CC_Data, (void **)&t_CC_Data, hex_data + start_CC_Data, CC_Data_length, 0, 0);
    if (rval_CC_Data.code != RC_OK)
    {
        printf("rval_CC_Data decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_ML1_Antenna_Switch_Diversity_v131074_CC_Data, t_CC_Data);

    printf("Decode B98F_v131074 complete.\n");
}