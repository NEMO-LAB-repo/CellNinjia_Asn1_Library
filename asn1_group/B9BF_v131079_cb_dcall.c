#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-ML1-Search-HO-Acq-Confirm-S-H-v131079.h"
#include "NR5G-ML1-Search-HO-Acq-Confirm-HO-ACQ-Pas-Result-v131079.h"
#include "host.h"

void convert_S_H_B9BF_v131079(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 1;
    convert_endianess(hex_data, index, 3);
}

void convert_HO_ACQ_Pas_Result_B9BF_v131079(uint8_t *hex_data, int *index)
{
    *index += 8;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index += 2;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void decode_NR5G_ML1_Search_HO_Acq_Confirm_v131079(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_ML1_Search_HO_Acq_Confirm_S_H_v131079_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_ML1_Search_HO_Acq_Confirm_HO_ACQ_Pas_Result_v131079_t *t_HO_ACQ_Pas_Result = 0;
    asn_dec_rval_t rval_HO_ACQ_Pas_Result;

    // S-H
    int start_S_H = *index;
    convert_S_H_B9BF_v131079(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_ML1_Search_HO_Acq_Confirm_S_H_v131079, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_ML1_Search_HO_Acq_Confirm_S_H_v131079, t_S_H);

    // HO-ACQ-Pas-Result
    int start_HO_ACQ_Pas_Result = *index;
    convert_HO_ACQ_Pas_Result_B9BF_v131079(hex_data, index);
    int HO_ACQ_Pas_Result_length = *index - start_HO_ACQ_Pas_Result;
    
    rval_HO_ACQ_Pas_Result = uper_decode(0, &asn_DEF_NR5G_ML1_Search_HO_Acq_Confirm_HO_ACQ_Pas_Result_v131079, (void **)&t_HO_ACQ_Pas_Result, hex_data + start_HO_ACQ_Pas_Result, HO_ACQ_Pas_Result_length, 0, 0);
    if (rval_HO_ACQ_Pas_Result.code != RC_OK)
    {
        printf("rval_HO_ACQ_Pas_Result decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_ML1_Search_HO_Acq_Confirm_HO_ACQ_Pas_Result_v131079, t_HO_ACQ_Pas_Result);

    // Free allocated memory
    ASN_STRUCT_FREE(asn_DEF_NR5G_ML1_Search_HO_Acq_Confirm_S_H_v131079, t_S_H);
    ASN_STRUCT_FREE(asn_DEF_NR5G_ML1_Search_HO_Acq_Confirm_HO_ACQ_Pas_Result_v131079, t_HO_ACQ_Pas_Result);

    printf("Decoding NR5G_ML1_Search_HO_Acq_Confirm_v131079 completed successfully.\n");
}