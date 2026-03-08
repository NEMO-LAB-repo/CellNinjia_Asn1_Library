#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "DCIReport.h"
#include "RecordHeader.h"
#include "DCIUL.h"
#include "DCIDL.h"
#include "host.h"


// Metadata header
void convert_S_H_B16C(uint8_t *hex_data, int *index)
{
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=1;
}


void convert_R_H_B16C(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
}


void convert_UL_B16C(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=4;
}


//DL decode
void convert_DL_B16C(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index+=6;
}



void decode_B16C(uint8_t *hex_data, size_t length, int *index)
{
    DCIReport_t *t =0;
    asn_dec_rval_t rval; /* Decoder return value  */
    RecordHeader_t *t1 =0;
    asn_dec_rval_t rval1; 
    DCIUL_t *t2 =0;
    asn_dec_rval_t rval2;
    DCIDL_t *t3 =0;
    asn_dec_rval_t rval3;

    int start_S_H = *index;
    printf("start_S_H=%d\n",start_S_H);
    convert_S_H_B16C(hex_data, index);
    int S_H_length = *index - start_S_H;
    printf("S_H_length=%d\n", S_H_length);
    printf("Converted Hex Data: ");
    print_hex(hex_data, start_S_H, start_S_H+S_H_length);

    rval = uper_decode(0, &asn_DEF_DCIReport, (void **)&t, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval.code != RC_OK) {
        printf("rval_S_H decode error\n");
        exit(65); /* better, EX_DATAERR */
    }

    xer_fprint(stdout, &asn_DEF_DCIReport, t);

    int num_of_records = ((hex_data[start_S_H+1] & 0x07) << 2) | ((hex_data[start_S_H+2] & 0xC0) >> 6);
    printf("num of records=%d\n", num_of_records);

    for(int i=0;i<num_of_records;i++)
    {
        //R_H
        int temp_start_R_H = *index;
        convert_R_H_B16C(hex_data, index);
        int R_H_length = *index-temp_start_R_H;
        
        rval1 = uper_decode(0, &asn_DEF_RecordHeader, (void **)&t1, hex_data+temp_start_R_H, R_H_length, 0, 0);
        if(rval1.code != RC_OK) {
            printf("rval_R_H decode error\n");
            exit(66); /* better, EX_DATAERR */
        }
        xer_fprint(stdout, &asn_DEF_RecordHeader, t1);

        int num_of_ul = ((hex_data[temp_start_R_H+1] & 0x01)<<2) | ((hex_data[temp_start_R_H+2] & 0xC0)>>6);
        int num_of_dl = ((hex_data[temp_start_R_H+1] & 0x0E)>>1);
        printf("NUM OF DL=%d\n",num_of_dl);
        printf("num of Ul=%d\n", num_of_ul);

        //ul
        for(int j=0;j<num_of_ul;j++)
        {
            int temp_start_UL = *index;
            convert_UL_B16C(hex_data, index);
            int U_L_length = *index - temp_start_UL;
            rval2 = uper_decode(0, &asn_DEF_DCIUL, (void **)&t2, hex_data+temp_start_UL, U_L_length, 0, 0);
            if(rval2.code != RC_OK) {
                printf("rval_UL decode error\n");
                exit(67); /* better, EX_DATAERR */
            }
            xer_fprint(stdout, &asn_DEF_DCIUL, t2);
        }

        //dl
        for(int j=0;j<num_of_dl;j++)
        {
            int temp_start_DL = *index;
            convert_DL_B16C(hex_data, index);
            int D_L_length = *index - temp_start_DL;
            rval3 = uper_decode(0, &asn_DEF_DCIDL, (void **)&t3, hex_data+temp_start_DL, D_L_length, 0, 0);
            if(rval3.code != RC_OK) {
                printf("rval_DL decode error\n");
                exit(68); /* better, EX_DATAERR */
            }
            xer_fprint(stdout, &asn_DEF_DCIDL, t3);
        }
    }
    printf("decode_B16C over!!!!\n");
    printf("index=%d\n",*index);
}