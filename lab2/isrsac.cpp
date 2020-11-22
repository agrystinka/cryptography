#include "isrsac.h"
#include "log.h"


ISRSAC::ISRSAC()
{
    //Initialize p, q
    std::cout << "p =" << p << std::endl;
    std::cout << "q =" << q << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "m =" << m << std::endl;
    std::cout << "n =" << n << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "lamda =" << lamda << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "E =" << m << std::endl;
    std::cout << "D =" << n << std::endl;
    std::cout << "---------------------" << std::endl;
}

//template <typename T>
ISRSAC::ISRSAC(T argp, T argq)
{
    p = argp;
    q = argq;

    //calculate modulos
    m = p * q;
    n = p * q * (p - 1) * (q - 1);

    //find r
    r = 1;
    while((1 << r) < p && (1 << r) < q)
        ++r;
    --r;

    T tmp = 1 << r; //2^r

    //calculate lamda(n)
    lamda = (p - 1) * (q - 1) * (p - tmp) * (q - tmp);
    lamda /= tmp;

    //find keys

    std::cout << "Initialization" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "m = " << m << std::endl;
    std::cout << "n = " << n << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "r = " << r << std::endl;
    std::cout << "lamda = " << lamda << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "E = " << encryption_key << std::endl;
    std::cout << "D = " << decryption_key << std::endl;
    std::cout << "---------------------" << std::endl;

}


ISRSAC::~ISRSAC()
{

}
