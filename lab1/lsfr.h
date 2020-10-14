#include <stdint.h>
#include <stdbool.h>

#define BYTE_SIZE 8

/**
 * lsfr_1_32_r() - program simulation of linear-feedback shift register
 * @uint32_t rule: binary represantation of rule.
 * @uint8_t bitness: size of rule.
 * @uint32_t *seed: previous state of lsfr
 *
 * Return: bool.
 *
 * Return true if lsfr output is 1, false if lsfr output is 0.
 */
bool lsfr_1_32_r(uint32_t rule, uint8_t bitness, uint32_t *seed);

/**
 * rule_x() - program simulation of linear-feedback shift register
 * @uint8_t *result: byte sequence.
 * @uint32_t num: size of byte sequence.
 * @uint32_t seed: initial state of lsfr.
 *
 * LSFR for x Galois polinomial.
 * Return: viod.
 *
 */

//x^4 + x^3 + 1
void rule_4_3(uint8_t *result, uint32_t num, uint32_t seed);

//x^8 + x^6 + x^5 + x^2 + 1
void rule_8_6_5_2(uint8_t *result, uint32_t num, uint32_t seed);

//x^9 + x^6 + x^4 + x^3 + 1
void rule_9_6_4_3(uint8_t *result, uint32_t num, uint32_t seed);

//x^10 + x^3 + 1
void rule_10_3(uint8_t *result, uint32_t num, uint32_t seed);
