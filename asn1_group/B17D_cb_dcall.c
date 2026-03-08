#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Idle-Measurement-Request-S-H.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-1.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-2.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-5.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-6.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-7.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-7-cell.h"
#include "LTE-ML1-Idle-Measurement-Request-Sub-Pkt-8.h"
#include "host.h"

void convert_S_H_B17D(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_pkt1_B17D(uint8_t *hex_data, int *index)
{
    //1 2 3
    *index+=3;
    //4 5
    convert_endianess(hex_data, index, 2);
    //6 7
    convert_endianess(hex_data, index, 2);
}

void convert_pkt2_B17D(uint8_t *hex_data, int *index)
{
    //1 2 3
    *index+=3;
    //4 5
    convert_endianess(hex_data, index, 2);
    //6 7
    convert_endianess(hex_data, index, 2);
}

void convert_pkt5_B17D(uint8_t *hex_data, int *index)
{
    //1 2 3
    *index+=3;
    //4 5
    convert_endianess(hex_data, index, 2);
    //6 7 8 9 10 11
    *index +=6;
    //12 13
    convert_endianess(hex_data, index, 2);
    //14 15
    *index +=2;
}

void convert_pkt6_B17D(uint8_t *hex_data, int *index)
{
    //1 2 3
    *index+=3;
    //4 5
    convert_endianess(hex_data, index, 2);
    //6 7 8 9 10 11 12 13 14 15 16 17 18 19 
    *index +=14;
    //20 21
    convert_endianess(hex_data, index, 2);
    //22 23
    *index +=2;
}

void convert_pkt7_B17D(uint8_t *hex_data, int *index)
{
    //1 2 3
    *index+=3;
    //4 5
    convert_endianess(hex_data, index, 2);
}

void convert_pkt7_cell_B17D(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
}

void convert_pkt8_B17D(uint8_t *hex_data, int *index)
{
    //1 2 3
    *index+=3;
    //4 5
    convert_endianess(hex_data, index, 2);
    //6 7 
    *index+=2;
}

void decode_B17D(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_Idle_Measurement_Request_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_1_t  *t_pkt_1 = 0;
    asn_dec_rval_t rval_pkt_1;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_2_t  *t_pkt_2 = 0;
    asn_dec_rval_t rval_pkt_2;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_5_t  *t_pkt_5 = 0;
    asn_dec_rval_t rval_pkt_5;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_6_t  *t_pkt_6 = 0;
    asn_dec_rval_t rval_pkt_6;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_7_t  *t_pkt_7 = 0;
    asn_dec_rval_t rval_pkt_7;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_7_cell_t  *t_pkt_7_cell = 0;
    asn_dec_rval_t rval_pkt_7_cell;
    LTE_ML1_Idle_Measurement_Request_Sub_Pkt_8_t  *t_pkt_8 = 0;
    asn_dec_rval_t rval_pkt_8;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B17D(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_S_H, t_S_H);

    //get number of subpkt
    int num_of_subpkt = hex_data[start_S_H+1];
    printf("num_of_subpkt=%d\n",num_of_subpkt);

    for(int i=0;i<num_of_subpkt;i++)
    {
        /*subpacket id*/
        int subpacket_id = hex_data[*index];
        printf("subpkt_id = %d\n",subpacket_id);
        *index+=1;

        switch(subpacket_id)
        {
            case 1:
            {
                printf("SubPacket ID : 1\n");
                int start_id1 = *index;
                convert_pkt1_B17D(hex_data, index);
                int id1_length = *index - start_id1;
                rval_pkt_1 = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_1, (void **)&t_pkt_1, hex_data+start_id1, id1_length, 0, 0);
                if(rval_pkt_1.code != RC_OK) {
                    printf("rval_pkt_1 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_1, t_pkt_1); 
                break;
            }
            case 2:
            {
                printf("SubPacket ID : 2\n");
                int start_id2 = *index;
                convert_pkt2_B17D(hex_data, index);
                int id2_length = *index - start_id2;
                rval_pkt_2 = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_2, (void **)&t_pkt_2, hex_data+start_id2, id2_length, 0, 0);
                if(rval_pkt_2.code != RC_OK) {
                    printf("rval_pkt_2 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_2, t_pkt_2); 
                break;
            }
            case 5:
            {
                printf("SubPacket ID : 5\n");
                int start_id5 = *index;
                convert_pkt5_B17D(hex_data, index);
                int id5_length = *index - start_id5;
                rval_pkt_5 = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_5, (void **)&t_pkt_5, hex_data+start_id5, id5_length, 0, 0);
                if(rval_pkt_5.code != RC_OK) {
                    printf("rval_pkt_5 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_5, t_pkt_5); 
                break;
            }
            case 6:
            {
                printf("SubPacket ID : 6\n");
                int start_id6 = *index;
                convert_pkt6_B17D(hex_data, index);
                int id6_length = *index - start_id6;
                rval_pkt_6 = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_6, (void **)&t_pkt_6, hex_data+start_id6, id6_length, 0, 0);
                if(rval_pkt_6.code != RC_OK) {
                    printf("rval_pkt_6 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_6, t_pkt_6); 
                break;
            }
            case 7:
            {
                printf("SubPacket ID : 7\n");
                int start_id7 = *index;
                convert_pkt7_B17D(hex_data, index);
                int id7_length = *index - start_id7;
                rval_pkt_7 = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_7, (void **)&t_pkt_7, hex_data+start_id7, id7_length, 0, 0);
                if(rval_pkt_7.code != RC_OK) {
                    printf("rval_pkt_7 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_7, t_pkt_7); 

                //num_white_listed_cells
                int num_white_listed_cells = hex_data[start_id7+4] & 0x07;
                printf("num_white_listed_cells=%d\n",num_white_listed_cells);
                
                for(int j=0;j<num_white_listed_cells;j++)
                {
                    printf("[%d]\n",j);
                    int start_id7_cell = *index;
                    convert_pkt7_cell_B17D(hex_data, index);
                    int id7_cell_length = *index - start_id7_cell;
                    rval_pkt_7_cell = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_7_cell, (void **)&t_pkt_7_cell, hex_data+start_id7_cell, id7_cell_length, 0, 0);
                    if(rval_pkt_7_cell.code != RC_OK) {
                        printf("rval_pkt_7_cell decode error\n");
                        exit(65);
                    }
                    xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_7_cell, t_pkt_7_cell); 
                }
                //skip 2 Bytes in the end
                *index+=2;
                break;
            }
            case 8:
            {
                printf("SubPacket ID : 8\n");
                int start_id8 = *index;
                convert_pkt8_B17D(hex_data, index);
                int id8_length = *index - start_id8;
                rval_pkt_8 = uper_decode(0, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_8, (void **)&t_pkt_8, hex_data+start_id8, id8_length, 0, 0);
                if(rval_pkt_8.code != RC_OK) {
                    printf("rval_pkt_8 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Idle_Measurement_Request_Sub_Pkt_8, t_pkt_8); 
                break;
            }
            default:
            {
                printf("in default\n");
                break;
            }
        }
    }
    printf("decode_B17D over!!!!\n");
}