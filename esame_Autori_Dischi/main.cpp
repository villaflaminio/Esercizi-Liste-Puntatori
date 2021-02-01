#include <iostream>

using namespace std;
//------------definizione delle struct
struct Disco{
    string titolo;
    Disco *nextDi;
};

struct Autore{
    int numeroDischi;
    string cognome;
    Autore *nextAu;
    Disco *dischi;
};
//--------prototipi di funzione--------

void printList(Autore *&root);
void inserimento(Autore *&root);
void rimuoviAutore(Autore *&root);
void cercaAutore(Autore *&root);
void aggiungiDisco(Autore *&root);
void cerca(Autore *&root);
void rimuovi(Disco *&root);
void inserimentoAlfabetico(Autore *&root);

void eliminaRicorsivaDoc(Disco *disk);
void eliminaRicorsivaParola(Autore *nod);
void eliminaTutto(Autore  *&testa);
void menu();




//----------MAIN-----------
int main()
{
    Autore *root= NULL;
    int scelta=0;

    do{

        menu();
        cin>>scelta;

        switch(scelta){

        case 1:
            inserimento(root);
            break;

        case 2:
            rimuoviAutore(root);
            break;

        case 3:
            aggiungiDisco(root);
            break;
        case 4:
            cerca(root);
            break;
        case 5:
            cercaAutore(root);
            break;

        case 6:
            printList(root);
            break;
        case 7:
            inserimentoAlfabetico(root);
        case 8:
            printList(root);

            eliminaTutto(root);
            printList(root);

        case 99:

            break;
        }
    }while(scelta!=99);

    return 0;
}

//-----------SVILUPPO DEI PROTOTIPI----------------------------

void menu(){
    cout<<".......... Menu Lista Normale .........."<<endl;
    cout<<"1) Inserisci un nuovo autore "<<endl;
    cout<<"2) Rimuovere un autore per cognome"<<endl;
    cout<<"3) Aggiungi disco ad autore"<<endl;
    cout<<"4) Elimina un disco ad autore "<<endl;
    cout<<"5) Cerca autore e stampa i suoi dischi"<<endl;
    cout<<"6) Stampa tutti gli autori "<<endl;
    cout<<"7) Inserisci un nuovo autore in ordine alfabetico "<<endl;
    cout<<"7) Elimina tutto "<<endl;

    cout<<"99) esci"<<endl;
}

