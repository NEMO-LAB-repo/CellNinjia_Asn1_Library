#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-L2-DL-DATA-PDU-S-H.h"
#include "NR5G-L2-DL-DATA-PDU-RB-Config.h"
#include "NR5G-L2-DL-DATA-PDU-TB-Data-Agg.h"
#include "host.h"

void convert_S_H_B857(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    *index += 2;
}

void convert_RB_B857(uint8_t *hex_data, int *index)
{
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 1;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_TB_B857(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
}

void decode_NR5G_L2_DL_DATA_PDU_v6(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_L2_DL_DATA_PDU_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_L2_DL_DATA_PDU_RB_Config_t *t_RB = 0;
    asn_dec_rval_t rval_RB;
    NR5G_L2_DL_DATA_PDU_TB_Data_Agg_t *t_TB = 0;
    asn_dec_rval_t rval_TB;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B857(hex_data, index);
    int S_H_length = *index - start_S_H; 

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_L2_DL_DATA_PDU_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_L2_DL_DATA_PDU_S_H, t_S_H);

    long long num_tb = ((hex_data[start_S_H + 4] << 24) | (hex_data[start_S_H + 5] << 16) | (hex_data[start_S_H + 6] << 8) | (hex_data[start_S_H + 7]));
    int num_lcid = (hex_data[start_S_H + 10]);

    /* RB Config */
    for (int i = 0; i < num_lcid; i++)
    {
        int start_RB = *index;
        convert_RB_B857(hex_data, index);
        int RB_length = *index - start_RB;

        rval_RB = uper_decode(0, &asn_DEF_NR5G_L2_DL_DATA_PDU_RB_Config, (void **)&t_RB, hex_data + start_RB, RB_length, 0, 0);
        if (rval_RB.code != RC_OK)
        {
            printf("rval_RB decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_DL_DATA_PDU_RB_Config, t_RB);
    }

    /*TB Data Agg*/
    for (int i = 0; i < num_tb; i++)
    {
        int start_TB = *index;
        convert_TB_B857(hex_data, index);
        int TB_length = *index - start_TB;

        rval_TB = uper_decode(0, &asn_DEF_NR5G_L2_DL_DATA_PDU_TB_Data_Agg, (void **)&t_TB, hex_data + start_TB, TB_length, 0, 0);
        if (rval_TB.code != RC_OK)
        {
            printf("rval_TB decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_DL_DATA_PDU_TB_Data_Agg, t_TB);

        long long num_logged_subheaders = ((hex_data[start_TB + 12] << 24) | (hex_data[start_TB + 13] << 16) | (hex_data[start_TB + 14] << 8) | (hex_data[start_TB + 15]));

        printf("num_logged_subheaders = %lld\n", num_logged_subheaders);
        printf("Raw bytes: %02X %02X %02X %02X\n", 
            hex_data[start_TB + 12], hex_data[start_TB + 13], 
            hex_data[start_TB + 14], hex_data[start_TB + 15]);

        /* Combined Headers */
        for (int k = 0; k < num_logged_subheaders; k++)
        {
            printf("<Combined-Header>\n[%d]\n",k);

            int start_combined_H = *index;
            int fill = (hex_data[start_combined_H] & 0x40) >> 6;
            int lcid = (hex_data[start_combined_H] & 0x0F);
            if (fill == 0)
            {
                int L8 = hex_data[start_combined_H + 1];
                int first_byte_rlc_header = hex_data[start_combined_H + 2];
                if (first_byte_rlc_header == 0)
                {
                    // 
                    printf("\t<Fill>%d</Fill>\n\t<LCID>%d</LCID>\n\t<L8>%d</L8>\n\t<First Byte RLC Header>%d</First Byte RLC Header>\n\t<Last 4 Bytes Raw>%02X%02X%02X%02X</Last 4 Bytes Raw>\n\t<First Byte PDCP Header>%d</First Byte PDCP Header>\n", 
                        fill, lcid, L8, first_byte_rlc_header, 
                        hex_data[start_combined_H + 3], hex_data[start_combined_H + 4], 
                        hex_data[start_combined_H + 5], hex_data[start_combined_H + 6], 
                        hex_data[start_combined_H + 7]);
                    
                    if (hex_data[start_combined_H + 7] == 0)
                    {
                        // L8 0 0
                        printf("\t<Last 2 Bytes Raw>%02X%02X</Last 2 Bytes Raw>\n", 
                            hex_data[start_combined_H + 8], hex_data[start_combined_H + 9]);
                    }
                    else
                    {
                        // L8 0 1
                        int pdcp_sn_18_bits = (hex_data[start_combined_H + 8] << 8) | (hex_data[start_combined_H + 9]);
                        printf("\t<PDCP SN 18 Bits>%d</PDCP SN 18 Bits>\n", pdcp_sn_18_bits);
                    }
                }
                else
                {
                    //L8 1
                    int RLC_sn_18_bits = ((hex_data[start_combined_H + 2] & 0x03) << 16) | (hex_data[start_combined_H + 3] << 8) | (hex_data[start_combined_H + 4]);
                    int first_byte_pdcp_header = hex_data[start_combined_H + 5];
                    printf("\t<Fill>%d</Fill>\n\t<LCID>%d</LCID>\n\t<L8>%d</L8>\n\t<First Byte RLC Header>%d</First Byte RLC Header>\n\t<RLC SN 18 Bits>%d</RLC SN 18 Bits>\n\t<First Byte PDCP Header>%d</First Byte PDCP Header>\n", 
                        fill, lcid, L8, first_byte_rlc_header, RLC_sn_18_bits, first_byte_pdcp_header);
                    
                    if (first_byte_pdcp_header == 0)
                    {
                        // L8 1 0
                        printf("\t<Last 2 Bytes Raw>%02X%02X</Last 2 Bytes Raw>\n", 
                            hex_data[start_combined_H + 6], hex_data[start_combined_H + 7]);
                    }
                    else
                    {
                        // L8 1 1
                        int pdcp_sn_18_bits = (hex_data[start_combined_H + 6] << 8) | (hex_data[start_combined_H + 7]);
                        printf("\t<PDCP SN 18 Bits>%d</PDCP SN 18 Bits>\n", pdcp_sn_18_bits);
                    }
                }
            }
            else if (fill == 1)
            {
                int L16 = (hex_data[start_combined_H + 1] << 8) | (hex_data[start_combined_H + 2]);
                int first_byte_rlc_header = hex_data[start_combined_H + 3];
                // L16 0
                if (first_byte_rlc_header == 0)
                {
                    printf("\t<Fill>%d</Fill>\n\t<LCID>%d</LCID>\n\t<L16>%d</L16>\n\t<First Byte RLC Header>%d</First Byte RLC Header>\n\t<Last 4 Bytes Raw>%02X%02X%02X%02X</Last 4 Bytes Raw>\n\t<First Byte PDCP Header>%d</First Byte PDCP Header>\n", 
                        fill, lcid, L16, first_byte_rlc_header, 
                        hex_data[start_combined_H + 4], hex_data[start_combined_H + 5], 
                        hex_data[start_combined_H + 6], hex_data[start_combined_H + 7], 
                        hex_data[start_combined_H + 8]);
                    
                    if (hex_data[start_combined_H + 8] == 0)
                    {
                        // L16 0 0
                        printf("\t<Last 2 Bytes Raw>%02X%02X</Last 2 Bytes Raw>\n", 
                            hex_data[start_combined_H + 9], hex_data[start_combined_H + 10]);
                    }
                    else
                    {
                        // L16 0 1
                        int pdcp_sn_18_bits = (hex_data[start_combined_H + 9] << 8) | (hex_data[start_combined_H + 10]);
                        printf("\t<PDCP SN 18 Bits>%d</PDCP SN 18 Bits>\n", pdcp_sn_18_bits);
                    }
                }
                else
                {
                    //L16 1
                    int RLC_sn_18_bits = ((hex_data[start_combined_H + 3] & 0x03) << 16) | (hex_data[start_combined_H + 4] << 8) | (hex_data[start_combined_H + 5]);
                    int first_byte_pdcp_header = hex_data[start_combined_H + 6];

                    printf("\t<Fill>%d</Fill>\n\t<LCID>%d</LCID>\n\t<L16>%d</L16>\n\t<First Byte RLC Header>%d</First Byte RLC Header>\n\t<RLC SN 18 Bits>%d</RLC SN 18 Bits>\n\t<First Byte PDCP Header>%d</First Byte PDCP Header>\n", 
                        fill, lcid, L16, first_byte_rlc_header, RLC_sn_18_bits, first_byte_pdcp_header);

                    if (first_byte_pdcp_header == 0)
                    {
                        // L16 1 0
                        printf("\t<Last 2 Bytes Raw>%02X%02X</Last 2 Bytes Raw>\n", 
                            hex_data[start_combined_H + 7], hex_data[start_combined_H + 8]);
                    }
                    else
                    {
                        // L16 1 1
                        int pdcp_sn_18_bits = (hex_data[start_combined_H + 7] << 8) | (hex_data[start_combined_H + 8]);
                        printf("\t<PDCP SN 18 Bits>%d</PDCP SN 18 Bits>\n", pdcp_sn_18_bits);
                    }
                }
            }
            printf("</Combined-Header>\n");
            *index += 12;
        }
    }
    printf("decode over\n");
}