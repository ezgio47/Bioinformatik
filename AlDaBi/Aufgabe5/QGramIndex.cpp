#include "QGramIndex.hpp"
#include <iostream>
#include "a5_util.hpp"
#include <cmath> //std::pow(Basis,Exponent)

QGramIndex::QGramIndex(const std::string& text, const uint8_t q): //Konstruktor
    text_r(text), q_r(q) 
{
    if(q < 1 || q > 13){ //Überprüfung!!!
    throw std::invalid_argument("Invalid q!");
    }
    else{
        std::string qgram_f = text_r.substr(0,q); //Erstellung Teilstring aus text_r
        uint32_t s= std::pow(4,q_r); //Berechnung Anzahl der möglichen Q-Gramme 4^q_r
        dir.resize(s); //Wird auf die Größe von s erweitert
        suftab.resize(text_r.size()-q+1); // wird auf die Größe von Anzahl der möglichen Positionen erweitert
        //Pseudocode aus Vorlesung:

        //Teil 1: Zähler auf setzen

        for(uint32_t j = 0; j < s; j++){ // s = Anzahl der möglichen q-gramme
            dir[j] = 0; 
        }

        //Teil 2: q-gramme zählen
        uint32_t in_dir = QGramIndex::hash(qgram_f); //Berechnung Hashwert für q-gramme
        dir[in_dir]++; //Zähler für q-gramme erhöhen

        for(uint32_t i = 0; i < text_r.length()-q ; i++){ 
        //Aktualisierung von dir und nächste Berechnung für q-gramme mit hashNext
            in_dir = QGramIndex::hashNext(in_dir,text[i+q-1]);
            dir[in_dir]++; //Erhöhung des Wertes um 1 mit Zähler
        }
        //Teil 3: kumultative Summe bilden
        for(uint32_t k = 1; k < s; ++k){
            dir[k] += dir[k-1]; // Wert an Position [k-1] wird an Position [k] berechnet.
        }
        dir_l = suftab.size(); //speichern für hits für spätere Berechnung

        //Teil 4: Vorkommen einsortieren
        uint32_t hash = QGramIndex::hash(qgram_f); //Hashwert-Berechnung für 1.q-gramm
        dir[hash]--; //hash wird in dir um 1 verringert
        suftab[dir[hash]]= 0; //Wert an Position [0] wird auf 0 gesetzt.

        for(uint32_t i = 1; i < text_r.length()-q; i++){ 
            hash = QGramIndex::hashNext(hash,text[i+q-1]); //Nächste Hashwert-Berechnung und Einsortierung
            dir[hash]--; //Hashwert wird um 1 verringert
            suftab[dir[hash]]= i; 
        }

    }
}

const std::string& QGramIndex::getText() const{
    return text_r;
}

uint8_t QGramIndex::getQ() const{
    return q_r;
}

uint32_t QGramIndex::hash(const std::string& qgram) const{ //Berechnung HashWert vom Q-Gramm
    uint32_t hash_value = 0; 
   
    //Folie 14
    if(qgram.length() == q_r){ // q_r ist erwartete Länge von Q-Gramm, nicht vergessen!!
        // Berechnung Hashwert:
        uint32_t i = 0;
        while(i < qgram.size()){ //durchläuft jedes Zeichen in q-gramm
            hash_value <<=2; //Verschibung von Hashwert aktuell um 2 Bits nach links
            hash_value |= ordValue(qgram[i]); //Kombination mit den aktuellen 2Bits des Zeichens im q-gramm
            //oldValue gibt den numerischen Wert des aktuellen Zeichens
            ++i; //dann nächstes Zeichen im q-gramm
        }
        return hash_value;
    }
    else{
        throw std::invalid_argument("Wrong QGram size"); //Bei nicht erwarteter Größe
    }    
}

//Folie 20 
//hashNext soll den nächsten Hashwert berechnen:
uint32_t QGramIndex::hashNext(const uint32_t prev_hash, const char new_pos) const{ 
    uint32_t mask = ~0 <<2*q_r; // in mask alle Bits auf 1 setzen und um 2*q_r nach links
    uint32_t hashValue = (prev_hash <<2) & ~mask; //~ = Bitwechseloperator // 2 Positionen nach links für zwei neue Bits
    //Alle Bits bis auf 2*q_r werden auf 0 gesetzt mit neg-mask.
    hashValue |= ordValue(new_pos); //Numerische Ordnung

    return hashValue;
}


//An welchen Positionen wurden q-gramme mit Hash-Wert h gefunden?
std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const{ 
    
    uint32_t s = std::pow(4,q_r); //Berechnung Anzahl der Hashwerte für q_r => 4^q_r
    if(h>= 0 && h<s){
    std::vector<uint32_t> hits{};
    uint32_t sa_f = dir[h]; //Anfang im Suffixarray mit Hashwert h
    uint32_t sa_l; //Ende im Suffixarray
    if (h == s-1){ //Entspricht h dem maximal möglichen Wert??
        //dir_l speichert länge des Suffixarrays
        sa_l = dir_l; //sa_l auf die Position des letzten Vorkommens
    }
    else {
        sa_l = dir[h+1]; //sa_l auf die Position des ersten Vorkommens im nächsten q-gramm
    }
    uint32_t pos_in_sa = sa_f;
    while(pos_in_sa < sa_l){
        hits.emplace_back(suftab[pos_in_sa]); //Position am Ende von hits einfügen
        pos_in_sa++; //zum nächsten Vorkommen usw...
    }
    return hits;
    }
    else{
        throw std::invalid_argument("Invalid hash"); //nächstes mal vielleicht erst thrown??
    }
}