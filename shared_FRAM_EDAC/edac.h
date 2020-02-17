//EDAC Header

#include <stdint.h>

uint16_t parity_encode (uint8_t *raw_data);

uint8_t parity_decode (uint16_t *enc_data);
