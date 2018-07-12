#include "RSA_encoder.h"

string in_file_name="file.txt";
string out_file_name="cipher_text.txt";

RSA_encoder::RSA_encoder(){
    in_file.open(in_file_name,ios::in);
    out_file.open(out_file_name,ios::out);
}
RSA_encoder::~RSA_encoder(){}

void RSA_encoder::run(){
    ///In this function, we will encrypt the text into cipher-text by RSA encoder.
    ///While there are characters having to be encrypted in the file,
    ///this function would get 3(MEMBER) characters at a time using RSA algorithm to encrypt them into cipher-text "c".
    ///You would need the parameter MEMBER and PROTOCOL in this process.

    if(!in_file){
        cout<<"Fail to read the file.\n";
    }
    else{
        cout<<"<------------------------------[origin contains]------------------------------>\n"<<endl;
        int file_size=0;
        vector<char> v;
        while(!in_file.eof()){
            char ch;
            in_file.get(ch);
            if(file_size<MEMBER){
                file_size++;
                v.push_back(ch);
            }
            else{
                unsigned long long sum=0;
                int power=1;
                for(int i=MEMBER-1;i>=0;i--){
                    sum+=v[i]*power;
                    power*=PROTOCOL;
                }
                c=exp_mod(sum,e.get_number(),n.get_number());
                cipher_text.push_back(c);
                v.clear();
                v.push_back(ch);
                file_size=1;
            }
            cout<<ch;//print the contain of the original text.
        }
        if(!v.empty()){//if there are more or less characters in the file, we should handle them too.
            unsigned long long sum=0;
            int power=1;
            for(int i=v.size()-1;i>=0;i--){
                sum+=v[i]*power;
                power*=PROTOCOL;
            }
            c=exp_mod(sum,e.get_number(),n.get_number());
            cipher_text.push_back(c);
        }
        in_file.close();
        cout<<endl;
        cout<<"<------------------------------[RSA. encryption]------------------------------>\n"<<endl;
        int cur=0;
        for(int i=0;i<cipher_text.size();i++){
            out_file<<cipher_text[i];
            if(i!=cipher_text.size()-1)out_file<<" ";
            cout<<setw(12)<<cipher_text[i]<<" ";
            cur++;if(cur==6){cout<<endl;cur=0;}
        }
        cout<<endl<<endl;
        out_file.close();
        printKey();
    }
}

void RSA_encoder::key_gen(int ketbyte){
    ///explanation and some examples:
    ///The first step is to find two primes "p(9-bit unsigned)" and "q(9-bit unsigned)".
    ///Second, we have to find "n(18-bit unsigned)", which equals to p*q.
    ///Third we have to find "phin(18-bit unsigned)", which equals to (p-1)*(q-1).
    ///Fourth, we have to find the encryption key "e(9-bit unsigned)", which doesn't have the greatest common factor with phin.
    ///This will be complete with a while-loop function.
    ///Fifth, we have to find  the declassify key "(18-bit unsigned)", which is the result of the inverse mod of e.
    srand(time(NULL));

    SecureRandom sr1(NBITS/2, PARAMETER_P), sr2(NBITS/2, PARAMETER_Q);
    p=sr1;
    q=sr2;
    n=p.multiply(q);
    phin=p.subtract(1).multiply(q.subtract(1));

    SecureRandom ee;
    do{
        unsigned int rnd=(unsigned int)rand()%PARAMETER_RND+1;
        SecureRandom sr3(NBITS/2, rnd);
        ee=sr3;
        e=sr3;
    }while(!(ee.gcd(phin).equals(1)));

    d=e.mode_inverse(phin);
}
void RSA_encoder::printKey(){
    cout<<"<------------------------------[  cipher keys  ]------------------------------>\n"<<endl;
    cout<<"p = "<<p<<endl;
    cout<<"q = "<<q<<endl;
    cout<<"n = "<<n<<endl;
    cout<<"phin = "<<phin<<endl;
    cout<<"e = "<<e<<endl;
    cout<<"d = "<<d<<endl;
}
unsigned long long RSA_encoder::exp_mod(unsigned long long a,unsigned long long n,unsigned long long b){
    unsigned long long r=1;
    while(n){
        if(n&1)r=(r*a)%b;
        a=(a*a)%b;
        n=n>>1;
    }
    return r;
}
