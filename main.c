#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

const char *FILENAME = "image.png";

void reverse_bytes(void *buf0, size_t buf_cap)
{
    uint8_t *buf = buf0;
    for (size_t i = 0; i < buf_cap/2; ++i) {
        uint8_t t = buf[i];
        buf[i] = buf[buf_cap - i - 1];
        buf[buf_cap - i - 1] = t;
    }
}

void print_bytes(uint8_t *buf, size_t buf_cap)
{
    for (size_t i = 0; i < buf_cap; ++i) {
        printf("%02x ", buf[i]);
    }
    printf("\n");
}

#define PNG_SIG_CAP 8
const uint8_t png_sig[PNG_SIG_CAP] = {137, 80, 78, 71, 13, 10, 26, 10};

int main() {
    FILE *fileptr;
  
    fileptr = fopen(FILENAME, "r");

    // Check that file is a png
    uint8_t sig[PNG_SIG_CAP];
    fread(sig, PNG_SIG_CAP, 1, fileptr);
    if (memcmp(sig, png_sig, PNG_SIG_CAP) != 0) {
      printf("File is not a png\n");
    }

    // IHDR chunk
    // Get size of chunk's content
    uint32_t IHDR_chunk_size;
    fread(&IHDR_chunk_size, sizeof(IHDR_chunk_size), 1, fileptr);
    reverse_bytes(&IHDR_chunk_size, sizeof(IHDR_chunk_size));

    // Chunk type
    uint8_t IHDR_chunk_type[4];
    fread(IHDR_chunk_type, sizeof(IHDR_chunk_type), 1, fileptr);

    // Image width
    uint32_t image_width;
    fread(&image_width, sizeof(image_width), 1, fileptr);
    reverse_bytes(&image_width, sizeof(image_width));

    // Image height
    uint32_t image_height;
    fread(&image_height, sizeof(image_height), 1, fileptr);
    reverse_bytes(&image_height, sizeof(image_height));

    // Image bit depth
    uint8_t image_bit_depth;
    fread(&image_bit_depth, sizeof(image_bit_depth), 1, fileptr);
    reverse_bytes(&image_bit_depth, sizeof(image_bit_depth));

    // Image color type
    uint8_t image_color_type;
    fread(&image_color_type, sizeof(image_color_type), 1, fileptr);
    reverse_bytes(&image_color_type, sizeof(image_color_type));
    
    // Image compression method
    uint8_t image_compression_method;
    fread(&image_compression_method, sizeof(image_compression_method), 1, fileptr);
    reverse_bytes(&image_compression_method, sizeof(image_compression_method));

    // Image filter type
    uint8_t image_filter_type;
    fread(&image_filter_type, sizeof(image_filter_type), 1, fileptr);
    reverse_bytes(&image_filter_type, sizeof(image_filter_type));

    // Image interlace method
    uint8_t image_interlace_method;
    fread(&image_interlace_method, sizeof(image_interlace_method), 1, fileptr);
    reverse_bytes(&image_interlace_method, sizeof(image_interlace_method));

    // Crc
    uint8_t IHDR_crc[4];
    fread(IHDR_crc, sizeof(IHDR_crc), 1, fileptr);

    for (int i = 0; i < 10; i++) {
         // Get size of chunk's content
        uint32_t chunk_size;
        fread(&chunk_size, sizeof(chunk_size), 1, fileptr);
        reverse_bytes(&chunk_size, sizeof(chunk_size));
        printf("Chunk content size: %u\n", chunk_size);

        // Chunk type
        uint8_t chunk_type[4];
        fread(chunk_type, sizeof(chunk_type), 1, fileptr);
        printf("Chunk type: %c%c%c%c\n", chunk_type[0], chunk_type[1], chunk_type[2], chunk_type[3]);

        // Chunk content
        uint8_t content_buf[chunk_size];
        fread(content_buf, chunk_size, 1, fileptr);

        // Crc
        uint8_t crc[4];
        fread(crc, sizeof(crc), 1, fileptr);
    }

    fclose(fileptr);

    return 0;
}
