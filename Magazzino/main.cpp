#include <iostream>
#include <process.h>

using namespace std;
//struct utilizzate
struct Articoli{

    string nomeArticolo;
    int codiceArticolo=0;
    int qta;
    Articoli * next;

};

struct Preventivo{
    int codicePreventivo=0;
    int numeroProdotti=0;
    string nome;
    string cognome;
    bool pagato=false;
    Preventivo *next;
    Articoli *articoli;

};
//prototipi di funzione (Quelli adiacenti funzionano insieme)
void menu();

void stampaPreventivi(Preventivo *rootPreventivi);
void stampaArticoli(Preventivo *&ordine);

void inserisciPreventivo(Preventivo *&rootPreventivi);

void rimuoviArticolo(Preventivo *&ordine);
void prelevaOrdine(Preventivo *&rootMagazzino);

void copiaPreventivoInMagazzino(Preventivo *&daCopiare,Preventivo *&nuovo );
void trasferisciInMagazzino(Preventivo *&daCopiare,Preventivo *&rootMagazzino);
void rimuoviDaPreventivi(Preventivo *&rootPreventivi,int codicePreventivo );
void pagaPreventivo(Preventivo *&rootPreventivi,Preventivo *&rootMagazzino);

int main() {
    int scelta=0;
    Preventivo *rootPreventivi= NULL;
    Preventivo *rootMagazzino= NULL;

    do{
        menu();
        cin>>scelta;

        switch(scelta){

        case 1:
            inserisciPreventivo(rootPreventivi);
            system("cls");
            break;

        case 2:
            system("cls");
            stampaPreventivi(rootPreventivi);

            break;

        case 3:
            system("cls");
            pagaPreventivo(rootPreventivi,rootMagazzino);

            break;
        case 4:
            system("cls");
            stampaPreventivi(rootMagazzino);

            break;

        case 5:
            system("cls");
            prelevaOrdine(rootMagazzino);
            break;

        }


    }while(scelta!=99);
    return 0;
}
// menu del sistema
void menu(){
    cout<<".......... Menu Sistema .........."<<endl;
    cout<<"1) Inserimento Preventivo"<<endl;
    cout<<"2) Stato preventivi"<<endl;
    cout<<"3) Paga preventivo"<<endl;
    cout<<"4) Stato magazzino"<<endl;
    cout<<"5) Preleva prodotto da magazzino"<<endl;
    cout<<"99) Exit"<<endl;
    cout<<"Scelta : ";
}

//-------------------------------------------FUNZIONI DI STAMPA---------------------------
void stampaPreventivi(Preventivo *rootPreventivi) {
    if(rootPreventivi == NULL)
        cout<<"Non ci sono ordini."<<endl;
    else {
        //stampa i preventivi o gli ordini in magazzino
        for(Preventivo *currPreventivo = rootPreventivi; currPreventivo != NULL; currPreventivo = currPreventivo->next) {   //puntatore d'appoggio per gli artisti
            cout<<"Codice preventivo : "<<currPreventivo->codicePreventivo<<endl;
            cout<<"Nome: "<<currPreventivo->nome<<endl;
            cout<<"Cognome :"<<currPreventivo->cognome<<endl;
            cout<<"Pagato? :"<<currPreventivo->pagato<<endl<<endl;
        //stampa gli articoli
            for(Articoli *currArticolo = currPreventivo->articoli; currArticolo != NULL; currArticolo = currArticolo->next) {  //puntatore d'appoggio per i dischi

                cout<<"        "<<"Codice articolo: "<<currArticolo->codiceArticolo<<endl;
                cout<<"        "<<"Nome articolo: "<<currArticolo->nomeArticolo<<endl;
                cout<<"        "<<"Quantita': "<<currArticolo->qta<<endl<<endl;
            }
            cout<<endl<<endl;
        }
    }
    cout<<endl;
}
void stampaArticoli(Preventivo *&ordine){
    for(Articoli *currArticolo = ordine->articoli; currArticolo != NULL; currArticolo = currArticolo->next) {
        cout<<"Codice articolo: "<<currArticolo->codiceArticolo<<endl;
        cout<<"Nome articolo: "<<currArticolo->nomeArticolo<<endl;
        cout<<"Quantita': "<<currArticolo->qta<<endl<<endl;
        cout<<endl;
    }
}

