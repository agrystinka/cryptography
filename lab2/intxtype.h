//#include <bool>
#include <string>

//Size in bytes
#define INTX_TYPE_SIZE 128
constexpr int INTX_SIZE = INTX_TYPE_SIZE / 8;

#define LINE_LENGTH 64

class intx_t {
private:
    uint8_t *number;
protected:
    bool if_num(std::string);
    void put_zero();
    uint8_t get_num(char num);
    char get_char(uint8_t num);
public:
    intx_t();
    intx_t(std::string);
    intx_t(const intx_t &arg);
    intx_t(intx_t &&arg);
    ~intx_t();
    bool set_value(std::string);
    void print_value();
    std::string get_num();

    //c - return, a - current object, b - argument
    intx_t& operator=(const intx_t &arg);

    //arifmetical
    intx_t operator+(const intx_t& arg) const; //c = a + b
    intx_t operator-(const intx_t& arg) const; //c = a - b
    intx_t operator*(const intx_t& arg) const; //c = a / b; Mongomeri
    //binary
    intx_t operator&(const intx_t& arg) const; //c = a & b
    intx_t operator|(const intx_t& arg) const; //c = a | b
    intx_t operator^(const intx_t& arg) const; //c = a ^ b;
};
