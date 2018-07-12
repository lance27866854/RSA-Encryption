#include <iostream>
#define UPLIMIT 18446744073709551615    // the up limit of unsigned long long
#define NBITS 10                        //up limit is 18. (highly unrecommended)
using namespace std;

class SecureRandom{
    ///SecureRandom number is "prime-random number". Actually, the user can decide.

    public:
        SecureRandom(){keyBits=1,number=2;}
        SecureRandom(unsigned int, unsigned int);// keyBits and the order of the number users want to get.
        ~SecureRandom(){}
        SecureRandom multiply(SecureRandom);
        SecureRandom gcd(SecureRandom);
        SecureRandom mode_inverse(SecureRandom);
        SecureRandom subtract(unsigned long long);
        void set_value(unsigned long long);//just for debug
        bool equals(unsigned long long);
        unsigned long long get_number();
        void  printkey();
        friend ostream& operator<<(ostream&, const SecureRandom& );

    private:
        int keyBits;
        unsigned long long number;// keyBits bits.
};
