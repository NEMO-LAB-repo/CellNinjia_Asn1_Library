#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-ML1-Searcher-Measurement-Database-Update-Ext-S-H.h"
#include "NR5G-ML1-Searcher-Measurement-Database-Update-Ext-CompCarrierList.h"
#include "NR5G-ML1-Searcher-Measurement-Database-Update-Ext-Cell.h"
#include "NR5G-ML1-Searcher-Measurement-Database-Update-Ext-DetectedBeam.h"
#include "host.h"


void convert_S_H_B97F(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
    *index+=4;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);
}

void convert_CompCarrierList_B97F(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=12;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
}

void convert_Cell_B97F(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index+=4;
    // RSRP
    convert_endianess(hex_data, index, 2);
    *index+=2;
    // RSRQ
    convert_endianess(hex_data, index, 2);
    *index+=2;
}

void convert_DetectedBeam_B97F(uint8_t *hex_data, int *index)
{
    *index+=12;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 4);


    // RSRP
    convert_endianess(hex_data, index, 2);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=2;
    convert_endianess(hex_data, index, 2);
    *index+=2;
}

float convert_rsrp_to_dbm(int value) {
    if (value == 0) {
        return 0;  // NaN
    }
    
    int integer_part = (value >> 7) & 0xff;  
    int fractional_part = value & 0x7f;      
    
    float integer_dbm = (((integer_part ^ 0xff) + 1) * (-1));
    
    float fractional_dbm = fractional_part * 0.0078125;  // 0.0078125 = 1/128
    
    return integer_dbm + fractional_dbm;
} 


void decode_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_v131073(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_ML1_Searcher_Measurement_Database_Update_Ext_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_ML1_Searcher_Measurement_Database_Update_Ext_CompCarrierList_t *t_CompCarrierList = 0;
    asn_dec_rval_t rval_CompCarrierList;
    NR5G_ML1_Searcher_Measurement_Database_Update_Ext_Cell_t *t_Cell = 0;
    asn_dec_rval_t rval_Cell;
    NR5G_ML1_Searcher_Measurement_Database_Update_Ext_DetectedBeam_t *t_DetectedBeam = 0;
    asn_dec_rval_t rval_DetectedBeam;

    /*S-H*/
    int start_S_H = *index;
    convert_S_H_B97F(hex_data, index);
    int S_H_length = *index - start_S_H;
    rval_S_H = uper_decode(0, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_S_H, t_S_H);

    int num_carrier = (hex_data[start_S_H+8]);

    /*CompCarrierList*/
    for(int i = 0; i < num_carrier; i++)
    {   
        printf("[%d]\n",i);
        int start_CompCarrierList = *index;
        convert_CompCarrierList_B97F(hex_data, index);
        int CompCarrierList_length = *index - start_CompCarrierList;
        
        rval_CompCarrierList = uper_decode(0, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_CompCarrierList, (void **)&t_CompCarrierList, hex_data + start_CompCarrierList, CompCarrierList_length, 0, 0);
        if (rval_CompCarrierList.code != RC_OK)
        {
            printf("rval_CompCarrierList decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_CompCarrierList, t_CompCarrierList);

        int num_cell = (hex_data[start_CompCarrierList+5]);
        /*Cell*/
        for(int j = 0; j < num_cell; j++)
        {   
            printf("    [%d]\n",j);
            int start_Cell = *index;
            convert_Cell_B97F(hex_data, index);
            int Cell_length = *index - start_Cell;
            rval_Cell = uper_decode(0, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_Cell, (void **)&t_Cell, hex_data + start_Cell, Cell_length, 0, 0);
            if (rval_Cell.code != RC_OK)
            {
                printf("rval_Cell decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_Cell, t_Cell);
            
            int rsrp = (hex_data[start_Cell+8] << 8) + hex_data[start_Cell+9];
            int rsrq = (hex_data[start_Cell+12] << 8) + hex_data[start_Cell+13];

            float rsrp_dbm = convert_rsrp_to_dbm(rsrp);
            float rsrq_dbm = convert_rsrp_to_dbm(rsrq);

            printf("        rsrp_dbm: %f\n        rsrq_dbm: %f\n", rsrp_dbm, rsrq_dbm);

            int num_detected_beam = (hex_data[start_Cell+4]);
            /*DetectedBeam*/
            for(int k = 0; k < num_detected_beam; k++)
            {   
                printf("        [%d]\n",k);
                int start_DetectedBeam = *index;
                convert_DetectedBeam_B97F(hex_data, index);
                int DetectedBeam_length = *index - start_DetectedBeam;
                rval_DetectedBeam = uper_decode(0, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_DetectedBeam, (void **)&t_DetectedBeam, hex_data + start_DetectedBeam, DetectedBeam_length, 0, 0);
                
                if (rval_DetectedBeam.code != RC_OK)
                {
                    printf("rval_DetectedBeam decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_ML1_Searcher_Measurement_Database_Update_Ext_DetectedBeam, t_DetectedBeam);

                int rsrps_rsrp0 = (hex_data[start_DetectedBeam+20] << 8) + hex_data[start_DetectedBeam+21];
                int rsrps_rsrp1 = (hex_data[start_DetectedBeam+24] << 8) + hex_data[start_DetectedBeam+25];
                int filtered_tx_beam_rsrp = (hex_data[start_DetectedBeam+28] << 8) + hex_data[start_DetectedBeam+29];
                int filtered_tx_beam_rsrq = (hex_data[start_DetectedBeam+32] << 8) + hex_data[start_DetectedBeam+33];
                int l2nr_filtered_tx_beam_rsrp = (hex_data[start_DetectedBeam+36] << 8) + hex_data[start_DetectedBeam+37];
                int l2nr_filtered_tx_beam_rsrq = (hex_data[start_DetectedBeam+40] << 8) + hex_data[start_DetectedBeam+41];

                float rsrps_rsrp0_dbm = convert_rsrp_to_dbm(rsrps_rsrp0);
                float rsrps_rsrp1_dbm = convert_rsrp_to_dbm(rsrps_rsrp1);
                float filtered_tx_beam_rsrp_dbm = convert_rsrp_to_dbm(filtered_tx_beam_rsrp);
                float filtered_tx_beam_rsrq_dbm = convert_rsrp_to_dbm(filtered_tx_beam_rsrq);
                float l2nr_filtered_tx_beam_rsrp_dbm = convert_rsrp_to_dbm(l2nr_filtered_tx_beam_rsrp);
                float l2nr_filtered_tx_beam_rsrq_dbm = convert_rsrp_to_dbm(l2nr_filtered_tx_beam_rsrq);
                printf("            rsrps_rsrp0_dbm: %f\n            rsrps_rsrp1_dbm: %f\n            filtered_tx_beam_rsrp_dbm: %f\n            filtered_tx_beam_rsrq_dbm: %f\n            l2nr_filtered_tx_beam_rsrp_dbm: %f\n            l2nr_filtered_tx_beam_rsrq_dbm: %f\n", rsrps_rsrp0_dbm, rsrps_rsrp1_dbm, filtered_tx_beam_rsrp_dbm, filtered_tx_beam_rsrq_dbm, l2nr_filtered_tx_beam_rsrp_dbm, l2nr_filtered_tx_beam_rsrq_dbm);
            }
        }
    }
    printf("decode_B97F over!!!\n");
}
