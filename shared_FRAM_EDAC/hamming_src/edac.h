/* Author: Sloan Liu
 * Project: SlugSat Year 4
 * SubTeam: On-Baord Computer
 * 
 * Rights to the code go to the SlugSat Year 4 team 
 * to use/modify as desired
 */

//EDAC Header

#include <stdint.h>

uint16_t parity_encode (uint8_t *raw_data);

uint8_t parity_decode (uint16_t *enc_data);
