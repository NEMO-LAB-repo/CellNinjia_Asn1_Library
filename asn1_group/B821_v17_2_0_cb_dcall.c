#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "host.h"
#include "RRC_V17_2_0_PCCH-Message.h"
#include "RRC_V17_2_0_BCCH-BCH-Message.h"
#include "RRC_V17_2_0_BCCH-DL-SCH-Message.h"
#include "RRC_V17_2_0_DL-CCCH-Message.h"
#include "RRC_V17_2_0_DL-DCCH-Message.h"
#include "RRC_V17_2_0_UL-CCCH-Message.h"
#include "RRC_V17_2_0_UL-DCCH-Message.h"
#include "RRC_V17_2_0_RRCReconfiguration.h"
#include "RRC_V17_2_0_RRCReconfiguration-IEs.h"
#include "RRC_V17_2_0_RRCReconfiguration-v1530-IEs.h"
#include "RRC_V17_2_0_CellGroupConfig.h"

#include "RRC_V17_2_0_MCCH-Message-r17.h"
#include "RRC_V17_2_0_UL-CCCH1-Message.h"
#include "RRC_V17_2_0_CounterCheck.h"
#include "RRC_V17_2_0_MCGFailureInformation-r16.h"
#include "RRC_V17_2_0_MBSInterestIndication-r17.h"
#include "RRC_V17_2_0_MBSBroadcastConfiguration-r17.h"
#include "RRC_V17_2_0_LoggedMeasurementConfiguration-r16.h"

void convert_S_H_B821_RRC_V17_2_0(uint8_t *hex_data, int *index)
{
    *index+=8;
    convert_endianess(hex_data, index, 9);
    convert_endianess(hex_data, index, 3);
    convert_endianess(hex_data, index, 4);
    *index+=5;
    convert_endianess(hex_data, index, 2);
    *index+=1;
}

