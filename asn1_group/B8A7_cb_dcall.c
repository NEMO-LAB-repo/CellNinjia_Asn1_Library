#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-CSF-Report-S-H.h"
#include "NR5G-MAC-CSF-Report-R-H.h"
#include "NR5G-MAC-CSF-Report-Record-Report.h"
#include "NR5G-MAC-CSF-Report-Record-RSRP.h"
#include "NR5G-MAC-CSF-Report-Record-CSI.h"
#include "host.h"

void convert_S_H_B8A7(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 12;
}

void convert_R_H_B8A7(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 4;
}

void convert_CSF_Report_B8A7(uint8_t *hex_data, int *index)
{
    *index += 8;
}

void convert_RSRP_B8A7(uint8_t *hex_data, int *index)
{
    *index += 52;
}

void convert_CSI_B8A7(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 3);
    *index += 45;
    convert_endianess(hex_data, index, 3);
    *index += 1;
}

void decode_NR5G_MAC_CSF_Report_v131073(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_CSF_Report_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    NR5G_MAC_CSF_Report_R_H_t *t_R_H = 0;
    asn_dec_rval_t rval_R_H;
    NR5G_MAC_CSF_Report_Record_Report_t *t_Record_Report = 0;
    asn_dec_rval_t rval_Record_Report;
    NR5G_MAC_CSF_Report_Record_RSRP_t *t_RSRP = 0;
    asn_dec_rval_t rval_RSRP;
    NR5G_MAC_CSF_Report_Record_CSI_t *t_CSI = 0;
    asn_dec_rval_t rval_CSI;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B8A7(hex_data, index);
    int S_H_length = *index - start_S_H;
    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_CSF_Report_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_CSF_Report_S_H, t_S_H);

    int num_record = hex_data[start_S_H + 15];

    for (int i = 0; i < num_record; i++)
    {
        /*R_H*/
        int start_R_H = *index;
        convert_R_H_B8A7(hex_data, index);
        int R_H_length = *index - start_R_H;
        rval_R_H = uper_decode(0, &asn_DEF_NR5G_MAC_CSF_Report_R_H, (void **)&t_R_H, hex_data + start_R_H, R_H_length, 0, 0);
        if (rval_R_H.code != RC_OK)
        {
            printf("rval_R_H decode error\n");
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_CSF_Report_R_H, t_R_H);

        int report_num = hex_data[start_R_H + 4];

        for (int j = 0; j < report_num; j++)
        {
            /*CSF_Report*/
            int start_Record_Report = *index;
            convert_CSF_Report_B8A7(hex_data, index);
            int Record_Report_length = *index - start_Record_Report;
            rval_Record_Report = uper_decode(0, &asn_DEF_NR5G_MAC_CSF_Report_Record_Report, (void **)&t_Record_Report, hex_data + start_Record_Report, Record_Report_length, 0, 0);
            if (rval_Record_Report.code != RC_OK)
            {
                printf("rval_Record_Report decode error\n");
            }
            xer_fprint(stdout, &asn_DEF_NR5G_MAC_CSF_Report_Record_Report, t_Record_Report);

            int report_type = (hex_data[start_Record_Report + 2]);
            if (report_type == 23)
            {
                /*CSI*/
                int start_CSI = *index;
                convert_CSI_B8A7(hex_data, index);
                int CSI_length = *index - start_CSI;
                rval_CSI = uper_decode(0, &asn_DEF_NR5G_MAC_CSF_Report_Record_CSI, (void **)&t_CSI, hex_data + start_CSI, CSI_length, 0, 0);
                if (rval_CSI.code != RC_OK)
                {
                    printf("rval_CSI decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_CSF_Report_Record_CSI, t_CSI);
            }
            else if (report_type == 96)
            {
                /*RSRP*/
                int start_RSRP = *index;
                convert_RSRP_B8A7(hex_data, index);
                int RSRP_length = *index - start_RSRP;
                rval_RSRP = uper_decode(0, &asn_DEF_NR5G_MAC_CSF_Report_Record_RSRP, (void **)&t_RSRP, hex_data + start_RSRP, RSRP_length, 0, 0);
                if (rval_RSRP.code != RC_OK)
                {
                    printf("rval_RSRP decode error\n");
                }
                xer_fprint(stdout, &asn_DEF_NR5G_MAC_CSF_Report_Record_RSRP, t_RSRP);
            }
            else
            {
                printf("Unknown report type: %d\n", report_type);
            }
        }
    }
    printf("decode_B8A7 over!!!\n");
}
