#include "a4_util.h"
#include "BLAST_Neighborhood.hpp"

#include <iostream>
#include <stdexcept> //throw std::invalid_argument
#include <algorithm> // std::sort
#include <vector>

//Berechnung Score zwischen zwei Sequenzen (word && current_infix):
int BLAST_Neighborhood::calc_score(const std::string& word, const std::string& current_infix, const ScoreMatrix& matrix){
    int score = 0; // vorerst auf 0 setzen, wird aktualisiert

    //Durchlauf durch word und current_infix für Score-Berechnung
    for (uint32_t i = 0; i < word.size(); i++){
        score += matrix.score(word[i], current_infix[i]);
    }
    return score;
}

//nutzen um schneller voranzukommen
//Berechnung der besten potenziellen Nachbarn für jedes Zeichen in query:
void BLAST_Neighborhood::calc_best(const std::string& query, const ScoreMatrix& matrix){
    //Aminosäure:
    const std::vector<char> aminos = {'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V'};
                                        //Reihenfolge aus blosum62 übernommen
    for (uint32_t i = 0; i < query.size(); i++){
        if (!best.count(query[i])){ //Überprüfung ob Zeichen in best vorhanden?
             //Wenn nicht => Berechning Nachbarn und Speichern in best:
            std::vector<std::pair<char, int>> temporary; //Aminosäure && Score

        for (const char& c : aminos){ //iteriere durch Aminosäuren c in aminos
            temporary.emplace_back(c,matrix.score(query[i], c)); //Berechnung Score von Zeichen Query mit c
        }
        //sortieren absteigend der Nachbarn in Reihenfolge der score werten
        std::sort(temporary.begin(), temporary.end(), [] (std::pair<char, int> a, std::pair<char, int> b) {
            return a.second > b.second; //sortieren nach score
        });

        best[query[i]] = temporary; //speichert sort list in best
    }
  }
}

// Generiert Liste von Nachbarn für word and current:
void BLAST_Neighborhood::build_neighbors(const std::string& word, 
                                            const std::string& current,
                                            std::vector< std::pair <std::string, int>>& neighbor_list, 
                                            const int word_size,
                                            const int score_threshold, //Minimal akzeptabler Score
                                            bool& stop, //Suche beenden, wenn stop
                                            const ScoreMatrix& matrix){
    
    if (word.size() == static_cast<size_t>(word_size)){ //Überprüfung für gewünschte Wortlänge
        int score = calc_score(word, current, matrix); //Berechnung Score

    //Hat Score Schwellenwert erreicht oder überschritten??
    if (score >= score_threshold){ 
        neighbor_list.emplace_back(word, score); //Einfügen Score als Paar
    }
    else{
        stop = false; //Such NICHT beenden // Noch bessere Scores?
    }
    return;
     }

    //iteriere durch jede Aminosäure an der aktuellen position
    for (std::pair<char, int> pair : best[current[word.size()]]){
        if(!stop && pair != best[current[word.size()]][1]){ //stop=false? //Score aus best nicht zweitbeste Option
                stop = true; // dann stop Suche
                return; //Schlechtere erreichen Schwellenwert nicht
        }  


    std::string new_word = word + pair.first; //sonst new_word von aminos am ende von word

    //Aufruf der Funktion diesmal mit neuem word = new_word:
    build_neighbors(new_word, current, neighbor_list, word_size, score_threshold, stop, matrix);

    
    }
} //Static_cast => Konertierung des Types vom Wert
//Liste von Nachbarschaften für query
std::vector<NHResult> BLAST_Neighborhood::generateNeighborhood(const std::string& query,
                                               const ScoreMatrix& matrix,
                                               const int word_size,
                                               const int score_threshold,
                                               const int threads){
    best.clear(); 
    std::vector<NHResult> neighborhood; //Für Nachbarschaften
    //Gültige Anzahl von Threads?:
    if (threads < 1 ){ 
        throw std::invalid_argument("Ungültige Threadanzahl");
    }
    if(word_size < 1){
         throw std::invalid_argument("Was macht das für einen Sinn?");   
    }    
   
    if (static_cast<size_t>(word_size) > query.length()){ 
        return neighborhood; //leer
    }
    else if (query.empty()){
        return neighborhood; //leer
    }
    
    if (static_cast<size_t>(word_size) > query.length()){
        return neighborhood;
    } 

    neighborhood.resize(query.size() - word_size + 1); //Platz schaffen für Nachbarschaften mit resize
    
    calc_best(query, matrix); //Berechnung beste aminos in für jede Pos in query 
    
    // Beschleunigung mit Parallelisierung des Codeblockes:Anzahl Threads durch Threads festgelegt
    #pragma omp parallel for num_threads(threads)
    // Generierung der Nachbarschaften für jede Pos in query
    for (uint32_t i = 0; i <= query.size() - word_size; ++i){
        std::string current = query.substr(i, word_size); //Teilstring der Länge word_size ab i

        NHResult temp_neighborhood; 

        temp_neighborhood.infix = current; //current Zuweisung zu infix 

        std::vector< std::pair <std::string, int>> neighbor_list; //für gefundenen Nachbarn (Sequenzpaaar, Score)

        bool stop = true; //in built Neighbor die for-Schleife beenden

        //Hilfsfunktion, um Nachbarn und scores zu ermitteln
        // "" = Wortanfang
        build_neighbors("", current, neighbor_list, word_size, score_threshold, stop, matrix);

        std::sort(neighbor_list.begin(), neighbor_list.end()); //sortiert nach Alphabet

        //generierte Nachbarn Speicherung in temp_neighborhood
        temp_neighborhood.neighbors = neighbor_list;

        neighborhood[i] = temp_neighborhood; //Liste Nachbarschaften hier hinzufügen
    }
    return neighborhood;
}