/*
 *Questa funzione serve per inserire nella lista i preventivi
 *verranno poi inseriti gli articoli nella sottolista
*/
void inserisciPreventivo(Preventivo *&root){
    Preventivo* nuovoPreventivo =new Preventivo();
    int numeroProdotti;
    system("cls");
    cout<<"Inserire i seguenti dati: "<<endl;
    cout<<"Codice preventivo "<<endl;
    cin>>nuovoPreventivo->codicePreventivo;
    cout<<"Nome cliente "<<endl;
    cin>>nuovoPreventivo->nome;
    cout<<"Cognome cliente "<<endl;
    cin>>nuovoPreventivo->cognome;
    cout<<"Numero di prodotti da acquistare "<<endl;
    cin>>numeroProdotti;
    nuovoPreventivo->numeroProdotti=numeroProdotti;
    for (int i = 0; i < numeroProdotti; i++)
    {
        Articoli *nuovoArticolo=new Articoli;
        nuovoArticolo->next = NULL;
        cout<<"Inserire i seguenti dati: "<<endl;
        cout<<"Nome articolo ";
        cin>>nuovoArticolo->nomeArticolo;
        cout<<"Codice articolo ";
        cin>>nuovoArticolo->codiceArticolo;
        cout<<"Quantita' articolo ";
        cin>>nuovoArticolo->qta;
        cout<<endl;

        nuovoArticolo->next = nuovoPreventivo->articoli;
        nuovoPreventivo->articoli= nuovoArticolo;
    }
    nuovoPreventivo->next = root;
    root = nuovoPreventivo;
}


// LE PROSSIME 2 FUNZIONI VERRANNO ESEGUITE INSIEME

/*Questa funzione chiede al magazziniere di scansionare (nel nostro caso immettere manualmente l'id)
 * di ogni articolo che viene erogato.
 * Si uscirà da questa funzione dopo che tutti gli articoli dell'ordine sono sati erogati
 */
