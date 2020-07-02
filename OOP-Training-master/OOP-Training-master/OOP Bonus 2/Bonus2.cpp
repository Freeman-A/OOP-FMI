#include <iostream>
#include <vector>
#include <stdlib.h>

#define forp(i, n) for(int i=0; i<n; i++)
using namespace std;

class comun
{

    vector <string> nume;
    vector <string> prenume;
    string titlul;
public:
    comun() {}
    ~comun() {}
    comun(vector <string> numex, vector<string> prenumex, string titlulx)
    {
        nume = numex;
        prenume = prenumex;
        titlul = titlulx;
    }
    virtual void citire(istream &in, string which = "full")
    {
        if(which == "full")
        {
            cout<<"Cati autori sunt au contribuit:"<<endl;
            int n;
            cin>>n;
            forp(i, n)
            {
                cout<<"Introduceti autorii prin nume si prenume"<<endl;
                string nume_t, prenume_t;
                cout<<"Autorul "<<i<<endl;
                cin>>nume_t>>prenume_t;
                prenume.push_back(prenume_t);
                nume.push_back(nume_t);
            }
        }
    }
    virtual void afisare(ostream &out){
        for(int i=0; i<prenume.size(); i++)
             cout<<nume[i]<<" "<<prenume[i]<<endl;
        cout<<"Titlul este:"<<titlul<<endl;
    }
    vector<string> getter_nume()
    {
        return nume;

    }
    vector<string> getter_prenume()
    {
        return prenume;
    }
    string getter_titlul()
    {
        return titlul;
    }
     friend istream& operator>>(istream& in, comun& obj);

};


istream& operator>>(istream& in, comun& obj){
    obj.citire(in);
    return in;
}

class articol:public comun
{
    int an_publicare;
    vector <int> pagini; ///per string
    vector <int> count_pagini;
public:
    articol():comun() {}
    ~articol() {}
    articol(int an, vector<int> pag, vector<int> count_pag, vector <string> numex, vector<string> prenumex, string titlulx):comun(numex, prenumex, titlulx)
    {
        an_publicare = an;
        pagini = pag;
        count_pagini = count_pag;
    }
    void citire(istream &in)
    {
        comun::citire(in);
        for(int i=0; i<getter_prenume().size(); i++)
        {
            cout<<"Autorul "<<getter_nume()[i]<<" "<<getter_prenume()[i]<<" cate pagini a scris / contribuit?"<<endl;
            int k;
            cin>>k;
            cout<<"Introduceti paginile contribuite de el"<<endl;
            forp(j, k)
            {
                cout<<"Pagina "<<j<<endl;
                int a;
                cin>>a;
                pagini.push_back(a);
            }
            count_pagini.push_back(k);
        }
        cout<<"Introduceti anul cand s a publicat articolul"<<endl;
        cin>>an_publicare;
    }
    friend istream& operator>>(istream& in, articol& obj);
    friend ostream& operator>>(ostream& out, articol& obj);
};

istream& operator>>(istream& in, articol& obj){
        obj.citire(in);
        return in;
}

class carti:public comun
{
    int an_publicare;
    string oras;
    string editura;
public:
    carti():comun() {}
    ~carti() {}
    carti(int an, string oras_edi, string editura_edi, vector <string> numex, vector<string> prenumex, string titlulx):comun(numex, prenumex, titlulx)
    {
        an_publicare = an;
        oras = oras_edi;
        editura = editura_edi;
    }
    void citire(istream &in)
    {
        comun::citire(in);
        cout<<"Introduceti editura, orasul si anul cand s a publicat:"<<endl;
        cout<<"Oras"<<endl;
        cin>>oras;
        cout<<"Editura"<<endl;
        cin>>editura;
        cout<<"An publicare"<<endl;
        cin>>an_publicare;
    }
    void afisare(ostream &out){
       comun::afisare(out);
       cout<<oras<<" "<<editura<<an_publicare;
    }
    friend istream& operator>>(istream& in, carti& obj);
};

istream& operator>>(istream& in, carti& obj)
{
        obj.citire(in);
        return in;
}

class web:public comun
{
    string nume_organizatie;
    string prenume;
    string url;
    string titlul;
public:
    web():comun() {}
    web(string url_temp, string nume_organizatie, string prenume = NULL)
    {
        vector<string> temp_nume;
        temp_nume.push_back(nume_organizatie);
        vector <string> prenume_nume;
        prenume_nume.push_back(prenume);
        comun(temp_nume, prenume_nume, url);
    }
    void citire(istream& in)
    {
        cout<<"Nume organizatie:"<<endl;
        in>>nume_organizatie;
        cout<<"Url site ului:"<<endl;
        in>>url;
        cout<<"Titlul site ului:"<<endl;
        in>>titlul;

    }
   friend istream& operator>>(istream& in, web& obj);
};

istream& operator>>(istream& in, web& obj)
{
        obj.citire(in);
        return in;
}

int main()
{
    while(true)
    {
        system("cls");
        cout<<"Meniu"<<endl;
        cout<<"Selectati"<<endl;
        cout<<"1) Articole"<<endl;
        cout<<"2) Cartile"<<endl;
        cout<<"3) Paginele WEB"<<endl;
        string s;
        cin>>s;
        vector<comun*> all;
        system("cls");
        if(s == "1")
        {
           articol s;
           cin>>s;
           comun* temp = new articol;
           (*temp) = s;
           all.push_back(temp);
        }
        if(s == "2")
        {
           carti s;
           cin>>s;
            comun* temp = new carti;
           (*temp) = s;
           all.push_back(temp);
        }
        if(s == "3")
        {
           web s;
           cin>>s;
            comun* temp = new web;
           (*temp) = s;
           all.push_back(temp);
        }



    }
    return 0;
}
