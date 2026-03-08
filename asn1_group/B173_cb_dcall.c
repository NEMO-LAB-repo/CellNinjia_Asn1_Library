#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-PDSCH-Stat-Indication-S-H.h"
#include "LTE-ML1-PDSCH-Stat-Indication-R-H.h"
#include "LTE-ML1-PDSCH-Stat-Indication-TB.h"
#include "LTE-ML1-PDSCH-Stat-Indication-R-T.h"
#include "host.h"

void convert_S_H_B173(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_R_H_B173(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index+=10;
}

void convert_TB_B173(uint8_t *hex_data, int *index)
{
    *index+=4;
    convert_endianess(hex_data, index, 2);
    *index+=6;
}

void convert_R_T_B173(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void decode_B173(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    LTE_ML1_PDSCH_Stat_Indication_S_H_t *t_S_H=0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_PDSCH_Stat_Indication_R_H_t *t_R_H=0;
    asn_dec_rval_t rval_R_H;
    LTE_ML1_PDSCH_Stat_Indication_TB_t *t_TB=0;
    asn_dec_rval_t rval_TB;
    LTE_ML1_PDSCH_Stat_Indication_R_T_t *t_R_T=0;
    asn_dec_rval_t rval_R_T;
    
    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B173(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_S_H, t_S_H);   

    int num_of_record = (hex_data[start_S_H+1]);
    printf("num_of_record=%d\n",num_of_record);

    int firt_sub_frame_num = 0;
    int first_sys_frame_num = 0;

    for(int i=0;i<num_of_record;i++)
    {
        int start_record = *index;
        convert_R_H_B173(hex_data, index);
        int R_H_Length = *index-start_record;

        rval_R_H = uper_decode(0, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_R_H, (void **)&t_R_H, hex_data+start_record, R_H_Length, 0, 0);
        if(rval_R_H.code != RC_OK) {
            printf("rval_R_H decode error\n");
            exit(65);
        }
        
        xer_fprint(stdout, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_R_H, t_R_H); 
        if(i==0)
        {
            firt_sub_frame_num = t_R_H->subframe_number;
            first_sys_frame_num = t_R_H->frame_number;
        }

        int number_of_TB = (hex_data[start_record+4]);
        printf("number_of_TB=%d\n",number_of_TB);

        for(int j=0;j<2;j++)
        {
            if(number_of_TB==1 && j==1)
            {
                convert_TB_B173(hex_data, index);
                continue;
            }
            printf("[%d] TB\n",j);
            int start_TB = *index;
            convert_TB_B173(hex_data, index);
            int TB_Length = *index-start_TB;
            
            rval_TB = uper_decode(0, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_TB, (void **)&t_TB, hex_data+start_TB, TB_Length, 0, 0);
            if(rval_TB.code != RC_OK) {
                printf("rval_TB decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_TB, t_TB); 
        }

        int start_record_tail = *index;
        convert_R_T_B173(hex_data, index);
        int R_T_Length = *index-start_record_tail;

        rval_R_T = uper_decode(0, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_R_T, (void **)&t_R_T, hex_data+start_record_tail, R_T_Length, 0, 0);
        if(rval_R_T.code != RC_OK) {
            printf("rval_R_T decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_PDSCH_Stat_Indication_R_T, t_R_T); 
    }

    printf("decode_B173 over!!!!\n");
}