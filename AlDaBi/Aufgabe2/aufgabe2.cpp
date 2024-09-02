#include <iostream>
#include <cstring> //für strcmpn
#include <algorithm> //für sort
#include <cmath> // für ceil
#include <string>
#include "aufgabe2.hpp"

void construct(std::vector<uint32_t>& sa, const std::string& text){
    sa.clear(); //sicherstellen, dass wir mit leerem VEktor starten

    if(text.length() == 0) return; //wenn text leer ist, abbruch

    for(unsigned i=0; i < text.length(); i++){ //erstellen es Suffixarrays; einfügen der Anfangsindices
        sa.push_back(i);
    }

    auto sortieren = [&] (const uint32_t& a, const uint32_t& b){ //Lambdafunktion wird sortiert mit Hilfe von strcmp (Lexicographical comparison)
        if(strcmp(&text[a], &text[b])<0)return true; //a soll vor b
        else return false;
        
    };

    std::sort(sa.begin(),sa.end(), sortieren); //sortieren der indices basierend auf ihrem lexikographischen string
}

void find(const std::string& query, const std::vector<uint32_t>& sa, const std::string& text, std::vector<uint32_t>& hits){
	hits.clear();
	
	if(text.size() < query.size() || text.size()==0 || query.size()==0){
		return;
	}
	int LP;
	int RP;
	int M;
	// Lp-Suche:
	
	if(!lexicographical_compare(text.begin()+sa[0],text.end(),query.begin(),query.end())){ // Pattern <= Text in sa an Stelle 0 
		LP=0; // 0, da Indexverschiebung
	}
	else if(lexicographical_compare(text.begin()+sa[text.size()-1],text.end(),query.begin(),query.end())){ // Pattern > Text in sa an Stelle text.size()-1
		LP= text.size(); // ist wie länge+1, da Indexverschiebung
	}
	else{

		int L=0;
		int R=text.size()-1;
		
		while((R-L)>1){//Distanz zwischen R und L
			M = (L+R)/2.0;
            M = ceil(M);
			if(!lexicographical_compare(text.begin()+sa[M],text.end(),query.begin(),query.end())){ // Pattern <= Text in sa an betrachteter Stelle M
				R=M;
			}
			else{
				L=M;
			}
		}
		LP=R; 
	}
	
	//Rp Suche:

	if(!lexicographical_compare(query.begin(),query.end(),text.begin()+sa[text.size()-1],text.begin()+sa[text.size()-1]+query.size())){ // Pattern >= Text in sa an letzter Stelle
		RP=text.size()-1; // weil Pattern > Text in sa an letzter Stelle und somit nicht enthalten
	}
	else if(lexicographical_compare(query.begin(),query.end(),text.begin()+sa[0],text.begin()+sa[0]+query.size())){ // Pattern < Text sa an erster Stelle
		RP=-1; // weil Pattern dann nicht in sa enthalten
	}
	else{ //Pattern liegt zwischen Suffixen
		int L=0;
		int R=text.size()-1;
		
		while((R-L)>1){
			M = (L+R)/2.0;
            M = ceil(M);
			if(!lexicographical_compare(query.begin(),query.end(),text.begin()+sa[M],text.begin()+sa[M]+query.size())){ // Pattern >= sa an betrachteter Stelle M
				L=M;
			}
			else{
				R=M;
			}
		}
		RP=L;
	}
	//Verarbeitung der gefundenen hits:
	if(RP>=LP){ //Pattern im Text vorhanden
		int i = 0;
		while (i <= (RP - LP)) { //Durchlauf von index von LP bis RP
		    hits.push_back(sa[LP + i]);//+i um Ausgabe mit normalen Indexen von 1 beginnend zu bekommen
		    ++i;
		}
	}
	else{
		hits.clear();
	}

	sort(hits.begin(),hits.end(), [&](int a, int b){
		return a<b;
	});
}
