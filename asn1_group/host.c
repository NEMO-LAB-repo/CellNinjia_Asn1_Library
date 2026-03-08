#include "host.h"

long get_file_size(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        return -1; 
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
}

int get_item_id(int type_id) 
{
    const int ITEM_ID_MASK = 0x00000FFF;
    return type_id & ITEM_ID_MASK;
}

int get_equip_id(int type_id) 
{
    const int EQUIP_ID_MASK = 0x0000F000;
    return (type_id & EQUIP_ID_MASK) >> 12;
}

int map_index_logcode(int log_index)
{
    switch (log_index) 
    {
        case 1:
            return 0xB801;
        case 2:
            return 0xB80C;
        case 3:
            return 0xB814;
        case 4:
            return 0xB815;
        case 5:
            return 0xB822;
        case 6:
            return 0xB823;
        case 7:
            return 0xB825;
        case 8:
            return 0xB826;
        case 9:
            return 0xB840;
        case 10:
            return 0xB842;
        case 11:
            return 0xB84B;
        case 12:
            return 0xB84D;
        case 13:
            return 0xB84E;
        case 14:
            return 0xB857;
        case 15:
            return 0xB860;
        case 16:
            return 0xB861;
        case 17:
            return 0xB868;
        case 18:
            return 0xB871;
        case 19:
            return 0xB872;
        case 20:
            return 0xB873;
        case 21:
            return 0xB881;
        case 22:
            return 0xB885;
        case 23:
            return 0xB886;
        case 24:
            return 0xB887;
        case 25:
            return 0xB888;
        case 26:
            return 0xB889;
        case 27:
            return 0xB890;
        case 28:
            return 0xB89B;
        case 29:
            return 0xB89C;
        case 30:
            return 0xB8A7;
        case 31:
            return 0xB97F;
        case 32:
            return 0xB821;
        case 33:
            return 0xB88A;
        case 34:
            return 0xB896;
        case 35:
            return 0xB96F;
        case 36:
            return 0xB869;
        case 37:
            return 0xB98F;
        case 38:
            return 0xB8DD;
        case 39:
            return 0xB9BF;
        case 40:
            return 0xB870;
        case 41:
            return 0xB8C9;
        case 42:
            return 0xB883;
        case 99: // NAS now, suspend here
            return 0xB800;
        case 100: // NAS now, suspend here
            return 0xB80A;
        case 101:
            return 0xB0C0;
        default:
            return -1; // unknown msg type
    }

}

int map_logcode_index(int logcode)
{
    switch(logcode)
    {
        case 0xB801:
            return 1;
        case 0xB80C:
            return 2;
        case 0xB814:
            return 3;
        case 0xB815:
            return 4;
        case 0xB822:
            return 5;
        case 0xB823:
            return 6;
        case 0xB825:
            return 7;
        case 0xB826:
            return 8;
        case 0xB840:
            return 9;
        case 0xB842:
            return 10;
        case 0xB84B:
            return 11;
        case 0xB84D:
            return 12;
        case 0xB84E:
            return 13;
        case 0xB857:
            return 14;
        case 0xB860:
            return 15;
        case 0xB861:
            return 16;
        case 0xB868:
            return 17;
        case 0xB871:
            return 18;
        case 0xB872:
            return 19;
        case 0xB873:
            return 20;
        case 0xB881:
            return 21;
        case 0xB885:
            return 22;
        case 0xB886:
            return 23;
        case 0xB887:
            return 24;
        case 0xB888:
            return 25;
        case 0xB889:
            return 26;
        case 0xB890:
            return 27;
        case 0xB89B:
            return 28;
        case 0xB89C:
            return 29;
        case 0xB8A7:
            return 30;
        case 0xB97F:
            return 31;
        case 0xB821:
            return 32;
        case 0xB88A:
            return 33;
        case 0xB896:
            return 34;
        case 0xB96F:
            return 35;
        case 0xB869:
            return 36;
        case 0xB98F:
            return 37;
        case 0xB8DD:
            return 38;
        case 0xB9BF:
            return 39;
        case 0xB870:
            return 40;
        case 0xB8C9:
            return 41;
        case 0xB883:
            return 42;
        case 0xB800: // NAS now, suspend here
            return 99;
        case 0xB80A: // NAS now, suspend here
            return 100;
        case 0xB0C0:
            return 101;
        default:
            return -1; // unknown logcode
    }
}

