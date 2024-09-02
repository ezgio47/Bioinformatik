#include <iostream>
#include "aufgabe2.hpp"
using namespace std;

int main(int argc,const char* argv[]){  //argc = Argument Count; zählt Anzahl der eingegebenen Argumente
                                        //argv = Argument Vektor; Array von Zeigern auf Zeichenkette(char Array)
    std::vector<uint32_t> sa{};
    const std::string& text = argv[1];
    std::vector<uint32_t> hits{};

    if(argc <= 1){
        std::cout <<"unexpectet input" << std::endl;
        return 1;
    }

    construct(sa,text);

    if(argc == 2){
        for(uint32_t i =0; i<sa.size(); i++){
        std::cout<< sa[i] << std::endl;
        }
    }

    else{
        for(size_t j=2; j < static_cast<size_t>(argc); j++){
            find(argv[j],sa,text,hits); //keine geschweiften Klammern, da main und Funktionskörper in cpp
                std::cout<<argv[j] << ":" << std::endl;

            for(uint32_t k = 0; k<hits.size(); k++){
                std::cout<<hits[k]<< std::endl;
            }
        std::cout<<"\n";
        }
    return 0;
    }
}
