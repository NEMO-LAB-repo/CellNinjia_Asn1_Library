#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "NR5G-MAC-CDRX-Events-Info-S-H.h"
#include "NR5G-MAC-CDRX-Events-Info-Record.h"
#include "host.h"

void convert_S_H_B890(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 4);
    *index += 36;
}

void convert_Record_B890(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 3);
    *index+=1;
    convert_endianess(hex_data, index, 4);
    convert_endianess(hex_data, index, 3);
    *index+=1;
    convert_endianess(hex_data, index, 3);
    *index+=1;
    convert_endianess(hex_data, index, 3);
    *index+=5;
}

void decode_NR5G_MAC_CDRX_Events_Info_v131073(uint8_t *hex_data, size_t length, int *index)
{
    NR5G_MAC_CDRX_Events_Info_S_H_t *t_S_H = 0;
    NR5G_MAC_CDRX_Events_Info_Record_t *t_Record = 0;
    asn_dec_rval_t rval_S_H;
    asn_dec_rval_t rval_Record;

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B890(hex_data, index);
    int S_H_length = *index - start_S_H;

    rval_S_H = uper_decode(0, &asn_DEF_NR5G_MAC_CDRX_Events_Info_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error, may caused by diff version\n");
        // exit(65);
    }
    xer_fprint(stdout, &asn_DEF_NR5G_MAC_CDRX_Events_Info_S_H, t_S_H);

    int num_record = hex_data[start_S_H+15];
    /*Record*/
    for(int i=0; i < num_record; i++)
    {
        int start_Record = *index;
        convert_Record_B890(hex_data, index);
        int Record_length = *index - start_Record;

        rval_Record = uper_decode(0, &asn_DEF_NR5G_MAC_CDRX_Events_Info_Record, (void **)&t_Record, hex_data + start_Record, Record_length, 0, 0);
        if (rval_Record.code != RC_OK)
        {
            printf("rval_Record decode error, may caused by diff version\n");
            // exit(65);
        }
        xer_fprint(stdout, &asn_DEF_NR5G_MAC_CDRX_Events_Info_Record, t_Record);
    }
    printf("decode B890 over!\n");
}