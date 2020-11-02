#include "lsfr.h"
#include "tests.h"
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//15000 bit = 1875 byte
#define SEQ_SIZE 1875

uint32_t get_address(void);
bool table_cipher_bit(uint8_t *table, uint32_t size);
void table_cipher(uint8_t *table, uint32_t tsize, uint8_t *result, uint32_t rsize);
void get_random(uint8_t *table, uint32_t size);

int main(void)
{
    uint8_t table[512]; //2^12 = 4096 bits = 512 bytes
    get_random(&table[0], 512);

    uint8_t randseq[SEQ_SIZE];
    table_cipher(&table[0], 512, &randseq[0], SEQ_SIZE);

    printf("Frequency table test: %.6f\n\n", freq_test(&table[0], 512));

    printf("Frequency test: %.6f\n", freq_test(&randseq[0], SEQ_SIZE));
    printf("Diff frequency test: %.6f\n", diff_freq_test(&randseq[0], SEQ_SIZE));
    //printf("Non-linear complexity: %d\n", non_linear_test(&randseq[0], SEQ_SIZE));

    // bool rule[SEQ_SIZE * BYTE_SIZE];
    // printf("Linear complexity: %d\n", linear_test(&randseq[0], SEQ_SIZE, &rule));
    //
    // uint8_t seq[2] = {0xac, 0x8f};
    // bool rule[2 * BYTE_SIZE / 2];
    // printf("Linear complexity: %d\n", linear_test(&seq[0], 2, &rule));

    return 0;
}

/**
 * table_cipher() - generate pseudo random sequence.
 * @uint8_t *table: table.
 * @uint32_t tsize: size of table in bytes.
 * @uint8_t *result: pseudo random sequence.
 * @uint32_t rsize: size of result in bytes.
 *
 * Return: void.
 */
void table_cipher(uint8_t *table, uint32_t tsize, uint8_t *result, uint32_t rsize)
{
    for(int j = 0; j< rsize; j++){
        result[j] = 0;
        for(int i = 0; i < BYTE_SIZE; i++)
            if(table_cipher_bit(table, tsize))
                result[j] |= (1 << i);
    }
}

/**
 * table_cipher_bit() - get one bit of pseudo random sequence.
 * @uint8_t *table: table.
 * @uint32_t size: size of table in bytes.
 *
 * Return bit stored in table by pseudo random address, got as composition of lsfr outpu
 *
 * Return: bool.
 *
 * Return true if generator output is 1, false if lsfr output is 0.
 */
bool table_cipher_bit(uint8_t *table, uint32_t size)
{
    uint32_t addr = get_address();
    //return value from table
    if(check_bit(table[addr / BYTE_SIZE], addr % BYTE_SIZE))
        return true;
    return false;
}

/**
 * get_address() - get one bit of pseudo random sequence.
 *
 * Generate address which is composition of 12 lsfr outputs.
 *
 * Return: uint32_t.
 *
 * Return address.
 */
uint32_t get_address(void)
{
    //12 lsfr 8+ bitness
    uint32_t address = 0;
    static uint32_t seeds[12] = {1, 56, 1, 890, 2632, 2, 3, 8, 1, 907, 1, 1};

    //x^8 + x^6 + x^5 + x^2 + 1 ->  10110010
    if(lsfr_1_32_r(0xb2, 8, &seeds[0])) address |= (1 << 0);
    //x^9 + x^6 + x^4 + x^3 + 1 ->  100101100
    if(lsfr_1_32_r(0x012c, 9, &seeds[1])) address |= (1 << 1);
    //x^10 + x^3 + 1 ->  1000000100
    if(lsfr_1_32_r(0x204, 10, &seeds[2])) address |= (1 << 2);

    //x^11 + x^10 + x^3 + x^2 + 1 ->  11000000110
    if(lsfr_1_32_r(0x606, 11, &seeds[3])) address |= (1 << 3);
    //x^12 + x^11 + x^9 + x^7 + x^6 + x^4 + 1 ->  110101101000
    if(lsfr_1_32_r(0x0d68, 12, &seeds[4])) address |= (1 << 4);
    //x^13 + x^11 + x^10 + x^9 + x^8 + x^7 + x^6 + x^5 + x^4 + x^3 + x^2 + x^1 + 1 ->  1011111111111
    if(lsfr_1_32_r(0x17ff, 13, &seeds[5])) address |= (1 << 5);

    //x^14 + x^8 + x^6 + x^1 + 1 ->  10000010100001
    if(lsfr_1_32_r(0x20a1, 14, &seeds[6])) address |= (1 << 6);
    //x^15 + x^7 + 1 ->  00000001000000
    if(lsfr_1_32_r(0x4040, 15, &seeds[7])) address |= (1 << 7);
    //x^16 + x^12 + x^7 + x^2 + 1 ->  1000100001000010
    if(lsfr_1_32_r(0x8842, 16, &seeds[8])) address |= (1 << 8);

    //x^17 + x^12 + x^6 + x^3 + x^2 + x^1 + 1 -> 10000100000100111
    if(lsfr_1_32_r(0x10827, 17, &seeds[9])) address |= (1 << 9);
    //x^18 + x^7 + 1 ->  100000000001000000
    if(lsfr_1_32_r(0x20040, 18, &seeds[10])) address |= (1 << 10);
    //x^19 + x^9 + x^8 + x^7 + x^4 + x^3 + x^2 + x^1 + 1 ->  1000000000111001111
    if(lsfr_1_32_r(0x0401cf, 19, &seeds[11])) address |= (1 << 11);

    return address;
}

/**
 * get_random() - get pseudo random sequence usinr rand().
 * @uint8_t *table: table.
 * @uint32_t size: size of table in bytes.
 *
 * Generate address which is composition of 12 lsfr outputs.
 *
 * Return: uint32_t.
 *
 * Return address.
 */
void get_random(uint8_t *table, uint32_t size)
{
    srand(time(NULL));
    for(int i = 0; i < size; i++)
        table[i] = rand();

    // for(int i = 0; i < size; i++)
    //     table[i] = 0x55;
}
