#include <iostream>
using namespace std;
/*
 * ******************************************TRACCIA***********************************
Si vuole partecipare allo sviluppo di un software per archiviare e poi analizzare
le quotazioni di borsa di un insieme di società.
Realizzare un software che implementi le seguenti funzioni accessibili attraverso un menù:
1.	Inserimento dei dati per ciascuna azienda, secondo il seguente formato:
    nome_società#val1#val2#val3...#valn*
    dove nome_società è al massimo composto da 15 caratteri senza spazi,
    e il numero di valori rilevati può variare fra le varie aziende considerate.
    In tutti i casi la lista di valori di input è terminata dal carattere *
2.	Stampa dei dati memorizzati
3.	Eliminazione di un’azienda e dei relativi dati
4.	Calcolo della media, valore massimo delle quotazioni per tutte le aziende
5.	Calcolo della media, valore massimo delle quotazioni per un’azienda avendone specificato il nome
6.	Uscita dal programma
*/

struct quotazioni{
    int valore=0;
    quotazioni *next;
};

struct azienda{

    string nome;
    quotazioni *quotazioni;
    azienda *next;
};

void inserimentoAzienda(azienda *&root);

void printList(azienda *&root);

void rimuoviAzienda(azienda *&root);

void mediaAzienda(azienda *&root);

void MediaEMassimoGlobali(azienda *&root);

void aziendaOrdinata(azienda *&x,azienda *& rootOrdinata){
    azienda *ordinata = new azienda();
    //copia dei dati
    ordinata->nome=x->nome;
    ordinata->quotazioni=x->quotazioni;
    ordinata->next = NULL;
    //inserimento per ordine alfabetico

    if(rootOrdinata == NULL|| (rootOrdinata->nome).compare(x->nome) != -1 ){
        ordinata->next =rootOrdinata;
        rootOrdinata = ordinata;

    }else{

        azienda *i;
        //i->next != NULL vuol dire finchè non arrivo all'ultimo elemento
        //controllo se l'iniziale contenuta nel nodo successivo è minore di quella da inserire
        for(i = rootOrdinata;i->next != NULL &&  (i->next->nome).compare(x->nome) == -1 ;i = i->next);

        ordinata->next = i->next;
        i->next = ordinata;
    }
}
void ordinamentoAlfabetico(azienda *&root){
    azienda *rootOrdinata =NULL;
    azienda *x = root;
    for(x = root; x->next != NULL;x = x->next){
        aziendaOrdinata(x,rootOrdinata);

    }
    aziendaOrdinata(x,rootOrdinata);
    root=rootOrdinata;
}

int main()
{

    //*****************************************************************//
    azienda *root= NULL;
    int scelta=0;

    do{

        cout<<"............... Menu..............."<<endl;
        cout<<"1) Inserisci nuova azienda "<<endl;
        cout<<"2) stampa del database "<<endl;
        cout<<"3) Elimina azienda  "<<endl;
        cout<<"4) media e massimo di un' azienda"<<endl;
        cout<<"5) media e massimo globale "<<endl;
        cout<<"6) Riordina la lista in ordine alfabetico"<<endl;
        cin>>scelta;

        switch(scelta){

        case 1:
            inserimentoAzienda(root);
            break;

        case 2:
            printList(root);
            break;

        case 3:
            rimuoviAzienda(root);
            break;

        case 4:
            mediaAzienda(root);
            break;

        case 5:
            MediaEMassimoGlobali(root);
            break;

        case 6:
            ordinamentoAlfabetico(root);
            break;
        default:
            cout<<"selezione errata, riprova"<<endl;
        }
    }while(scelta!=99);

    return 0;
}

//-----------SVILUPPO DEI PROTOTIPI----------------------------



void inserimentoAzienda(azienda *&root)
{
    string inserimento="";
    cout<<"inserire nel seguente formato:  nome_societa'#val1#val2#val3...#valn* "<<endl;
    cin>>inserimento;

    int i=0;
    string nome;
    string valore;

    //assegno il nome all'azienda
    while (inserimento[i]!= '#') {
        nome+=inserimento[i];
        i++;
    }
    //controllo che la lunghezza del nome sia inferiore a 15
    if(i<15){
        //inserisco la nuova azienda
        azienda * nuovaAzienda =new azienda();
        nuovaAzienda->next= root;
        nuovaAzienda->nome=nome;
        root = nuovaAzienda;
        i++;

        while (inserimento[i]!='*') {
            //memorizzo i valori contenuti tra due #
            if(inserimento[i]!='#'){
                valore+=inserimento[i];
                i++;
            }
            else{
                //concateno la nuova quotazione a quelle già presenti
                quotazioni *nuovaQuotazione =new quotazioni;
                nuovaQuotazione->next = NULL;
                nuovaQuotazione->valore=atoi(valore.c_str());//funzione che trasforma la stringa in numeri
                nuovaQuotazione->next = nuovaAzienda->quotazioni;
                nuovaAzienda->quotazioni= nuovaQuotazione;
                i++;
                //svuoto la stringa in modo da avere il valore successivo contenuto tra i #
                valore=" ";
            }
        }
        //serve per concatenare nella lista di lista l'ultimo valore contenuto tra #___*
        quotazioni *nuovaQuotazione =new quotazioni;
        nuovaQuotazione->next = NULL;
        nuovaQuotazione->valore=atoi(valore.c_str());
        nuovaQuotazione->next = nuovaAzienda->quotazioni;
        nuovaAzienda->quotazioni= nuovaQuotazione;
        i++;
    }
    //messaggio di errore se la dim del nome è superiore a 15
    else{
        cout<<"hai superato il limite massimo di caratteri per il nome"<<endl;
    }
}


