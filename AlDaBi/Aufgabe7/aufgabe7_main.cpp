#include <iostream>
#include <string>
#include "PDA.hpp"

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << "Falsche Eingabe" << std::endl;
        return 1;
    }
    std::string input = argv[1];
    PDA::State state{PDA::State::IN_PROGRESS};

    if(input[0] != '(' || input[0] != ')'){ //Klammernüberprüfung
        input = input + "$";

    }
    
    if(state == PDA::State::SUCCESS){
        std::cout<<"ACCEPT" << std::endl;
        return 0;
        PDA pda{PDA::Language::HAIRPIN};
        //Aufruf der Objekten für zB die B´Verarbeitung des nächsten Zustands:
        for (int current = 0; state == PDA::State::IN_PROGRESS && current < input.size(); ++current){
        state = pda.next(input[current]);
        }
    }
    else{
         std::cout << "Wir akzeptieren keine Brackets" << std::endl;
    }

    if(state == PDA::State::SUCCESS){
        std::cout<<"ACCEPT" << std::endl;
        return 0;
    }
    else{
    std::cout<<"FAIL" << std::endl;
    return 1;
    }
}