const char* map_index_msgtype(int index)
{
    switch (index) 
    {
        case 1:
            return "NR5G NAS SM5G Plain OTA Outgoing Msg";
        case 2:
            return "NR5G NAS MM5G State";
        case 3:
            return "NR5G NAS Plain Message Container";
        case 4:
            return "NR5G NAS MM5G NSSAI Info";
        case 5:
            return "NR5G RRC MIB Info";
        case 6:
            return "NR5G RRC Serving Cell Info";
        case 7:
            return "NR5G RRC Configuration Info";
        case 8:
            return "NR5G RRC Supported CA Combos";
        case 9:
            return "NR5G PDCP DL Data Pdu";
        case 10:
            return "NR5G PDCP DL Rbs Stats";
        case 11:
            return "NR5G L2 DL Config";
        case 12:
            return "NR5G RLC DL Stats";
        case 13:
            return "NR5G RLC DL Status PDU";
        case 14:
            return "NR5G L2 DL DATA PDU";
        case 15:
            return "NR5G PDCP UL Stats";
        case 16:
            return "NR5G PDCP UL Control Pdu";
        case 17:
            return "NR5G RLC UL Stats";
        case 18:
            return "NR5G L2 UL Config";
        case 19:
            return "NR5G L2 UL TB";
        case 20:
            return "NR5G L2 UL BSR";
        case 21:
            return "NR5G MAC UL TB Stats";
        case 22:
            return "NR5G MAC DCI Info";
        case 23:
            return "NR5G MAC DL TB Report";
        case 24:
            return "NR5G MAC PDSCH Status";
        case 25:
            return "NR5G MAC PDSCH Stats";
        case 26:
            return "NR5G MAC RACH Trigger";
        case 27:
            return "NR5G MAC CDRX Events Info";
        case 28:
            return "NR5G MAC UCI Information";
        case 29:
            return "NR5G MAC Flow Control";
        case 30:
            return "NR5G MAC CSF Report";
        case 31:
            return "NR5G ML1 Searcher Measurement Database Update Ext";
        case 32:
            return "NR5G RRC OTA Packet";
        case 33:
            return "NR5G MAC RACH Attempt";
        case 34:
            return "NR5G MAC UCI Payload Information";
        case 35:
            return "NR5G ML1 Searcher Conn Eval";
        case 36:
            return "NR5G RLC UL Status PDU";
        case 37:
            return "NR5G ML1 Antenna Switch Diversity";
        case 38:
            return "NR5G LL1 FW Serving FTL";
        case 39:
            return "NR5G ML1 Search HO Acq Confirm"; 
        case 40:
            return "NR5G L2 UL Data PDU";
        case 41:
            return "NR5G LL1 FW RX Control AGC";
        case 42:
            return "NR5G MAC UL Physical Channel Schedule Report";
        case 99: // NAS now, suspend here
            return "NR5G NAS SM5G"; // Placeholder for NAS msg
        case 100: // NAS now, suspend here
            return "NR5G NAS MM5G"; // Placeholder for NAS msg
        case 101:
            return "LTE RRC OTA Packet";
        default:
            return NULL; // unknown msg type
    }
}

