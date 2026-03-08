#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Serving-Cell-Measurements-And-Evaluation-S-H.h"
#include "host.h"

void convert_S_H_B17F(uint8_t *hex_data, int *index)
{
    //1 2 3 4
    *index+=4;
    //5-8
    convert_endianess(hex_data, index, 4);
    //9-10
    convert_endianess(hex_data, index, 2);
    //11 12
    *index+=2;
    //13 14 15 16
    convert_endianess(hex_data, index, 4);
    //17-20
    convert_endianess(hex_data, index, 4);
    //21-24
    convert_endianess(hex_data, index, 4);
    //25-28
    convert_endianess(hex_data, index, 4);
    //29-30
    *index+=2;
    //31-33
    convert_endianess(hex_data, index, 3);
    //34-35
    convert_endianess(hex_data, index, 2);
    //36
    *index+=1;
    //37-39
    convert_endianess(hex_data, index, 3);
    //40
    *index+=1;
}

void decode_B17F(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_Serving_Cell_Measurements_And_Evaluation_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B17F(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Serving_Cell_Measurements_And_Evaluation_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Serving_Cell_Measurements_And_Evaluation_S_H, t_S_H); 

    double Measured_RSRP = ((hex_data[start_S_H+14]&0x07)<<8) | ((hex_data[start_S_H+15]&0xff));
    Measured_RSRP = (Measured_RSRP*0.0625)-180;
    printf("Measured_RSRP=%f\n",Measured_RSRP);

    double Average_RSRP = ((hex_data[start_S_H+18]&0x07)<<8) | ((hex_data[start_S_H+19]&0xff));
    Average_RSRP = (Average_RSRP*0.0625)-180;
    printf("Average_RSRP=%f\n",Average_RSRP);    

    double Measured_RSRQ = ((hex_data[start_S_H+22]&0x03)<<8) | ((hex_data[start_S_H+23]&0xff));
    Measured_RSRQ = (Measured_RSRQ*0.0625)-30;
    printf("Measured_RSRQ=%f\n",Measured_RSRQ);    
    double Averaged_RSRQ = ((hex_data[start_S_H+20]&0x3f)<<4) | ((hex_data[start_S_H+21]&0xf0)>>4);
    Averaged_RSRQ = (Averaged_RSRQ*0.0625)-30;
    printf("Averaged_RSRQ=%f\n",Averaged_RSRQ);    

    double Averaged_RSSI = ((hex_data[start_S_H+25]&0x0f)<<6) | ((hex_data[start_S_H+26]&0xfC)>>2);
    Averaged_RSSI = (Averaged_RSSI*0.0625)-110;
    printf("Averaged_RSSI=%f\n",Averaged_RSSI);     

    double Srxlev = ((hex_data[start_S_H+31]&0x03)<<5) | ((hex_data[start_S_H+32]&0xf8)>>3);
    Srxlev = (Srxlev-30);
    printf("Srxlev=%f\n",Srxlev);  

    printf("decode_B17F over!!!!\n");
}