#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-UCI-Payload-Information-S-H.h"
#include "NR5G-MAC-UCI-Payload-Information-R-H.h"
#include "NR5G-MAC-UCI-Payload-Information-Channel-Info.h"
#include "host.h"

void convert_S_H_B896(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 4;
}

void convert_R_H_B896(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 4;
}

void convert_Channel_Info_B896(uint8_t *hex_data, int *index)
{
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 9;
}

void decode_NR5G_MAC_UCI_Payload_Information_v196608(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_UCI_Payload_Information_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_UCI_Payload_Information_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_UCI_Payload_Information_Channel_Info_t *t_Channel_Info = 0;
    asn_dec_rval_t rval_Channel_Info;

    /* S-H */
    int start_S_H = *index;
    convert_S_H_B896(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Payload_Information_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK) {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Payload_Information_S_H, t_S_H);

    int num_records = (hex_data[start_S_H + 7]);

    /* R-H */
    for (int i = 0; i < num_records; i++)
    {
        printf("[%d]\n", i);

        int start_R_H = *index;
        convert_R_H_B896(hex_data, index);
        int R_H_length = *index - start_R_H;

        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Payload_Information_R_H, (void **)&t_R_H, hex_data + start_R_H, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK) {
            printf("rval_R_H decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Payload_Information_R_H, t_R_H);

        int num_channels = (hex_data[start_R_H + 4] & 0x0F);

        for (int j = 0; j < num_channels; j++)
        {
            printf("  [%d]\n", j);

            int start_Channel_Info = *index;
            convert_Channel_Info_B896(hex_data, index);
            int Channel_Info_length = *index - start_Channel_Info;

            rval_Channel_Info = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Payload_Information_Channel_Info, (void **)&t_Channel_Info, hex_data + start_Channel_Info, Channel_Info_length, 0, 0);
            if (rval_Channel_Info.code != RC_OK) {
                printf("rval_Channel_Info decode error\n");
                return;
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Payload_Information_Channel_Info, t_Channel_Info);

            int num_harq_payload = (hex_data[start_Channel_Info + 8]);
            int num_sr_payload = (hex_data[start_Channel_Info + 9]);
            int num_csi_p1_payload = (hex_data[start_Channel_Info + 10]);
            int num_csi_p2_payload = (hex_data[start_Channel_Info + 11]);
            
            int start_harq_payload = *index;
            if(num_harq_payload > 0) 
            {
                printf("    HARQ Payload: %02X%02X%02X%02X\n", hex_data[start_harq_payload], 
                                                            hex_data[start_harq_payload+1], 
                                                            hex_data[start_harq_payload+2], 
                                                            hex_data[start_harq_payload+3]);
                *index+=4;
            }
            


            int start_sr_payload = *index;
            if(num_sr_payload > 0) 
            {
                printf("    SR Payload: %02X%02X%02X%02X\n", hex_data[start_sr_payload], 
                                                            hex_data[start_sr_payload+1], 
                                                            hex_data[start_sr_payload+2], 
                                                            hex_data[start_sr_payload+3]);
                *index+=4;                                                            
            }


            int start_csi_p1_payload = *index;
            if(num_csi_p1_payload > 0) 
            {
                printf("    CSI P1 Payload: %02X%02X%02X%02X\n", hex_data[start_csi_p1_payload], 
                                                            hex_data[start_csi_p1_payload+1], 
                                                            hex_data[start_csi_p1_payload+2], 
                                                            hex_data[start_csi_p1_payload+3]);
                *index+=4;                                                            
            }


            int start_csi_p2_payload = *index;
            if(num_csi_p2_payload > 0) 
            {
                printf("    CSI P2 Payload: %02X%02X%02X%02X\n", hex_data[start_csi_p2_payload], 
                                                            hex_data[start_csi_p2_payload+1], 
                                                            hex_data[start_csi_p2_payload+2], 
                                                            hex_data[start_csi_p2_payload+3]);
                *index+=4;                                                            
            }

        }
    }
    printf("decode_B896 over!!!\n");
}
