#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

const int SOMETHINGFOUND=0;
const int NOTHINGFOUND=1;
const int INVALIDCOMMANDLINE=2;
const int CANNOTOPENTHEFILE=3;

void loadDictionnary(string filepath, multimap<string, string> *myDictionary){
    ifstream file(filepath);
    string line;
    string linekey;
    while(getline(file, line)) 
    {
        linekey = line;
        transform(linekey.begin(), linekey.end(), linekey.begin(), ::tolower);
        sort(linekey.begin(), linekey.end());
        myDictionary->insert(pair<string, string> (linekey, line));
    }
    file.close();
}

int main(int argc, char **argv){
    if(argc != 3 || argv[1] != string("-d")){
        cout << INVALIDCOMMANDLINE << std::endl;
        return EXIT_FAILURE;
    }

    ifstream infile(argv[2]);
    if(!(infile.good())){
        cout << CANNOTOPENTHEFILE << std::endl;
        return EXIT_FAILURE;
    }

    string input;
    int codeDeFin = NOTHINGFOUND;
    multimap<string, string> myDictionary;
    loadDictionnary(argv[2],&myDictionary);
    
    while (getline(cin, input)){
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        sort(input.begin(), input.end());

        if (myDictionary.find(input) != myDictionary.end()){
            if(codeDeFin == NOTHINGFOUND){
                codeDeFin = SOMETHINGFOUND;
            }
            std::pair<std::multimap<string,string>::iterator, std::multimap<string,string>::iterator> ret;
            ret = myDictionary.equal_range(input);
            for (std::multimap<string,string>::iterator it = ret.first; it != ret.second; ++it){
                cout << it->second << endl;
            }
        }
   }
    std::cout << codeDeFin << std::endl;

    return 0;
}