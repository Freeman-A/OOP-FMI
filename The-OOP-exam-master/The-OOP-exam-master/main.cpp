/** Mihalea Andreas Grupa 211
Compilator GNU GCC Compilator (C++ default) (Code::Blocks 17.12)
Tutore de laborator: Marian Gusatu **/

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <cstring>
#include <typeinfo>
#include <utility>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <time.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

using namespace std;

class masti
{
private:
    static int count;
    int id;
public:
    masti()
    {
        count++;
        id = count;
    }
    masti(const masti &obj)
    {
        this->id = obj.id;
    }
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream &in, masti &obj);
    friend ostream& operator<<(ostream &out, masti &obj);
    friend masti operator++(masti &obj);
    friend masti operator--(masti &obj);
};
int masti::count = 0;

masti operator++(masti &obj)
{
    obj.count++;
    return obj;
}

masti operator--(masti &obj)
{
    obj.count--;
    return obj;
}

void masti::citire(istream &in)
{
    masti::count++;
    id = count;
}

void masti::afisare(ostream &in)
{
    cout<<"Masca are id "<<id<<endl;
}

istream& operator>>(istream &in, masti &obj)
{
    obj.citire(in);
    return in;
}

ostream& operator<<(ostream& out, masti &obj)
{
    obj.afisare(out);
    return out;
}

class mastichirugicale:public masti
{
private:
    string tip_protectie, culoare;
    int nr_de_pliuri;
public:
    mastichirugicale():masti() {}
    mastichirugicale(string tip_protectie_t, string culoare_t, int nr_de_pliuri_t):masti()
    {
        tip_protectie = tip_protectie_t;
        culoare = culoare_t;
        nr_de_pliuri = nr_de_pliuri_t;
    }
    mastichirugicale(const mastichirugicale &obj):masti()
    {
        this->tip_protectie = tip_protectie;
        this->culoare = culoare;
        this->nr_de_pliuri = nr_de_pliuri;
    }
    string get_tip_protectie()
    {
        return tip_protectie;
    }
    string get_culoare()
    {
        return culoare;
    }
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, mastichirugicale &obj);
    friend ostream& operator<<(ostream &out, mastichirugicale &obj);
};

void mastichirugicale::citire(istream &in)
{

    masti::citire(in);
    cout<<"Ce tip de protectie are masca aceasta?"<<endl;
    cin>>tip_protectie;
    if(tip_protectie == "ffp1" || tip_protectie == "ffp2" || tip_protectie == "ffp3")
    {
        cout<<"Ce culoare are masca?"<<endl;
        cin.get();
        cin>>culoare;
        cout<<"Cate pliuri?"<<endl;
        cin>>nr_de_pliuri;
    }
    else
    {
        cout<<"Eroare 0x1, ai introdus prost tip ul de protectie la masca"<<endl;
        exit(1);
        masti g;
        --g;
        --g;
    }

}

void mastichirugicale::afisare(ostream &out)
{
    masti::afisare(out);
    cout<<endl<<"Masca este chirurgicala cu tip protectie "<< tip_protectie <<" cu culoarea "<< culoare<<"cu nr de pliuri "<<nr_de_pliuri;
    cout<<endl;
}


istream& operator>>(istream &in, mastichirugicale &obj)
{
    obj.citire(in);
    return in;
}

ostream& operator<<(ostream &in, mastichirugicale &obj)
{
    obj.afisare(in);
    return in;
}

class policarbonat:public masti
{
    static string tip_protectie;
    string tip_de_prindere;


public:
    policarbonat():masti() {}
    policarbonat(string tip_de_prindere_t):masti()
    {
        tip_de_prindere = tip_de_prindere_t;
    }
    policarbonat(const policarbonat& obj):masti()
    {
        this->tip_de_prindere = obj.tip_de_prindere;
    }
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, policarbonat &obj);
    friend ostream& operator<<(ostream &out, policarbonat &obj);
};
string policarbonat::tip_protectie = "ffp0";

void policarbonat::citire(istream &in)
{
    masti::citire(in);
    cout<<"Ati selectat masca policarbonata automat tipul de protectie e ffp0"<<endl;
    cout<<"Ce tip de prindere doriti?"<<endl;
    cin>>tip_de_prindere;
}

void policarbonat::afisare(ostream &out)
{
    cout<<"Masca este de tip policarbonata cu tip de protectie ffp0"<<endl;
    cout<<"Tipul de prindere este "<<tip_de_prindere;
}

