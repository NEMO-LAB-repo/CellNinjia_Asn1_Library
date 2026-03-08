#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-DCI-Information-Report-v48-S-H.h"
#include "LTE-ML1-DCI-Information-Report-v48-R-H.h"
#include "LTE-ML1-DCI-Information-Report-v48-R-UL.h"
#include "B16C_v48_cb_dcall.h"

void convert_S_H_B16C_v48(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_R_H_B16C_v48(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
}

void convert_R_UL_B16C_v48(uint8_t *hex_data, int *index)
{
    *index+=126;
}

void convert_R_DL_B16C_v48(uint8_t *hex_data, int *index)
{
    *index+=126;
}

void decode_B16C_v48(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    LTE_ML1_DCI_Information_Report_v48_S_H_t *t_S_H=0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_DCI_Information_Report_v48_R_H_t *t_R_H=0;
    asn_dec_rval_t rval_R_H;
    LTE_ML1_DCI_Information_Report_v48_R_UL_t *t_R_UL=0;
    asn_dec_rval_t rval_R_UL;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B16C_v48(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);

    int first_sub_frame_number = 0;
    int first_sys_frame_number = 0;

    for(int i=0;i<t_S_H->num_of_record;i++)
    {
        int start_record = *index;
        convert_R_H_B16C_v48(hex_data, index);
        int R_H_Length = *index-start_record;
        rval_R_H = uper_decode(0, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_H, (void **)&t_R_H, hex_data+start_record, R_H_Length, 0, 0);
        if(rval_R_H.code != RC_OK) {
            printf("rval_R_H decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_H, t_R_H); 

        
        if(i==0)
        {
            first_sub_frame_number = t_R_H->sub_frame_number;
            first_sys_frame_number = t_R_H->sys_frame_number;
        }

        if(t_R_H->num_ul_grant_info!=0)
        {
            int start_UL = *index;
            convert_R_UL_B16C_v48(hex_data, index);
            int R_UL_Length = *index-start_UL;
            rval_R_UL = uper_decode(0, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_UL, (void **)&t_R_UL, hex_data+start_UL, R_UL_Length, 0, 0);
            if(rval_R_UL.code != RC_OK) {
                printf("rval_R_UL decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_UL, t_R_UL); 
        }
        else
        {
            *index+=126;
        }
    }
    printf("decode B16C over!!!\n");
}