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

void bool_toggle(bool *a)
{
    if(*a) *a = false;
    else *a = true;
}

void bool_print(bool a)
{
    if(a) printf("1 ");
    else printf("0 ");
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

//need refactoring

uint32_t linear_test(uint8_t *seq, uint32_t size, bool *rule)
{
    uint32_t L = 0; //linear complexity
    int x = 1;

    uint32_t rulesize = 1;
    for(int i = 0; i < size * BYTE_SIZE; i++)
        rule[i] = false;
    rule[0] = true; //C(D) = 1

    uint32_t addpolsize = 1;
    bool *addpol = malloc((size * BYTE_SIZE) * (sizeof(bool))); //it is B(D), same size as rule
    for(int i = 0; i <  size * BYTE_SIZE; i++)
        addpol[i] = false;
    addpol[0] = true; //B(D) = 1

    for(long i = 0; i < size * BYTE_SIZE; i++){ //counter (num of current bit of sequence)
        //find current bit d
        bool d = check_bit(seq[i / BYTE_SIZE], i % BYTE_SIZE);
        for(int j = 1; j < rulesize; j++)
            if(rule[j] && check_bit(seq[(i - j) / BYTE_SIZE], (i - j) % BYTE_SIZE))
                    bool_toggle(&d);

        // for(int g = 0; g < rulesize; g++)
        //         bool_print(rule[g]);
        // printf("\n");
        // bool_print(d);

        if(d == false) //step 3
            x++; //C_D is correct
        else if(d == true)
            if(2 * L > i){ //step 4
                //correct polinomial without increasing L
                int newsize1 = 0;
                for(int j = 0; j < rulesize + x; j++)
                    if(j >= x){
                        if(addpol[j - x])
                            bool_toggle(&rule[j]);
                        if(rule[j])
                            newsize1 = j + 1;
                    }
                rulesize = newsize1;
                x++;
            }
            else{ //step 5
                //correct polinomial with increasing L
                //write C(D) -> tmp
                bool *tmp = malloc((rulesize) * (sizeof(bool)));
                uint32_t tmpsize = rulesize;
                for(int j = 0; j < rulesize; j++)
                    tmp[j] = rule[j];

                int newsize2 = 0;
                for(int j = 0; j < rulesize + x; j++)
                    if(j >= x){
                        if(addpol[j - x])
                            bool_toggle(&rule[j]);
                        if(rule[j])
                            newsize2 = j + 1;
                    }
                rulesize = newsize2;
                //write tmp -> B(D)
                for(int j = 0; j < tmpsize; j++)
                    addpol[j] = tmp[j];

                addpolsize = tmpsize;

                L = i + 1 - L;
                x = 0;
        }
        if (L >= size * BYTE_SIZE / 2){
            printf("FIN\n");
            return L;
        }
    }
    printf("FINISH\n");
    return L;
}