int map_msgtype_index(const char* msgtype)
{
    if (strcmp(msgtype, "NR5G NAS SM5G Plain OTA Outgoing Msg") == 0) return 1;
    if (strcmp(msgtype, "NR5G NAS MM5G State") == 0) return 2;
    if (strcmp(msgtype, "NR5G NAS Plain Message Container") == 0) return 3;
    if (strcmp(msgtype, "NR5G NAS MM5G NSSAI Info") == 0) return 4;
    if (strcmp(msgtype, "NR5G RRC MIB Info") == 0) return 5;
    if (strcmp(msgtype, "NR5G RRC Serving Cell Info") == 0) return 6;
    if (strcmp(msgtype, "NR5G RRC Configuration Info") == 0) return 7;
    if (strcmp(msgtype, "NR5G RRC Supported CA Combos") == 0) return 8;
    if (strcmp(msgtype, "NR5G PDCP DL Data Pdu") == 0) return 9;
    if (strcmp(msgtype, "NR5G PDCP DL Rbs Stats") == 0) return 10;
    if (strcmp(msgtype, "NR5G L2 DL Config") == 0) return 11;
    if (strcmp(msgtype, "NR5G RLC DL Stats") == 0) return 12;
    if (strcmp(msgtype, "NR5G RLC DL Status PDU") == 0) return 13;
    if (strcmp(msgtype, "NR5G L2 DL DATA PDU") == 0) return 14;
    if (strcmp(msgtype, "NR5G PDCP UL Stats") == 0) return 15;
    if (strcmp(msgtype, "NR5G PDCP UL Control Pdu") == 0) return 16;
    if (strcmp(msgtype, "NR5G RLC UL Stats") == 0) return 17;
    if (strcmp(msgtype, "NR5G L2 UL Config") == 0) return 18;
    if (strcmp(msgtype, "NR5G L2 UL TB") == 0) return 19;
    if (strcmp(msgtype, "NR5G L2 UL BSR") == 0) return 20;
    if (strcmp(msgtype, "NR5G MAC UL TB Stats") == 0) return 21;
    if (strcmp(msgtype, "NR5G MAC DCI Info") == 0) return 22;
    if (strcmp(msgtype, "NR5G MAC DL TB Report") == 0) return 23;
    if (strcmp(msgtype, "NR5G MAC PDSCH Status") == 0) return 24;
    if (strcmp(msgtype, "NR5G MAC PDSCH Stats") == 0) return 25;
    if (strcmp(msgtype, "NR5G MAC RACH Trigger") == 0) return 26;
    if (strcmp(msgtype, "NR5G MAC CDRX Events Info") == 0) return 27;
    if (strcmp(msgtype, "NR5G MAC UCI Information") == 0) return 28;
    if (strcmp(msgtype, "NR5G MAC Flow Control") == 0) return 29;
    if (strcmp(msgtype, "NR5G MAC CSF Report") == 0) return 30;
    if (strcmp(msgtype, "NR5G ML1 Searcher Measurement Database Update Ext") == 0) return 31;
    if (strcmp(msgtype, "NR5G RRC OTA Packet") == 0) return 32;
    if (strcmp(msgtype, "NR5G MAC RACH Attempt") == 0) return 33;
    if (strcmp(msgtype, "NR5G MAC UCI Payload Information") == 0) return 34;
    if (strcmp(msgtype, "NR5G ML1 Searcher Conn Eval") == 0) return 35;
    if (strcmp(msgtype, "NR5G RLC UL Status PDU") == 0) return 36;
    if (strcmp(msgtype, "NR5G ML1 Antenna Switch Diversity") == 0) return 37;
    if (strcmp(msgtype, "NR5G LL1 FW Serving FTL") == 0) return 38;
    if (strcmp(msgtype, "NR5G ML1 Search HO Acq Confirm") == 0) return 39;
    if (strcmp(msgtype, "NR5G L2 UL Data PDU") == 0) return 40;
    if (strcmp(msgtype, "NR5G LL1 FW RX Control AGC") == 0) return 41;
    if (strcmp(msgtype, "NR5G MAC UL Physical Channel Schedule Report") == 0) return 42;
    if (strcmp(msgtype, "NR5G NAS SM5G") == 0) return 99; // Placeholder for NAS msg
    if (strcmp(msgtype, "NR5G NAS MM5G") == 0) return 100; // Placeholder for NAS msg
    if (strcmp(msgtype, "LTE RRC OTA Packet") == 0) return 101; // Placeholder for NAS msg
    else
    {
        return -1; // unknown msg name
    }
}




