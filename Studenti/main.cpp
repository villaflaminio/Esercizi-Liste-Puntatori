#include <iostream>

using namespace std;
struct Voti{
    int voto;
    long int data;
    string tipo;
    Voti * next;
};
struct Studenti{
    string nome;
    string cognome;
    string nomeClasse;
    Studenti *next;
    Voti *voti;
};

struct Classi{
    string nomeClasse;
    Classi *next;
    Studenti *studenti;
};
void getData(long  int date ) {
    int giorno;
    int mese;
    int anno;
    giorno = date % 100;
    date /= 100;
    mese = date % 100;
    date /= 100;
    anno = date;
    cout<<"gg "<<giorno<<" mm "<<mese<<" aaaa "<<anno;
}
long int inserisciData(){
    int giorno;
    int mese;
    int anno;
    cout<<"inserire il giorno "<<endl;
    cin>>giorno;
    cout<<"inserire il mese"<<endl;
    cin>>mese;
    cout<<"inserire l'anno"<<endl;
    cin>>anno;

    return (giorno + mese * 100 + anno * 10000);

}

Studenti* creaStudente(){
    Studenti* nuovo = new Studenti();

    string nome;
    string cognome;
    string nomeClasse;
    cout<<"Nome"<<endl;
    cin>>nuovo->nome;
    cout<<"Cognome"<<endl;
    cin>>nuovo->cognome;
    cout<<"Classe"<<endl;
    cin>>nuovo->nomeClasse;
    nuovo->next=NULL;
    return nuovo;
}
Voti* creaVoto(){
    Voti* nuovo = new Voti();

    int voto;
    string tipo;
    cout<<"voto"<<endl;
    cin>>nuovo->voto;
    cout<<"tipo"<<endl;
    cin>>nuovo->tipo;
    cout<<"data"<<endl;
    nuovo->data=inserisciData();
    nuovo->next=NULL;
    return nuovo;
}
Studenti* trovaNodoString(Studenti* head, string nome) {
    if (head == NULL)
        return NULL;
    else if (nome == head->nome){
        cout<<"ho trovato"<<nome<<endl;
        return head;
    }
    else
        return trovaNodoString(head->next, nome);
}
void inserimentoVoti(Studenti *&root1,string nome){
    Studenti *AlunnoCercato= trovaNodoString(root1,nome);
    //Voti* root =;
    //inizializzo il nodo
    Voti* nuovoVoto =creaVoto();

    //se la root è vuota oppure se viene prima del primo elemento
    if(AlunnoCercato->voti == NULL || (AlunnoCercato->voti->data) > (nuovoVoto->voto) ){
        cout<<"ho inserito fuori"<<nome<<endl;

        nuovoVoto->next =AlunnoCercato->voti;
        AlunnoCercato->voti = nuovoVoto;

    }else{
        //serve per scorrere la lista
        Voti *i;
        //i->next != NULL vuol dire finchè non arrivo all'ultimo elemento
        //controllo se l'iniziale contenuta nel nodo successivo è minore di quella da inserire
        for(i = AlunnoCercato->voti;i->next != NULL && (AlunnoCercato->voti->next->data) > (nuovoVoto->voto) ;i = i->next);
        cout<<"ho inserito dentro"<<nome<<endl;

        nuovoVoto->next = i->next;
        i->next = nuovoVoto;
    }
}
void classe(Studenti *&root1,Classi *&rootClassi){
    cout<<"sono dento classe"<<endl;

    //inizializzo il nodo
    //root1->nomeClasse;
    Classi *i;
    bool trovato=false;

    for(i = rootClassi; i->next != NULL && i->nomeClasse!=root1->nomeClasse; i = i->next){
        cout<<"sono dento il for"<<endl;

        i->studenti = root1;
        //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
        i->next = rootClassi;
        //il nuovo elemento sarà la testa
        rootClassi = i;
        trovato=true;
    }
    if(trovato ==false){
        cout<<"sono dento false"<<endl;
        Classi* nuovaClasse = new Classi;
        nuovaClasse->nomeClasse=root1->nome;
        nuovaClasse->studenti = root1;
        //il next del nuovo dato è l'indirizzo dell'attuale primo elemento della lista
        nuovaClasse->next = rootClassi;
        //il nuovo elemento sarà la testa
        rootClassi = nuovaClasse;
    }

}
void inserimentoClassi(Studenti *&root,Classi *&rootClassi){

    //azienda *rootOrdinata =NULL;
    Studenti *x = root;
    for(x = root; x->next != NULL;x = x->next){
        classe(x,rootClassi);

    }
    //attento a ripeterlo
    classe(x,rootClassi);
}

