#include "RSA_decoder.h"

string out_file_name="file.txt";
string in_file_name="cipher_text.txt";

RSA_decoder::RSA_decoder(){
    in_file.open(in_file_name,ios::in);
    out_file.open(out_file_name,ios::out);
}

RSA_decoder::~RSA_decoder(){}

void RSA_decoder::run(){
    cout<<"Please input the key-1 : ";//protocol
    cin>>key1;
    cout<<endl;
    cout<<"Please input the key-2 : ";//d
    cin>>key2;
    cout<<endl;
    cout<<"Please input the key-3 : ";//n
    cin>>key3;
    cout<<endl;
    cout<<"<------------------------------[after restoring]------------------------------>\n"<<endl;

    while(!in_file.eof()){
        unsigned long long c, m;
        in_file>>c;
        m=exp_mod(c,key2,key3);

        int power=-1;
        unsigned long long test=1;
        while(m>test){//find the highest power.
            test*=key1;
            power++;
        }
        for(int i=power;i>=0;i--){
            unsigned long long position=1;
            for(int j=0;j<i;j++) position*=key1;
            int _count=0;
            while(_count*position<=m) _count++;
            m-=(_count-1)*position;
            char ch=_count-1;
            out_file<<ch;
            cout<<ch;
        }
    }
    in_file.close();
}
unsigned long long RSA_decoder::exp_mod(unsigned long long a,unsigned long long n,unsigned long long b){
    unsigned long long r=1;
    while(n){
        if(n&1)r=(r*a)%b;
        a=(a*a)%b;
        n=n>>1;
    }
    return r;
}
