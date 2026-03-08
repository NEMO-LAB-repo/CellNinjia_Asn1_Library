#include <stdio.h>
#include <stdint.h>
#include "NR5G-LL1-FW-RX-Control-AGC-v131072-S-H.h"
#include "NR5G-LL1-FW-RX-Control-AGC-v131072-AGC-Record.h"
#include "host.h"

void convert_S_H_B8C9_v131072(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 8;
}

void convert_AGC_Record_B8C9_v131072(uint8_t *hex_data, int *index)
{
    *index += 4; // Skip the first four bytes
    convert_endianess(hex_data, index, 4); // Convert the next four bytes
}

void decode_NR5G_LL1_FW_RX_Control_AGC_v131072(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_LL1_FW_RX_Control_AGC_v131072_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_LL1_FW_RX_Control_AGC_v131072_AGC_Record_t *t_AGC_Record = 0;
    asn_dec_rval_t rval_AGC_Record;

    // S-H
    int start_S_H = *index;
    convert_S_H_B8C9_v131072(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_LL1_FW_RX_Control_AGC_v131072_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_LL1_FW_RX_Control_AGC_v131072_S_H, t_S_H);

    int start_record = *index;
    int all_record_length = (hex_data[start_S_H + 14] << 8) | (hex_data[start_S_H + 13]);
    printf("all_record_length = %d\n", all_record_length);

    while(all_record_length-4>0)
    {
        int start_record = *index;

        int code_cur = hex_data[start_record];
        int length_cur = (hex_data[start_record + 1]);

        if(code_cur == 0xFC)
        {
            printf("Code: FULL_PKT\n");
            printf("Length: %d\n", length_cur);
            *index += 4;
            all_record_length -= 4;
        }
        else if(code_cur == 0xFD)
        {
            printf("Code: Discard_PKT\n");
            printf("Length: %d\n", length_cur);
            *index += 4;
            return;
        }
        else if(code_cur == 0xFE)
        {
            printf("Code: PAD_PKT\n");
            printf("Length: %d\n", length_cur);
            *index += 4;
            all_record_length -= length_cur;
        }
        else if(code_cur == 0x04)
        {
            printf("Code: AGC_Record\n");
            printf("Length: %d\n", length_cur);

            *index+=4;

            int start_AGC_Record = *index;
            convert_AGC_Record_B8C9_v131072(hex_data, index);
            int AGC_Record_length = *index - start_AGC_Record;

            rval_AGC_Record = uper_decode(0, &asn_DEF_NR5G_LL1_FW_RX_Control_AGC_v131072_AGC_Record, (void **)&t_AGC_Record, hex_data + start_AGC_Record, AGC_Record_length, 0, 0);
            if (rval_AGC_Record.code != RC_OK)
            {
                printf("rval_AGC_Record decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_LL1_FW_RX_Control_AGC_v131072_AGC_Record, t_AGC_Record);

            *index+=(length_cur-4-8);
            all_record_length -= length_cur;
        }
        else
        {
            printf("Unknown code: %02X\n", code_cur);
            return;
        }
    }
    printf("decode NR5G_LL1_FW_RX_Control_AGC_v131072 done\n");
}