#include <iostream>
#include <vector>
#include <string>

#include "Alignment.hpp"

using namespace std;

int main(int argc, const char* argv[]){
	std::string a1;
	std::string a2;
	std::string gaps;
	int score;

	if((argc !=3) && (argc !=6) && (argc !=7)){ //darf nur eine der 3 Möglichkeiten sein
		std::cout<< "Falsche Parameteranzahl" << std::endl;
		exit(1);
	}

	if (argc == 3)
	{
		//Needleman-Wunsch mit (3,-1,-2)
		Alignment al = Alignment(argv[1], argv[2]);
		al.compute(3, -1,-2);
		al.getAlignment(a1, gaps, a2);  
		score=al.getScore(); 
	}
	else if (argc == 6)
    {		
		Alignment al = Alignment(argv[1], argv[2]);
    	int a3 = std::atof(argv[3]); // atof speichert strings als ints
    	int a4 = std::atof(argv[4]);
    	int a5 = std::atof(argv[5]);

		al.compute(a3,a4,a5);
		al.getAlignment(a1, gaps, a2);
		score=al.getScore();   
    }
	else{
		Alignment al = Alignment(argv[1], argv[2]);
		//Smith-Waterman, wenn siebtes Argument
		int a3 = std::atof(argv[3]);
    	int a4 = std::atof(argv[4]);
    	int a5 = std::atof(argv[5]);
    
		al.compute(a3,a4,a5,true);
		al.getAlignment(a1, gaps, a2); 
		score=al.getScore(); 
	}  
	
	std::cout << a1 << std::endl;
	std::cout << gaps << std::endl;
	std::cout << a2 << std::endl;
	std::cout << "score:" << score << std::endl; 
}