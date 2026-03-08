#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-DCI-Info-v196617-S-H.h"
#include "NR5G-MAC-DCI-Info-v196617-UL-DCI-Slot-Info.h"
#include "NR5G-MAC-DCI-Info-v196617-UL-DCI.h"
#include "NR5G-MAC-DCI-Info-v196617-DL-DCI-C-TC-CS-Slot-Info.h"
#include "NR5G-MAC-DCI-Info-v196617-DL-DCI-C-TC-CS.h"
#include "NR5G-MAC-DCI-Info-v196617-DL-DCI-P-RA-SI-Slot-Info.h"
#include "NR5G-MAC-DCI-Info-v196617-DL-DCI-P-RA-SI.h"

void convert_S_H_B885_v196617(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 12;
}

void convert_UL_DCI_Slot_Info_B885_v196617(uint8_t *hex_data, int *index)
{
    *index += 2; // Skip first two bytes
    convert_endianess(hex_data, index, 2); // Convert slot number
}

void convert_UL_DCI_B885_v196617(uint8_t *hex_data, int *index)
{
    *index += 4; 
    convert_endianess(hex_data, index, 4); 
    convert_endianess(hex_data, index, 4); 
    convert_endianess(hex_data, index, 4); 
    convert_endianess(hex_data, index, 4); 
    *index += 1; 
    convert_endianess(hex_data, index, 3); 
    convert_endianess(hex_data, index, 3); 
    *index += 1;
    convert_endianess(hex_data, index, 2); 
    *index += 1;
    convert_endianess(hex_data, index, 3); 
    *index += 2; 
}

void convert_DL_DCI_C_TC_CS_Slot_Info_B885_v196617(uint8_t *hex_data, int *index)
{
    *index += 2; // Skip first two bytes
    convert_endianess(hex_data, index, 2); // Convert slot number
}

void convert_DL_DCI_C_TC_CS_B885_v196617(uint8_t *hex_data, int *index)
{
    *index+=12;
    convert_endianess(hex_data, index, 4); 
    *index += 5; 
    convert_endianess(hex_data, index, 2); 
    *index += 5; 
}

void convert_DL_DCI_P_RA_SI_Slot_Info_B885_v196617(uint8_t *hex_data, int *index)
{
    *index += 2; // Skip first two bytes
    convert_endianess(hex_data, index, 2); // Convert slot number
}

void convert_DL_DCI_P_RA_SI_B885_v196617(uint8_t *hex_data, int *index)
{
    *index += 12; 
    convert_endianess(hex_data, index, 4); 
    *index += 12; 
}

