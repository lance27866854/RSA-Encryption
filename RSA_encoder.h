#include "SecureRandom.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iomanip>

#define PARAMETER_P 134
#define PARAMETER_Q 392
#define PARAMETER_RND 91
#define PROTOCOL 128
#define MEMBER 3//It must be larger than 1.

using namespace std;

class RSA_encoder{
    public:
        RSA_encoder();
        ~RSA_encoder();
        void key_gen(int);
        void run();
        void printKey();
        unsigned long long exp_mod(unsigned long long,unsigned long long,unsigned long long);

    private:
        ifstream in_file;
        ofstream out_file;
        vector<unsigned long long> cipher_text;
        SecureRandom p, q, phin, d;//keep secret
        SecureRandom n, e;//public parameter
        unsigned long long m, c;
};
