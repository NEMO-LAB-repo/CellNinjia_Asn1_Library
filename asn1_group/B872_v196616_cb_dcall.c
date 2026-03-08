#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-L2-UL-TB-S-H-v196616.h"
#include "NR5G-L2-UL-TB-TTI-H-v196616.h"
#include "NR5G-L2-UL-TB-Content-v196616.h"
#include "host.h"

void convert_S_H_B872_v196616(uint8_t *hex_data, int *index)
{
    *index+=8;
}

void convert_TTI_H_B872_v196616(uint8_t *hex_data, int *index)
{
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=4;
}

void convert_TB_B872_v196616(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=12;
}

void decode_NR5G_L2_UL_TB_v196616(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_L2_UL_TB_S_H_v196616_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_L2_UL_TB_TTI_H_v196616_t *t_TTI_H = 0;
    asn_dec_rval_t rval_TTI_H;
    NR5G_L2_UL_TB_Content_v196616_t *t_Content = 0;
    asn_dec_rval_t rval_Content;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B872_v196616(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_TB_S_H_v196616, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_TB_S_H_v196616, t_S_H);

    int num_tti = ((hex_data[start_S_H + 4] ));

    /*TTI H*/
    for (int i = 0; i < num_tti; i++)
    {
        int start_TTI = *index;
        convert_TTI_H_B872_v196616(hex_data, index);
        int TTI_length = *index - start_TTI;

        rval_TTI_H = uper_decode(0, &asn_DEF_NR5G_L2_UL_TB_TTI_H_v196616, (void **)&t_TTI_H, hex_data + start_TTI, TTI_length, 0, 0);
        if (rval_TTI_H.code != RC_OK)
        {
            printf("rval_TTI decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_TB_TTI_H_v196616, t_TTI_H);

        int num_tb = hex_data[start_TTI + 4] & 0x0F;

        for(int k=0;k<num_tb;k++)
        {
            int start_TB = *index;
            convert_TB_B872_v196616(hex_data, index);
            int TB_length = *index - start_TB;

            rval_Content = uper_decode(0, &asn_DEF_NR5G_L2_UL_TB_Content_v196616, (void **)&t_Content, hex_data + start_TB, TB_length, 0, 0);
            if (rval_Content.code != RC_OK)
            {
                printf("rval_Content decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_L2_UL_TB_Content_v196616, t_Content);

            int mce_length = (hex_data[start_TB + 20] & 0x3F);

            int step = 0;
            int start_mce = *index;
            int mce_type = 0;

            int bsr_lcg = -1;
            int buffersize[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
            
            printf("<McePayload>\n");
            while (step < mce_length)
            {
                // start decode
                mce_type = hex_data[start_mce + step] & 0x3F;
                step++;

                if (mce_type == 62)
                {
                    // **********************L-BSR**********************
                    printf("<MCE Type>L-BSR</MCE Type>\n");
                    int l_bsr_length = hex_data[start_mce + step];
                    printf("    L-BSR-length=%d\n", l_bsr_length);
                    step++;

                    bsr_lcg = hex_data[start_mce + step];
                    printf("LCGx=%d\n", bsr_lcg);

                    step++;
                    if (l_bsr_length >= 2)
                    {
                        for (int k = 0; k < (l_bsr_length - 1); k++)
                        {
                            buffersize[k] = hex_data[start_mce + step];
                            printf("    BSR Index[%d]=%d\n", k, buffersize[k]);
                            step++;
                        }
                    }
                }
                else if (mce_type == 61)
                {
                    // **********************S-BSR**********************
                    printf("<MCE Type>S-BSR</MCE Type>\n");
                    bsr_lcg = (hex_data[start_mce + step] & 0xE0) >> 5;
                    printf("    LCGx=%d\n", bsr_lcg);
                    buffersize[0] = hex_data[start_mce + step] & 0x1F;
                    printf("    BSR Index[0]=%d\n", buffersize[0]);
                    step++;
                }
                else if (mce_type == 57)
                {
                    printf("<MCE Type>S-PHR</MCE Type>\n");
                    // there is sth wrong here 
                    // so if first is l-bsr second is s-phr
                    // in the B872_report it will show 57 but not s-phr
                    // S-PHR
                    // step += 2;

                    int s_phr_ph = hex_data[start_mce + step] & 0x3F;
                    step++;
                    int s_phr_r = (hex_data[start_mce + step] & 0xC0) >> 6;
                    int s_phr_fc = hex_data[start_mce + step] & 0x3F;
                    step++;
                    printf("    PH=%d\n", s_phr_ph);
                    printf("    R=%d\n", s_phr_r);
                    printf("    FC=%d\n", s_phr_fc);
                }
                else
                {
                    // unknown52
                    printf("<MCE Type>unknown:%d</MCE Type>\n", mce_type);
                    step += mce_length;
                    // break;
                    // fp_B872 = fopen("B872_report.txt", "a+");
                    // fprintf(fp_B872, "unknown mce_type=%d\n", mce_type);
                    // fclose(fp_B872);
                }
            }
            printf("</McePayload>\n");
            *index += mce_length;
        }
    }
}