#include <iostream>

using namespace std;
#include <stdlib.h>

struct Articolo{
    int codice;
    string descrittore;
    int qta;
    Articolo  *next;
    Articolo *next100;
};
//passo la root
void centinaioSucc(Articolo *&first){

    Articolo *temp;
    Articolo *scorr;

   for(temp=first; temp->next != NULL && temp->codice/100 == temp->next->codice/100  ;temp = temp->next);
   for(scorr=first; temp->next != NULL && scorr != temp->next; scorr = scorr->next){
       scorr->next100 = temp->next;
   }
   if(temp->next == NULL){
       return;
   }else{
       centinaioSucc(temp->next);
   }

}

void inserimentoOrdinato(Articolo *&first, Articolo *articolo,int qta){

    Articolo *art= first;
    if(first == NULL){
        first = articolo;
        first->next = NULL;
        first->next100 = NULL;
        return;
    }else if(first->codice == articolo->codice){
       first->qta+=qta;
       delete articolo;
    }else if(first->codice < articolo->codice){
        inserimentoOrdinato(first->next, articolo,qta);
    }else if(first->codice > articolo->codice){
        articolo->next = first;
        first = articolo;
    }

    centinaioSucc(first);
}

void print(Articolo *first){
    if(first!=NULL){
        if(first->next100!= NULL)
            cout << "Codice: " << first->codice<< " qta: " << first->qta << " Next100: " <<  first->next100->codice<< endl;
        else
            cout << "Codice: " << first->codice << " Next100: NULL" << endl;
    print(first->next);
    }else{
        return;
    }
}
void reverseList(Articolo* &head) {
    Articolo* newHead = NULL;
    Articolo* current = head;
    Articolo* tmp;
    while (current != NULL) {
        tmp = current;
        current = current->next;
        tmp->next = newHead;
        newHead = tmp;
    }
    head = newHead;
}



int main()
{
    Articolo *magazzino = NULL;
    Articolo *artic;
    int scelta =0;
    int qta;
    while(scelta != 5){
        cout << "Inserisci 1" << endl;
        cout << "Inserisci random 2" << endl;

        cout << "Stampa 3" << endl;
        cout << "esci 4" << endl;

        cin >> scelta;

        switch (scelta) {
        case 1:
            artic = new Articolo;
            cout << "Inserire il codice" << endl;
            cin >> artic->codice;
            cout << "Inserire la quantita'" << endl;
            cin >> qta;
            artic->qta=qta;
            inserimentoOrdinato(*&magazzino,artic,qta);
            break;
        case 2:
            for (int i=0;i<500;i++){
                artic = new Articolo;
                    int casuale;
                    casuale = rand();
                    artic->codice=casuale;
                    qta=rand()/100;
 artic->qta=qta;

            inserimentoOrdinato(*&magazzino,artic,qta);
            }
            break;
        case 3:
            print(magazzino);
            break;
        case 4:
            reverseList(magazzino);
            break;

        default:
            break;

        }
    }

    return 0;
}
