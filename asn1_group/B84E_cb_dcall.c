#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RLC-DL-Status-PDU-S-H.h"
#include "NR5G-RLC-DL-Status-PDU-PDU-H.h"
#include "host.h"

void convert_S_H_B84E(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_PDU_H_B84E(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 4;
}

void decode_NR5G_RLC_DL_Status_PDU_v1(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RLC_DL_Status_PDU_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_RLC_DL_Status_PDU_PDU_H_t *t_PDU_H = 0;
    asn_dec_rval_t rval_PDU_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B84E(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RLC_DL_Status_PDU_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RLC_DL_Status_PDU_S_H, t_S_H);

    long long num_status_pdu = ((hex_data[start_S_H + 4] << 24) | (hex_data[start_S_H + 5] << 16) | (hex_data[start_S_H + 6] << 8) | (hex_data[start_S_H + 7]));

    /*PDU H*/
    for (int i = 0; i < num_status_pdu; i++)
    {
        int start_PDU_H = *index;
        convert_PDU_H_B84E(hex_data, index);
        int PDU_H_length = *index - start_PDU_H;

        rval_PDU_H = uper_decode(0, &asn_DEF_NR5G_RLC_DL_Status_PDU_PDU_H, (void **)&t_PDU_H, hex_data + start_PDU_H, PDU_H_length, 0, 0);
        if (rval_PDU_H.code != RC_OK)
        {
            printf("rval_PDU_H decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RLC_DL_Status_PDU_PDU_H, t_PDU_H);

        int status_pdu_size = hex_data[start_PDU_H + 6];
        int start_PDU_Content = *index;

        printf("<NR5G-RLC-DL-Status-PDU-Content>\n");

        if (status_pdu_size >= 3)
        {
            int ack_sn_part1 = hex_data[start_PDU_Content] & 0x0F;
            int ack_sn_part2 = hex_data[start_PDU_Content + 1];
            int ack_sn_part3 = ((hex_data[start_PDU_Content + 2] & 0xFC) >> 2);
            int E1 = ((hex_data[start_PDU_Content + 2] & 0x02) >> 1);

            printf("  <ack_sn_part1>%d</ack_sn_part1>\n", ack_sn_part1);
            printf("  <ack_sn_part2>%d</ack_sn_part2>\n", ack_sn_part2);
            printf("  <ack_sn_part3>%d</ack_sn_part3>\n", ack_sn_part3);
            printf("  <Header E1>%d</Header E1>\n", E1);

            *index += 3;

            if (status_pdu_size > 6)
            {
                int nack_sn_part1 = hex_data[start_PDU_Content + 3];
                int nack_sn_part2 = hex_data[start_PDU_Content + 4];
                int nack_sn_part3 = (hex_data[start_PDU_Content + 5] & 0xC0) >> 6;
                int NACK_E1 = (hex_data[start_PDU_Content + 5] & 0x20) >> 5;
                int NACK_E2 = (hex_data[start_PDU_Content + 5] & 0x10) >> 4;
                int NACK_E3 = (hex_data[start_PDU_Content + 5] & 0x08) >> 3;

                printf("  <nack_sn_part1>%d</nack_sn_part1>\n", nack_sn_part1);
                printf("  <nack_sn_part2>%d</nack_sn_part2>\n", nack_sn_part2);
                printf("  <nack_sn_part3>%d</nack_sn_part3>\n", nack_sn_part3);
                printf("  <NACK_E1>%d</NACK_E1>\n", NACK_E1);
                printf("  <NACK_E2>%d</NACK_E2>\n", NACK_E2);
                printf("  <NACK_E3>%d</NACK_E3>\n", NACK_E3);

                *index += 3;
                int nack_range = 0;
                if (status_pdu_size == 7) /*7*/
                {
                    nack_range = hex_data[start_PDU_Content + 6];
                    printf("  <NACK_range>%d</NACK_range>\n", nack_range);
                    *index += 1;
                }
                else if (status_pdu_size > 7) /*10*/
                {
                    int SO_Start = (hex_data[start_PDU_Content + 6] << 8) | (hex_data[start_PDU_Content + 7]);
                    int SO_End = (hex_data[start_PDU_Content + 8] << 8) | (hex_data[start_PDU_Content + 9]);

                    printf("  <SO_Start>%d</SO_Start>\n", SO_Start);
                    printf("  <SO_End>%d</SO_End>\n", SO_End);
                    *index += 4;

                    if (status_pdu_size > 10) /*11*/
                    {
                        nack_range = hex_data[start_PDU_Content + 10];
                        printf("  <NACK_range>%d</NACK_range>\n", nack_range);
                        *index += 1;
                    }
                }
            }
            printf("</NR5G-RLC-DL-Status-PDU-Content>\n");
        }
    }

    printf("decode_B84E over!!!!\n");
    return;
}