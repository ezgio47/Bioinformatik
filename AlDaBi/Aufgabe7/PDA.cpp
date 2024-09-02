#include <iostream>
#include "PDA.hpp"
//Funktion crasht und ist unvollständig


PDA::PDA(const Language l){ //Konstruktor mit Parameter für Übergangsregeln basierend auf language
    if(l == Language::BRACKETS){ //Funktion wird umgehend beeendet
        return;
    }
    //Produktionsregeln für RNA Hairpins werden in die rules-Map eingefügt Paarweise
    else if(l == Language::HAIRPIN){
    rules[{'a', '$'}] = "u1"; //Stapel-Top ist a und Endsymbol $ //u1 wird auf den Stapel gepusht
    rules[{'c', '$'}] = "c1";
    rules[{'g', '$'}] = "c1"; 
    rules[{'u', '$'}] = "a1";
    rules[{'a', '1'}] = "u2";
    rules[{'c', '1'}] = "g2";
    rules[{'g', '1'}] = "c2";
    rules[{'u', '1'}] = "a2";
    rules[{'a', '2'}] = "u3";
    rules[{'c', '2'}] = "g3";
    rules[{'g', '2'}] = "c3";
    rules[{'u', '2'}] = "a3";
    rules[{'g', '3'}] = "4"; 
    rules[{'a', '4'}] = "aa"; 
    rules[{'c', '4'}] = "aa";
    }
} //rules verwendet std::map<std::pair<char, char>, string> rules
//pair<char,char> für jedes Paar von Zeichen 

void PDA::reset(){ //Soll PDA in seinen Anfangszustand setzten
//Sollte stack geleert werden? 
//Sollte eventuell all_good zurückgesetzt werden?
    stack = std::stack<char>({'$'}); //wird mit neuem Standard-Element initialisiert mit std::stack Objekt
// Wenn Zustand repräsentiert wird, vielleicht all_good = true?
}

//Bestimmung des nächsten Zustands:mit Parameter a, der gelesen werden soll
PDA::State PDA::next(const char a){ //Warnung im Terminal: Funktion gibt keinen Wert zurück, es ist kein void!!
//Einige Implementierungen zum nächsten Zustand des PDA fehlen wohl, konnte nicht fixen.
//Implementierung für ungültige Eingabesymbole fehlen?
    std::pair<char, char> stack_top = {a, stack.top()}; //Eingabezeichen a und Stapel-top zum Paar machen
    stack.pop(); //Stapel-Top wird von stack entfernt durch pop()
    //pop() entfernt oberstes element im Container 

    std::string no_ter = "$1234"; 
    bool is_variable = true; //Oberstes Symbol ist eine Variable/Terminal?
    for(char nt : no_ter){  
        if (stack_top.second == nt){  //Ist zweites Element vom Paar stack_top = nt??
            is_variable = false; 
        }
    }
    //Prüfung des aktuellen Zustands: zB a == Stapel-top-Symbol(oberst. Element im Stapelspeicher)
    
    if (stack_top.first == stack_top.second || rules.count(stack_top)) {
        //count durchsucht map oben, Gibt es eine gültige Regel für die aktuelle Situation
    if (stack_top.first == stack_top.second) { 
    //Also Symbole oberstes Element und Eingabe gleich
        for (auto s : rules[stack_top]) { //dazugehörige Symbole der Regelanwendung in stack pushen
            stack.push(s);
        }
    }
    return State::IN_PROGRESS;//Zustand //Verarbeitung nicht abgeschlossen
    }
    else if(is_variable == false){ 
        return State::FAIL; //count findet keine gültige Regel => Ungültiger Zustand
        //Eingabe entspricht nicht der Sprache 
    }
    //aktuelles Zeichen a == $ UND Oberstes Element == $?
    else if(a == '$' && stack_top.second == '$'){
        return State::SUCCESS;//Eingabe entspricht der Sprache und wurde erfolgreich verarbeitet.
    }
 //Am ende sollte zB. return State::IN_PROGRESS sein
}