void printList(azienda *&root)
{
    azienda *i;
    quotazioni *x;
    int numeroQuotazioni=1;
    if (root)
    {
        for (i = root; i != 0; i = i->next){
            //stampo il nome dell'azienda
            cout << "nome: " << i->nome << endl;
            for (x = i->quotazioni; x != 0; x = x->next)
            {
                //stampo il valore di ogni quotazione
                cout << endl << " valore quotazione numero "<<numeroQuotazioni<<": " << x->valore << endl;
                numeroQuotazioni++;
            }
            cout << endl;
        }
        cout << endl;
    }
    else
        cout << endl << "La lista e' vuota" << endl;
}


void rimuoviAzienda(azienda *&root) { //rimuove un elemento dato il nome
    //controlla prima se esiste una sottolista che è possibile rimuovere
    if(root !=NULL){
        azienda *corrente;
        azienda *successivo;
        corrente = root;
        successivo = corrente->next;
        bool rimosso = false;

        string aziendaDaRimuovere;
        cout<<"chi desideri rimuovere? ";
        cin>>aziendaDaRimuovere;

        //controllo se è il primo della lista e lo elimino
        if(corrente->nome == aziendaDaRimuovere){
            delete corrente;
            root = successivo;

        }else{
            while (successivo != NULL && !rimosso)
            {
                if (successivo->nome == aziendaDaRimuovere) {
                    delete  corrente->next;
                    corrente->next = successivo->next;
                    rimosso = true;
                }
                else {
                    corrente = successivo;
                    successivo = successivo->next;
                }
            }
        }
    }
    else{
        cout<<" non puoi eliminare un'azienda se la lista e' vuota !!"<<endl;
    }

}
//funzione di appoggio per il calcolo della media e del massimo delle aziende
void mediaEMax(azienda *corrente){
    quotazioni *i;
    int somma=0;
    int massimo=0;
    int contaValori=0;
    float media=0.0;

    for (i = corrente->quotazioni; i != 0; i = i->next)
    {

        somma+=i->valore;
        contaValori++;
        if(i->valore > massimo){
            massimo=i->valore;
        }
    }
    media=somma/contaValori;

    cout << "La media e' di : "<< media << endl;
    cout << "La quotazione massima e' pari a  : "<< massimo << endl;
}

void mediaAzienda(azienda *&root){

    azienda *corrente;
    azienda *successivo;
    corrente = root;
    successivo = corrente->next;
    bool trovato = false;

    string nomeDaCercare;
    cout<<"Di quale azienda desideri vare la media delle quotazioni?  ";
    cin>>nomeDaCercare;
    //viene cercata l'azienda corrispondente e poi fatta la media
    if(corrente->nome == nomeDaCercare){
        mediaEMax(corrente);
        trovato = true;
    }else{
        while (corrente != NULL && !trovato)
        {
            if (corrente->nome == nomeDaCercare) {
                mediaEMax(corrente);
                trovato = true;
            }
            else {
                corrente = corrente->next;

            }
        }
    }
    if(trovato==false)
        cout<<"Azienda non trovata";
}

void MediaEMassimoGlobali(azienda *&root)
{
    azienda *i;
    quotazioni *x;

    int somma=0;
    int massimo=0;
    int contaValori=0;
    float media=0.0;

    if (root)//se esistono aziende
    {
        for (i = root; i != 0; i = i->next){
            // Stampo il nome dell'azienda
            cout << "nome: " << i->nome << endl;
            for (x = i->quotazioni; x != 0; x = x->next)
            {

                somma+=x->valore;
                contaValori++;

                if(x->valore > massimo){
                    massimo=x->valore;
                }
            }
            cout << endl;
        }
        cout << endl;
        media=somma/contaValori;

        cout << "La media e' di : "<< media << endl;
        cout << "La quotazione massima e' pari a  : "<< massimo << endl;
    }
    else
        cout << endl << "La lista e' vuota" << endl;
}

