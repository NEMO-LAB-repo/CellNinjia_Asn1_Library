#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "host.h"
#include "PCCH-Message.h"
#include "BCCH-BCH-Message.h"
#include "BCCH-DL-SCH-Message.h"
#include "DL-CCCH-Message.h"
#include "DL-DCCH-Message.h"
#include "UL-CCCH-Message.h"
#include "UL-DCCH-Message.h"
#include "RRCReconfiguration.h"
#include "RRCReconfiguration-IEs.h"
#include "RRCReconfiguration-v1530-IEs.h"
#include "CellGroupConfig.h"


void convert_S_H_B821(uint8_t *hex_data, int *index)
{
    *index+=8;
    convert_endianess(hex_data, index, 9);
    convert_endianess(hex_data, index, 3);
    convert_endianess(hex_data, index, 4);
    *index+=5;
    convert_endianess(hex_data, index, 2);
}


void decode_NR5G_RRC_OTA_Packet_v1660(uint8_t *hex_data, size_t length, int *index)
{
    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B821(hex_data, index);
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
    printf("pdu_type = %d\n", pdu_type);
    printf("content_length = %d\n", content_length);

    if(pdu_type == 1)
    {
        /*BCCH-BCH-Message*/
        BCCH_BCH_Message_t *t_BCCH = 0;
        asn_dec_rval_t rval_BCCH;

        int start_BCCH_BCH = *index;
        int BCCH_BCH_Length = content_length;

        rval_BCCH = uper_decode(0, &asn_DEF_BCCH_BCH_Message, (void **)&t_BCCH, hex_data+start_BCCH_BCH, BCCH_BCH_Length, 0, 0);
        if(rval_BCCH.code != RC_OK) {
            printf("rval_BCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_BCCH_BCH_Message, t_BCCH);
        *index += BCCH_BCH_Length;
    }
    else if(pdu_type == 2)
    {
        /*BCCH-DL-SCH-Message*/
        BCCH_DL_SCH_Message_t *t_BCCH_DL = 0;
        asn_dec_rval_t rval_BCCH_DL_SCH;

        int start_BCCH_DL_SCH = *index;
        int BCCH_DL_SCH_Length = content_length;

        rval_BCCH_DL_SCH = uper_decode(0, &asn_DEF_BCCH_DL_SCH_Message, (void **)&t_BCCH_DL, hex_data+start_BCCH_DL_SCH, BCCH_DL_SCH_Length, 0, 0);
        if(rval_BCCH_DL_SCH.code != RC_OK) {
            printf("rval_BCCH_DL_SCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_BCCH_DL_SCH_Message, t_BCCH_DL);
        *index += BCCH_DL_SCH_Length;
    }
    else if(pdu_type == 3)
    {
        /*DL-CCCH-Message*/
        DL_CCCH_Message_t *t_DL_CCCH = 0;
        asn_dec_rval_t rval_DL_CCCH;

        int start_DL_CCCH = *index;
        int DL_CCCH_Length = content_length;

        rval_DL_CCCH = uper_decode(0, &asn_DEF_DL_CCCH_Message, (void **)&t_DL_CCCH, hex_data+start_DL_CCCH, DL_CCCH_Length, 0, 0);
        if(rval_DL_CCCH.code != RC_OK) {
            printf("rval_DL_CCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_DL_CCCH_Message, t_DL_CCCH);
        *index += DL_CCCH_Length;
    }
    else if(pdu_type == 4)
    {
        /*DL-DCCH-Message*/
        DL_DCCH_Message_t *t_DL_DCCH = 0;
        asn_dec_rval_t rval_DL_DCCH;

        int start_DL_DCCH = *index;
        int DL_DCCH_Length = content_length;

        rval_DL_DCCH = uper_decode(0, &asn_DEF_DL_DCCH_Message, (void **)&t_DL_DCCH, hex_data+start_DL_DCCH, DL_DCCH_Length, 0, 0);
        if(rval_DL_DCCH.code != RC_OK) {
            printf("rval_DL_DCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_DL_DCCH_Message, t_DL_DCCH);
        *index += DL_DCCH_Length;

        if(t_DL_DCCH->message.choice.c1 && t_DL_DCCH->message.choice.c1->present == DL_DCCH_MessageType__c1_PR_rrcReconfiguration)
        {
            printf("c1 checked\n");
            RRCReconfiguration_t *t_RRCReconfiguration = t_DL_DCCH->message.choice.c1->choice.rrcReconfiguration;

            if(t_RRCReconfiguration->criticalExtensions.present == RRCReconfiguration__criticalExtensions_PR_rrcReconfiguration)
            {
                printf("RRCReconfiguration_IEs\n");
                RRCReconfiguration_IEs_t *t_RRCReconfiguration_IEs = t_RRCReconfiguration->criticalExtensions.choice.rrcReconfiguration;

                if(t_RRCReconfiguration_IEs && t_RRCReconfiguration_IEs->nonCriticalExtension)
                {
                    printf("RRCReconfiguration_v1530_IEs\n");
                    RRCReconfiguration_v1530_IEs_t *t_RRCReconfiguration_v1530_IEs = t_RRCReconfiguration_IEs->nonCriticalExtension;

                    if(t_RRCReconfiguration_v1530_IEs->masterCellGroup)
                    {
                        printf("masterCellGroup present\n");
                        CellGroupConfig_t *t_CellGroupConfig = NULL;
                        asn_dec_rval_t rval_CellGroupConfig;

                        uint8_t *cellGroupData = t_RRCReconfiguration_v1530_IEs->masterCellGroup->buf;
                        size_t cellGroupSize = t_RRCReconfiguration_v1530_IEs->masterCellGroup->size;

                        printf("masterCellGroup size: %zu bytes\n", cellGroupSize);

                        printf("About to decode CellGroupConfig...\n");
                        printf("asn_DEF_CellGroupConfig: %p\n", &asn_DEF_CellGroupConfig);
                        printf("cellGroupData pointer: %p\n", cellGroupData);
                        printf("cellGroupSize: %zu\n", cellGroupSize);
                        if(&asn_DEF_CellGroupConfig == NULL) {
                            printf("asn_DEF_CellGroupConfig is NULL!\n");
                            return;
                        }


                        rval_CellGroupConfig = uper_decode(0, &asn_DEF_CellGroupConfig, (void **)&t_CellGroupConfig, cellGroupData, cellGroupSize, 0, 0);
                        if(rval_CellGroupConfig.code != RC_OK) {
                            printf("rval_CellGroupConfig decode error\n");
                            
                        }
                        xer_fprint(stdout, &asn_DEF_CellGroupConfig, t_CellGroupConfig);


                    }
                }
            }

        }
    }
    else if(pdu_type == 5)
    {
        /*PCCH-Message*/
        // printf("pcch confirm\n");
        PCCH_Message_t *t_PCCH = 0;
        asn_dec_rval_t rval_PCCH;

        int start_PCCH = *index;
        int PCCH_Length = content_length;

        rval_PCCH = uper_decode(0, &asn_DEF_PCCH_Message, (void **)&t_PCCH, hex_data+start_PCCH, PCCH_Length, 0, 0);
        if(rval_PCCH.code != RC_OK) {
            printf("rval_PCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_PCCH_Message, t_PCCH);
        *index += PCCH_Length; 
    }
    else if(pdu_type == 6)
    {
        /*UL-CCCH-Message*/
        UL_CCCH_Message_t *t_UL_CCCH = 0;
        asn_dec_rval_t rval_UL_CCCH;
        
        int start_UL_CCCH = *index;
        int UL_CCCH_Length = content_length;

        rval_UL_CCCH = uper_decode(0, &asn_DEF_UL_CCCH_Message, (void **)&t_UL_CCCH, hex_data+start_UL_CCCH, UL_CCCH_Length, 0, 0);
        if(rval_UL_CCCH.code != RC_OK) {
            printf("rval_UL_CCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_UL_CCCH_Message, t_UL_CCCH);
        *index += UL_CCCH_Length;
    }
    else if(pdu_type == 8)
    {
        /*UL-DCCH-Message*/
        UL_DCCH_Message_t *t_UL_DCCH = 0;
        asn_dec_rval_t rval_UL_DCCH;

        int start_UL_DCCH = *index;
        int UL_DCCH_Length = content_length;

        rval_UL_DCCH = uper_decode(0, &asn_DEF_UL_DCCH_Message, (void **)&t_UL_DCCH, hex_data+start_UL_DCCH, UL_DCCH_Length, 0, 0);
        if(rval_UL_DCCH.code != RC_OK) {
            printf("rval_UL_DCCH decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_UL_DCCH_Message, t_UL_DCCH);
        *index += UL_DCCH_Length;
    }
    else
    {
        printf("current pdu type: %d, please contact the author ASAP!\n", pdu_type);
    }
    printf("decode_B821 over!!!\n");

}