istream& operator>>(istream &in, policarbonat &obj)
{
    obj.citire(in);
    return in;
}

ostream& operator<<(ostream &in, policarbonat &obj)
{
    obj.afisare(in);
    return in;
}

class dezifectat
{
    int nr_specii_organisme;
    vector <string> ingrediente;
    vector <string> tipurile_de_suprafata;
    int count_ingrediente;
    int count_suprafete;
    vector < pair<string, int> > specii_organisme;
public:
    dezifectat() {}
    ~dezifectat()
    {
        ingrediente.clear();
        tipurile_de_suprafata.clear();
    }
    void modificare_reteta(vector<string> ingr, int nr_specii_organisme_t, vector <pair <string, int> > specii_organisme_t){
            specii_organisme = specii_organisme_t;
            nr_specii_organisme = nr_specii_organisme_t;
            ingrediente = ingr;
    }
    dezifectat(int nr_specii, vector<string> ingrediente_t, vector<string> tipurile_de_suprafata_t)
    {
        nr_specii_organisme = nr_specii;
        ingrediente = ingrediente_t;
        tipurile_de_suprafata = tipurile_de_suprafata_t;
    }
    void citire(istream &in);
    void afisare(ostream &out);
    vector< pair<string, float> > calcul_eficienta_dezifectat();
    friend istream& operator>>(istream &in, dezifectat &obj);
    friend ostream& operator<<(ostream &out, dezifectat &obj);
};

///parse string_or = {i}%
vector< pair<string, float> > dezifectat::calcul_eficienta_dezifectat()
{
    long long int total_bacteri = pow(10, 9);
    long double total_fungi = (1.5) * pow(10, 6);
    long long int total_virusi = pow(10, 8);
    float eficienta_vir, eficienta_fung, eficienta_bac;
    for(int i=0; i<nr_specii_organisme; i++)
    {
        if(specii_organisme[i].first == "virus")
        {
            eficienta_vir = (float)(specii_organisme[i].second / total_virusi) * 100;
        }
        if(specii_organisme[i].first == "fungi")
        {
            eficienta_fung = (float)(specii_organisme[i].second / total_fungi) * 100;

        }
        if(specii_organisme[i].first == "bacterii")
        {
            eficienta_bac = (float)(specii_organisme[i].second / total_bacteri) * 100;

        }

    }
    vector < pair<string, float> > temp;
    ostringstream s;
    s.precision(3);
    s << eficienta_bac;
    temp.push_back(make_pair("Eficienta bacterii "+ s.str(), eficienta_bac));
    s.precision(3);
    s << eficienta_vir;
    temp.push_back(make_pair("Eficienta virusi "+ s.str(), eficienta_vir));
    s.precision(3);
    s << eficienta_fung;
    temp.push_back(make_pair("Eficienta bacterii "+ s.str(), eficienta_fung));
    return temp;
}

void dezifectat::citire(istream &in)
{

    cout<<"Cate ingrediente are acest dezifectat?"<<endl;
    cout<<"Ce ingrediente are aces dezifectat?"<<endl;
    cin>>count_ingrediente;
    for(int i=0; i<count_ingrediente; i++)
    {
        cout<<"Cititi ingredientele pe rand"<<endl;
        string temp;
        cin>>temp;
        ingrediente.push_back(temp);
    }
    cout<<"La cate suprafete se poate aplica?"<<endl;
    cin>>count_suprafete;
    for(int i=0; i<count_suprafete; i++)
    {
        cout<<"Cititi suprafetele care se poate aplica pe rand:"<<endl;
        string temp;
        cin>>temp;
        tipurile_de_suprafata.push_back(temp);
    }
    cout<<"Cate tipuri de specii poate omari?"<<endl;
    try
    {
        cin>>nr_specii_organisme;
    }
    catch(std::ios::failure &fail) {}
    if(nr_specii_organisme < 3)
    {
        for(int i=0; i<nr_specii_organisme; i++)
        {
            string temp;
            cout<<"Introduceti tipul speciei pt organism (virus / fungi / bacterii)"<<endl;
            cin>>temp;
            if(temp == "virus" || temp == "fungi" || temp == "bacterii")
            {
                cout<<"Introduceti cate specii poate omori in organism?"<<endl;
                int n;
                try
                {
                    cin>>n;
                }
                catch(std::ios::failure &fail) {}
                specii_organisme.push_back(make_pair(temp, n));
            }
            else
            {
                exit(2);
            }
        }
    }
    else
    {
        exit(3);
    }

}

