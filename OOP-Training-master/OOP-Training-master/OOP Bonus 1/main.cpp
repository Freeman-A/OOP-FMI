#include <iostream>
#include <time.h>
#include <sstream>
#include <vector>
#include <stdlib.h>

using namespace std;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"

class date
{
    int mon, dd, yyyy;
public:
    date(int m, int d, int y)
    {
        mon = m;
        dd = d;
        yyyy = y;
    }
    ~date()
    {

    }
    date() {}
    friend istream& operator>>(istream &in, date obj);
    friend ostream& operator<<(ostream &out, date &obj);
    date operator=(date in)
    {
        this->dd = in.dd;
        this->mon = in.mon;
        this->yyyy = in.yyyy;
        return *this;
    }
    friend bool operator==(date obj, date obj2);
    friend string convert_cout(const date &obj);
};

bool operator==(date obj, date obj2)
{

    return obj.dd == obj2.dd && obj.mon == obj2.mon && obj.yyyy == obj2.yyyy;
}

istream& operator>>(istream &in, date obj)
{

    cout<<"Cititi ziua, luna si anul in ordine"<<endl;
    cin>>obj.dd;
    cin>>obj.mon;
    cin>>obj.yyyy;
    return in;
}

ostream& operator<<(ostream &out, date &obj)
{

    out<<obj.dd<<obj.mon<<obj.yyyy;
    return out;
}

string convert_cout(const date &obj)
{

    string temp, temp2, temp3;
    temp = static_cast<ostringstream*>(& (ostringstream() << obj.dd) )->str();
    temp2 = static_cast<ostringstream*>(& (ostringstream() << obj.mon) )-> str();
    temp3 = static_cast<ostringstream*>(& (ostringstream() << obj.yyyy) ) -> str();
    return temp + "." + temp2 + "." + temp3;

}
class magazin;

class produs
{

    date data;
    string tip_produs;
    string tip_cantitate;
    float cantitate, pret;
public:
    produs(date obj, const string tip_pro, const string tip_cant, const float cant, float pret_t)
    {
        data = obj;
        tip_produs = tip_pro;
        tip_cantitate = tip_cant;
        cantitate = cant;
        pret = pret_t;
    }
    virtual ~produs()
    {


    }
    void edit_pret(float pret_t)
    {
        pret = pret_t;
    }
    produs()
    {

    }
    date get_data()
    {
        return data;
    }
    string get_nume()
    {
        return tip_produs;
    }
    float get_cantitate()
    {
        return cantitate;
    }
    float get_pret()
    {
        return pret;
    }
    friend istream& operator>>(istream& in, produs& obj);
    friend ostream& operator<<(ostream& in, produs& obj);
    friend class magazin;
};

istream& operator>>(istream& in, produs& obj)
{

    cout<<"Cititi in ordine: data, tip_produs, tip_cantitate, pret si apoi cantitate"<<endl;
    cin>>obj.data;
    cin>>obj.tip_produs>>obj.tip_cantitate>>obj.pret>>obj.cantitate;
    return in;
}

ostream& operator<<(ostream& in, produs& obj)
{
    cout<<"Pe data de "<<convert_cout(obj.data)<<", magazinul primeste "<<obj.get_cantitate()<<"de "<<obj.get_nume();
    cout<<" la pretul de "<<obj.get_pret()<<endl;
    return in;
}


class magazin
{
    vector <produs> temp;
    static int magazin_count;
    int magazin_id;
public:
    magazin()
    {
        magazin_count++;
        magazin_id = magazin_count;
    }

    ~magazin()
    {


    }
    friend istream& operator>>(istream& in, magazin obj);
    friend ostream& operator<<(ostream& out, magazin obj);
    void afisare(date &obj)
    {
        for(int i=0; i<temp.size(); i++)
        {
            if(temp[i].get_data() == obj)
                cout<<temp[i]<<" "<<magazin_id<<endl;
        }
    }
    void delete_t(const string &nume_produs)
    {
        int elem;
        for(int i=0; i<temp.size(); i++)
        {
            if(temp[i].get_nume() == nume_produs)
            {
                elem = i;
                break;
            }

        }
        temp.erase(temp.begin() + elem);
    }
    void edit_price(float price, int i)
    {
        temp[i].edit_pret(price);
    }
    int size()
    {
        return temp.size();
    }
    friend class produs;

};
int magazin::magazin_count = 0;

istream& operator>>(istream& in, magazin obj)
{
    cout<<"Cate magazine doriti sa cititi?"<<endl;
    int e;
    cin>>e;
    for(int i=0; i<e; i++)
    {
        cout<<"Magazinul "<<i<<": "<<endl;
        produs temp;
        cin>>temp;
        obj.temp.push_back(temp);
    }
    return in;

}

ostream& operator<<(ostream& in, magazin obj)
{
    for(int i=0; i<obj.temp.size(); i++)
    {
        cout<<"Pe data de "<<convert_cout(obj.temp[i].get_data())<<", magazinul primeste "<<obj.temp[i].get_cantitate()<<"de "<<obj.temp[i].get_nume();
        cout<<" la pretul de "<<obj.temp[i].get_pret()<<endl;
    }
    return in;

}


int main()
{
    vector<magazin> array_t;
    while(true)
    {
        cout<<"1. Adaugarea unui magazin nou cu produsele comercializate"<<endl;
        cout<<"2. Afisarea tuturor magazinelor cu produsele comercializate"<<endl;
        cout<<"3. Afisarea tuturor produselor primite la o anumita data si magazinul de care apartin"<<endl;
        cout<<"4. Stergerea unui produs dintr-un magazin (se face după nume)"<<endl;
        cout<<"5. Modificarea pretului unui produs dintr-un magazin"<<endl;
        cout<<"6. Afisarea magazinului cu cele mai multe produse."<<endl;
        cout<<"7. Exit"<<endl;
        int e;
        try
        {
            cin>>e;
        }
        catch(std::ios::failure &fail) {}
        system("cls");
        if(e == 7)
            break;
        if(e == 1)
        {

            magazin temp;
            cin>>temp;
            array_t.push_back(temp);
        }
        if(e == 2)
        {
            if(array_t.size() == 0)
                cout<<"No data"<<endl;
            else
            {
                for(int i=0; i<array_t.size(); i++)
                    cout<<array_t[i]<<endl;
            }
        }
        if(e == 3)
        {
            if(array_t.size() == 0)
                cout<<"No data"<<endl;
            else
            {
                date data;
                cin>>data;
                for(int i=0; i<array_t.size(); i++)
                    array_t[i].afisare(data);
            }
        }
        if(e == 4)
        {
            if(array_t.size() == 0)
            {
                cout<<"No data"<<endl;
            }
            else
            {
                int i;
                string temp;
                cin>>temp>>i;
                array_t[i].delete_t(temp);
            }
        }
        if(e == 5)
        {
            if(array_t.size() == 0)
            {
                cout<<"No data"<<endl;

            }
            else
            {
                int i, j;
                float pret;
                cin>>i>>j>>pret;
                array_t[i].edit_price(pret, j);
            }
        }
        if(e == 6)
        {
            int max = 0, j;
            if(array_t.size() == 0)
                cout<<"no data"<<endl;
            else
            {
                for(int i=0; i<array_t.size(); i++)
                    if(max < array_t[i].size())
                    {
                        max = array_t[i].size();
                        j = i;
                    }

                cout<<array_t[j]<<endl;
            }
        }


    }
    return 0;
}

#pragma GCC diagnostic pop
