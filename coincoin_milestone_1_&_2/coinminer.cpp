#include <string.h>
#include <openssl/sha.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
    unsigned char TRIOWN[] = "DST";
    unsigned char PROTO[6] = "CC1.0";
    unsigned char RESERVED[7] = "0f0f0f";

    const short LEN_COIN = 60;
    const short LEN_NONCE =32;

    using namespace std;

    // Ma classe abstraite coincoin
    class Coincoin
    {
    public:
        virtual std::vector<unsigned char> gen_nonce(std::vector<unsigned char> chars, short len_nonce)=0;
        virtual std::string type_coin(short coin)=0;
        virtual void gen_coin(short len_nonce,std::vector<unsigned char> nonce, char* timestamp,unsigned char (&coin)[60], unsigned char (&obuf)[41],unsigned char *triown)=0;
        virtual short countNumberOfC(unsigned char* obuf, short cptC)=0;
        virtual void estimation(short numberofC, float time)=0;
        virtual inline void show_coin(unsigned char pieceOfCoin)=0;
        virtual bool isNumber(const string& str)=0;
    };

    // Ma classe Coinminer
    class Coinminer : Coincoin
    {
        private:

        public:
        // Mon constructeur et destructeur Coinminer
        Coinminer() {}
        ~Coinminer(){}

        /*   Les fonctions de ma classe coinminer    */
        vector<unsigned char> gen_nonce(vector<unsigned char> chars, short len_nonce){
            chars.clear();
            // caractères ascii imprimables ([32-126])
            for (int i = 0; i < len_nonce; i++)
            {
                chars.push_back(((rand() % ((94) +1))+32));
            }
            return chars;
        }

        inline void show_coin(unsigned char pieceOfCoin){
            printf("%02x", pieceOfCoin);
        }

        string type_coin(short coin){
            switch (coin)
            {
            case 6:
                return "subcoin";
            case 7:
                return "coin";
            case 8:
                return "hexcoin";
            case 9:
                return "arkenstone";
            case 10:
                return "blackstar";
            case 11:
                return "grand cross";
            default:
                return "miette";
            }
        }

        void gen_coin(short len_nonce ,vector<unsigned char> nonce, char* timestamp,unsigned char (&coin)[60], unsigned char (&obuf)[41], unsigned char *triown){
            nonce = gen_nonce(nonce, len_nonce);
            get_timestamp(timestamp);
            memcpy(coin,reinterpret_cast<char*>(nonce.data()),33);
            memcpy(coin+len_nonce, "-", 2); //32
            memcpy(coin+len_nonce+1, triown, 4); //36
            memcpy(coin+len_nonce+4, "-", 2); //37
            memcpy(coin+len_nonce+5, PROTO, 6); //42
            memcpy(coin+len_nonce+10, "-", 2);//43
            memcpy(coin+len_nonce+11, timestamp, 10);//53
            memcpy(coin+len_nonce+21, "-", 2);//54
            memcpy(coin+len_nonce+22, RESERVED, 7);//60
            SHA1(coin, 60, obuf);
        }

        short countNumberOfC(unsigned char* obuf, short cptC=0){
            for (short elt = 0; elt < 20; elt++)
            {
                if(obuf[elt]==204){
                    cptC+=2;
                }else if(obuf[elt] >= 192 && obuf[elt] < 207){
                    cptC++;
                    break;
                }else{
                    break;
                }
            }
            return cptC;
        }

        void estimation(short numberofC, float time){
            if(numberofC < 12){
                for (short i = numberofC; i < 12; i++)
                {
                    if(i == numberofC){
                        std::cout << i  << "c ("<< type_coin(i) <<") \t\t";
                        printf("%.2f s \t\t (%.1f h) \n",time, (time/3600));
                    }else{
                        time = (int)time*16;
                        std::cout << i  << "c ("<< type_coin(i) <<") \t\t";
                        printf("%.0f s \t\t (%.1f h) \n",time, (time/3600));
                    }
                }
            }
        }

        template <typename T>
        T* get_timestamp(T *timestamp){
            time_t now;
            now = time(0);
            std::string now_converted = to_string((int)now);
            short now_len = now_converted.length();

            while (now_len > 10){
                now = time(0);
                now_converted = to_string((int)now);
                now_len = now_converted.length();
            }
            if(now_len < 10){
                string addLeftZero="";
                for (size_t i = 0; i < 10-now_converted.length(); i++)
                {
                    addLeftZero += "0";
                }
                now_converted = addLeftZero+now_converted;
            }
            strcpy(timestamp, now_converted.c_str());
            return timestamp;
        }

        bool isNumber(const string& str)
        {
            return str.find_first_not_of("0123456789") == string::npos;
        }

    };




