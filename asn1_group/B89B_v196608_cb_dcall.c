#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-UCI-Information-v196608-S-H.h"
#include "NR5G-MAC-UCI-Information-v196608-R-H.h"
#include "NR5G-MAC-UCI-Information-v196608-UCI-H.h"
#include "NR5G-MAC-UCI-Information-v196608-HARQ-DATA.h"
#include "NR5G-MAC-UCI-Information-v196608-SR-DATA.h"
#include "NR5G-MAC-UCI-Information-v196608-CSF-DATA.h"
#include "host.h"

void convert_S_H_B89B_v196608(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 4;
}

void convert_R_H_B89B_v196608(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 4;
}

void convert_UCI_H_B89B_v196608(uint8_t *hex_data, int *index)
{
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 5;
}

void convert_HARQ_DATA_B89B_v196608(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_SR_DATA_B89B_v196608(uint8_t *hex_data, int *index)
{
    *index += 4;
}
void convert_CSF_DATA_B89B_v196608(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void decode_NR5G_MAC_UCI_Information_v196608(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_UCI_Information_v196608_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_UCI_Information_v196608_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_UCI_Information_v196608_UCI_H_t *t_UCI_H = 0;
    asn_dec_rval_t rval_UCI_H;
    NR5G_MAC_UCI_Information_v196608_HARQ_DATA_t *t_HARQ_DATA = 0;
    asn_dec_rval_t rval_HARQ_DATA;
    NR5G_MAC_UCI_Information_v196608_SR_DATA_t *t_SR_DATA = 0;
    asn_dec_rval_t rval_SR_DATA;
    NR5G_MAC_UCI_Information_v196608_CSF_DATA_t *t_CSF_DATA = 0;
    asn_dec_rval_t rval_CSF_DATA;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B89B_v196608(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Information_v196608_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Information_v196608_S_H, t_S_H);

    int num_records = (hex_data[start_S_H + 7]);
    for (int i = 0; i < num_records; i++)
    {
        /*R_H*/
        printf("[%d]\n", i);
        int start_R_H = *index;
        convert_R_H_B89B_v196608(hex_data, index);
        int R_H_length = *index - start_R_H;

        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Information_v196608_R_H, (void **)&t_R_H, hex_data + start_R_H, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK)
        {
            printf("rval_R_H decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Information_v196608_R_H, t_R_H);

        int num_UCI = (hex_data[start_R_H + 4]);
        for (int j = 0; j < num_UCI; j++)
        {
            /*UCI_Info*/
            printf("  [%d]\n", j);
            int start_UCI_H = *index;
            convert_UCI_H_B89B_v196608(hex_data, index);
            int UCI_H_length = *index - start_UCI_H;
            rval_UCI_H = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Information_v196608_UCI_H, (void **)&t_UCI_H, hex_data + start_UCI_H, UCI_H_length, 0, 0);
            if (rval_UCI_H.code != RC_OK)
            {
                printf("rval_UCI_H decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Information_v196608_UCI_H, t_UCI_H);

            int num_HARQ = (hex_data[start_UCI_H + 4] & 0x07);
            int num_SR = (hex_data[start_UCI_H + 3] & 0x02) >> 1;
            int num_CSF = (hex_data[start_UCI_H + 3] & 0x30) >> 4;

            for(int k = 0; k < num_HARQ; k++)
            {
                /*HARQ_DATA*/
                printf("    [HARQ-%d]\n", k);
                int start_HARQ_DATA = *index;
                convert_HARQ_DATA_B89B_v196608(hex_data, index);
                int HARQ_DATA_length = *index - start_HARQ_DATA;
                rval_HARQ_DATA = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Information_v196608_HARQ_DATA, (void **)&t_HARQ_DATA, hex_data + start_HARQ_DATA, HARQ_DATA_length, 0, 0);
                if (rval_HARQ_DATA.code != RC_OK)
                {
                    printf("rval_HARQ_DATA decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Information_v196608_HARQ_DATA, t_HARQ_DATA);
            }

            for(int k = 0; k < num_SR; k++)
            {
                /*SR_DATA*/
                printf("    [SR-%d]\n", k);
                int start_SR_DATA = *index;
                convert_SR_DATA_B89B_v196608(hex_data, index);
                int SR_DATA_length = *index - start_SR_DATA;
                rval_SR_DATA = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Information_v196608_SR_DATA, (void **)&t_SR_DATA, hex_data + start_SR_DATA, SR_DATA_length, 0, 0);
                if (rval_SR_DATA.code != RC_OK)
                {
                    printf("rval_SR_DATA decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Information_v196608_SR_DATA, t_SR_DATA);
            }

            for(int k = 0; k < num_CSF; k++)
            {
                /*CSF_DATA*/
                printf("    [CSF-%d]\n", k);
                int start_CSF_DATA = *index;
                convert_CSF_DATA_B89B_v196608(hex_data, index);
                int CSF_DATA_length = *index - start_CSF_DATA;
                rval_CSF_DATA = uper_decode(0, &asn_DEF_NR5G_MAC_UCI_Information_v196608_CSF_DATA, (void **)&t_CSF_DATA, hex_data + start_CSF_DATA, CSF_DATA_length, 0, 0);
                if (rval_CSF_DATA.code != RC_OK)
                {
                    printf("rval_CSF_DATA decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_UCI_Information_v196608_CSF_DATA, t_CSF_DATA);
            }
        }
    }
    printf("Decoding NR5G MAC UCI Information v196608 completed.\n");
}