istream& operator>>(istream &in, dezifectat &obj)
{
    obj.citire(in);
    return in;

}

bool compare(const pair<string, float> &a,  const pair<string, float> &b)
{
    return (a.second < b.second);
}

class arhiva_contabila
{
    string nume_client, data;
    vector <dezifectat*> date_dezifectat;
    vector <mastichirugicale*> date_masti_chirurgicale;
    vector <policarbonat*> date_masti_policarbonat;
    vector < pair <string, float> > preturi;
    static vector <pair <string, float> > venit;
    float total_comanda;
    static float total_achizitie;
    static float total_achizitie_dezifectat;
    static float total_achizitie_masti;
    static vector < pair<string, float> > clienti;
    static string id;
public:
    arhiva_contabila()
    {
        total_comanda = 0;
    }
    arhiva_contabila(string nume, string data_t, vector<dezifectat*> date_dezifectat_t, vector<mastichirugicale*> date_masti_t, vector<policarbonat*> masti)
    {
        nume_client = nume;
        data = data_t;
        date_dezifectat = date_dezifectat_t;
        date_masti_chirurgicale = date_masti_t;
        date_masti_policarbonat = masti;
        total_comanda = 0;
    }
    arhiva_contabila(const arhiva_contabila &obj)
    {
        this->nume_client = obj.nume_client;
        this->data = obj.data;
        this->date_masti_chirurgicale = date_masti_chirurgicale;
        this->date_masti_policarbonat = date_masti_policarbonat;
        total_comanda = 0;
    }

    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, arhiva_contabila &obj);
    friend ostream& operator<<(ostream &out, arhiva_contabila &obj);
    static vector < pair<string, float> >total_luna()
    {
        return venit;
    }
    static float get_masti(){
       return arhiva_contabila::total_achizitie_masti;
    }
    static vector < pair<string, float> > clienti_t(){
           return clienti;
    }
};

float arhiva_contabila::total_achizitie = 0;
float arhiva_contabila::total_achizitie_dezifectat = 0;
float arhiva_contabila::total_achizitie_masti = 0;
vector <pair <string, float> > arhiva_contabila::venit;
vector < pair<string, float> > arhiva_contabila::clienti;
string arhiva_contabila::id;

void arhiva_contabila::citire(istream &in)
{
    cout<<"Ce doriti sa cumparati? (masti, dezifectati)"<<endl;
    string s;
    cin>>s;
    time_t lt = time(NULL);
    struct tm tm = *localtime(&lt);
    int an = tm.tm_year + 1900;
    int luna = tm.tm_mon + 1;
    int zi = tm.tm_mday;
    string luna_t = static_cast<ostringstream*>(&(ostringstream() << luna)) -> str();
    data = static_cast<ostringstream*>(&(ostringstream() << zi)) -> str() + "/" + static_cast<ostringstream*>(&(ostringstream() << luna)) -> str() + "/" + static_cast<ostringstream*>(&(ostringstream() << an)) -> str();
    if(s == "masti")
    {
        cout<<"De care masti doriti sa cumparati?"<<endl;
        cout<<"(chirurgicala / policarbonat"<<endl;
        string s1;
        cin>>s1;
        if(s1 == "chirurgicala")
        {
            mastichirugicale* temp = new mastichirugicale();
            cin>>*temp;
            string temp2 = temp->get_tip_protectie();
            if(temp2 == "ffp1")
                total_comanda += 5;
            if(temp2 == "ffp2")
                total_comanda += 10;
            if(temp2 == "ffp3")
                total_comanda += 15;
        }
        if(s1 == "policarbonat")
        {
            policarbonat* temp = new policarbonat();
            cin>>*temp;
            total_comanda += 20;
        }
        total_achizitie_masti += total_comanda;
    }
    if(s == "dezifecatat")
    {
        dezifectat *temp = new dezifectat();
        cin>>*temp;
        vector< pair<string, float> > calcul = temp->calcul_eficienta_dezifectat();
        float max = 0;
        for(int i=0; i<calcul.size(); i++)
        {
            if(max < calcul[i].second)
            {
                max = calcul[i].second;
            }
        }
        if(max < 90)
            total_comanda += 10;
        if(max < 95 && max > 90)
            total_comanda += 25;
        if(max < 97.5 && max > 95)
            total_comanda += 30;
        if(max < 99 && max > 97.5)
            total_comanda += 40;
        if(max > 99 && max < 99.9)
            total_comanda += 50;
    }
    clienti.push_back(make_pair(id, total_achizitie));
    venit.push_back(make_pair(luna_t, total_achizitie));
}

