#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "change_byte_sequence.h"
#include "host.h"


void decode_NAS_800_v1(uint8_t *hex_data, size_t length, int *index, int msg_len, uint64_t time_in_us_total)
{
    int start_S_H = *index;
    *index+=7;
    int version = hex_data[start_S_H];
    printf("Version: %d\n", version);
    if (version != 0x01)
    {
        printf("Unsupported version: %d\n", version);
        return;
    }

    int start_NAS_msg = *index;
    int NAS_msg_length = msg_len - 19;

    // Set pcap magic header
    FILE *pcap_file = fopen("B800.pcap", "rb");
    if (pcap_file == NULL) 
    {
        printf("Creating new pcap file: B800.pcap\n");
        pcap_file = fopen("B800.pcap", "wb");
        if (pcap_file == NULL) {
            printf("Error: Cannot create pcap file\n");
            return;
        }
        
        uint8_t pcap_header[] = {
            0xd4, 0xc3, 0xb2, 0xa1,  // magic number
            0x02, 0x00,              // version major
            0x04, 0x00,              // version minor
            0x00, 0x00, 0x00, 0x00,  // time zone
            0x00, 0x00, 0x00, 0x00,  // sigfigs
            0xff, 0xff, 0x00, 0x00,  // snaplen
            0x93, 0x00, 0x00, 0x00   // network: DLT_USER0 (147)
        };
        fwrite(pcap_header, 1, sizeof(pcap_header), pcap_file);
    } 
    else 
    {
        fclose(pcap_file);
        pcap_file = fopen("B800.pcap", "ab");
        if (pcap_file == NULL) {
            printf("Error: Cannot open pcap file for append\n");
            return;
        }
    }

    // Set pkt header
    uint64_t timestamp_usec = time_in_us_total;
    uint64_t timestamp_sec = time_in_us_total / 1000000;
    uint32_t incl_len = NAS_msg_length;
    uint32_t orig_len = NAS_msg_length;

    // Write packet header
    fwrite(&timestamp_sec, 4, 1, pcap_file);    // timestamp seconds
    fwrite(&timestamp_usec, 4, 1, pcap_file);   // timestamp usec
    fwrite(&incl_len, 4, 1, pcap_file);         // incl_len
    fwrite(&orig_len, 4, 1, pcap_file);         // orig_len

    // Write NAS message data
    fwrite(&hex_data[start_NAS_msg], 1, NAS_msg_length, pcap_file);
    printf("Written %d bytes of NAS message to pcap file\n", NAS_msg_length);

    fclose(pcap_file);
    printf("Pcap file B800.pcap updated successfully\n");
}


