#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-S-H.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-R-H.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-Carrier-Header.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-PUSCH.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-SRS-H.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-SRS-Payload.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-PRACH.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-PUCCH-H.h"
#include "NR5G-MAC-UL-Physical-Channel-Schedule-Report-v196623-PUCCH-Payload.h"

void convert_S_H_B883_v196623(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 4;
}

void convert_R_H_B883_v196623(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
}

void convert_Carrier_Header_B883_v196623(uint8_t *hex_data, int *index)
{
    *index += 4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 6;
}

void convert_PUSCH_B883_v196623(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    *index += 8;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_SRS_H_B883_v196623(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_SRS_Payload_B883_v196623(uint8_t *hex_data, int *index)
{
    *index += 8;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

void convert_PRACH_B883_v196623(uint8_t *hex_data, int *index)
{
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 2;
}

void convert_PUCCH_H_B883_v196623(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_PUCCH_Payload_B883_v196623(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    *index += 8;
}

void decode_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_Carrier_Header_t *t_Carrier_Header = 0;
    asn_dec_rval_t rval_Carrier_Header;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUSCH_t *t_PUSCH = 0;
    asn_dec_rval_t rval_PUSCH;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_SRS_H_t *t_SRS_H = 0;
    asn_dec_rval_t rval_SRS_H;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_SRS_Payload_t *t_SRS_Payload = 0;
    asn_dec_rval_t rval_SRS_Payload;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PRACH_t *t_PRACH = 0;
    asn_dec_rval_t rval_PRACH;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUCCH_H_t *t_PUCCH_H = 0;
    asn_dec_rval_t rval_PUCCH_H;
    NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUCCH_Payload_t *t_PUCCH_Payload = 0;
    asn_dec_rval_t rval_PUCCH_Payload;

    /* S_H */
    int start_S_H = *index;
    convert_S_H_B883_v196623(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_S_H, t_S_H);

    int num_records = hex_data[start_S_H + 7];

    for (int i = 0; i < num_records; i++)
    {
        /*R_H*/
        int start_R_H = *index;
        convert_R_H_B883_v196623(hex_data, index);
        int R_H_length = *index - start_R_H;

        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_R_H, (void **)&t_R_H, hex_data + start_R_H, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK)
        {
            printf("rval_R_H decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_R_H, t_R_H);

        int num_carriers = (hex_data[start_R_H + 2] & 0xFC) >> 2;

        for (int j = 0; j < num_carriers; j++)
        {
            /*Carrier_Header*/
            int start_Carrier_Header = *index;
            convert_Carrier_Header_B883_v196623(hex_data, index);
            int Carrier_Header_length = *index - start_Carrier_Header;

            rval_Carrier_Header = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_Carrier_Header, (void **)&t_Carrier_Header, hex_data + start_Carrier_Header, Carrier_Header_length, 0, 0);
            if (rval_Carrier_Header.code != RC_OK)
            {
                printf("rval_Carrier_Header decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_Carrier_Header, t_Carrier_Header);

            int phyhan_bit_mask = hex_data[start_Carrier_Header + 1] & 0x0F;

            if(phyhan_bit_mask == 1)
            {
                /*PUSCH_BM*/
                int start_PUSCH = *index;
                convert_PUSCH_B883_v196623(hex_data, index);
                int PUSCH_length = *index - start_PUSCH;
                rval_PUSCH = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUSCH, (void **)&t_PUSCH, hex_data + start_PUSCH, PUSCH_length, 0, 0);
                if (rval_PUSCH.code != RC_OK)
                {
                    printf("rval_PUSCH decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUSCH, t_PUSCH);

            }
            if(phyhan_bit_mask == 2)
            {
                /*PUCCH_BM*/
                int start_PUCCH_H = *index;
                convert_PUCCH_H_B883_v196623(hex_data, index);
                int PUCCH_H_length = *index - start_PUCCH_H;
                rval_PUCCH_H = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUCCH_H, (void **)&t_PUCCH_H, hex_data + start_PUCCH_H, PUCCH_H_length, 0, 0);
                if (rval_PUCCH_H.code != RC_OK)
                {
                    printf("rval_PUCCH_H decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUCCH_H, t_PUCCH_H);

                int num_pucch = hex_data[start_PUCCH_H];
                for (int k = 0; k < num_pucch; k++)
                {
                    /*PUCCH_payload*/
                    int start_PUCCH_Payload = *index;
                    convert_PUCCH_Payload_B883_v196623(hex_data, index);
                    int PUCCH_Payload_length = *index - start_PUCCH_Payload;
                    rval_PUCCH_Payload = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUCCH_Payload, (void **)&t_PUCCH_Payload, hex_data + start_PUCCH_Payload, PUCCH_Payload_length, 0, 0);
                    if (rval_PUCCH_Payload.code != RC_OK)
                    {
                        printf("rval_PUCCH_Payload decode error\n");
                    }
                    xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PUCCH_Payload, t_PUCCH_Payload);
                }
            }
            if (phyhan_bit_mask == 4)
            {
                /*SRS_BM*/
                int start_SRS_H = *index;
                convert_SRS_H_B883_v196623(hex_data, index);
                int SRS_H_length = *index - start_SRS_H;
                rval_SRS_H = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_SRS_H, (void **)&t_SRS_H, hex_data + start_SRS_H, SRS_H_length, 0, 0);
                if (rval_SRS_H.code != RC_OK)
                {
                    printf("rval_SRS_H decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_SRS_H, t_SRS_H);

                int num_srs = hex_data[start_SRS_H];
                for (int k = 0; k < num_srs; k++)
                {
                    /*SRS_Payload*/
                    int start_SRS_Payload = *index;
                    convert_SRS_Payload_B883_v196623(hex_data, index);
                    int SRS_Payload_length = *index - start_SRS_Payload;
                    rval_SRS_Payload = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_SRS_Payload, (void **)&t_SRS_Payload, hex_data + start_SRS_Payload, SRS_Payload_length, 0, 0);
                    if (rval_SRS_Payload.code != RC_OK)
                    {
                        printf("rval_SRS_Payload decode error\n");
                    }
                    xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_SRS_Payload, t_SRS_Payload);
                }
            }
            if(phyhan_bit_mask == 8)
            {
                /*PRACH_BM*/
                int start_PRACH = *index;
                convert_PRACH_B883_v196623(hex_data, index);
                int PRACH_length = *index - start_PRACH;
                rval_PRACH = uper_decode(0, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PRACH, (void **)&t_PRACH, hex_data + start_PRACH, PRACH_length, 0, 0);
                if (rval_PRACH.code != RC_OK)
                {
                    printf("rval_PRACH decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623_PRACH, t_PRACH);
            }
        }
    }
    printf("decode_NR5G_MAC_UL_Physical_Channel_Schedule_Report_v196623 completed\n");
}