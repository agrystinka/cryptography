#include <iostream>

//template <typename T>

typedef int T;
class ISRSAC {
private:
    T p, q;
    T m;
    T n;
    int r;
    T lamda;
    T decryption_key, encryption_key;
public:
    ISRSAC();
    ISRSAC(T, T);
    ~ISRSAC();
};
