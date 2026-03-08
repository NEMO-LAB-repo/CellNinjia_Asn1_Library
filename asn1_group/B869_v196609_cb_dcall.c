#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-RLC-UL-Status-PDU-S-H.h"
#include "NR5G-RLC-UL-Status-PDU-PDUContent.h"
#include "host.h"

void convert_S_H_B869_v196609(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 4;
}

void convert_PDUContent_B869_v196609(uint8_t *hex_data, int *index)
{
    *index += 2;                           // Skip the first two bytes
    convert_endianess(hex_data, index, 2); // Convert the next two bytes
    *index += 2;                           // Skip the next two bytes
    convert_endianess(hex_data, index, 2); // Convert the next two bytes
    *index += 12;                          // Skip the next two bytes
}

void decode_NR5G_RLC_UL_Status_PDU_v196609(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_RLC_UL_Status_PDU_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_RLC_UL_Status_PDU_PDUContent_t *t_PDUContent = 0;
    asn_dec_rval_t rval_PDUContent;

    // S-H
    int start_S_H = *index;
    convert_S_H_B869_v196609(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_RLC_UL_Status_PDU_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_RLC_UL_Status_PDU_S_H, t_S_H);

    // PDUContent
    int num_records = (hex_data[start_S_H + 4]);
    for (int i = 0; i < num_records; i++)
    {
        printf("[%d]\n", i);
        int start_PDUContent = *index;
        convert_PDUContent_B869_v196609(hex_data, index);
        int PDUContent_length = *index - start_PDUContent;

        rval_PDUContent = uper_decode(0, &asn_DEF_NR5G_RLC_UL_Status_PDU_PDUContent, (void **)&t_PDUContent, hex_data + start_PDUContent, PDUContent_length, 0, 0);
        if (rval_PDUContent.code != RC_OK)
        {
            printf("rval_PDUContent decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_RLC_UL_Status_PDU_PDUContent, t_PDUContent);

        printf("<NR5G-RLC-UL-Status-PDU-PDUContent-Payload>\n");

        int sn_length = (hex_data[start_PDUContent + 4] & 0x40) >> 6; // Length of SN field
        int pdu_type = (hex_data[start_PDUContent + 6] & 0x02) >> 1;  // PDU type
        int size = (hex_data[start_PDUContent + 5] & 0xFE) >> 1;      // Size of the PDU
        int pad_size = (hex_data[start_PDUContent + 7] & 0x60)>>5;       // Padding size

        int ack_sn_part1 = 0;
        int ack_sn_part2 = 0;
        int ack_sn_part3 = 0;
        int header_e1 = 0;

        if (sn_length == 0) // 12
        {
            ack_sn_part1 = hex_data[start_PDUContent + 20] & 0x0F;
            ack_sn_part2 = hex_data[start_PDUContent + 21] & 0xFF;
            int ack_sn_12bits  = (ack_sn_part1 << 8) | ack_sn_part2;
            header_e1 = (hex_data[start_PDUContent + 22] & 0x80) >> 7;
            printf("    ACK SN 12 bits = %d\n    header_e1 = %d\n", ack_sn_12bits, header_e1);
        }
        else if (sn_length == 1) // 18
        {
            ack_sn_part1 = hex_data[start_PDUContent + 20] & 0x0F;
            ack_sn_part2 = hex_data[start_PDUContent + 21] & 0xFF;
            ack_sn_part3 = (hex_data[start_PDUContent + 22] & 0xFC) >> 2;

            int ack_sn_18bits = (ack_sn_part1 << 14) | (ack_sn_part2 << 6) | ack_sn_part3;
            header_e1 = (hex_data[start_PDUContent + 22] & 0x02) >> 1;
            printf("    ACK SN 18 bits = %d\n    header_e1 = %d\n", ack_sn_18bits, header_e1);
        }
        else
        {
            printf("Error: Invalid SN length %d\n", sn_length);
        }

        *index += 3;
        int start_payload = *index;

        if (pdu_type == 0) // ack_only
        {
            for (int j = 0; j < pad_size; j++)
            {
                printf("    Pad Payload [%d]: %d\n", j, hex_data[start_payload + j]);
            }
            *index += pad_size;
        }
        else // nack
        {
            printf("    NACK SN Set\n");
            int index_nack = 0;
            int nack_sn_set_index = 0;
            while (index_nack < size-3)
            {
                printf("    [%d]\n", nack_sn_set_index);
                nack_sn_set_index++;

                int nack_sn_part1_value = hex_data[start_payload + index_nack] & 0xFF;
                int nack_sn_18Bits_part2_value = hex_data[start_payload + index_nack + 1] & 0xFF;
                int nack_sn_part3_value = (hex_data[start_payload + index_nack + 2] & 0xC0) >> 6;

                int nack_sn_18bits = (nack_sn_part1_value << 10) | (nack_sn_18Bits_part2_value << 2) | nack_sn_part3_value;

                int E1 = (hex_data[start_payload + index_nack + 2] & 0x20) >> 5;
                int E2 = (hex_data[start_payload + index_nack + 2] & 0x10) >> 4;
                int E3 = (hex_data[start_payload + index_nack + 2] & 0x08) >> 3;
                int R = (hex_data[start_payload + index_nack + 2] & 0x04) >> 2;

                // printf("      NACK SN Part 1: %d\n", nack_sn_part1_value);
                // printf("      NACK SN Part 2: %d\n", nack_sn_18Bits_part2_value);
                // printf("      NACK SN Part 3: %d\n", nack_sn_part3_value);
                printf("      NACK SN 18 bits: %d\n", nack_sn_18bits);
                printf("      E1: %d\n      E2: %d\n      E3: %d\n      R: %d\n", E1, E2, E3, R);

                index_nack += 3;

                if (E2 == 1)
                {
                    int SO_Start = (hex_data[start_payload + index_nack]) << 8 | hex_data[start_payload + index_nack+1];
                    int SO_End = (hex_data[start_payload + index_nack + 2]) << 8 | hex_data[start_payload + index_nack + 3];
                    printf("      SO Start: %d\n      SO End: %d\n", SO_Start, SO_End);
                    index_nack += 4;
                }
                if (E3 == 1)
                {
                    int nack_range = hex_data[start_payload + index_nack];
                    printf("      NACK Range: %d\n", nack_range);
                    index_nack++;
                }
            }

            *index += (size-3);
            int start_nack_pad_payload = *index;
            for (int j = 0; j < pad_size; j++)
            {
                printf("      Pad Payload [%d]: %d\n", j, hex_data[start_nack_pad_payload + j]);
            }
            *index += pad_size;
        }
        printf("</NR5G-RLC-UL-Status-PDU-PDUContent-Payload>\n");
    }
    printf("decode finished\n");
}