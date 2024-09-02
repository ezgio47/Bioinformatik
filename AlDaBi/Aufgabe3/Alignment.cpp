#include "Alignment.hpp"
#include <iostream>
//optimales-lokales-Sequenzalingnment: Smith-Watermann
//Unterschied der Matrixaufspannung: Smith-Watermann wird score-Matrix komplett mit Nullen initialisiert, es gibt keine negativen Werte

Alignment::Alignment(const std::string& seq_v, const std::string& seq_h): //initialisiert Objektvariablen
    seq_v(seq_v),//Initialisierung Vertikal
    seq_h(seq_h) // Initialisierung horizontal
{} //Construktor-Körper

enum class traceback_values{ //Tutor sagt enum class statt plain enum
    horizontal,
    vertikal,
    diagonal,
    leer //Kein Alignment
    };
    //Reihenfolge für Schleifen: diagonal,vertikal,horizontal

void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align){ // local_alignwert später von main übergeben wird und von Anzahl der Eingaben abhängt
    
    this-> vorhanden = true; //compute kann ausgeführt werden
    uint32_t size_h = seq_h.size()+1; //+1 um Platz für den Null-Index zu schaffen
    uint32_t size_v = seq_v.size()+1;

    if(seq_v.empty() && seq_h.empty()){
        this->a1 = ""; //leer
		this->a2 = ""; //leer
		this->gap = ""; //leer
		this->score = 0;
		return;
    }  
    
    //Anzahl der Zellen in Matrix: 
    std::vector<int> score_matrix(size_h*size_v,0); //erstellen der score-Matrix, Initialisierung mit Nullen
    //Zeile mal Spalte
    std::vector<traceback_values> traceback(size_h*size_v,traceback_values::leer); //ertsellen der traceback-Matrix, Initialisierung leer
    int d; //  diagonal
    int v; //  vertikal
	int h; //  horizontal
    //vergleiche übersichtlicher 

    uint32_t i; //Zeile
    uint32_t j; //Spalte //Nutzung für Traceback
    //Stelle, an der Maximun liegt, gespeichert in pair

    if(!local_align){ //Needleman - Wunsch
        //Initialisierung: erste Spalte,Zeile mit gap-penalty
        for(uint32_t i = 0; i < size_h; i++){//horizontal erste Zeile
			score_matrix[i] = i*gap;
			traceback[i]= traceback_values::horizontal;
		}
		for(unsigned j = 0; j < size_v; j++){//vertikal erste Spalte
			// Matrix an Stelle j*a + 0
			score_matrix[j*size_h]=j*gap;
			traceback[j*size_h]= traceback_values::vertikal;
		}

        //Matrix befüllen

        for (uint32_t i = 1; i < size_h; i++){ //horizontal
            for (uint32_t j = 1; j < size_v; j++){ //vertikal
            int current = j*size_h+i; //Aktuelle pos mit i=horizintaler Verschiebung

                if (seq_v[j-1] == seq_h[i-1]){ //String beginnt bei 0, deshalb -1
                    d = score_matrix[(j-1)*size_h+(i-1)] + match;
                }
                else{
                    d = score_matrix[(j-1)*size_h+(i-1)] + mismatch;
                }

                v = score_matrix[(j-1)*size_h+i] + gap;
                h = score_matrix[j*size_h+(i-1)] + gap; 
				
                if (d >= h && d>= v){
					score_matrix[current] = d;
					traceback[current] = traceback_values::diagonal; //diagonal bester Wert
				}
                else if(v >= d && v >=h){
					score_matrix[current] = v;
					traceback[current] = traceback_values::vertikal; //horizontal bester Wert
				}
                else{
					score_matrix[current] = h;
					traceback[current] = traceback_values::horizontal; //vertikal bester Wert
				}
            }
            
        }    
        this->score = score_matrix[size_h*size_v-1]; // Wert an letzter Stelle des Matrixvektors
    
    	i = size_h-1; 
    	j = size_v-1;
    }
    else{ //Smith_Waterman
        //throw std::invalid_argument("Error: Compute was not called");
        int max_value = 0; //höchster Alignment Score
        std::pair<uint32_t,uint32_t> pos; //pos für Zeile und Spalte
        for(uint32_t i = 1; i < size_h; i++){ 
            for(uint32_t j = 1; j < size_v; j++){
                
                int current = j*size_h+i; //aktuelle pos
                
                if (seq_v[j-1] == seq_h[i-1]){ //String beginnt bei 0, deshalb -1
                    d = score_matrix[(j-1)*size_h+(i-1)] + match;
                }
                else{
                    d = score_matrix[(j-1)*size_h+(i-1)] + mismatch;
                }

                v = score_matrix[(j-1)*size_h+i] + gap;
                h = score_matrix[j*size_h+(i-1)] + gap; //leicher, als immer zu schreiben
				
                if (d >= h && d>= v){
					score_matrix[current] = d;
					traceback[current] = traceback_values::diagonal; //diagonal bester Wert
				}
                else if(v >= d && v >=h){
					score_matrix[current] = v;
					traceback[current] = traceback_values::vertikal; //horizontal bester Wert
				}
                else if(h >= d && h>= v){
					score_matrix[current] = h;
					traceback[current] = traceback_values::horizontal; //vertikal bester Wert
				}

                if(score_matrix[current] <0){ //unterschied zu Needleman-Wunsch: keine negativen Werte erlaubt
                    score_matrix[current] = 0;
                    traceback[current] = traceback_values::leer;
                }

                if(score_matrix[current] >= max_value){
                    max_value = score_matrix[current];
                    pos.first = j;
                    pos.second = i;
                }

            }
        }
        this->score = max_value;

        i = pos.second;
        j = pos.first;
    }
    
//Traceback verfolgen+
    this->a1.clear();
	this->a2.clear();
	this->gap.clear(); //vor jedem Durchgang vorheriges löschen

    for( ; i+j > 0 ;){
        //Weg von (size_h*size_v) bis (0;0)
        if(traceback[j*size_h+i] == traceback_values::leer){
            break; //gibt keinen Weg
        }
        else if(traceback[j*size_h+i] == traceback_values::diagonal){
            if(seq_h[i-1] == seq_v[j-1]){
                this->gap = '|' + this->gap; //Hinzufügen eines Striches bei Match, an Anfang von gap string
            }
            else{
                this->gap = ' ' + this->gap; //kein Strich, da Mismatch
            }

            this->a1 = seq_v[j-1] + this->a1; // Buchstabe wird vorne angefügt, da wir von hinten durchgehen
			this->a2 = seq_h[i-1] + this->a2;
			j--;
			i--;
        }
        else if (traceback[j*size_h+i] == traceback_values::horizontal){ //horizontal
			this->a1 = '-' + this->a1;
			this->a2 = seq_h[i-1] + this->a2;
            this->gap = ' ' + this->gap;
			i--;
		}
		else { // vertikal			
			this->a1 = seq_v[j-1] + this->a1;
			this->a2 = '-' + this->a2;
            this->gap = ' ' + this->gap;
			j--;
		}
    }
    score_matrix.clear();
    traceback.clear();    
}

int Alignment::getScore() const{
    if (vorhanden == false){
        throw std::invalid_argument("Error: Compute was not called");
    }
    return score;
}

void Alignment::getAlignment(std::string& a1, std::string& gaps, std::string& a2) const{
    if (vorhanden == false){
        throw std::invalid_argument("Error: Compute was not called");
    }
    else{
        a1 = this->a1;
		gaps=this->gap;
		a2=this->a2;
    }
}