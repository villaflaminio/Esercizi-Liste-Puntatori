#include <iostream>

using namespace std;



void menu();

long int inserisciData();
void getData(long  int date );

void inserimentoProdotto(prodotti *&root,string nome,double peso);
void inserimentoLotto(prodotti *&root, double peso);
void inserimento(prodotti *&root);

void rimuovi(lotti *&root);
void preleva(prodotti *&corrente,double qta );

void cercaProdotto(prodotti *&root);
void printList(prodotti *&root);

int main()
{
    int scelta=0;

    prodotti *root= NULL;
    do{
        menu();
        cin>>scelta;

        switch(scelta){

            case 1:

                 inserimento(root);
                break;

            case 2:
                cercaProdotto(root);
                break;

            case 3:
              printList(root);
                break;
            case 4:

                break;
        }


    }while(scelta!=99);
    return 0;
}
void menu(){
    cout<<"............... Menu .............."<<endl;
    cout<<"1) Inserimento prodotto "<<endl;
    cout<<"2) Preleva prodotto"<<endl;
    cout<<"3) Stampa lo stato del magazzino"<<endl;
    cout<<"99) Exit"<<endl;
    cout<<"Scelta : ";
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

void inserimentoLotto(prodotti *&root, double peso){

    lotti *nuovoLotto=new lotti;
    nuovoLotto->next = NULL;
    cout<<"inserire la data di scadenza:"<<endl;
    nuovoLotto->data=inserisciData();
    nuovoLotto->peso=peso;

    if(root->nextLotto == NULL || root->nextLotto->data > nuovoLotto->data){
         nuovoLotto->next = root->nextLotto;
         root->nextLotto= nuovoLotto;

    }else{
        lotti *i;

        for(i = root->nextLotto;i->next != NULL && i->next->data < nuovoLotto->data ;i = i->next);
        nuovoLotto->next = i->next;
        i->next = nuovoLotto;
    }
}


void inserimentoProdotto(prodotti *&root,string nome,double peso)
{

    prodotti* nuovoProdotto =new prodotti();
    nuovoProdotto->next = root;
    nuovoProdotto->nomeProdotto= nome;
    nuovoProdotto->peso=peso;

    inserimentoLotto(nuovoProdotto,peso);
    root = nuovoProdotto;
}

void inserimento(prodotti *&root){

    double peso=0.0;

    prodotti* nuovoProdotto =new prodotti();
    string nomeProdotto;

    cout<<"Che prodotto desideri aggiungere ?  ";
    cin>>nomeProdotto;
    nuovoProdotto->nomeProdotto=nomeProdotto;
    cout<<"inserie il peso"<<endl;
    cin>>peso;
    nuovoProdotto->peso=peso;

    if(root==NULL){
    inserimentoProdotto(root,nomeProdotto,peso);
    }
    else{

    prodotti *corrente= new prodotti;
    corrente = root;

    bool trovato = false;

    //se è il primo lo elimino adesso perchè il codice parte dal secondo||(corrente->nomeProdotto == nuovoProdotto->nomeProdotto)
    if (corrente->nomeProdotto == nuovoProdotto->nomeProdotto){
        corrente->peso+=peso;
        inserimentoLotto(corrente,peso);


    trovato = true;
    }else{
        while (corrente != NULL && !trovato)
        {
            if (corrente->nomeProdotto == nuovoProdotto->nomeProdotto) {
                corrente->peso+=peso;
                inserimentoLotto(corrente,peso);
                trovato = true;
            }
            else {
                corrente = corrente->next;

            }
        }
    }
    if(trovato==false){
        inserimentoProdotto(root,nomeProdotto,peso);
    }
    }
}
/*
void rimuovi(lotti *&root) { //rimuove un elemento dato il nome

    lotti *corrente;
    lotti *successivo;
    corrente =root;
    successivo = corrente->next;
     delete corrente;
    root = successivo;

}*/
void removeLotto(lotti** head) {
    lotti* tmp = (*head)->next;
    delete (*head);
    *head = tmp;
}

void preleva(prodotti *&corrente,double qta ){
    prodotti* al = corrente;
    /*
    if (qta < 0)
        return 0;
    if (al == NULL)
        return 0;
    if (al->peso < qta)
        return 0;*/
    lotti** current = &(corrente->nextLotto);
    al->peso -= qta;

    while (qta > 0) {
        int qtaLotto = corrente->peso;
        if (qtaLotto > qta) {
            (*current)->peso -= qta;
            qta = 0;
        } else {
            qta -= qtaLotto;

            removeLotto(current);
        }
        if ((*current)->next != NULL)
            current = &((*current)->next);
    }
    //return 1;
}


void cercaProdotto(prodotti *&root){

    double qta=0.0;
    string nomeProdotto;

    cout<<"Che prodotto desideri prelevare ?  ";
    cin>>nomeProdotto;
    cout<<"Quanti kg? "<<endl;
    cin>>qta;

    prodotti *corrente= new prodotti;
    corrente = root;

    bool rimosso = false;

    //se è il primo lo elimino adesso perchè il codice parte dal secondo||(corrente->nomeProdotto == nuovoProdotto->nomeProdotto)
    if (corrente->nomeProdotto == nomeProdotto){


    preleva(corrente,qta);

    rimosso = true;
    }else{
        while (corrente != NULL && !rimosso)
        {
            if (corrente->nomeProdotto == nomeProdotto) {
                preleva(corrente,qta);
              //  inserimentoLotto(corrente,peso);
                rimosso = true;
            }
            else {
                corrente = corrente->next;

            }
        }
    }

}
void printList(prodotti *&root)
{
    prodotti *prod;
    lotti *lot;

    if (root)
    {
        for (prod = root; prod != 0; prod = prod->next){
            // Stampo le informazioni sull'autore

            cout << "nome: " << prod->nomeProdotto << endl;
            cout << "peso totale: " << prod->peso << endl;

            for (lot = prod->nextLotto; lot != 0; lot = lot->next)
            {

                cout << endl << "   data:  " ;
                getData(lot->data);
                cout << endl << "   peso: " << lot->peso << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
    else
        cout << endl << "Il magazzino e' vuota" << endl;
}