void rimuoviArticolo(Preventivo *&ordine){

    for(int i=0; i<ordine->numeroProdotti;i++){
        system("cls");

        cout<<"L'ordine da emettere e' il seguente:"<<endl;
        stampaArticoli(ordine);

        Articoli *corrente;
        Articoli *successivo;
        corrente = ordine->articoli;
        successivo = corrente->next;
        bool rimosso = false;
        int codiceArticolo;
        cout<<"inserire il codice corrispondente all'articolo da rimuovere"<<endl;
        cin>>codiceArticolo;
        if(corrente->codiceArticolo == codiceArticolo){
            delete corrente;
            ordine->articoli = successivo;
        }else{
            while (successivo != NULL && !rimosso)
            {
                if (corrente->codiceArticolo == codiceArticolo) {
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
    system("cls");

    cout<<"Ordine completato!"<<endl;
}

/*Quando il magazziniere deve erogare un ordine, il primo ordine della lista viene passato alla funzione sopra
 *in seguito verrà eliminato l'ordine già processato
*/
void prelevaOrdine(Preventivo *&rootMagazzino){
    Preventivo *corrente;
    Preventivo *successivo;
    corrente = rootMagazzino;


    if(corrente != NULL){
        successivo = corrente->next;
        rimuoviArticolo(corrente);
        delete corrente;
        rootMagazzino = successivo;
    }
    else{
        cout<<"Non ci sono ordini in magazzino da erogare"<<endl;
    }

}

//LE PROSSIME 4 FUNZIONI VERRANNO ESEGUITE INSIEME

// 1
//copia il preventivo pagato nella lista del magazzino
/*
 * piu complessa di quella sotto , scorre la sottolista per copiarla
void copiaPreventivoInMagazzino(Preventivo *&daCopiare,Preventivo *&nuovo ){
    //copia i valori dalla lista del preventivo alla lista del magazzino
    nuovo->codicePreventivo= daCopiare->codicePreventivo;
    nuovo->nome= daCopiare->nome;
    nuovo->cognome=daCopiare->cognome;
    nuovo->pagato=daCopiare->pagato;
    nuovo->numeroProdotti=daCopiare->numeroProdotti;
    nuovo->articoli=daCopiare->articoli;/*
    for (int i = 0; i < nuovo->numeroProdotti; i++)
    {

        for(Articoli *currArticolo = daCopiare->articoli; currArticolo != NULL; currArticolo = currArticolo->next) {
            //crea una sotto lista di articoli copiando la lista attuale del preventivo
            Articoli *copiaArticolo=new Articoli;
            copiaArticolo->next = NULL;
            copiaArticolo->nomeArticolo= daCopiare->articoli->nomeArticolo;
            copiaArticolo->codiceArticolo=  daCopiare->articoli->codiceArticolo;
            copiaArticolo->qta=  daCopiare->articoli->qta;

            copiaArticolo->next = nuovo->articoli;
            nuovo->articoli= copiaArticolo;
            //importante! scorre gli articoli della lista del preventivo
            daCopiare->articoli=daCopiare->articoli->next;
        }
    }
}
*/
void copiaPreventivoInMagazzino(Preventivo *&daCopiare,Preventivo *&nuovo ){
    //copia i valori dalla lista del preventivo alla lista del magazzino
    nuovo->codicePreventivo= daCopiare->codicePreventivo;
    nuovo->nome= daCopiare->nome;
    nuovo->cognome=daCopiare->cognome;
    nuovo->pagato=daCopiare->pagato;
    nuovo->numeroProdotti=daCopiare->numeroProdotti;
    nuovo->articoli=daCopiare->articoli;
}

// 2
//crea la lista del magazzino con inserimento in coda degli ordini da erogare, già pagati
void trasferisciInMagazzino(Preventivo *&daCopiare,Preventivo *&rootMagazzino){

    Preventivo* nuovoOrdine =new Preventivo();
    nuovoOrdine->next = NULL;
    if(rootMagazzino == NULL){
        copiaPreventivoInMagazzino(daCopiare,nuovoOrdine);
        rootMagazzino = nuovoOrdine;
    }else{
        Preventivo *i;
        for(i = rootMagazzino;i->next != NULL;i = i->next);
        copiaPreventivoInMagazzino(daCopiare,nuovoOrdine);

        i->next = nuovoOrdine;
    }
}

// 3
/*RIMUOVE IL PREVENTIVO DALLA LISTA DEI PREVENTIVI
 * dopo che l'ordine è stato pagato e copiato nella lista del magazzino
*/
void rimuoviDaPreventivi(Preventivo *&rootPreventivi,int codicePreventivo ) {
    Preventivo *corrente;
    Preventivo *successivo;
    corrente = rootPreventivi;
    successivo = corrente->next;
    bool rimosso = false;
    //se è il primo lo elimino adesso perchè il codice parte dal secondo
    if(corrente->codicePreventivo == codicePreventivo){
        delete corrente;
        rootPreventivi = successivo;
    }else{
        while (successivo != NULL && !rimosso)
        {
            if (corrente->codicePreventivo == codicePreventivo) {
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
// 4

void pagaPreventivo(Preventivo *&rootPreventivi,Preventivo *&rootMagazzino){
    int codicePreventivo=0;

    Preventivo *corrente= new Preventivo;
    corrente = rootPreventivi;
    bool trovato = false;

    cout<<"Inserire il codice del preventivo da pagare "<<endl;
    cin>>codicePreventivo;

    if (corrente->codicePreventivo == codicePreventivo){
        corrente->pagato=true;
        trasferisciInMagazzino(corrente,rootMagazzino);
        rimuoviDaPreventivi(rootPreventivi, codicePreventivo ); //rimuove un elemento dato il nome

        trovato = true;

    }else{
        while (corrente != NULL && !trovato)
        {
            if (corrente->codicePreventivo == codicePreventivo) {
                corrente->pagato=true;
                trasferisciInMagazzino(corrente,rootMagazzino);
                rimuoviDaPreventivi(rootPreventivi, codicePreventivo ); //rimuove un elemento dato il nome

                trovato = true;
            }
            else {
                corrente = corrente->next;

            }
        }
    }
}
