#!/bin/bash

# Compile all ASN.1 files individually
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_Contention_Resolution_Message_MSG4_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_LL1_PCFICH_Decoding_Results.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_LL1_RACH_TX_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_LL1_Serving_Cell_Measurement_Results.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_MAC_UL_Transport_Block.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_AdvRx_IC_Cell_List.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_CA_Metrics_Log_Packet.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Cell_Measurement_Results.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Common_DC_Offset.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_DCI_Information_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_DCI_Information_Report_v48.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_GM_TX_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Idle_Measurement_Request.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Intra_Frequency_Cell_Reselection.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_PDSCH_Stat_Indication.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Random_Access_Request_MSG1_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Random_Access_Response_MSG2_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_S_Criteria_Check_Procedure.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Serving_Cell_Information.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_ML1_Serving_Cell_Measurements_And_Evaluation.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_PDCP_DL_Data_PDU.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_PDCP_UL_Delay_Statistics.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_RLC_DL_AM_Control_PDU.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_RRC_Supported_CA_Combos.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto LTE_UE_Identification_Message_MSG3_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto Metadata_Header.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_DL_Config.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_DL_DATA_PDU.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_UL_BSR.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_UL_Config.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_UL_Data_PDU_v196611.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_UL_TB.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_L2_UL_TB_v196616.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_LL1_FW_RX_Control_AGC_v131072.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_LL1_FW_Serving_FTL.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_CDRX_Events_Info.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_CSF_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_CSF_Report_v196613.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_DCI_Info.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_DCI_Info_v196617.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_DL_TB_Report.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_Flow_Control.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_PDSCH_Stats.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_PDSCH_Status.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_PDSCH_Status_v196611.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_RACH_Attempt.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_RACH_Trigger.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_UCI_Information.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_UCI_Information_v196608.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_UCI_Payload_Information.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_MAC_UL_TB_Stats.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_ML1_Antenna_Switch_Diversity.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_ML1_Search_HO_Acq_Confirm_v131079.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_ML1_Searcher_Conn_Eval_v131075.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_ML1_Searcher_Measurement_Database_Update_Ext.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_NAS_MM5G_NSSAI_Info.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_NAS_MM5G_State.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_NAS_Plain_Message_Container.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_NAS_SM5G_Plain_OTA_Outgoing_Msg.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_PDCP_DL_Data_Pdu.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_PDCP_DL_Rbs_Stats.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_PDCP_UL_Control_Pdu.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_PDCP_UL_Stats.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RLC_DL_Stats.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RLC_DL_Status_PDU.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RLC_UL_Stats.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RLC_UL_Status_PDU.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RRC_Configuration_Info.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RRC_MIB_Info.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RRC_Serving_Cell_Info.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto NR5G_RRC_Supported_CA_Combos.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto -fprefix=RRC_V16_1_0_ rrc_g10.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto -fprefix=RRC_V15_10_0_ rrc_fa0.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto -fprefix=RRC_V17_2_0_ rrc_h20.asn1
asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -findirect-choice -fincludes-quoted -fno-include-deps -pdu=auto rrc_g60.asn1

echo "All ASN.1 files compiled successfully!"