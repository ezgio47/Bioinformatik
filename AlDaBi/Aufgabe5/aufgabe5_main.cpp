#include "QGramIndex.hpp"
#include "a5_util.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main(int argc, const char* argv[]){
        if(argc!=3){
			std::cout<<"unexpected input"<<std::endl;
			return 1;
		}
        std::string text;
        std::ifstream myfile(argv[1]);
        std::string query=argv[2];
        uint32_t a = query.length(); //Länge soll ausgegeben werden

        std::getline(myfile,text);
        myfile.close();
        uint8_t q=query.size();
        QGramIndex qind=QGramIndex(text,q); // Konstruktor aufrufen
        uint32_t h=qind.hash(query);
        std::vector<uint32_t> hash=qind.getHits(h);
        std::cout<<query<<": ";
        std::cout << a << " " ;
        for(unsigned i=0; i<hash.size(); i++){
                std::cout<<hash[i]<<" ";
        }
        std::cout<<std::endl;
}