void decode_NR5G_MAC_DCI_Info_v196617(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_DCI_Info_v196617_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_DCI_Info_v196617_UL_DCI_Slot_Info_t *t_UL_DCI_Slot_Info = 0;
    asn_dec_rval_t rval_UL_DCI_Slot_Info;
    NR5G_MAC_DCI_Info_v196617_UL_DCI_t *t_UL_DCI = 0;
    asn_dec_rval_t rval_UL_DCI;
    NR5G_MAC_DCI_Info_v196617_DL_DCI_C_TC_CS_Slot_Info_t *t_DL_DCI_C_TC_CS_Slot_Info = 0;
    asn_dec_rval_t rval_DL_DCI_C_TC_CS_Slot_Info;
    NR5G_MAC_DCI_Info_v196617_DL_DCI_C_TC_CS_t *t_DL_DCI_C_TC_CS = 0;
    asn_dec_rval_t rval_DL_DCI_C_TC_CS;
    NR5G_MAC_DCI_Info_v196617_DL_DCI_P_RA_SI_Slot_Info_t *t_DL_DCI_P_RA_SI_Slot_Info = 0;
    asn_dec_rval_t rval_DL_DCI_P_RA_SI_Slot_Info;
    NR5G_MAC_DCI_Info_v196617_DL_DCI_P_RA_SI_t *t_DL_DCI_P_RA_SI = 0;
    asn_dec_rval_t rval_DL_DCI_P_RA_SI;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B885_v196617(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_S_H, t_S_H);

    int num_ul_dci = hex_data[start_S_H + 8];
    int num_dl_dci_c_tc_cs = hex_data[start_S_H + 9];
    int num_dl_dci_p_ra_si = hex_data[start_S_H + 10];
    int num_dl_dci_pdcch_oreder = hex_data[start_S_H + 11];
    int num_dl_dci_tpc = hex_data[start_S_H + 12];
    int num_dl_dci_ps = hex_data[start_S_H + 13];

    if(num_dl_dci_pdcch_oreder > 0 || num_dl_dci_tpc > 0 || num_dl_dci_ps > 0)
    {
        printf("Error: PDCCH order, TPC, and PS are not supported in this version.\n");
        return;
    }

    for(int i=0;i<num_ul_dci;i++)
    {
        int start_UL_DCI_Slot_Info = *index;
        convert_UL_DCI_Slot_Info_B885_v196617(hex_data, index);
        int UL_DCI_Slot_Info_length = *index - start_UL_DCI_Slot_Info;
        rval_UL_DCI_Slot_Info = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_UL_DCI_Slot_Info, (void **)&t_UL_DCI_Slot_Info, hex_data + start_UL_DCI_Slot_Info, UL_DCI_Slot_Info_length, 0, 0);
        if (rval_UL_DCI_Slot_Info.code != RC_OK)
        {
            printf("rval_UL_DCI_Slot_Info decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_UL_DCI_Slot_Info, t_UL_DCI_Slot_Info);

        int start_UL_DCI = *index;
        convert_UL_DCI_B885_v196617(hex_data, index);
        int UL_DCI_length = *index - start_UL_DCI;
        rval_UL_DCI = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_UL_DCI, (void **)&t_UL_DCI, hex_data + start_UL_DCI, UL_DCI_length, 0, 0);
        if (rval_UL_DCI.code != RC_OK)
        {
            printf("rval_UL_DCI decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_UL_DCI, t_UL_DCI);
    }

    for(int i=0;i<num_dl_dci_c_tc_cs;i++)
    {
        int start_DL_DCI_C_TC_CS_Slot_Info = *index;
        convert_DL_DCI_C_TC_CS_Slot_Info_B885_v196617(hex_data, index);
        int DL_DCI_C_TC_CS_Slot_Info_length = *index - start_DL_DCI_C_TC_CS_Slot_Info;

        rval_DL_DCI_C_TC_CS_Slot_Info = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_C_TC_CS_Slot_Info, (void **)&t_DL_DCI_C_TC_CS_Slot_Info, hex_data + start_DL_DCI_C_TC_CS_Slot_Info, DL_DCI_C_TC_CS_Slot_Info_length, 0, 0);
        if (rval_DL_DCI_C_TC_CS_Slot_Info.code != RC_OK)
        {
            printf("rval_DL_DCI_C_TC_CS_Slot_Info decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_C_TC_CS_Slot_Info, t_DL_DCI_C_TC_CS_Slot_Info);

        int start_DL_DCI_C_TC_CS = *index;
        convert_DL_DCI_C_TC_CS_B885_v196617(hex_data, index);
        int DL_DCI_C_TC_CS_length = *index - start_DL_DCI_C_TC_CS;

        rval_DL_DCI_C_TC_CS = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_C_TC_CS, (void **)&t_DL_DCI_C_TC_CS, hex_data + start_DL_DCI_C_TC_CS, DL_DCI_C_TC_CS_length, 0, 0);
        if (rval_DL_DCI_C_TC_CS.code != RC_OK)
        {
            printf("rval_DL_DCI_C_TC_CS decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_C_TC_CS, t_DL_DCI_C_TC_CS);
    }

    for(int i=0;i<num_dl_dci_p_ra_si;i++)
    {
        int start_DL_DCI_P_RA_SI_Slot_Info = *index;
        convert_DL_DCI_P_RA_SI_Slot_Info_B885_v196617(hex_data, index);
        int DL_DCI_P_RA_SI_Slot_Info_length = *index - start_DL_DCI_P_RA_SI_Slot_Info;

        rval_DL_DCI_P_RA_SI_Slot_Info = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_P_RA_SI_Slot_Info, (void **)&t_DL_DCI_P_RA_SI_Slot_Info, hex_data + start_DL_DCI_P_RA_SI_Slot_Info, DL_DCI_P_RA_SI_Slot_Info_length, 0, 0);
        if (rval_DL_DCI_P_RA_SI_Slot_Info.code != RC_OK)
        {
            printf("rval_DL_DCI_P_RA_SI_Slot_Info decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_P_RA_SI_Slot_Info, t_DL_DCI_P_RA_SI_Slot_Info);

        int start_DL_DCI_P_RA_SI = *index;
        convert_DL_DCI_P_RA_SI_B885_v196617(hex_data, index);
        int DL_DCI_P_RA_SI_length = *index - start_DL_DCI_P_RA_SI;

        rval_DL_DCI_P_RA_SI = uper_decode(0, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_P_RA_SI, (void **)&t_DL_DCI_P_RA_SI, hex_data + start_DL_DCI_P_RA_SI, DL_DCI_P_RA_SI_length, 0, 0);
        if (rval_DL_DCI_P_RA_SI.code != RC_OK)
        {
            printf("rval_DL_DCI_P_RA_SI decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_DCI_Info_v196617_DL_DCI_P_RA_SI, t_DL_DCI_P_RA_SI);
    }

    printf("decode_B885_v196617 over!!!\n");
}
