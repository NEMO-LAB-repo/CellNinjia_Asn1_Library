#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-AdvRx-IC-Cell-List-S-H.h"
#include "LTE-ML1-AdvRx-IC-Cell-List-Neighbor.h"
#include "host.h"

void convert_S_H_B18F(uint8_t *hex_data, int *index)
{
    //1 2 3 4
    *index+=4;
    //5 6 7 8
    convert_endianess(hex_data, index, 4);
    //9 10
    *index+=2;
    //11 12
    convert_endianess(hex_data, index, 2);
    //13 14
    *index+=2;
    //15 16
    convert_endianess(hex_data, index, 2);
    //17 18 19 20
    *index+=4;
    //21 22
    convert_endianess(hex_data, index, 2);
    //23 24
    convert_endianess(hex_data, index, 2);
    //25 26 27 28
    *index+=4;
    //29 30
    convert_endianess(hex_data, index, 2);
    //31 32 33 34 35 36 -48
    *index+=18;
}

void convert_Neighbor_B18F(uint8_t *hex_data, int *index)
{
    //1 2
    convert_endianess(hex_data, index, 2);
    //3 4 
    convert_endianess(hex_data, index, 2);
    //5 6 7 8
    *index+=4;
    //9 10
    convert_endianess(hex_data, index, 2);
    //11 12 13 14 15 16 17 18 19 20-28
    *index+=18;
}

void decode_B18F(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_AdvRx_IC_Cell_List_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_AdvRx_IC_Cell_List_Neighbor_t  *t_Neighbor = 0;
    asn_dec_rval_t rval_Neighbor;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B18F(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_AdvRx_IC_Cell_List_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_AdvRx_IC_Cell_List_S_H, t_S_H);

    //num neighbord
    int num_neighbors = hex_data[start_S_H+9];
    printf("num_neighbors= %d\n",num_neighbors);

    for(int i=0;i<num_neighbors;i++)
    {
        printf("[%d]\n",i);
        int start_neighbor = *index;
        convert_Neighbor_B18F(hex_data, index);
        int neighbor_length = *index - start_neighbor;
        rval_Neighbor = uper_decode(0, &asn_DEF_LTE_ML1_AdvRx_IC_Cell_List_Neighbor, (void **)&t_Neighbor, hex_data+start_neighbor, neighbor_length, 0, 0);
        if(rval_Neighbor.code != RC_OK) {
            printf("rval_Neighbor decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_AdvRx_IC_Cell_List_Neighbor, t_Neighbor); 
    }
    *index+=12;
    printf("decode_B18F over!!!!\n");
}