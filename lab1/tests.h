#include <stdint.h>
#include <stdbool.h>

#define BYTE_SIZE 8

/**
 * freq_test() - frequency test.
 * @uint8_t *seq: sequence needed to be tested.
 * @int size: its size.
 *
 * Return: float.
 *
 * Return coefficient that is equal to amount of '1' divided on all amount of bits in sequence.
 */
float freq_test(uint8_t *seq, int size);

/**
 * diff_freq_test() - differential frequency test.
 * @uint8_t *seq: sequence needed to be tested.
 * @int size: its size.
 *
 * Return: float.
 *
 * Return coefficient that is equal to amount of pais of different bits ("10", "01")
 * divided on all amount of bits in sequence minus 1.
 */
float diff_freq_test(uint8_t *seq, int size);

/**
 * rang_test() - rang (window) test.
 * @uint8_t *seq: sequence needed to be tested.
 * @int size: its size.
 *
 * Return: float.
 *
 * Return coefficient that is equal to amount of pais of different bits ("10", "01")
 * divided on all amount of bits in sequence minus 1.
 */
bool check_bit(uint8_t num, uint8_t bit_num);

/**
 * non_linear_test() - non-linear complexity test.
 * @uint8_t *seq: sequence needed to be tested.
 * @int size: its size.
 *
 * Return: long long.
 *
 * return non-linear complexity of subsequence
 * (the number of previous bits that have impact on current bit).
 */
uint32_t linear_test(uint8_t *seq, uint32_t size, bool *rule);
