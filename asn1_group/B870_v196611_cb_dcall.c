#include <stdio.h>
#include <stdint.h>
#include "NR5G-L2-UL-Data-PDU-v196611-S-H.h"
#include "NR5G-L2-UL-Data-PDU-v196611-LC.h"
#include "NR5G-L2-UL-Data-PDU-v196611-TTI-H.h"
#include "NR5G-L2-UL-Data-PDU-v196611-TB-H.h"
#include "NR5G-L2-UL-Data-PDU-v196611-LC-Packet-Info.h"
#include "NR5G-L2-UL-Data-PDU-v196611-PDU-Info.h"
#include "host.h"

void convert_S_H_B870_v196611(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 4;
}

void convert_LC_B870_v196611(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 5);
    *index += 25;
}

void convert_TTI_H_B870_v196611(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 4;
}

void convert_TB_H_B870_v196611(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_LC_Packet_Info_B870_v196611(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 6);
    convert_endianess(hex_data, index, 2);
    *index += 14;
    *index += 16;
    convert_endianess(hex_data, index, 2);
    *index += 2;
}

void convert_PDU_Info_B870_v196611(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void decode_NR5G_L2_UL_Data_PDU_v196611(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_L2_UL_Data_PDU_v196611_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_L2_UL_Data_PDU_v196611_LC_t *t_LC = 0;
    asn_dec_rval_t rval_LC;
    NR5G_L2_UL_Data_PDU_v196611_TTI_H_t *t_TTI_H = 0;
    asn_dec_rval_t rval_TTI_H;
    NR5G_L2_UL_Data_PDU_v196611_TB_H_t *t_TB_H = 0;
    asn_dec_rval_t rval_TB_H;
    NR5G_L2_UL_Data_PDU_v196611_LC_Packet_Info_t *t_LC_Packet_Info = 0;
    asn_dec_rval_t rval_LC_Packet_Info;
    NR5G_L2_UL_Data_PDU_v196611_PDU_Info_t *t_PDU_Info = 0;
    asn_dec_rval_t rval_PDU_Info;

    // S-H
    int start_S_H = *index;
    convert_S_H_B870_v196611(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_S_H, t_S_H);

    // LC
    int num_LC = (hex_data[start_S_H + 4] & 0xF0) >> 4;
    for (int i = 0; i < num_LC; i++)
    {
        printf("[%d]\n", i);
        int start_LC = *index;
        convert_LC_B870_v196611(hex_data, index);
        int LC_length = *index - start_LC;

        rval_LC = uper_decode(0, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_LC, (void **)&t_LC, hex_data + start_LC, LC_length, 0, 0);
        if (rval_LC.code != RC_OK)
        {
            printf("rval_LC decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_LC, t_LC);
    }

    //TTI
    int num_TTI = (hex_data[start_S_H + 4] & 0x0F);
    for (int i = 0; i < num_TTI; i++)
    {
        printf("[%d]\n", i);
        int start_TTI = *index;
        convert_TTI_H_B870_v196611(hex_data, index);
        int TTI_length = *index - start_TTI;

        rval_TTI_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_TTI_H, (void **)&t_TTI_H, hex_data + start_TTI, TTI_length, 0, 0);
        if (rval_TTI_H.code != RC_OK)
        {
            printf("rval_TTI_H decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_TTI_H, t_TTI_H);

        // TB Header
        int num_TB = (hex_data[start_TTI + 5] & 0xE0) >> 5;
        for (int j = 0; j < num_TB; j++)
        {
            printf("    [%d]\n", j);
            int start_TB = *index;
            convert_TB_H_B870_v196611(hex_data, index);
            int TB_length = *index - start_TB;

            rval_TB_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_TB_H, (void **)&t_TB_H, hex_data + start_TB, TB_length, 0, 0);
            if (rval_TB_H.code != RC_OK)
            {
                printf("rval_TB_H decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_TB_H, t_TB_H);

            // LC Packet Info
            int num_LC_Packet_Info = (hex_data[start_TB + 3] & 0x07);
            for (int k = 0; k < num_LC_Packet_Info; k++)
            {
                printf("        [%d]\n", k);
                int start_LC_Packet_Info = *index;
                convert_LC_Packet_Info_B870_v196611(hex_data, index);
                int LC_Packet_Info_length = *index - start_LC_Packet_Info;

                rval_LC_Packet_Info = uper_decode(0, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_LC_Packet_Info, (void **)&t_LC_Packet_Info, hex_data + start_LC_Packet_Info, LC_Packet_Info_length, 0, 0);
                if (rval_LC_Packet_Info.code != RC_OK)
                {
                    printf("rval_LC_Packet_Info decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_LC_Packet_Info, t_LC_Packet_Info);
                
                // PDU Info
                int pdu_info_count = (hex_data[start_LC_Packet_Info + 7] & 0x0F);
                for (int l = 0; l < pdu_info_count; l++)
                {
                    printf("            [%d]\n", l);
                    int start_PDU_Info = *index;
                    convert_PDU_Info_B870_v196611(hex_data, index);
                    int PDU_Info_length = *index - start_PDU_Info;

                    rval_PDU_Info = uper_decode(0, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_PDU_Info, (void **)&t_PDU_Info, hex_data + start_PDU_Info, PDU_Info_length, 0, 0);
                    if (rval_PDU_Info.code != RC_OK)
                    {
                        printf("rval_PDU_Info decode error\n");
                    }
                    xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_Data_PDU_v196611_PDU_Info, t_PDU_Info);
                }
            }
        }
    }
    printf("decode NR5G_L2_UL_Data_PDU_v196611 finished\n");
}

