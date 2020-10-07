#include "lsfr.h"

inline bool check_bit_32(uint32_t num, uint8_t bit_num)
{
    return (num & (1 << bit_num)) != 0;
}


bool lsfr_1_32_r(uint32_t rule, uint8_t bitness, uint32_t *seed)
{
    bool res = check_bit_32(*seed, bitness - 1); //save hight bit

    //refresh lsfr for next cycle
    *seed <<= 1; //shift all bits
    //high is stored as low
    if(res)  *seed |= 1;
    else     *seed &= 0xfffffffe;
    //xor some bits using rule
    if(res){
        *seed = *seed ^ (rule << 1);
        uint32_t tmp = 0;
        for(int i = 0; i < bitness; i++)
            tmp = (tmp << 1) | 1;
        *seed &= tmp;
    }
    return res;
}

//x^4 + x^3 + 1
void rule_4_3(uint8_t *result, uint32_t num, uint32_t seed)
{
    uint32_t static cur_seed = 1;

    if(seed != 0)
        cur_seed = seed;

    for(int i = 0; i < num; i++){
        result[i] = 0;
        for(int j = BYTE_SIZE - 1; j >= 0; j--)
            if(lsfr_1_32_r(0xc, 4, &cur_seed))
                result[i] |= (1 << j);
    }
}

//x^8 + x^6 + x^5 + x^2 + 1
void rule_8_6_5_2(uint8_t *result, uint32_t num, uint32_t seed)
{
    uint32_t static cur_seed = 1;

    if(seed != 0)
        cur_seed = seed;

    for(int i = 0; i < num; i++){
        result[i] = 0;
        for(int j = BYTE_SIZE - 1; j >= 0; j--)
            if(lsfr_1_32_r(10110010, 8, &cur_seed))
                result[i] |= (1 << j);
    }
}

//x^9 + x^6 + x^4 + x^3 + 1
void rule_9_6_4_3(uint8_t *result, uint32_t num, uint32_t seed)
{
    uint32_t static cur_seed = 1;

    if(seed != 0)
        cur_seed = seed;

    for(int i = 0; i < num; i++){
        result[i] = 0;
        for(int j = BYTE_SIZE - 1; j >= 0; j--)
            if(lsfr_1_32_r(100101100, 9, &cur_seed))
                result[i] |= (1 << j);
    }
}

//x^10 + x^3 + 1
void rule_10_3(uint8_t *result, uint32_t num, uint32_t seed)
{
    uint32_t static cur_seed = 1;

    if(seed != 0)
        cur_seed = seed;

    for(int i = 0; i < num; i++){
        result[i] = 0;
        for(int j = BYTE_SIZE - 1; j >= 0; j--)
            if(lsfr_1_32_r(1000000100, 10, &cur_seed))
                result[i] |= (1 << j);
    }
}