void inserimentoStudente(Studenti *&root){
    //inizializzo il nodo
    Studenti* nuovoStudente =creaStudente();

    //se la root è vuota oppure se viene prima del primo elemento
    if(root == NULL || (root->nome).compare(nuovoStudente->nome)!= -1 ){
        nuovoStudente->next =root;
        root = nuovoStudente;

    }else{
        //serve per scorrere la lista
        Studenti *i;
        //i->next != NULL vuol dire finchè non arrivo all'ultimo elemento
        //controllo se l'iniziale contenuta nel nodo successivo è minore di quella da inserire
        for(i = root;i->next != NULL && (i->next->nome).compare(nuovoStudente->nome) == -1 ;i = i->next);
        nuovoStudente->next = i->next;
        i->next = nuovoStudente;
    }
}

void menu(){
    cout<<".......... Menu Lista Normale .........."<<endl;
    cout<<"1) Inserimento Testa"<<endl;
    cout<<"2) Stampa"<<endl;
    cout<<"3) Inserimento voto"<<endl;
    cout<<"4) Inserimento in classi"<<endl;
    cout<<"5) Print classi"<<endl;/*
    cout<<"6) Rimuovi nodo"<<endl;
    cout<<"7) Inserimento Ordinato Cre"<<endl;
    cout<<"8) Inserimento Ordinato Dec"<<endl;
    cout<<"9) Rimuovi Primo Nodo"<<endl;
    cout<<"10 ) Rimuovi Ultimo Nodo"<<endl;*/
    cout<<"99) Exit"<<endl;
    cout<<"Scelta : ";
}
void stampa(Studenti *rootStudenti) {
    if(rootStudenti == NULL)
        cout<<"Non ci sono ordini."<<endl;
    else {
        for(Studenti *currStudenti = rootStudenti; currStudenti != NULL; currStudenti = currStudenti->next) {   //puntatore d'appoggio per gli artisti
            cout<<"Nome: "<<currStudenti->nome<<endl;
            cout<<"Cognome :"<<currStudenti->cognome<<endl;
            cout<<"nome classe  :"<<currStudenti->nomeClasse<<endl<<endl;
            cout<<endl;
            for(Voti *currVoti = currStudenti->voti; currVoti != NULL; currVoti = currVoti->next) {  //puntatore d'appoggio per i dischi
                cout<<"        "<<"tipo: "<<currVoti->tipo<<endl;
                cout<<"        "<<"voto: "<<currVoti->voto<<endl;
                cout<<"        "<<"data: ";
                getData(currVoti->data);
                cout<<endl;
            }
            cout<<endl<<endl;
        }
    }
    cout<<endl;
}
void stampaClassi(Classi *rootClassi) {
    cout<<"sono in stampa classi."<<endl;

    if(rootClassi == NULL)
        cout<<"Non ci sono classi."<<endl;
    else {
        for(Classi *currClasse = rootClassi; currClasse != NULL; currClasse = currClasse->next) {   //puntatore d'appoggio per gli artisti
            cout<<"Nome: "<<currClasse->nomeClasse<<endl;
        }

            cout<<endl;
        for(Studenti *currStudenti = rootClassi->studenti; currStudenti != NULL; currStudenti = currStudenti->next) {   //puntatore d'appoggio per gli artisti
            cout<<"Nome: "<<currStudenti->nome<<endl;
            cout<<"Cognome :"<<currStudenti->cognome<<endl;
            cout<<"nome classe  :"<<currStudenti->nomeClasse<<endl<<endl;
            cout<<endl;
        }

            /*
            for(Voti *currVoti = currStudenti->voti; currVoti != NULL; currVoti = currVoti->next) {  //puntatore d'appoggio per i dischi
                cout<<"        "<<"tipo: "<<currVoti->tipo<<endl;
                cout<<"        "<<"voto: "<<currVoti->voto<<endl;
                cout<<"        "<<"data: ";
                getData(currVoti->data);
                cout<<endl;
            }
            cout<<endl<<endl;
        }*/
    }
    cout<<endl;
}
int main() {
    /*
    string s1 = "aaaab", s2 = "aaaaaaaac";
    cout << s1.compare(s2);
*/
    Classi *rootClassi=NULL;
    int scelta=0;
    string dopo;
    Studenti *root= NULL;
    do{
        menu();
        cin>>scelta;

        switch(scelta){

        case 1:
            inserimentoStudente(root);
            break;

        case 2:
            stampa(root);
            break;

        case 3:{
            string nome;
            cout<<"nome"<<endl;
            cin>>nome;
            inserimentoVoti(root,nome);
            break;
        }

        case 4:
            inserimentoClassi(root,rootClassi);
            break;
        case 5:
            stampaClassi(rootClassi);

            break;



        }


    }while(scelta!=99);
    return 0;
}