void decode_NR5G_RRC_OTA_Packet_v1720(uint8_t *hex_data, size_t length, int *index)
{
    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B821_RRC_V17_2_0(hex_data, index);
    int S_H_length = *index - start_S_H;
    int version = hex_data[start_S_H];
    int rrc_ver1 = hex_data[start_S_H+4];
    int rrc_ver2 = (hex_data[start_S_H+5] & 0xF0) >> 4;
    int rrc_ver3 = (hex_data[start_S_H+5] & 0x0F);
    int physicall_cell_id = hex_data[start_S_H+7];
    int Frequency = hex_data[start_S_H+17]<<16 | hex_data[start_S_H+18]<<8 | hex_data[start_S_H+19];
    long long Sfn = (hex_data[start_S_H+20]<<24) | (hex_data[start_S_H+21]<<16) | (hex_data[start_S_H+22]<<8) | (hex_data[start_S_H+23]);
    int pdu_type = hex_data[start_S_H+24];
    int content_length = (hex_data[start_S_H+29]<<8) | (hex_data[start_S_H+30]);
    

    printf("version : %d\n", version);
    printf("RRC version : %d.%d.%d\n", rrc_ver1, rrc_ver2, rrc_ver3);
    printf("physicall_cell_id : %d\n", physicall_cell_id);
    printf("NR Global Cell Identity : %02X%02X%02X%02X%02X%02X%02X%02X%02X\n", 
        hex_data[start_S_H+8], hex_data[start_S_H+9], hex_data[start_S_H+10], 
        hex_data[start_S_H+11], hex_data[start_S_H+12], hex_data[start_S_H+13], 
        hex_data[start_S_H+14], hex_data[start_S_H+15], hex_data[start_S_H+16]);
    printf("Frequency : %d\n", Frequency);
    printf("Sfn : %lld\n", Sfn);
    printf("pdu_type : %d\n", pdu_type);
    printf("content_length : %d\n", content_length);

    if(pdu_type == 1)
    {
        /*BCCH-BCH-Message*/
        RRC_V17_2_0_BCCH_BCH_Message_t *t_BCCH_BCH = 0;
        asn_dec_rval_t rval_BCCH_BCH;

        int start_BCCH_BCH = *index;
        int BCCH_BCH_Length = content_length;

        rval_BCCH_BCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_BCCH_BCH_Message, (void **)&t_BCCH_BCH, hex_data+start_BCCH_BCH, BCCH_BCH_Length, 0, 0);
        if(rval_BCCH_BCH.code != RC_OK) {
            printf("rval_BCCH_BCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_BCCH_BCH_Message, t_BCCH_BCH);
        *index += BCCH_BCH_Length;
    }
    else if(pdu_type == 2)
    {
        /*BCCH-DL-SCH-Message*/
        RRC_V17_2_0_BCCH_DL_SCH_Message_t *t_BCCH_DL = 0;
        asn_dec_rval_t rval_BCCH_DL_SCH;

        int start_BCCH_DL_SCH = *index;
        int BCCH_DL_SCH_Length = content_length;

        rval_BCCH_DL_SCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_BCCH_DL_SCH_Message, (void **)&t_BCCH_DL, hex_data+start_BCCH_DL_SCH, BCCH_DL_SCH_Length, 0, 0);
        if(rval_BCCH_DL_SCH.code != RC_OK) {
            printf("rval_BCCH_DL_SCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_BCCH_DL_SCH_Message, t_BCCH_DL);
        *index += BCCH_DL_SCH_Length;
    }
    else if(pdu_type == 3)
    {
        /*DL-CCCH-Message*/
        RRC_V17_2_0_DL_CCCH_Message_t *t_DL_CCCH = 0;
        asn_dec_rval_t rval_DL_CCCH;

        int start_DL_CCCH = *index;
        int DL_CCCH_Length = content_length;

        rval_DL_CCCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_DL_CCCH_Message, (void **)&t_DL_CCCH, hex_data+start_DL_CCCH, DL_CCCH_Length, 0, 0);
        if(rval_DL_CCCH.code != RC_OK) {
            printf("rval_DL_CCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_DL_CCCH_Message, t_DL_CCCH);
        *index += DL_CCCH_Length;
    }
    else if(pdu_type == 4)
    {
        /*DL-DCCH-Message*/
        RRC_V17_2_0_DL_DCCH_Message_t *t_DL_DCCH = 0;
        asn_dec_rval_t rval_DL_DCCH;

        int start_DL_DCCH = *index;
        int DL_DCCH_Length = content_length;

        rval_DL_DCCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_DL_DCCH_Message, (void **)&t_DL_DCCH, hex_data+start_DL_DCCH, DL_DCCH_Length, 0, 0);
        if(rval_DL_DCCH.code != RC_OK) {
            printf("rval_DL_DCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_DL_DCCH_Message, t_DL_DCCH);
        *index += DL_DCCH_Length;
    }
    else if(pdu_type == 5)
    {
        /*MCCH-Message-r17*/
        RRC_V17_2_0_MCCH_Message_r17_t *t_MCCH = 0;
        asn_dec_rval_t rval_MCCH;

        int start_MCCH = *index;
        int MCCH_Length = content_length;

        rval_MCCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_MCCH_Message_r17, (void **)&t_MCCH, hex_data+start_MCCH, MCCH_Length, 0, 0);
        if(rval_MCCH.code != RC_OK) {
            printf("rval_MCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_MCCH_Message_r17, t_MCCH);
        *index += MCCH_Length;
    }
    else if(pdu_type==6)
    {
        /*PCCH-Message*/
        RRC_V17_2_0_PCCH_Message_t *t_PCCH = 0;
        asn_dec_rval_t rval_PCCH;
        int start_PCCH = *index;
        int PCCH_Length = content_length;

        rval_PCCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_PCCH_Message, (void **)&t_PCCH, hex_data+start_PCCH, PCCH_Length, 0, 0);
        if(rval_PCCH.code != RC_OK) {
            printf("rval_PCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_PCCH_Message, t_PCCH);
        *index += PCCH_Length;
    }
    else if(pdu_type == 7)
    {
        /*UL-CCCH-Message*/
        RRC_V17_2_0_UL_CCCH_Message_t *t_UL_CCCH = 0;
        asn_dec_rval_t rval_UL_CCCH;

        int start_UL_CCCH = *index;
        int UL_CCCH_Length = content_length;

        rval_UL_CCCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_UL_CCCH_Message, (void **)&t_UL_CCCH, hex_data+start_UL_CCCH, UL_CCCH_Length, 0, 0);
        if(rval_UL_CCCH.code != RC_OK) {
            printf("rval_UL_CCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_UL_CCCH_Message, t_UL_CCCH);
        *index += UL_CCCH_Length;
    }
    else if(pdu_type == 8)
    {
        /*UL-CCCH1-Message*/
        RRC_V17_2_0_UL_CCCH1_Message_t *t_UL_CCCH1 = 0;
        asn_dec_rval_t rval_UL_CCCH1;

        int start_UL_CCCH1 = *index;
        int UL_CCCH1_Length = content_length;

        rval_UL_CCCH1 = uper_decode(0, &asn_DEF_RRC_V17_2_0_UL_CCCH1_Message, (void **)&t_UL_CCCH1, hex_data+start_UL_CCCH1, UL_CCCH1_Length, 0, 0);
        if(rval_UL_CCCH1.code != RC_OK) {
            printf("rval_UL_CCCH1 decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_UL_CCCH1_Message, t_UL_CCCH1);
        *index += UL_CCCH1_Length;
    }
    else if(pdu_type == 9)
    {
        /*UL-DCCH-Message*/
        RRC_V17_2_0_UL_DCCH_Message_t *t_UL_DCCH = 0;
        asn_dec_rval_t rval_UL_DCCH;

        int start_UL_DCCH = *index;
        int UL_DCCH_Length = content_length;

        rval_UL_DCCH = uper_decode(0, &asn_DEF_RRC_V17_2_0_UL_DCCH_Message, (void **)&t_UL_DCCH, hex_data+start_UL_DCCH, UL_DCCH_Length, 0, 0);
        if(rval_UL_DCCH.code != RC_OK) {
            printf("rval_UL_DCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_RRC_V17_2_0_UL_DCCH_Message, t_UL_DCCH);
        *index += UL_DCCH_Length;
    }
    else
    {
        printf("Unknown pdu_type: %d\n", pdu_type);
        return;
    }
    printf("Decoded RRC OTA packet V17_2_0 successfully.\n");
}