// Mon Main
int main(int argc, char **argv) {
    Coinminer miner;
    //test the arguments
    try {
      	if (argc == 2 && argv[1]!=string("-z")){throw 2;}
        if (argc == 5 &&(argv[1]!=string("-t") || strlen(argv[2])!=3  || argv[3]!=string("-m") || !miner.isNumber(argv[4]))) {throw 5;}
        if((argc>2 && argc < 5) || (argc > 5)){throw 7;}
    } catch (int nbArg ) {
        if(nbArg==2){cout << "You have to run with ./coinminer -z";}
        else if (nbArg==5){cout << "./coinminer -t TRI -m X\n (X: number)\n";}
        if(nbArg==7){cout << "You have to run with ./coinminer  or ./coinminer -z or ./coinminer -t TRI -m X \n";}
        exit(EXIT_FAILURE);
    }

    // create a new process
    // fork();
    srand( (unsigned)time(NULL) );
    vector<unsigned char> nonce {};
    nonce.reserve(LEN_NONCE);
    char timestamp[11];
    unsigned char coin[LEN_COIN];

    unsigned char obuf[41];

    short cptC = 0;
    short numberof_c_desired;

    if(argc == 5 && argv[1]==string("-t") && argv[3]==string("-m")){
        unsigned char tmp[4];
        for (size_t i = 0; i < strlen(argv[2]); i++)
        {
            tmp[i] = argv[2][i];
        }

    	while (true)
        {
            miner.gen_coin(LEN_NONCE,nonce, timestamp, coin, obuf, tmp);
            cptC=miner.countNumberOfC(obuf);
            numberof_c_desired = atoi(argv[4]);
            if(cptC>=numberof_c_desired){//number of c desired
                cout << coin <<endl;
                for(short i = 0; i < 20; i++) {
                    miner.show_coin(obuf[i]);
                }
                cout << endl;
                cptC = 0;
            }
        }
    }

    //if we have two parameters
    if(argc == 2 && argv[1]==string("-z")){
        using namespace std::chrono;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        high_resolution_clock::time_point t2;
        duration<double> time_span;
        float time;

        while (true)
        {

            miner.gen_coin(LEN_NONCE,nonce, timestamp, coin, obuf, TRIOWN);
            cptC=miner.countNumberOfC(obuf);
            if(cptC>=6){
                t2 = high_resolution_clock::now();
                time_span = duration_cast<duration<double>>(t2 - t1);
                time = time_span.count();
                cout << "Starting benchmark…" <<endl;
                std::cout << cptC << "c (" << miner.type_coin(cptC) << ") mined in ";
                printf("%.2f s \n", time);
                cout << "*** Mining projections ***" << endl;
                miner.estimation(cptC,time);
                cout << coin <<endl;
                for(short i = 0; i < 20; i++) {
                    miner.show_coin(obuf[i]);
                }
                cout << endl;
                cptC = 0;
                break;
            }
        }
    }else if(argc==1){
            while (true)
            {
                miner.gen_coin(LEN_NONCE, nonce, timestamp, coin, obuf, TRIOWN);
                cptC=miner.countNumberOfC(obuf);
                if(cptC>=1){
                    cout << coin << "\n\t"<<endl;
                    for(short i = 0; i < 20; i++) {
                        miner.show_coin(obuf[i]);
                    }
                    cout << "\n";
                    cptC = 0;
                }
            }
        }


    return 0;
}
