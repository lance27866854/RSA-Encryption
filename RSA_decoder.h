#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
using namespace std;

class RSA_decoder{
    public:
        RSA_decoder();
        ~RSA_decoder();
        void run();
        unsigned long long exp_mod(unsigned long long,unsigned long long,unsigned long long);

    private:
        ifstream in_file;
        ofstream out_file;
        int key1;//protocol
        unsigned long long key2, key3;//d, n
};
