    #include "aufgabe1.h"
    
    void::Horspool::setPattern(const std::string& pat){ //Pattern speichern
    this -> pat = pat;
    int d;
    char c;
    //Shift-Tabelle erstellen: 
    shift_table.push_back(std::make_pair(pat[pat.length()-1],pat.length()));
    //Hilfsfunktion make_pair für std::pair für zwei Typen
    for(unsigned int i=0; i < pat.length()-1; i++){
        bool vorhanden = false;
        for(unsigned j=0; j <= shift_table.size(); j++){ //Durchsuchung Shift-Tabelle
            if(shift_table[j].first == pat[i]){ //first = Buchstabe
            shift_table[j].second = pat.length()-i-1; //second = Distanz
            vorhanden = true;
            }
        }
        if (vorhanden == false){
            d = pat.length()-i-1; //-1, da letzte Stelle nicht beachtet bei Lookup table
            c= pat[i];
            shift_table.push_back(std::make_pair(c,d));
        }
    }
}
//m-j

const std::string& Horspool::getPattern() const{
    return pat;
}
//zugriff auf shiftdistance wenn Mismatch
uint32_t Horspool::getShift_(const char last_char) const{ //letztes Symbol im Text    
    
    for(uint32_t k = 0; k < shift_table.size(); k++){
        if(shift_table[k].first == last_char){ //ist last_char in shifttabelle? 
            return shift_table[k].second; //Distanz
        }     
    }
    return pat.length(); // für * wenn nicht vorhanden
}
 
//Orientierung am Pseudocode
std::vector<size_t> Horspool::getHits(const std::string& text) const{

std::vector<size_t> hits = {}; 
size_t n = text.length();
size_t m = pat.length();
size_t pos=0;//aktuelle Position
size_t shift_dist;


    if(text.length() >= pat.length()){

        while(pos <= n-m){ //solange pos im Text 

            alignCheck_(pos);
            size_t j = m-1; // -1, da Indexverschiebung
                  
                while((j>0) && ((text[pos+j]) == (pat[j]) || pat[j]=='?' || text[pos+j] == '?' )){             
                    j--; //Solange die Bedingung gilt => von links nach rechts 
                }
                
                //Wenn vollständiges Patternmatch gefunden wird: => pos kommt in hits
                if((j==0) && ((text[pos+j]) == (pat[j]) || pat[j]=='?' || text[pos+j] == '?')){
                        hits.push_back(pos);
                    }
                
                //Berechnung Verschiebungsdistanz:
                char last_char=text[pos+m-1];
                shift_dist = getShift_(text[pos+m-1]); //Aufruf von getShift
                if (pat[m-1] == '?' ||last_char == '?') {
                shift_dist = 1;
            }
                pos = pos + shift_dist;
        }

        
        
        
    }
    
    return hits;
}
