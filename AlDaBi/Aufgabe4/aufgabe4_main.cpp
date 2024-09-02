#include "BLAST_Neighborhood.hpp"
#include "a4_util.h"

#include <iostream>
#include <omp.h>

int main(int argc, char const *argv[]){
    if(argc == 6){
        BLAST_Neighborhood BN{};

        ScoreMatrix m{};
        m.load(argv[2]); //zweites Eingabeargument

        double time = -omp_get_wtime();
        std::vector<NHResult> neighborhood = BN.generateNeighborhood(argv[1], m, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        time += omp_get_wtime();

        for(auto i : neighborhood){
            std::cout << i.infix << ":";
            for(auto j : i.neighbors){
                std::cout << "(" << j.first << " " << j.second <<") ";
            }
            std::cout << std::endl;
        }
        std::cout << "time: " << time << "sec" << std::endl;

        return 0; 
    }
    else{
        std::cerr << "Input muss diese Form haben: <SEQ> <SCORE_MATRIX> <WORD_SIZE> <THRESHOLD> <THREADS>" << std::endl;

        return 1; 
    }
}