#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-Flow-Control-S-H.h"
#include "NR5G-MAC-Flow-Control-R-H.h"
#include "NR5G-MAC-Flow-Control-MTPL.h"
#include "NR5G-MAC-Flow-Control-PUCCH-BACKOFF.h"
#include "NR5G-MAC-Flow-Control-UL-BACKOFF.h"
#include "host.h"

void convert_S_H_B89C(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 12;
}

void convert_R_H_B89C(uint8_t *hex_data, int *index)
{
    *index += 1;
}

void convert_MTPL_B89C(uint8_t *hex_data, int *index)
{
    *index += 15;
    convert_endianess(hex_data, index, 2);
    *index += 10;
}

void convert_PUCCH_BACKOFF_B89C(uint8_t *hex_data, int *index)
{
    *index += 11;
    convert_endianess(hex_data, index, 2);
    *index += 14;
}

void convert_UL_BACKOFF_B89C(uint8_t *hex_data, int *index)
{
    *index += 19;
    convert_endianess(hex_data, index, 2);
    *index += 6;
}

void decode_NR5G_MAC_Flow_Control_v131073(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_Flow_Control_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_Flow_Control_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_Flow_Control_MTPL_t *t_MTPL = 0;
    asn_dec_rval_t rval_MTPL;
    NR5G_MAC_Flow_Control_PUCCH_BACKOFF_t *t_PUCCH_BACKOFF = 0;
    asn_dec_rval_t rval_PUCCH_BACKOFF;
    NR5G_MAC_Flow_Control_UL_BACKOFF_t *t_UL_BACKOFF = 0;
    asn_dec_rval_t rval_UL_BACKOFF;

    /*S-H*/
    int start_S_H = *index;
    convert_S_H_B89C(hex_data, index);
    int S_H_length = *index - start_S_H;
    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_Flow_Control_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_Flow_Control_S_H, t_S_H);

    int num_records = (hex_data[start_S_H + 15]);
    
    /*R-H*/
    for(int i=0;i<num_records;i++)
    {
        printf("[%d]\n",i);
        int start_R_H = *index;
        convert_R_H_B89C(hex_data, index);
        int R_H_length = *index - start_R_H;
        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_Flow_Control_R_H, (void **)&t_R_H, hex_data + start_R_H, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK)
        {
            printf("rval_R_H decode error\n");
            return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_Flow_Control_R_H, t_R_H);

        int fc_reason = hex_data[start_R_H] & 0x0F;

        if(fc_reason==0)
        {
            /*UL-BACKOFF*/
            int start_UL_BACKOFF = *index;
            convert_UL_BACKOFF_B89C(hex_data, index);
            int UL_BACKOFF_length = *index - start_UL_BACKOFF;
            rval_UL_BACKOFF = uper_decode(0, &asn_DEF_NR5G_MAC_Flow_Control_UL_BACKOFF, (void **)&t_UL_BACKOFF, hex_data + start_UL_BACKOFF, UL_BACKOFF_length, 0, 0);
            if (rval_UL_BACKOFF.code != RC_OK)
            {
                printf("rval_UL_BACKOFF decode error\n");
                return;
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_Flow_Control_UL_BACKOFF, t_UL_BACKOFF);
        }
        else if(fc_reason==1)
        {
            /*PUCCH-BACKOFF*/
            int start_PUCCH_BACKOFF = *index;
            convert_PUCCH_BACKOFF_B89C(hex_data, index);
            int PUCCH_BACKOFF_length = *index - start_PUCCH_BACKOFF;
            rval_PUCCH_BACKOFF = uper_decode(0, &asn_DEF_NR5G_MAC_Flow_Control_PUCCH_BACKOFF, (void **)&t_PUCCH_BACKOFF, hex_data + start_PUCCH_BACKOFF, PUCCH_BACKOFF_length, 0, 0);
            if (rval_PUCCH_BACKOFF.code != RC_OK)
            {
                printf("rval_PUCCH_BACKOFF decode error\n");
                return;
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_Flow_Control_PUCCH_BACKOFF, t_PUCCH_BACKOFF);
        }
        else if(fc_reason==2)
        {
            /*MTPL*/
            int start_MTPL = *index;
            convert_MTPL_B89C(hex_data, index);
            int MTPL_length = *index - start_MTPL;
            rval_MTPL = uper_decode(0, &asn_DEF_NR5G_MAC_Flow_Control_MTPL, (void **)&t_MTPL, hex_data + start_MTPL, MTPL_length, 0, 0);
            if (rval_MTPL.code != RC_OK)
            {
                printf("rval_MTPL decode error\n");
                return;
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_Flow_Control_MTPL, t_MTPL);
        }
        else
        {
            printf("Unknown Flow Control Reason\n");
            *index+=27;
            return;
        }
    }
    printf("decode_B89C over!!!!\n");

}