#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-S-H.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-Payload-H.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-pkt-10.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-pkt-5.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-pkt-11.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-pkt-11-layer.h"
#include "LTE-ML1-Intra-Frequency-Cell-Reselection-pkt-11-layer-cell.h"
#include "host.h"

void convert_S_H_B181(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_payload_H_B181(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_pkt_10_B181(uint8_t *hex_data, int *index)
{
    //1 2 3 4
    convert_endianess(hex_data, index, 4);
    //5 6
    convert_endianess(hex_data, index, 2);
    //7 8
    *index+=2;
}

void convert_pkt_5_B181(uint8_t *hex_data, int *index)
{
    //1-8
    *index+=8;
    //9 10
    convert_endianess(hex_data, index, 2);
    //11 12
    *index+=2;
}

void convert_pkt_11_B181(uint8_t *hex_data, int *index)
{
    //1-8
    *index+=8;
}

void convert_pkt_11_layer_B181(uint8_t *hex_data, int *index)
{
    //1-4
    convert_endianess(hex_data, index, 4);
    //5-12
    *index+=8;
}

void convert_pkt_11_layer_cell_B181(uint8_t *hex_data, int *index)
{
    //1-4
    convert_endianess(hex_data, index, 4);
    //5-10
    *index+=6;
    //11-12
    convert_endianess(hex_data, index, 2);
    //13-16
    *index+=4;
}

void decode_B181(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_Intra_Frequency_Cell_Reselection_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_Intra_Frequency_Cell_Reselection_Payload_H_t  *t_Payload_H = 0;
    asn_dec_rval_t rval_Payload_H;
    LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_10_t  *t_pkt_10 = 0;
    asn_dec_rval_t rval_pkt_10;
    LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_5_t  *t_pkt_5 = 0;
    asn_dec_rval_t rval_pkt_5;
    LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_t  *t_pkt_11 = 0;
    asn_dec_rval_t rval_pkt_11;
    LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_layer_t  *t_pkt_11_layer = 0;
    asn_dec_rval_t rval_pkt_11_layer;
    LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_layer_cell_t  *t_pkt_11_layer_cell = 0;
    asn_dec_rval_t rval_pkt_11_layer_cell;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B181(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_S_H, t_S_H); 

    //get  number of subpkt
    int num_of_subpkt = hex_data[start_S_H+1];
    printf("num_of_subpkt=%d\n",num_of_subpkt);

    for(int i=0;i<num_of_subpkt;i++)
    {
        printf("[%d] subpkt\n",i);

        int start_Payload_H = *index;
        convert_payload_H_B181(hex_data, index);
        int Payload_length = *index-start_Payload_H;
        rval_Payload_H = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_Payload_H, (void **)&t_Payload_H, hex_data+start_Payload_H, Payload_length, 0, 0);
        if(rval_Payload_H.code != RC_OK) {
            printf("rval_Payload_H decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_Payload_H, t_Payload_H); 

        //get subpkt id
        int subpkt_id = hex_data[start_Payload_H];
        switch(subpkt_id)
        {
            case 10:
            {
                int start_pkt_10 = *index;
                convert_pkt_10_B181(hex_data, index);
                int pkt_10_length = *index-start_pkt_10;
                rval_pkt_10 = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_10, (void **)&t_pkt_10, hex_data+start_pkt_10, pkt_10_length, 0, 0);
                if(rval_pkt_10.code != RC_OK) {
                    printf("rval_pkt_10 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_10, t_pkt_10);
                break; 
            }
            case 5:
            {
                int start_pkt_5 = *index;
                convert_pkt_5_B181(hex_data, index);
                int pkt_5_length = *index-start_pkt_5;
                rval_pkt_5 = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_5, (void **)&t_pkt_5, hex_data+start_pkt_5, pkt_5_length, 0, 0);
                if(rval_pkt_5.code != RC_OK) {
                    printf("rval_pkt_5 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_5, t_pkt_5); 
                break;
            }
            case 11:
            {
                int start_pkt_11 = *index;
                convert_pkt_11_B181(hex_data, index);
                int pkt_11_length = *index-start_pkt_11;
                rval_pkt_11 = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11, (void **)&t_pkt_11, hex_data+start_pkt_11, pkt_11_length, 0, 0);
                if(rval_pkt_11.code != RC_OK) {
                    printf("rval_pkt_11 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11, t_pkt_11); 

                //get num of layers
                int num_of_layers = hex_data[start_pkt_11+4];
                printf("num_of_layers=%d\n",num_of_layers);

                for(int j=0;j<num_of_layers+1;j++)
                {
                    printf("layer: [%d] \n",j);
                    int start_pkt_11_layers = *index;
                    convert_pkt_11_layer_B181(hex_data, index);
                    int pkt_11_layer_length = *index-start_pkt_11_layers;
                    printf("pkt_11_layer_length=%d\n", pkt_11_layer_length);
                    rval_pkt_11_layer = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_layer, (void **)&t_pkt_11_layer, hex_data+start_pkt_11_layers, pkt_11_layer_length, 0, 0);
                    if(rval_pkt_11_layer.code != RC_OK) {
                        printf("rval_pkt_11_layer decode error\n");
                        exit(65);
                    }
                    xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_layer, t_pkt_11_layer); 

                    //get num of cells

                    int num_of_cells = hex_data[start_pkt_11_layers+5];
                    printf("num_of_cells=%d\n",num_of_cells);

                    for(int k=0;k<num_of_cells;k++)
                    {
                        printf("cell : [%d]\n");
                        int start_pkt_11_layers_cell = *index;
                        convert_pkt_11_layer_cell_B181(hex_data, index);
                        int pkt_11_layer_cell_length = *index-start_pkt_11_layers_cell;
                        rval_pkt_11_layer_cell = uper_decode(0, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_layer_cell, (void **)&t_pkt_11_layer_cell, hex_data+start_pkt_11_layers_cell, pkt_11_layer_cell_length, 0, 0);
                        if(rval_pkt_11_layer_cell.code != RC_OK) {
                            printf("rval_pkt_11_layer_cell decode error\n");
                            exit(65);
                        }
                        xer_fprint(stdout, &asn_DEF_LTE_ML1_Intra_Frequency_Cell_Reselection_pkt_11_layer_cell, t_pkt_11_layer_cell); 
                    }
                }
                break;
            }
            default:
            {
                printf("in default\n");
                break;
            }
        }
    }
    printf("decode_B181 over!!!!\n");
}