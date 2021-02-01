//
//  main.cpp
//  ListeDiListeEs31Genn
//
//  Created by Vasile Andrei Calin on 31/01/2020.
//  Copyright © 2020 Vasile Andrei Calin. All rights reserved.
//

#include <iostream>
using namespace std;



struct Prenotazioni{
    int idGruppo;
    string nome;
    string cognome;
    Prenotazioni* next;

    Prenotazioni(string nome,string cognome , int idGruppo){
        this->nome = nome;
        this->cognome = cognome;
        this->idGruppo = idGruppo;
    }


};

struct Turista{
    Turista* next;
    Prenotazioni* prenotazione;
};


struct Gruppi{
    int idGruppo;
    Gruppi*next;
    Turista* turisti;
    Gruppi(int idGruppo){
        this->idGruppo = idGruppo;
    }
};


void addCodaTuristi(Turista* &turista,Prenotazioni* &nuovaPrenotazione) {
    if (turista == NULL) {
        Turista* node = new Turista();
        node->next = NULL;
        node->prenotazione = nuovaPrenotazione;
        turista = node;

    } else{
        addCodaTuristi(turista->next,nuovaPrenotazione);
    }

}
void addGruppi(Gruppi *&rootG,Prenotazioni* nuovaPrenotazione,int idGruppo){
    Gruppi* nuovoNodo =new Gruppi(idGruppo);
    nuovoNodo->next = NULL;
    nuovoNodo->turisti = NULL;
    //se la lista dei gruppi è vuota
    if(rootG == NULL){

        addCodaTuristi(nuovoNodo->turisti,nuovaPrenotazione);
        rootG = nuovoNodo;
    }else{
        Gruppi *i;
        for(i = rootG;i->next != NULL && i->idGruppo != idGruppo;i = i->next);
        if(i->idGruppo == idGruppo){
            addCodaTuristi(i->turisti,nuovaPrenotazione);
        }else{
            addCodaTuristi(nuovoNodo->turisti,nuovaPrenotazione);
            nuovoNodo->next = i->next;
            i->next = nuovoNodo;

        }

    }

}

//L'inserimento viene effettuato in coda
//rootG è la testa della lista dei gruppi
void addCodaPrenotazioni(Prenotazioni* &rootP,Gruppi* &rootG,string nome,string cognome,int idGruppo) {
    if (rootP == NULL) {

        Prenotazioni* nuovaPrenotazione = new Prenotazioni(nome,cognome,idGruppo);
        nuovaPrenotazione->next = NULL;
        rootP = nuovaPrenotazione;
        addGruppi(rootG,nuovaPrenotazione,idGruppo);

    } else{
        //scorre la lista in modo ricorsivo finquando non arriva all'ultimo elemento
        addCodaPrenotazioni(rootP->next,rootG, nome,cognome,idGruppo);
    }

}


void printPrenotazioni(Prenotazioni* rootP,Gruppi* rootG) {
    cout<<"Prenotazioni:"<<endl<<"*=> ";
    for (Prenotazioni* current = rootP; current != NULL; current = current->next) {
        cout <<"{"<< current->idGruppo<<"|"<<current->nome << "} => ";
    }
    cout << endl<<endl;

    cout<<"Gruppi:"<<endl;
    for (Gruppi* current = rootG; current != NULL; current = current->next) {
        cout <<endl<<"{"<< current->idGruppo << "} --> ( "<<endl;
        for (Turista *j=current->turisti; j != NULL; j=j->next) {
            cout<<"[ "<<j->prenotazione->idGruppo<<"|"<<j->prenotazione->nome<<" ] =>";
        }
        cout<<endl<<")"<<endl<<endl<<"|"<<endl<<"V"<<endl<<endl;
    }
    cout << endl;
}



int main() {
    Prenotazioni* rootP = NULL;
    Gruppi* rootG = NULL;
    addCodaPrenotazioni(rootP,rootG, "aome1", "cognome1", 75);
    addCodaPrenotazioni(rootP,rootG, "bome4", "cognome4", 87);
    addCodaPrenotazioni(rootP,rootG, "come6", "cognome6", 75);
    addCodaPrenotazioni(rootP,rootG, "dome2", "cognome2", 75);
    addCodaPrenotazioni(rootP,rootG, "eome5", "cognome5", 90);
    addCodaPrenotazioni(rootP,rootG, "fome3", "cognome3", 90);
    addCodaPrenotazioni(rootP,rootG, "gome7", "cognome7", 87);
    addCodaPrenotazioni(rootP,rootG, "home8", "cognome8", 90);
    addCodaPrenotazioni(rootP,rootG, "iome9", "cognome8", 81);
    addCodaPrenotazioni(rootP,rootG, "bome2", "cognome2", 75);

    printPrenotazioni(rootP,rootG);


    return 0;
}
