#include "SecureRandom.h"

SecureRandom::SecureRandom(unsigned int bits, unsigned int order){
    keyBits=bits;
    unsigned long long down_limit_number=1;
    unsigned long long up_limit_number=10;
    for(int i=1;i<bits;i++){
        down_limit_number*=10;
        up_limit_number*=10;
    }
    ///To find the order-th number, and store it.
    for(unsigned long long i=down_limit_number;i<up_limit_number;i++){
        bool flag=true;
        for(unsigned long long j=2;j*j<=i;j++){
            if(i%j==0){
                flag=false;
                break;
            }
        }
        if(flag){
            order--;
            if(order==0){
                number=i;
                break;
            }
        }
    }
}
SecureRandom SecureRandom::multiply(SecureRandom sr2){
    SecureRandom sr1;
    sr1.keyBits=sr2.keyBits+keyBits;//but not actual.
    sr1.number=sr2.number*number;
    return sr1;
}
SecureRandom SecureRandom::subtract(unsigned long long n){
    SecureRandom sr1;
    sr1.keyBits=keyBits;//but not actual.
    sr1.number=number-n;
    return sr1;
}
SecureRandom SecureRandom::gcd(SecureRandom sr2){
    SecureRandom sr1;
    if(sr2.number) while((number%=sr2.number)&&(sr2.number%=number));
    sr1.number=number+sr2.number;
    sr1.keyBits=keyBits;
    return sr1;
}
bool SecureRandom::equals(unsigned long long n){
    return number==n;
}
SecureRandom SecureRandom::mode_inverse(SecureRandom _phin){
    ///from 0 to the mode number, our mission is to find the modular inverse number of the target.

    SecureRandom sr1;
    unsigned long long _e=number;
    for(unsigned long long i=0;i<_phin.number;i++){//mode phin
        if((((_e*i)-1)%_phin.number)==0){
            sr1.number=i;
            break;
        }
    }
    sr1.keyBits=NBITS/2;
    return sr1;
}
ostream& operator<<(ostream& os, const SecureRandom& sr){
    os << sr.number << endl;
    return os;
}
void SecureRandom::set_value(unsigned long long num){
    number=num;
}
unsigned long long SecureRandom::get_number(){
    return number;
}
