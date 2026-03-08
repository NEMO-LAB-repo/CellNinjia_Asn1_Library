#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-L2-UL-BSR-S-H.h"
#include "NR5G-L2-UL-BSR-TTI.h"
#include "host.h"

void convert_S_H_B873(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_TTI_B873(uint8_t *hex_data, int *index)
{
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 4);
    *index+=3;
}

void decode_NR5G_L2_UL_BSR_v196611(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_L2_UL_BSR_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_L2_UL_BSR_TTI_t *t_TTI = 0;
    asn_dec_rval_t rval_TTI;
    int start_S_H = *index;
    convert_S_H_B873(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_BSR_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        // return;
    }
    xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_BSR_S_H, t_S_H);

    int num_records = (hex_data[start_S_H+7] & 0x0F);

    /*TTI*/
    for (int i = 0; i < num_records; i++)
    {   
        printf("[%d]\n",i);

        int start_TTI = *index;
        convert_TTI_B873(hex_data, index);
        int TTI_length = *index - start_TTI;

        rval_TTI = uper_decode(0, &asn_DEF_NR5G_L2_UL_BSR_TTI, (void **)&t_TTI, hex_data + start_TTI, TTI_length, 0, 0);
        if (rval_TTI.code != RC_OK)
        {
            printf("rval_TTI decode error\n");
            // return;
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_BSR_TTI, t_TTI);

        int num_lcid = ((hex_data[start_TTI+6] & 0xF0)>>4);
        printf("    QOS LCID\n");
        for(int j=0;j<num_lcid;j++)
        {
            printf("     [%d] : %d\n", j, hex_data[*index + j]);
        }
        *index += num_lcid;

        // Extract the bitmask from hex_data
        int lcg_bitmask = ((hex_data[start_TTI+6] & 0x0F) << 4) | ((hex_data[start_TTI+7] & 0xF0) >> 4);
        int count = 0;
        for (int i = 0; i < 8; i++) 
        {
            if ((lcg_bitmask & (1 << i)) == (1 << i)) 
            {
                count++;
            }
        }

        if(count==1)
        {
            *index+=4;
        }
        else if(count==2)
        {
            *index+=8;
        }
        else
        {
            *index+=4;
        }

        int mce_type = ((hex_data[*index]));
        printf("    BSR MCE Buffer\n");
        printf("        MCE Type: %d\n", mce_type);
        if(mce_type == 62)
        {
            int length = (hex_data[*index+1]);
            int lcgx = (hex_data[*index+2]);
            int bsr_index_0 = (hex_data[*index+3]);
            int bsr_index_1 = (hex_data[*index+4]);
            *index+=5;
            printf("        length: %d\n", length);
            printf("        lcgx: %d\n", lcgx);
            printf("        bsr-index[0]: %d\n", bsr_index_0);
            printf("        bsr-index[1]: %d\n", bsr_index_1);
        }
        else if(mce_type == 61)
        {
            int bsr_lcg_raw = (hex_data[*index+1]&0xE0)>>5;
            int bsr_index = (hex_data[*index+1]&0x1F);
            *index+=2; 
            printf("        bsr-lcg-raw: %d\n", bsr_lcg_raw);
            printf("        bsr-index: %d\n", bsr_index);
        }
        else
        {
            *index+=2;
        }
    }
    printf("decode over!!!\n");
}