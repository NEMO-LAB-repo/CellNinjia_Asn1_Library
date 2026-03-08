#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "host.h"
#include "RRC_V16_1_0_PCCH-Message.h"
#include "RRC_V16_1_0_DL-CCCH-Message.h"
#include "RRC_V16_1_0_DL-DCCH-Message.h"
#include "RRC_V16_1_0_UL-CCCH-Message.h"
#include "RRC_V16_1_0_UL-DCCH-Message.h"


void convert_S_H_B0C0_RRC_V16_1_0(uint8_t *hex_data, int *index)
{
    *index+=6;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index+=5;
    convert_endianess(hex_data, index, 2);
}

void decode_LTE_RRC_OTA_Packet_v16_1_0(uint8_t *hex_data, size_t length, int *index)
{
    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B0C0_RRC_V16_1_0(hex_data, index);
    int S_H_length = *index - start_S_H;
    int version = hex_data[start_S_H];

    int LTE_ver1 = hex_data[start_S_H+1];
    int LTE_ver2 = (hex_data[start_S_H+2] & 0xF0) >> 4;
    int LTE_ver3 = (hex_data[start_S_H+2] & 0x0F);

    int NR_ver1 = hex_data[start_S_H+3];
    int NR_ver2 = (hex_data[start_S_H+4] & 0xF0) >> 4;
    int NR_ver3 = (hex_data[start_S_H+4] & 0x0F);

    int physicall_cell_id = (hex_data[start_S_H+6]<<8) | (hex_data[start_S_H+7]);
    long long Frequency = hex_data[start_S_H+8]<<24 | hex_data[start_S_H+9]<<16 | hex_data[start_S_H+10]<<8 | hex_data[start_S_H+11];
    int Sfn = (hex_data[start_S_H+12]<<8) | (hex_data[start_S_H+13]<<16);
    int pdu_type = hex_data[start_S_H+14];
    int content_length = (hex_data[start_S_H+19]<<8) | (hex_data[start_S_H+20]);
    

    printf("version : %d\n", version);
    printf("LTE RRC version : %d.%d.%d\n", LTE_ver1, LTE_ver2, LTE_ver3);
    printf("NR RRC version : %d.%d.%d\n", NR_ver1, NR_ver2, NR_ver3);
    printf("physicall_cell_id : %d\n", physicall_cell_id);
    printf("Frequency : %lld\n", Frequency);
    printf("Sfn : %d\n", Sfn);
    printf("pdu_type : %d\n", pdu_type);
    printf("content_length : %d\n", content_length);

    if(pdu_type == 4)
    {
        /*PCCH-Message*/
        RRC_V16_1_0_PCCH_Message_t *t_PCCH = 0;
        asn_dec_rval_t rval_PCCH;

        int start_PCCH = *index;
        int PCCH_Length = content_length;

        rval_PCCH = uper_decode(0, &asn_DEF_RRC_V16_1_0_PCCH_Message, (void **)&t_PCCH, hex_data+start_PCCH, PCCH_Length, 0, 0);
        if(rval_PCCH.code != RC_OK) {
            printf("rval_PCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V16_1_0_PCCH_Message, t_PCCH);
        *index += PCCH_Length;
    }
    else if(pdu_type == 5)
    {
        /*DL-CCCH-Message*/
        RRC_V16_1_0_DL_CCCH_Message_t *t_DL_CCCH = 0;
        asn_dec_rval_t rval_DL_CCCH;

        int start_DL_CCCH = *index;
        int DL_CCCH_Length = content_length;

        rval_DL_CCCH = uper_decode(0, &asn_DEF_RRC_V16_1_0_DL_CCCH_Message, (void **)&t_DL_CCCH, hex_data+start_DL_CCCH, DL_CCCH_Length, 0, 0);
        if(rval_DL_CCCH.code != RC_OK) {
            printf("rval_DL_CCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V16_1_0_DL_CCCH_Message, t_DL_CCCH);
        *index += DL_CCCH_Length;
    }
    else if(pdu_type == 6)
    {
        /*DL-DCCH-Message*/
        RRC_V16_1_0_DL_DCCH_Message_t *t_DL_DCCH = 0;
        asn_dec_rval_t rval_DL_DCCH;

        int start_DL_DCCH = *index;
        int DL_DCCH_Length = content_length;

        rval_DL_DCCH = uper_decode(0, &asn_DEF_RRC_V16_1_0_DL_DCCH_Message, (void **)&t_DL_DCCH, hex_data+start_DL_DCCH, DL_DCCH_Length, 0, 0);
        if(rval_DL_DCCH.code != RC_OK) {
            printf("rval_DL_DCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V16_1_0_DL_DCCH_Message, t_DL_DCCH);
        *index += DL_DCCH_Length;
    }
    else if(pdu_type == 7)
    {
        /*UL_CCCH-Message*/
        RRC_V16_1_0_UL_CCCH_Message_t *t_UL_CCCH = 0;
        asn_dec_rval_t rval_UL_CCCH;

        int start_UL_CCCH = *index;
        int UL_CCCH_Length = content_length;

        rval_UL_CCCH = uper_decode(0, &asn_DEF_RRC_V16_1_0_UL_CCCH_Message, (void **)&t_UL_CCCH, hex_data+start_UL_CCCH, UL_CCCH_Length, 0, 0);
        if(rval_UL_CCCH.code != RC_OK) {
            printf("rval_UL_CCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V16_1_0_UL_CCCH_Message, t_UL_CCCH);
        *index += UL_CCCH_Length;
    }
    else if(pdu_type==8)
    {
        /*UL-DCCH-Message*/
        RRC_V16_1_0_UL_DCCH_Message_t *t_UL_DCCH = 0;
        asn_dec_rval_t rval_UL_DCCH;

        int start_UL_DCCH = *index;
        int UL_DCCH_Length = content_length;

        rval_UL_DCCH = uper_decode(0, &asn_DEF_RRC_V16_1_0_UL_DCCH_Message, (void **)&t_UL_DCCH, hex_data+start_UL_DCCH, UL_DCCH_Length, 0, 0);
        if(rval_UL_DCCH.code != RC_OK) {
            printf("rval_UL_DCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V16_1_0_UL_DCCH_Message, t_UL_DCCH);
        *index += UL_DCCH_Length;
    }
    else
    {
        printf("Unknown pdu_type: %d\n", pdu_type);
        return;
    }
    printf("Decoded LTE OTA packet V16_1_0 successfully.\n");
}
