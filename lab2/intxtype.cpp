#include "intxtype.h"
#include "log.h"

using namespace std;
#include <iostream>

intx_t::intx_t() : number{new uint8_t[INTX_TYPE_SIZE]{0}}
{
    _log("Initialize num as zero");
};

intx_t::intx_t(std::string num) : number{new uint8_t[INTX_TYPE_SIZE]{0}}
{
    if(!if_num(num)){
        _log("Failed attempt to initialize num as NON zero");
    }else{
        _log("Initialize num as NON zero");
        int i = num.length() - 1;
        int j = INTX_SIZE - 1;
        bool low = true;
        while(i >= 0){
            if(low){
                number[j] |= get_num(num[i]);
            }else{
                number[j] |= get_num(num[i]) << 4;
                --j;
            }
            low = !low;
            --i;
        }
    }
}

intx_t::intx_t(const intx_t &arg) : number{new uint8_t[INTX_TYPE_SIZE]{0}}
{
    _log("Initialize num in copy constructor");
    for(int i = 0; i < INTX_SIZE; ++i)
        number[i] = arg.number[i];
};

intx_t::intx_t(intx_t &&arg) : number{new uint8_t[INTX_TYPE_SIZE]{0}}
{
    _log("Initialize num in move constructor");
    for(int i = 0; i < INTX_SIZE; ++i)
        number[i] = arg.number[i];
    arg.number = nullptr;
};

intx_t::~intx_t()
{
    _log("Delete num");
    delete[] number;
};


intx_t& intx_t::operator=(const intx_t &arg)
{
    _log("Copy");
    for(int i = 0; i < INTX_SIZE; ++i)
        number[i] = arg.number[i];
    return *this;
};


void intx_t::print_value()
{
    for(int i = 0; i < INTX_SIZE; ++i){
        if(i % LINE_LENGTH == 0)
            std::cout << std::endl;
        std::cout << get_char((number[i] >> 4) & 0x0f) << get_char(number[i] & 0x0f) << " ";
    }
    std::cout << std::endl << std::endl;
}

//------------------------------------------------------------------------------
//arifmetical operators
//c - return, a - current object, b - argument
//------------------------------------------------------------------------------

//c = a + b
intx_t intx_t::operator+(const intx_t& arg)  const
{
    intx_t res;
    uint16_t tmp = 0;
    for(int i = INTX_SIZE - 1; i >= 0; --i){
        tmp += arg.number[i];
        tmp += this->number[i];
        res.number[i] = tmp;
        tmp >>= 8;
    }
    return res;
}

//c = a * b
intx_t intx_t::operator*(const intx_t& arg)  const
{
    intx_t res;
    uint16_t tmp = 0;
    for(int i = INTX_SIZE - 1; i >= 0; --i){
        tmp += arg.number[i];
        tmp += this->number[i];
        res.number[i] = tmp;
        tmp >>= 8;
    }
    return res;
}

//------------------------------------------------------------------------------
//c - return, a - current object, b - argument
//binary operators
//------------------------------------------------------------------------------

//c = a & b
intx_t intx_t::operator&(const intx_t& arg)  const
{
    intx_t res;
    for(int i = 0; i < INTX_SIZE; ++i)
        res.number[i] = arg.number[i] & this->number[i];
    return res;
}

//c = a | b
intx_t intx_t::operator|(const intx_t& arg)  const
{
    intx_t res;
    for(int i = 0; i < INTX_SIZE; ++i)
        res.number[i] = arg.number[i] | this->number[i];
    return res;
}

//c = a ^ b
intx_t intx_t::operator^(const intx_t& arg)  const
{
    intx_t res;
    for(int i = 0; i < INTX_SIZE; ++i)
        res.number[i] = arg.number[i] ^ this->number[i];
    return res;
}

//------------------------------------------------------------------------------
//service functions
//------------------------------------------------------------------------------

void intx_t::put_zero()
{
    for(int i = 0; i < INTX_SIZE; ++i)
        number[i] = 0;
    _log("Number is zero");
}

bool intx_t::if_num(std::string num)
{
    if(num.length() > INTX_SIZE * 2){
        _log("Invalid number in string. String is too long.");
        return false;
    }
    for(auto c : num)
        if(!((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))){
            _log("Invalid number in string. Invalid chars in number representation");
            return false;
        }
    return true;
}

uint8_t intx_t::get_num(char num)
{
    if (num >= '0' && num <= '9') return (uint8_t)(num - '0');
    if (num >= 'a' && num <= 'f') return (uint8_t)(num - 'a' + 10);
    if (num >= 'A' && num <= 'F') return (uint8_t)(num - 'A' + 10);
}

char intx_t::get_char(uint8_t num)
{
    if (num >= 0 && num <= 9) return num + '0';
    if (num >= 10 && num <= 15) return num - 10 + 'a';
}