char* generate_cfg(const char* msgtype_list[], int logcode_num)
{
    int equip_id = -1;
    int highest = 0;

    for(int i = 0; i < logcode_num; i++)
    {
        int cur_index = map_msgtype_index(msgtype_list[i]);
        int cur_logcode = map_index_logcode(cur_index);

        printf("Current log index: %d, logcode: 0x%04X\n", cur_index, cur_logcode);
        
        if (cur_logcode == -1) 
        {
            printf("Error: Invalid log index %d\n", msgtype_list[i]);
            return NULL;
        }
        int e = get_equip_id(cur_logcode);
        if (equip_id == -1) 
        {
            equip_id = e;
            highest = (highest > get_item_id(cur_logcode)) ? highest : get_item_id(cur_logcode);
        } 
        else if (equip_id == e) 
        {
            highest = (highest > get_item_id(cur_logcode)) ? highest : get_item_id(cur_logcode);
        } 
        else 
        {
            equip_id = -1;
            break;
        }
    }
    switch (equip_id) 
    {
        case 0x00000001:    // CDMA, _1xEV, ......
            highest = 0x00000FD3;
            break;
        case 0x00000004:    // WCDMA, ......
            highest = 0x00000920;
            break;
        case 0x00000007:    // UMTS, ......
            highest = 0x00000B56;
            break;
        case 0x0000000b:    // LTE, 5G ......
            highest = 0x00000FFF;
            break;
        default:
            break;
    }
    int mask_len = (highest / 8) + 1;
    int buf_size = sizeof(char) * 4 + sizeof(int) * 3 + mask_len;
    
    char* buf = (char*)malloc(buf_size);

    buf[0] = 115; // 0x73
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    *((int *)(buf + 4)) = 3;
    *((int *)(buf + 8)) = equip_id;
    *((int *)(buf + 12)) = highest + 1;
    char* mask = buf + 16;
    memset(mask, 0, mask_len);
    
    for (int i = 0; i < logcode_num; i++) 
    {
        int cur_index = map_msgtype_index(msgtype_list[i]);
        int cur_logcode = map_index_logcode(cur_index);

        int id = cur_logcode & 0x0FFF;
        mask[id / 8] |= 1 << (id % 8);
    }
    return buf;

    // cfg_file.close();
}



void decode_header(const char *output_frame, int start_index, uint64_t *msg_header)
{
    //msg_len
    int log_msg_len_start_index = start_index;
    uint16_t msglen_1 = (uint16_t)(output_frame[log_msg_len_start_index] & 0xFF);
    uint16_t msglen_2 = (uint16_t)(output_frame[log_msg_len_start_index+1] & 0xFF);
    uint16_t msg_len = (msglen_2<<8)+msglen_1;

    // logcode
    int logcode_start_index = start_index+2;
    uint16_t logcode_1stByte = (uint16_t)(output_frame[logcode_start_index] & 0xFF);
    uint16_t logcode_2ndByte = (uint16_t)(output_frame[logcode_start_index+1] & 0xFF);
    int logcode = (logcode_2ndByte<<8)+logcode_1stByte;
    // logcode_index
    int logcode_index = map_logcode_index(logcode);
    

    //timestamp
    int timestamp_start_index = start_index+4;
    uint64_t t_1 = (uint64_t)(output_frame[timestamp_start_index] & 0xFF);
    uint64_t t_2 = (uint64_t)(output_frame[timestamp_start_index+1] & 0xFF);
    uint64_t t_3 = (uint64_t)(output_frame[timestamp_start_index+2] & 0xFF);
    uint64_t t_4 = (uint64_t)(output_frame[timestamp_start_index+3] & 0xFF);
    uint64_t t_5 = (uint64_t)(output_frame[timestamp_start_index+4] & 0xFF);
    uint64_t t_6 = (uint64_t)(output_frame[timestamp_start_index+5] & 0xFF);
    uint64_t t_7 = (uint64_t)(output_frame[timestamp_start_index+6] & 0xFF);
    uint64_t t_8 = (uint64_t)(output_frame[timestamp_start_index+7] & 0xFF);

    uint64_t timestamp = ((t_8<<56)|(t_7<<48)|(t_6<<40)|(t_5<<32)|(t_4<<24)|(t_3<<16)|(t_2<<8)|t_1);

    // This version may not be true
    int version_start_index = start_index+12;
    int version = ((output_frame[version_start_index+3] & 0xFF)<<24) | ((output_frame[version_start_index+2] & 0xFF)<<16) | ((output_frame[version_start_index+1] & 0xFF)<<8) | ((output_frame[version_start_index] & 0xFF));

    msg_header[0]=msg_len;
    msg_header[1]=logcode_index;
    msg_header[2]=timestamp;
    msg_header[3]=version;
}      



