#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-MAC-Ul-Transport-Block-S-H.h"
#include "LTE-MAC-Ul-Transport-Block-Subpkt-H.h"
#include "LTE-MAC-Ul-Transport-Block-Sample-H.h"
#include "B064_cb_dcall.h"

void convert_S_H_B064(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_Subpkt_H_B064(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 1;
}

void convert_Sample_H_B064(uint8_t *hex_data, int *index)
{
    *index += 4;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 3;
}

void getBsrEventString(int num, char *output) {
    switch (num) {
        case 0:
            strcpy(output, "none");
            break;
        case 1:
            strcpy(output, "periodic");
            break;
        case 2:
            strcpy(output, "high-data-arrival");
            break;
        case 3:
            strcpy(output, "robustness-bsr");
            break;
        default:
            strcpy(output, "invalid");
            break;
    }
}
void getBsrTrigString(int num, char *output) {
    switch (num) {
        case 0:
            strcpy(output, "no-bsr");
            break;
        case 1:
            strcpy(output, "cacelled");
            break;
        case 2:
            strcpy(output, "l-bsr");
            break;
        case 3:
            strcpy(output, "s-bsr");
            break;
        case 4:
            strcpy(output, "pad-l-bsr");
            break;
        case 5:
            strcpy(output, "pad-s-bsr");
            break;
        case 6:
            strcpy(output, "pad-t-bsr");
            break;
        default:
            strcpy(output, "invalid");
            break;
    }
}

void decode_B064(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    LTE_MAC_Ul_Transport_Block_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_MAC_Ul_Transport_Block_Subpkt_H_t *t_Subpkt_H = 0;
    asn_dec_rval_t rval_Subpkt_H;
    LTE_MAC_Ul_Transport_Block_Sample_H_t *t_Sample_H = 0;
    asn_dec_rval_t rval_Sample_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B064(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_MAC_Ul_Transport_Block_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_MAC_Ul_Transport_Block_S_H, t_S_H);

    for (int i = 0; i < t_S_H->num_subpkt; i++)
    {
        int start_Subpkt_H = *index;
        convert_Subpkt_H_B064(hex_data, index);
        int Subpkt_H_length = *index - start_Subpkt_H;

        rval_Subpkt_H = uper_decode(0, &asn_DEF_LTE_MAC_Ul_Transport_Block_Subpkt_H, (void **)&t_Subpkt_H, hex_data + start_Subpkt_H, Subpkt_H_length, 0, 0);
        if (rval_Subpkt_H.code != RC_OK)
        {
            printf("rval_Subpkt_H decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_MAC_Ul_Transport_Block_Subpkt_H, t_Subpkt_H);

        int num_sample = hex_data[start_Subpkt_H + 4];
        printf("num_sample=%d\n", num_sample);

        int first_sub_frame_number = 0;
        int first_sys_frame_number = 0;
        
        for (int j = 0; j < t_Subpkt_H->num_samples; j++)
        {
            printf("Samples [%d]\n", j);
            int start_Sample_H = *index;
            convert_Sample_H_B064(hex_data, index);
            int Sample_H_length = *index - start_Sample_H;

            rval_Sample_H = uper_decode(0, &asn_DEF_LTE_MAC_Ul_Transport_Block_Sample_H, (void **)&t_Sample_H, hex_data + start_Sample_H, Sample_H_length, 0, 0);
            if (rval_Sample_H.code != RC_OK)
            {
                printf("rval_Sample_H decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_MAC_Ul_Transport_Block_Sample_H, t_Sample_H);
            
            if(j==0)
            {
                first_sub_frame_number = t_Sample_H->sub_fn;
                first_sys_frame_number = t_Sample_H->sfn;
            }
            int hdrlen = t_Sample_H->hdr_len;

            /*element*/
            int lcg = -1;
            int bsr_type = 0;
            int step = 0;
            int start_element=*index;
            int E = -1;
            int LCID_data = -1;
            int F = -1;
            int L = -1;
            int buffer_size[4] = {0, 0, 0, 0};
            while (step < hdrlen)
            {
                E = (hex_data[start_element+step] >> 5) & 1;
                //printf("E=%d\n", E);
                LCID_data = (hex_data[start_element+step]) & 31;
                //printf("LCID_data=%d\n", LCID_data);

                if (LCID_data == 29)
                {
                    //printf("***** Short BSR *****\n");
                    bsr_type = 1;
                }
                else if (LCID_data == 30)
                {
                    //printf("***** Long BSR *****\n");
                    bsr_type = 2;
                }
                else if (LCID_data == 31)
                {
                    if (bsr_type == 0)
                    {
                        //printf("***** Padding *****\n");
                        bsr_type = 3;
                    }
                }


                if (E == 1 && LCID_data <= 11)
                {
                    step += 1;
                    F = (hex_data[start_element+step] >> 7) & 1;
                    //printf("F=%d\n", F);
                    if (F == 0)
                    {
                        L = (hex_data[start_element+step]) & 127;
                        //printf("L=%d\n", L);
                    }
                    else if (F != 0)
                    {
                        step += 1;
                    }
                }
                else if (E == 0)
                {
                    step += 1;
                    if (bsr_type == 1)
                    {
                        lcg = (hex_data[start_element+step] >> 6) & 3;
                        buffer_size[lcg] = (hex_data[start_element+step] & 63);
                        //printf("BSR index saved\n");
                    }
                    else if (bsr_type == 2)
                    {
                        buffer_size[0] = (hex_data[start_element+step] & 0xFC) >> 2;
                        buffer_size[1] = ((hex_data[start_element+step] & 3) << 4) | ((hex_data[start_element+step + 1] & 0xF0) >> 4);
                        buffer_size[2] = ((hex_data[start_element+step + 1] & 15) << 2) | ((hex_data[start_element+step + 2] & 0xC0) >> 6);
                        buffer_size[3] = (hex_data[start_element+step + 2] & 63);
                        //printf("BSR index saved\n");
                        step += 2;
                    }
                    if (step + 1 > (hdrlen))
                    {
                        bsr_type -= bsr_type;
                    }
                    break;
                }
                step += 1;
            }
            *index += (hdrlen) ;

            char bsr_event[50];
            getBsrEventString(t_Sample_H->bsr_event, bsr_event);
            char bsr_trig[50];
            getBsrTrigString(t_Sample_H->bsr_trig, bsr_trig);
        }
    }
    printf("B064 over!!!!\n");
}