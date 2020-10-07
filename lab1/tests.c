#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * bool check_bit() - check the valyu of specific bit in byte.
 * @uint8_t nub: byte.
 * @uint8_t bit_num: number of bit in byte.
 *
 * For example byte is 0x01: bit number 0 is equal to '1', bit number 7 is equal to '0'.
 *
 * Return: bool.
 *
 * Return True if bit is 1, false if bit is 0.
 */
inline bool check_bit(uint8_t num, uint8_t bit_num)
{
    return (num & (1 << bit_num)) != 0;
}


float freq_test(uint8_t *seq, int size)
{
    if(seq == NULL || size <= 0)
        return -1;

    int count = 0;

    for(int i = 0; i < size; i++)
        for(int j = 0; j < BYTE_SIZE; j++)
            if((seq[i] & (1 << j)) != 0)
                count++;

    return (count + 0.0) / (size * BYTE_SIZE);
}


float diff_freq_test(uint8_t *seq, int size)
{
    if(seq == NULL || size == 0)
        return -1;

    int equal = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < BYTE_SIZE - 1; j++)
            //if bits in pair are equal
            if((((seq[i] & (1 << j)) != 0) && ((seq[i] & (1 << (j + 1))) != 0)) ||
                (((seq[i] & (1 << j)) == 0) && ((seq[i] & (1 << (j + 1))) == 0)))
                equal++;

        //for "borders" between 2 bytes
        if(i < size - 1)
            if((((seq[i] & (1 << 0)) != 0) && ((seq[i + 1] & (1 << 7)) != 0)) ||
                (((seq[i] & (1 << 0)) == 0) && ((seq[i] & (1 << 7)) == 0)))
                equal++;
    }

    return (size * BYTE_SIZE - 1 - equal + 0.0) / (size  * BYTE_SIZE);
}


bool rang_test(uint8_t *seq, int size, int rang)
{

}


long long non_linear_test(uint8_t *seq, int size)
{
    bool flag = false;

    for(long long i = 1; i < size * BYTE_SIZE; i++){ //size of subsequences in bits
        flag = true;
        for(long long j = 0; j < size * BYTE_SIZE - i - 1; j++){ //start point of first subsequence (number of bit)
            for(long long k = j + 1; k < size * BYTE_SIZE - i - 1; k++){ //start point of second subsequence (number of bit)
                long long g = 0;
                //compare i bits
                while(check_bit(seq[(j + g) / BYTE_SIZE], (j + g) % BYTE_SIZE) ==
                    check_bit(seq[(k + g) / BYTE_SIZE], (k + g) % BYTE_SIZE))
                    g++;
                if(g == i && check_bit(seq[(j + g) / BYTE_SIZE], (j + g) % BYTE_SIZE) !=
                    check_bit(seq[(k + g) / BYTE_SIZE], (k + g) % BYTE_SIZE)){
                    flag = false;
                    break;
                }
            }
            if(flag == false)
                break;
        }
        if(flag == true)
            return i;
        i++;
    }
    return -1;
}

/**
 * linear_test() - linear complexity test.
 * @uint8_t *seq: sequence needed to be tested.
 * @int size: its size.
 *
 * Linear complexity test based on Berlecamp-Massey algorithm.
 *
 * Return: long long.
 *
 * return linear complexity of subsequence
 * (the number of previous bits that have impact on current bit).
 */
long long linear_test(uint8_t *seq, int size)
{

}