void printList(Autore *&root)
{
    Autore *tmpAu;
    Disco *tmpDi;

    if (root)
    {
        for (tmpAu = root; tmpAu != 0; tmpAu = tmpAu->nextAu){
            // Stampo le informazioni sull'autore

            cout << "cognome: " << tmpAu->cognome << endl;
            for (tmpDi = tmpAu->dischi; tmpDi != 0; tmpDi = tmpDi->nextDi)
            {
                // Stampo le informazioni sul disco
                cout << endl << "   titolo disco: " << tmpDi->titolo << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
    else
        cout << endl << "La lista e' vuota" << endl;
}

void inserimento(Autore *&root)
{
    int numeroDischi=0;
    Autore* nuovoAutore =new Autore();
    nuovoAutore->nextAu = root;

    cout<<"inserire il cognome dell'autore  ";
    cin>>nuovoAutore->cognome;
    cout << endl << "Inserire il suo numero di dischi: ";
    cin >> numeroDischi;
    nuovoAutore->numeroDischi=numeroDischi;

    // Creo i nuovi dischi e li aggiungo al nuovo autore
    for (int i = 0; i < nuovoAutore->numeroDischi; i++)
    {
        Disco *nuovoDisco=new Disco;
        nuovoDisco->nextDi = NULL;

        cout<<"inserire il titolo  ";
        cin>>nuovoDisco->titolo;
        //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
        nuovoDisco->nextDi = nuovoAutore->dischi;
        nuovoAutore->dischi= nuovoDisco;
    }
    root = nuovoAutore;
}

void inserimentoAlfabetico(Autore *&root){
    int numeroDischi=0;
    Autore* nuovoAutore =new Autore();
    string cognome;
    cout<<"inserire il cognome dell'autore  ";
    cin>>cognome;
    nuovoAutore->cognome=cognome;

    cout << endl << "Inserire il suo numero di dischi: ";
    cin >> numeroDischi;
    nuovoAutore->numeroDischi=numeroDischi;

    nuovoAutore->nextAu = NULL;
    //se la root è vuota oppure se viene prima del primo elemento
    if(root == NULL || root->cognome.at(0) > cognome.at(0)){
        nuovoAutore->nextAu =root;
        root = nuovoAutore;

        for (int j = 0; j < nuovoAutore->numeroDischi; j++)
        {
            Disco *nuovoDisco=new Disco;
            nuovoDisco->nextDi = NULL;

            cout<<"inserire il titolo  ";
            cin>>nuovoDisco->titolo;
            //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
            nuovoDisco->nextDi = nuovoAutore->dischi;
            nuovoAutore->dischi= nuovoDisco;
        }

    }else{
        //serve per scorrere la lista
        Autore *i;
        //i->next != NULL vuol dire finchè non arrivo all'ultimo elemento
        //controllo se l'iniziale contenuta nel nodo successivo è minore di quella da inserire

        for(i = root;i->nextAu != NULL && cognome.at(0) > i->nextAu->cognome.at(0)   ;i = i->nextAu);
        nuovoAutore->nextAu = i->nextAu;
        i->nextAu = nuovoAutore;


        for (int x = 0; x < nuovoAutore->numeroDischi; x++)
        {
            Disco *nuovoDisco=new Disco;
            nuovoDisco->nextDi = NULL;

            cout<<"inserire il titolo  ";
            cin>>nuovoDisco->titolo;
            //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
            nuovoDisco->nextDi = nuovoAutore->dischi;
            nuovoAutore->dischi= nuovoDisco;
        }
    }
}

void rimuoviAutore(Autore *&root) { //rimuove un elemento dato il nome

    Autore *corrente;
    Autore *successivo;
    corrente = root;
    successivo = corrente->nextAu;
    string AutoreDaRimuovere;
    cout<<"chi desideri rimuovere? ";
    cin>>AutoreDaRimuovere;
    bool rimosso = false;
    if(corrente!=NULL){
        //se è il primo lo elimino adesso perchè il codice parte dal secondo
        if(corrente->cognome == AutoreDaRimuovere){
            delete corrente;
            root = successivo;

        }else{
            while (successivo != NULL && !rimosso)
            {
                if (successivo->cognome == AutoreDaRimuovere) {
                    delete  corrente->nextAu;
                    corrente->nextAu = successivo->nextAu;
                    rimosso = true;
                }
                else {
                    corrente = successivo;
                    successivo = successivo->nextAu;
                }
            }
        }
    }
    else{
        cout<<"la lista è vuota !!"<<endl;
    }

}

//stampa la discografia dell'autore
void cercaAutore(Autore *&root){
    Autore *corrente;
    Autore *successivo;
    corrente = root;
    successivo = corrente->nextAu;

    string cognomeAutore;
    cout<<"A chi desideri cercare ";
    cin>>cognomeAutore;

    bool trovato = false;

    //se è il primo lo elimino adesso perchè il codice parte dal secondo
    if(corrente->cognome == cognomeAutore){

        Disco *i;
        cout<<"L'autore ha "<< corrente->numeroDischi<<" dischi"<<endl;
        for (i = corrente->dischi; i != 0; i = i->nextDi)
        {
            // Stampo le informazioni sul disco
            cout << endl << "   titolo disco: " << i->titolo << endl;
        }
        cout << endl;
    trovato = true;
    }else{
        while (corrente != NULL && !trovato)
        {
            if (corrente->cognome == cognomeAutore) {

                Disco *i;
                cout<<"L'autore ha "+corrente->numeroDischi<<endl;
                for (i = corrente->dischi; i != 0; i = i->nextDi)
                {
                    // Stampo le informazioni sul disco
                    cout << endl << "   titolo disco: " << i->titolo << endl;
                }
                cout << endl;
                trovato = true;
            }
            else {
                corrente = corrente->nextAu;
            }
        }
    }
    if(trovato==false)
        cout<<"artista non trovato";
}

void aggiungiDisco(Autore *&root) { //rimuove un elemento dato il nome

    Autore *corrente;
    Autore *successivo;
    corrente = root;
    successivo = corrente->nextAu;

    string cognomeAutore;
    cout<<"a chi desideri aggiungere un'album ?";
    cin>>cognomeAutore;
    bool aggiunto = false;

    //se è il primo lo elimino adesso perchè il codice parte dal secondo
    if(corrente->cognome == cognomeAutore){
        Disco *nuovoDisco=new Disco;
        nuovoDisco->nextDi = NULL;

        cout<<"inserire il titolo  ";
        cin>>nuovoDisco->titolo;
        //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
        nuovoDisco->nextDi = corrente->dischi;
        corrente->dischi= nuovoDisco;

    //root = successivo;
    }else{
        while (successivo != NULL && !aggiunto)
        {
            if (successivo->cognome == cognomeAutore) {
                Disco *nuovoDisco=new Disco;
                nuovoDisco->nextDi = NULL;

                cout<<"inserire il titolo  ";
                cin>>nuovoDisco->titolo;
                //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
                nuovoDisco->nextDi = successivo->dischi;
                successivo->dischi= nuovoDisco;


                aggiunto = true;
            }
            else {
                corrente = successivo;
                successivo = successivo->nextAu;
            }
        }
    }
}
//cerca l'artista corrispondente ed elimina il disco selezionato

void cerca(Autore *&root){
    Autore *corrente;
    Autore *successivo;
    corrente = root;
    successivo = corrente->nextAu;

    string cognomeAutore;
    cout<<"A chi desideri cercare ";
    cin>>cognomeAutore;

    bool trovato = false;

    //se è il primo lo elimino adesso perchè il codice parte dal secondo
    if(corrente->cognome == cognomeAutore){
    rimuovi(corrente->dischi);

    trovato = true;
    }else{
        while (corrente != NULL && !trovato)
        {
            if (corrente->cognome == cognomeAutore) {

                rimuovi(corrente->dischi);
                trovato = true;
            }
            else {
                corrente = corrente->nextAu;

            }
        }
    }
    if(trovato==false)
        cout<<"artista non trovato";
}
//continuazione del metodo sopra
void rimuovi(Disco *&root) {

    Disco *corrente;
    Disco *successivo;
    corrente = root;
    successivo = corrente->nextDi;
    bool rimosso = false;
    string nomeDisco;
    cout<<"inserire il nome del disco ";
    cin>>nomeDisco;
    //se è il primo lo elimino adesso perchè il codice parte dal secondo
    if(corrente->titolo == nomeDisco){
        delete corrente;
        root = successivo;

    }else{
        while (successivo != NULL && !rimosso)
        {
            if (successivo->titolo == nomeDisco) {
                delete  corrente->nextDi;
                corrente->nextDi = successivo->nextDi;
                rimosso = true;
            }
            else {
                corrente = successivo;
                successivo = successivo->nextDi;
            }
        }
    }
}

// eliminazione di tutto

void eliminaRicorsivaDoc(Disco *disk) {

    if(disk == NULL)
        return;

    else{
        eliminaRicorsivaDoc(disk->nextDi);
        delete disk;
    }
}

void eliminaRicorsivaParola(Autore *nod){

    if(nod == NULL)
        return;

    else{
        eliminaRicorsivaParola(nod->nextAu);
        delete nod;
    }
}

void eliminaTutto(Autore  *&testa) {

    if(testa == NULL)
        return;

    else{

        Autore *curr = testa;

        //Elimino i documenti di ogni nodo
        while(curr->nextAu != NULL) {
            eliminaRicorsivaDoc(curr->dischi);
            curr = curr->nextAu;
        }

        //Elimino tutti i nodi
        Autore *curr2 = testa;
        eliminaRicorsivaParola(curr2);
        testa = NULL;

    }

}