istream& operator>>(istream &in, arhiva_contabila &obj)
{
    obj.citire(in);
    return in;
}

void arhiva_contabila::afisare(ostream &out)
{

}

ostream& operator<<(ostream &in, arhiva_contabila &obj)
{
    obj.afisare(in);
    return in;
}


int main()
{
    vector <dezifectat> temp_dez;
    while(true)
    {
        int n;
        cout<<"1. Adauga un nou dezinfectant in stoc"<<endl;
        cout<<"2. Adauga o noua masca in stoc"<<endl;
        cout<<"3. Adauga o noua achizitie"<<endl;
        cout<<"4. Afiseaza dezinfectantul cel mai eficient"<<endl;
        cout<<"5. Calculeaza venitul dintr-o anumita luna"<<endl;
        cout<<"6. Calculeaza venitul obtinut din mastile chirurgicale cu model."<<endl;
        cout<<"7. Modifica reteta unui dezinfectant, modificand unul sau mai multe";
        cout<<" ingrediente, lucru ce conduce si la o modificarea a numarului de specii de";
        cout<<" organisme ce vor fi ucise si a suprafețelor pe care poate fi aplicat."<<endl;
        cout<<"8. Afiseaza cel mai fidel client (clientii NU au nume unic)"<<endl;
        cout<<"9. Afiseaza ziua cu cele mai slabe venituri, de la deschidere pana in prezent"<<endl;
        cout<<"10.Calculeaza TVA-ul (19% din venituri) care trebuie returnat la ANAF";
        cout<<" pentru un anumit an."<<endl;
        try
        {
            cin>>n;
        }
        catch(std::ios::failure &fail) {}
        if(n == 1)
        {
            dezifectat* temp = new dezifectat();
            cin>>*temp;
            temp_dez.push_back(*temp);
        }
        if(n == 2)
        {
            cout<<"Ce masca doriti sa baga in stoc? (chirurgical / policarbonat)"<<endl;
            string masca_t;
            cin>>masca_t;
            if(masca_t == "chirurgical")
            {
                mastichirugicale* temp = new mastichirugicale();
                cin>>*temp;
            }
            if(masca_t == "policarbonat")
            {
                policarbonat* temp = new policarbonat();
                cin>>*temp;
            }
        }
        if(n == 3)
        {
            arhiva_contabila *temp = new arhiva_contabila();
            cin>>*temp;
        }
        if(n == 4)
        {
            vector <float> max_f;
            for(int i=0; i<temp_dez.size(); i++)
            {

                vector< pair<string, float> > calcul = temp_dez[i].calcul_eficienta_dezifectat();
                float max = 0;
                for(int i=0; i<calcul.size(); i++)
                {
                    if(max < calcul[i].second)
                    {
                        max = calcul[i].second;
                    }
                }
                max_f.push_back(max);

            }
            sort(max_f.begin(), max_f.end());
            cout<<max_f[0]<<endl;
        }
        if(n == 5)
        {
            string luna_t;
            cout<<"Din ce luna doriti sa afisati?"<<endl;
            cin>>luna_t;
            for(int i=0; i<arhiva_contabila::total_luna().size(); i++){
                   if(arhiva_contabila::total_luna()[i].first == luna_t){
                              cout<<arhiva_contabila::total_luna()[i].second;
                              break;}

            }

        }
        if(n == 6){
             cout<<arhiva_contabila::get_masti();
        }
        if(n == 7){
            cout<<"Introduceti reteta noua si id ul dezifectatului"<<endl;
            int i, n;
            cin>>i;
            vector<string> reteta;
            cout<<"Cate ingrediente sunt?"<<endl;
            cin>>n;
            for(int j=0; j<n; j++){
                  string temp;
                  cout<<"Reteta "<<j<<endl;
                  cin>>temp;
                  reteta.push_back(temp);
            }


        }
        if(n == 8){
            vector < pair<string, float> > clienti = arhiva_contabila::clienti_t();
            int max = 0, j=0;
            for(int i=0; i<clienti.size(); i++)
            if(max < clienti[i].second){
                      max = clienti[i].second;
                      j = i;}
                      cout<<clienti[j].first;
        }

    }
    return 0;
}
#pragma GCC diagnostic pop