int S_D_V_decode(uint8_t *hex_data, size_t file_size, int msg_index, int *index_in, uint64_t time_in_us_total, int crc_check, int check_format, int pkt_type, int msg_len, int version_4B)
{
    uint8_t *output = NULL;
    int index = *index_in;
    int logcode = map_index_logcode(msg_index);

    switch (logcode)
    {
    case 0xB083:
    {
        // printf("in B083 branch\n");
        decode_B083(hex_data, file_size, &index);
        *index_in = index;
        return 83;
    }
    case 0xB0A1:
    {
        decode_B0A1(hex_data, file_size, &index);
        *index_in = index;
        return 161;
    }
    case 0xB0B6:
    {
        decode_B0B6(hex_data, file_size, &index);
        *index_in = index;
        return 182;
    }
    case 0xB0CD:
    {
        decode_B0CD(hex_data, file_size, &index);
        *index_in = index;
        return 205;
    }
    case 0xB116:
    {
        decode_B116(hex_data, file_size, &index);
        *index_in = index;
        return 278;
    }
    case 0xB12A:
    {
        decode_B12A(hex_data, file_size, &index);
        *index_in = index;
        return 298;
    }
    case 0xB144:
    {
        decode_B144(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB167:
    {
        decode_B167(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB168:
    {
        decode_B168(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB169:
    {
        decode_B169(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB16A:
    {
        decode_B16A(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB16C:
    {
        decode_B16C(hex_data, file_size, &index);
        *index_in = index;
        return 1;
    }
    case 0xB16D:
    {
        decode_B16D(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB173:
    {
        decode_B173(hex_data, file_size, &index, time_in_us_total, logcode);
        *index_in = index;
        return 173;
    }
    case 0xB17A:
    {
        decode_B17A(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB17D:
    {
        decode_B17D(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB17F:
    {
        decode_B17F(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB181:
    {
        decode_B181(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB184:
    {
        decode_B184(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB18F:
    {
        decode_B18F(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB196:
    {
        decode_B196(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB197:
    {
        decode_B197(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB1B2:
    {
        decode_B1B2(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB0C0:
    {
        printf("in B0C0 branch\n");
        decode_LTE_RRC_OTA_Packet_v16_1_0(hex_data, file_size, &index);
        *index_in = index;
        return 325;
    }
    case 0xB801:
    {
        decode_NR5G_NAS_SM5G_Plain_OTA_Outgoing_Msg_v1(hex_data, file_size, &index);
        *index_in = index;
        return 801;
    }
    case 0xB80C:
    {
        decode_NR5G_NAS_MM5G_State_v1(hex_data, file_size, &index);
        *index_in = index;
        return 324;
    }
    case 0xB814:
    {
        decode_NR5G_NAS_Plain_Message_Container_v1(hex_data, file_size, &index, msg_len);
        *index_in = index;
        return 814;
    }
    case 0xB815:
    {
        decode_NR5G_NAS_MM5G_NSSAI_Info_v1(hex_data, file_size, &index);
        *index_in = index;
        return 815;
    }
    case 0xB822:
    {
        decode_NR5G_RRC_MIB_Info_v1(hex_data, file_size, &index);
        *index_in = index;
        return 822;
    }
    case 0xB823:
    {
        decode_NR5G_RRC_Serving_Cell_Info_v4(hex_data, file_size, &index);
        *index_in = index;
        return 823;
    }
    case 0xB825:
    {
        decode_NR5G_RRC_Configuration_Info_v8(hex_data, file_size, &index);
        *index_in = index;
        return 825;
    }
    case 0xB826:
    {
        decode_NR5G_RRC_Supported_CA_Combos_v7(hex_data, file_size, &index);
        *index_in = index;
        return 826;
    }
    case 0xB840:
    {
        decode_NR5G_PDCP_DL_Data_Pdu_v6(hex_data, file_size, &index);
        *index_in = index;
        return 840;
    }
    case 0xB842:
    {
        decode_NR5G_PDCP_DL_Rbs_Stats_v5(hex_data, file_size, &index);
        *index_in = index;
        return 842;
    }
    case 0xB84B:
    {
        decode_NR5G_L2_DL_Config_v5(hex_data, file_size, &index);
        *index_in = index;
        return 2123;
    }
    case 0xB84D:
    {
        decode_NR5G_RLC_DL_Stats_v196608(hex_data, file_size, &index);
        *index_in = index;
        return 2125;
    }
    case 0xB84E:
    {
        decode_NR5G_RLC_DL_Status_PDU_v1(hex_data, file_size, &index);
        *index_in = index;
        return 2126;
    }
    case 0xB857:
    {
        decode_NR5G_L2_DL_DATA_PDU_v6(hex_data, file_size, &index);
        *index_in = index;
        return 2135;
    }
    case 0xB860:
    {
        decode_NR5G_PDCP_UL_Stats_v9(hex_data, file_size, &index);
        *index_in = index;
        return 2144;
    }
    case 0xB861:
    {
        decode_NR5G_PDCP_UL_Control_Pdu_v196609(hex_data, file_size, &index);
        *index_in = index;
        return 2161;
    }
    case 0xB868:
    {
        decode_NR5G_RLC_UL_Stats_v4(hex_data, file_size, &index);
        *index_in = index;
        return 2168;
    }
    case 0xB871:
    {
        decode_NR5G_L2_UL_Config_v5(hex_data, file_size, &index);
        *index_in = index;
        return 2171;
    }
    case 0xB872:
    {
        if(version_4B <= 4)
        {
            decode_NR5G_L2_UL_TB_v4(hex_data, file_size, &index);
        }
        else
        {
            decode_NR5G_L2_UL_TB_v196616(hex_data, file_size, &index);
        }
        *index_in = index;
        return 2178;
    }
    case 0xB873:
    {
        decode_NR5G_L2_UL_BSR_v196611(hex_data, file_size, &index);
        *index_in = index;
        return 2179;
    }
    case 0xB881:
    {
        decode_NR5G_MAC_UL_TB_Stats_v196609(hex_data, file_size, &index);
        *index_in = index;
        return 2181;
    }
    case 0xB885:
    {
        if(version_4B == 5)
        {
            decode_NR5G_MAC_DCI_Info_v131077(hex_data, file_size, &index);
        }
        else
        {
            decode_NR5G_MAC_DCI_Info_v196617(hex_data, file_size, &index);
        }
        *index_in = index;
        return 2181;
    }
    case 0xB886:
    {
        decode_NR5G_MAC_DL_TB_Report_v3(hex_data, file_size, &index);
        *index_in = index;
        return 2182;
    }
    case 0xB887:
    {
        if(version_4B == 5)
        {
            decode_NR5G_MAC_PDSCH_Status_v5(hex_data, file_size, &index);
        }
        else
        {
            decode_NR5G_MAC_PDSCH_Status_v196611(hex_data, file_size, &index);
        }
        
        *index_in = index;
        return 2183;
    }
    case 0xB888:
    {
        decode_NR5G_MAC_PDSCH_Stats_v196608(hex_data, file_size, &index);
        *index_in = index;
        return 2184;
    }
    case 0xB889:
    {
        decode_NR5G_MAC_RACH_Trigger_v196615(hex_data, file_size, &index);
        *index_in = index;
        return 2185;
    }
    case 0xB890:
    {
        decode_NR5G_MAC_CDRX_Events_Info_v131073(hex_data, file_size, &index);
        *index_in = index;
        return 2186;
    }
    case 0xB89B:
    {
        if(version_4B == 2)
        {
            decode_NR5G_MAC_UCI_Information_v2(hex_data, file_size, &index);
        }
        else
        {
            decode_NR5G_MAC_UCI_Information_v196608(hex_data, file_size, &index);
        }
        *index_in = index;
        return 2187;
    }
    case 0xB89C:
    {
        decode_NR5G_MAC_Flow_Control_v131073(hex_data, file_size, &index);
        *index_in = index;
        return 2188;
    }
    case 0xB8A7:
    {
        if(version_4B == 131073)
        {
            decode_NR5G_MAC_CSF_Report_v131073(hex_data, file_size, &index);
        }
        else
        {
            decode_NR5G_MAC_CSF_Report_v196613(hex_data, file_size, &index);
        }
        *index_in = index;
        return 2186;
    }
    case 0xB97F:
    {
        decode_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_v131073(hex_data, file_size, &index);
        *index_in = index;
        return 999;
    }
    case 0xB821:
    {
        if(version_4B == 20)// we should use rrc_ver1 rrc_ver2 rrc_ver3 to distinguish the version
        {
            decode_NR5G_RRC_OTA_Packet_v1720(hex_data, file_size, &index);
        }
        else
        {
            decode_NR5G_RRC_OTA_Packet_v1660(hex_data, file_size, &index);
        }
        *index_in = index;
        return 2081;
    }
    case 0xB88A:
    {
        decode_NR5G_MAC_RACH_Attempt_v196616(hex_data, file_size, &index);
        *index_in = index;
        return 2186;
    }
    case 0xB896:
    {
        decode_NR5G_MAC_UCI_Payload_Information_v196608(hex_data, file_size, &index);
        *index_in = index;
        return 896;
    }
    case 0xB800:
    {
        // printf("in B800 branch\n");
        decode_NAS_800_v1(hex_data, file_size, &index, msg_len, time_in_us_total);
        *index_in = index;
        return 800;
    }
    case 0xB80A:
    {
        // printf("in B80A branch\n");
        decode_NAS_80A_v1(hex_data, file_size, &index, msg_len, time_in_us_total);
        *index_in = index;
        return 80;
    }
    case 0xB869:
    {
        decode_NR5G_RLC_UL_Status_PDU_v196609(hex_data, file_size, &index);
        *index_in = index;
        return 869;
    }
    case 0xB96F:
    {
        // printf("in B96F branch\n");
        decode_NR5G_ML1_Searcher_Conn_Eval_v131075(hex_data, file_size, &index);
        *index_in = index;
        return 969;
    }
    case 0xB98F:
    {
        decode_NR5G_ML1_Antenna_Switch_Diversity_v131074(hex_data, file_size, &index);
        *index_in = index;
        return 989;
    }
    case 0xB8DD:
    {
        // printf("in B8DD branch\n");
        decode_NR5G_LL1_FW_Serving_FTL_v7(hex_data, file_size, &index);
        *index_in = index;
        return 8;
    }
    case 0xB9BF:
    {
        // printf("in B9BF branch\n");
        decode_NR5G_ML1_Search_HO_Acq_Confirm_v131079(hex_data, file_size, &index);
        *index_in = index;
        return 999;
    }
    case 0xB870:
    {
        decode_NR5G_L2_UL_Data_PDU_v196611(hex_data, file_size, &index);
        *index_in = index;
        return 40;
    }
    case 0xB8C9:
    {
        decode_NR5G_LL1_FW_RX_Control_AGC_v131072(hex_data, file_size, &index);
        *index_in = index;
        return 41;
    }
    case 0xB883:
    {
        decode_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623(hex_data, file_size, &index);
        *index_in = index;
        return 883;
    }
    default:
    {
        printf("Other_logcode\n");
        *index_in = index;
        // fclose(fp);
        return 999;
    }
    }

    return 0;
}