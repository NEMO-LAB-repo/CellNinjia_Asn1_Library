#include <stdint.h>
#include <change_byte_sequence.h>

uint16_t convert_2_bytes_little_to_big(uint16_t little_endian)
{
    return (little_endian >> 8) | (little_endian << 8);
}

uint32_t convert_3_bytes_little_to_big(uint32_t little_endian)
{
    return ((little_endian & 0x0000FF) << 16) | 
           ((little_endian & 0x00FF00)) |       
           ((little_endian & 0xFF0000) >> 16); 
}

uint32_t convert_4_bytes_little_to_big(uint32_t little_endian)
{
    return ((little_endian & 0x000000FF) << 24) |
           ((little_endian & 0x0000FF00) << 8) |
           ((little_endian & 0x00FF0000) >> 8) |
           ((little_endian & 0xFF000000) >> 24);
}

uint64_t convert_8_bytes_little_to_big(uint64_t little_endian)
{
    return ((little_endian & 0x00000000000000FF) << 56) |
           ((little_endian & 0x000000000000FF00) << 40) |
           ((little_endian & 0x0000000000FF0000) << 24) |
           ((little_endian & 0x00000000FF000000) << 8) |
           ((little_endian & 0x000000FF00000000) >> 8) |
           ((little_endian & 0x0000FF0000000000) >> 24) |
           ((little_endian & 0x00FF000000000000) >> 40) |
           ((little_endian & 0xFF00000000000000) >> 56);
}

void convert_endianess(uint8_t* hex_data, int *index, size_t length) 
{
    int start = *index;
    int end = *index + length - 1;

    while (start < end) {
        uint8_t temp = hex_data[start];
        hex_data[start] = hex_data[end];
        hex_data[end] = temp;

        start++;
        end--;
    }
    *index += length;
}


void print_hex(const uint8_t *data, size_t start, size_t end)
{
    printf("print hex\n");
    for (size_t i = start; i < end; i++)
    {
        printf("%02x", data[i]);
    }
    printf("\n");
}