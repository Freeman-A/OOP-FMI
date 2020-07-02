/** Se dorește implementarea unei aplicații care sa permita gestionarea conturilor
deschise la banca X. Fiecare cont bancar are obligatoriu un detinator, o data a deschiderii lui
și un sold. În cazul conturilor de economii, trebuie retinuta si rata dobânzii (care poate fi pe 3
luni, pe 6 luni sau la un an), precum și un istoric al reactualizarii soldurilor de la deschidere și
până în prezent. În cazul în care deținătorul optează pentru un cont curent, el beneficiază de
un număr de tranzacții gratuite și altele contra cost (de exemplu orice depunere este
gratuită, dar retragerea poate sa coste dacă s-a depășit numărul de tranzacții gratuite, sau e
făcută de la bancomatele altor bănci; sau orice cumparatura online are un cost, etc.).
Simulati cat mai corect activitatea băncii X.
*/

#define _WIN32_WINNT 0x0500
#include <map>
#include <exception>
#include <iostream>
#include <vector>
#include <complex>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <windows.h>
#include <windowsx.h>

using std::find;
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::ostringstream;
using std::cin;
using std::cout;
using std::endl;


template <typename T>
T getline_type(istream &in)
{
    string read;
    in>>read;
    T temp;
    std::stringstream convert(read);
    convert >> temp;
    return temp;
}



namespace tip_cont
{

class is_credit
{
    static const bool val = true;
    static const bool val2 = false;
public:
    static const bool get(int type)
    {
        if(type == 1)
            return val2;
        return val;
    }
};

class is_standard
{
    static const bool val = true;
    static const bool val2 = false;
public:
    static const bool get(int type)
    {
        if(type == 1)
            return val2;
        return val;
    }
};
}


class data
{
    int an, luna, zi;

public:
    data()
    {
        zi = -1;
        luna = -1;
        an = -1;
    }
    data(int z, int l, int a)
    {
        if(z < 0 || l < 0 || a < 0)
        {
            zi = -1;
            luna = -1;
            an = -1;
            ///warning 1
        }
        else
        {
            zi = z;
            luna = l;
            an = a;
        }
    }

    vector<int> getter()
    {
        vector <int> x;
        x.push_back(zi);
        x.push_back(luna);
        x.push_back(an);
        return x;
    }
    int size()
    {
        if(zi == -1 || an == -1 || luna == -1)
            return 0;
        else
            return 1;

    }
    friend bool operator==(const data &obj2, const data &obj1);
    friend bool operator!=(const data &obj2, const data &obj1);
    friend ostream& operator<<(ostream& out, const data &obj1);
};

ostream& operator<<(ostream& out, const data &obj1)
{

    cout<<obj1.an<<" "<<obj1.luna<<" "<<obj1.zi<<endl;
    return out;
}

bool operator==(const data &obj2, const data &obj1)
{
    if(obj2.an != obj1.an)
        return 0;
    else
    {
        if(obj2.luna != obj1.luna)
            return 0;
        else
        {
            if(obj1.zi != obj2.zi)
                return 0;
            else
                return 1;

        }


    }
}

bool operator!=(const data &obj2, const data &obj1)
{
    return !(obj2 == obj1);
}

string converter(data x, string s = "/")
{
    vector <int> temp = x.getter();
    string ret_temp;
    if(s == "/")
    {
        ret_temp = static_cast<ostringstream*>( &(ostringstream() << temp[0]) )->str() + "/";
        ret_temp += static_cast<ostringstream*>( &(ostringstream() << temp[1]) )->str() + "/" ;
        ret_temp += static_cast<ostringstream*>( &(ostringstream() << temp[2]) )->str();
    }
    else
    {
        ret_temp = static_cast<ostringstream*>( &(ostringstream() << temp[0]) )->str();
        ret_temp += static_cast<ostringstream*>( &(ostringstream() << temp[1]) )->str();
        ret_temp += static_cast<ostringstream*>( &(ostringstream() << temp[2]) )->str();
    }
    return ret_temp;
}


///nu e nevoie de citiri si afisari getterul e super puternic
class detinator
{
    string nume;
    string prenume;
    data data_nasterii_detinator; ///optional
public:
    detinator() {}
    detinator(string numex, string prenumex, data data_nasterii)
    {
        nume = numex;
        prenume = prenumex;
        data_nasterii_detinator = data_nasterii;
    }
    vector <string> getter()
    {
        vector <string> temp;
        temp.push_back(nume);
        temp.push_back(prenume);
        if(data_nasterii_detinator.size()!=0)
        {
            temp.push_back(converter(data_nasterii_detinator));
        }

        return temp;
    }

    friend bool operator==(const detinator &obj2, const detinator &obj1);
    friend bool operator!=(const detinator &obj1, const detinator &obj2);
    friend ostream& operator<<(ostream& out, const detinator &obj1);
};

ostream& operator<<(ostream &out, const detinator &obj1)
{
    out<<obj1.nume<<" "<<obj1.prenume<<" "<<obj1.data_nasterii_detinator<<endl;
    return out;
}

bool operator==(const detinator &obj2, const detinator &obj1)
{
    if(obj1.nume != obj2.nume)
        return 0;
    else
    {
        if(obj1.prenume != obj2.prenume)
            return 0;

        else
        {
            if(obj1.data_nasterii_detinator != obj2.data_nasterii_detinator)
                return 0;
            else
            {
                return 1;
            }
        }

    }
}

bool operator!=(const detinator &obj1, const detinator &obj2)
{
    return !(obj1 == obj2);
}


class sold
{
    float credit, debit;
public:
    sold()
    {
        credit = 0;
        debit = 0;
    }
    sold(int which, float cat_de_mult = 0)
    {
        if(which == 0)
        {
            credit = cat_de_mult;
            debit = 0;
        }
        if(which == 1)
        {
            debit = cat_de_mult;
            credit = 0;
        }
        ///tip = debit > credit;
    }
    void deleter(int which, float cat_de_mult = 0)
    {
        if(which == 0)
        {
            credit = credit - cat_de_mult;
        }
        if(which == 1)
        {
            debit = debit - cat_de_mult;
        }

    }
    void setter(int which, float cat_de_mult=0)
    {
        if(which == 0)
        {
            credit = credit + cat_de_mult;
        }
        if(which == 1)
        {
            debit = debit + cat_de_mult;
        }
        ///tip = debit > credit;
    }
    vector <float> getter()
    {
        vector<float> temp;
        temp.push_back(credit);
        temp.push_back(debit);
        if(debit > credit)
            temp.push_back(1);
        else
        {
            temp.push_back(0);
        }
        return temp;
    }
    vector <string> gett_mesaj()
    {
        vector<string> temp;
        string s = "Credit:";
        temp.push_back(s);
        s = "Debit:";
        temp.push_back(s);
        s = "Tipul contului:";
        temp.push_back(s);
        return temp;
    }
    sold operator=(sold obj)
    {
        this->credit = obj.credit;
        this->debit = obj.debit;
        return *this;
    }
    friend sold &operator+(const sold& obj1, const sold&obj);
    friend sold &operator-(const sold& obj1, const sold&obj);
    friend sold &operator +=(sold& obj1, const sold& obj);
    friend sold &operator-=(sold& obj1, const sold& obj);
    friend ostream & operator <<(ostream& out, sold soldx);
};


sold &operator+(const sold& obj1, const sold& obj2)
{
    sold* temp = new sold();
    temp->credit = obj1.credit + obj2.credit;
    temp->debit = obj1.debit + obj2.debit;
    return *temp;
}

sold &operator-(const sold& obj1, const sold& obj2)
{
    sold* temp = new sold();
    temp->credit = obj1.credit - obj2.credit;
    temp->debit = obj1.debit - obj2.debit;
    return *temp;
}


sold &operator+=(sold& obj1, const sold& obj)
{
    obj1 = obj1 + obj;
    return obj1;
}

sold &operator-=(sold& obj1, const sold& obj)
{
    obj1 = obj1 - obj;
    return obj1;
}

ostream& operator <<(ostream& out, sold soldx)
{
    out<<soldx.credit<<" "<<soldx.debit<<" ";
    return out;
}


namespace banca
{

float rata_dobanda_per_banca_fixa; ///per suta la per banca


namespace dobanda_variabila
{

float dobanda()
{
    int rand_t = rand()%15 + 10; ///10 - 15;
    float rata_dobanda_per_banca_variabila = rand_t / 100;
    return rata_dobanda_per_banca_variabila;
}

};


class logs_t
{
private:
    vector <string> logs;

public:
    void insert_data(string data)
    {
        logs.push_back(data);
    }
    vector <string> get_data()
    {
        return logs;
    }
};

class id_cont
{
    detinator alpha;
    data beta;
    sold gamma;
    string id_cont_banca;
    static int counter;
    logs_t temp;
public:
    id_cont() {}
    ~id_cont() {}
    friend class logs_t;
    void insert_data(string data)
    {
        temp.insert_data(data);
    }
    vector <string> get_data()
    {
        return temp.get_data();
    }
    void sold_deleter(float temp, int which)
    {
        gamma.deleter(which, temp);
    }
    void sold_inserter(float temp, int which)
    {
        gamma.setter(which, temp);
        /// sold soldx(which, temp);
        /// tie(soldx);
    }
    void tie(sold soldx)
    {
        gamma = gamma + soldx;
        cout<<gamma;
    }
    id_cont(detinator detinatorx, data datax, sold soldx)
    {
        alpha = detinatorx;
        beta = datax;
        gamma = soldx;
        id_cont_banca = detinatorx.getter()[0] + detinatorx.getter()[1] + converter(datax, "0");
    }
    virtual string cont_bancar()
    {
        return id_cont_banca;
    }
    string status_nume()
    {
        return alpha.getter()[0] + " " + alpha.getter()[1];
    }
    string data_n()
    {
        return converter(beta);
    }
    vector <float> sold_co()
    {
        return gamma.getter();
    }
    vector <string> sold_co_msg()
    {
        return gamma.gett_mesaj();
    }
    static void add()
    {
        counter++;
    }
    const bool retrieve_type()
    {
        return tip_cont::is_standard::get(0);
    }
};
int id_cont::counter = 0;




class id_cont_economie:public id_cont
{
    float rata_dobanzii;
    float dobanda_per_luna;
    float suma_totala_dobandita;
    float cat_timp_per_timp;
    string tip;
    logs_t temp;

public:
    friend class logs_t;
    void insert_data(string data)
    {
        temp.insert_data(data);
    }
    vector <string> get_data()
    {
        return temp.get_data();
    }
    void sold_deleter(float temp, int which)
    {
        id_cont::sold_deleter(which, temp);
    }
    void sold_inserter(float temp, int which)
    {
        id_cont::sold_inserter(which, temp);
        ///sold soldx(which, temp);
        ///id_cont::tie(soldx);
    }
    static void add()
    {
        id_cont::add();
    }
    string cont_bancar()
    {
        return "ECO" + id_cont::cont_bancar();
    }
    id_cont_economie():id_cont() {}
    id_cont_economie(int which, int cat_timp, float cat_de_mult, detinator detinatorx, data datax, sold soldx):id_cont(detinatorx, datax, soldx)
    {
        if(which == 0 || which == 1)
        {
            if(which == 0)
                tip = "Fixa";
            if(which == 1)
                tip = "Variabila";
            if(which == -1)
                tip = "No";
            suma_totala_dobandita = cat_de_mult;
            cat_timp_per_timp = cat_timp;
            if(which == 0)
            {
                rata_dobanzii = rata_dobanda_per_banca_fixa;
                dobanda_per_luna = cat_de_mult / cat_timp + rata_dobanzii * cat_de_mult / cat_timp;
            }
            if(which == 1)
            {
                dobanda_per_luna = cat_de_mult / cat_timp;
                rata_dobanzii = 0; ///variabila
            }
        }
    }
    void platire_dobanda(float suma)
    {
        if(tip == "Fixa")
        {
            dobanda_per_luna =  suma_totala_dobandita / cat_timp_per_timp + rata_dobanzii * suma_totala_dobandita / cat_timp_per_timp + (dobanda_per_luna - suma);
        }
        if(tip == "Variabila")
        {
            float rest = dobanda_per_luna + dobanda_variabila::dobanda() * dobanda_per_luna - suma;
            dobanda_per_luna = suma_totala_dobandita / cat_timp_per_timp + rest;
        }

    }
    vector <float> status()
    {
        if(tip != "No")
        {
            vector<float> temp;
            temp.push_back(id_cont::sold_co()[0]);
            temp.push_back(id_cont::sold_co()[1]);
            temp.push_back(id_cont::sold_co()[2]);
            temp.push_back(rata_dobanzii);
            temp.push_back(dobanda_per_luna);
            temp.push_back(suma_totala_dobandita);
            temp.push_back(cat_timp_per_timp);
            return temp;
        }
        return id_cont::sold_co();
    }
    string status2()
    {
        return tip;
    }
    string status_te()
    {
        return id_cont::status_nume() + " data: " + id_cont::data_n();
    }
    const bool retrieve_type()
    {
        return tip_cont::is_standard::get(1);
    }

};
};

vector <detinator> data_ep;
vector <banca::id_cont> data_ep2;
vector <banca::id_cont_economie> data_ep3;



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
void meniu(int index, char whichx)
{
    while(true)
    {
        system("cls");
        cout<<"Bine ati venit / revenit domnule "<<data_ep[index].getter()[0]<<" "<<data_ep[index].getter()[1]<<endl;
        cout<<"Contul dvs este:";
        if(whichx == 'E' || whichx == 'e')
            cout<<" economic"<<endl;
        else
            cout<<" simplu"<<endl;
        cout<<"Meniu:"<<endl;
        cout<<"1) Depozitare numerar"<<endl<<"2) Scoatere numerar"<<endl<<"3) Plati dobanzi (ECO)"<<endl<<"4) Tranzactii "<<endl<<"5) Consolidare cont"<<endl;
        cout<<"6) Iesire"<<endl<<"7) Logare in alt cont (BACK)"<<endl;
        string which;
        cin>>which;
        system("cls");
        if(which == "1")
        {
            cout<<"Cat doresti sa depozitezi?"<<endl;
            float how;
            try
            {
                cin>>how;
            }
            catch(std::ios::failure &fail) {}
            cout<<"Ce fel de tip sunt banii acestia?"<<endl;
            cout<<"Credit - 0, Debit - 1"<<endl;
            int care;
            try
            {
                do
                {
                    cin>>care;
                    if(care <0 || care >1)
                    {
                        cout<<"Ai introdus orice altceva in afara de 0 sau 1"<<endl;
                    }
                }
                while(!(care >= 0 && care <= 1));

            }
            catch(std::ios::failure &fail) {}
            cout<<"Dobanda este de 5%, vor fi scosi din banii, depozitati"<<endl;
            how = (float)95/100 * how;
            if(whichx == 'E' || whichx == 'e')
            {
                data_ep3[index].sold_inserter(how, care);
                string how_string =  static_cast<ostringstream*>( &(ostringstream() << how) )->str();
                string combine = "Depozitare  " + how_string + " bani in lei";
                data_ep3[index].insert_data(combine);

            }
            if(whichx == 'S' || whichx == 's')
            {
                data_ep2[index].sold_inserter(how, care);
                string how_string =  static_cast<ostringstream*>( &(ostringstream() << how) )->str();
                string combine = "Depozitare  " + how_string + " bani in lei";
                data_ep2[index].insert_data(combine);
            }
            cout<<"Banii au fost introdusi cu succes"<<endl;
            cout<<"Aveti 30 secunde sa iesiti sau apasati enter"<<endl;
            system("timeout 30 > null");
        }
        if(which == "2")
        {
            cout<<"Cat doresti sa scoti?"<<endl;
            float how;
            try
            {
                cin>>how;
            }
            catch(std::ios::failure &fail) {}
            cout<<"Ce fel de tip sunt banii acestia?"<<endl;
            cout<<"Credit - 0, Debit - 1"<<endl;
            int care;
            try
            {
                do
                {
                    cin>>care;
                    if(care <0 || care >1)
                    {
                        cout<<"Ai introdus orice altceva in afara de 0 sau 1"<<endl;
                    }
                }
                while(!(care >= 0 && care <= 1));

            }
            catch(std::ios::failure &fail) {}
            cout<<"Dobanda este de 5%, vor fi scosi din banii pe care ii scoti!"<<endl;
            how = (float)95/100 * how;
            if(whichx == 'E' || whichx == 'e')
            {
                data_ep3[index].sold_deleter(how, care);
                string how_string =  static_cast<ostringstream*>( &(ostringstream() << how) )->str();
                string combine = "Depozitare  " + how_string + " bani in lei";
                data_ep3[index].insert_data(combine);
            }
            if(whichx == 'S' || whichx == 's')
            {
                data_ep2[index].sold_deleter(how, care);
                string how_string =  static_cast<ostringstream*>( &(ostringstream() << how) )->str();
                string combine = "Depozitare  " + how_string + " bani in lei";
                data_ep2[index].insert_data(combine);
            }
            cout<<"Banii au fost scosi cu succes"<<endl;
            cout<<"Aveti 30 secunde sa iesiti sau apasati enter"<<endl;
            system("timeout 30 > null");
        }
        if(which == "3")
        {
            if(whichx == 'E' || whichx == 'e')
            {





            }
        }
        if(which == "4")
        {




        }
        if(which == "5")
        {
            if(whichx == 'E' || whichx == 'e')
            {
                ///for(vector<float>::iterator it=data_ep3[index].status().begin(); it!=data_ep3[index].status().end(); it++)cout<<*it<<endl;
                cout<<endl<<"Numele contului: "<<data_ep3[index].status_nume()<<endl<<"Cu contul: "<<data_ep3[index].cont_bancar()<<endl;
                cout<<endl<<data_ep3[index].status2()<<endl<<data_ep3[index].status_te()<<endl;
                for(int i=0; i<data_ep3[index].sold_co().size(); i++)
                {
                    cout<<" "<<i<<") "<<data_ep3[index].sold_co_msg()[i]<<" "<<data_ep3[index].sold_co()[i];
                    if(i != data_ep3[index].sold_co().size() - 1)
                        cout<<" Lei"<<endl;
                    else
                        cout<<endl;
                }
                cout<<endl<<"Indice: 0 - credit, 1 - debit"<<endl;
            }
            if(whichx == 'S' || whichx == 's')
            {
                cout<<endl<<"Numele contului: "<<data_ep2[index].status_nume()<<endl<<"Cu contul: "<<data_ep2[index].cont_bancar()<<endl;
                cout<<"Ai soldul de: "<<endl;
                for(int i=0; i<data_ep2[index].sold_co().size(); i++)
                {
                    cout<<" "<<i<<") "<<data_ep2[index].sold_co_msg()[i]<<" "<<data_ep2[index].sold_co()[i];
                    if(i != data_ep2[index].sold_co().size() - 1)
                        cout<<" Lei"<<endl;
                    else
                        cout<<endl;
                }
                cout<<endl<<"Indice: 0 - credit, 1 - debit"<<endl;

            }
            system("timeout 30");

        }
        if(which == "6")
            exit(1);
        if(which == "7")
            break;
    }

}

void error(const char *file, int line, int err)
{
    cout<<file<<"   "<<line<<" "<<" "<<err<<endl;
}

class UI
{
    static int transparency_t;
    static int backcolor_t;
    static int forecolor_t;

public:
    UI()
    {

    }
    UI(int transparency, int forecolor, int backcolor)
    {
        transparency_t = transparency;
        forecolor_t = forecolor;
        backcolor_t = backcolor;
        string combination =  static_cast<ostringstream*>( &(ostringstream() << backcolor) )->str() + static_cast<ostringstream*> (&(ostringstream() << forecolor)) ->str();
        string color = "color ";
        system((color + combination).c_str());
        HWND hWnd = GetConsoleWindow();
        LONG lRet = SetWindowLong(hWnd, GWL_EXSTYLE,
                                  GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        lRet = SetLayeredWindowAttributes(hWnd, 0, transparency, LWA_ALPHA);
        if(lRet)
        {
            cout<<"Transparency imported successfully"<<endl;
        }
        else
        {
            error(__FILE__, __LINE__, GetLastError());
        }
    }
    void hidden_setter(int transparency, int forecolor, int backcolor)
    {
        transparency_t = transparency;
        forecolor_t = forecolor;
        backcolor_t = backcolor;
    }
    static vector <int> getter()
    {
        vector <int> temp;
        temp.push_back(transparency_t);
        temp.push_back(backcolor_t);
        temp.push_back(forecolor_t);
        return temp;
    }
};
int UI::backcolor_t = 0;
int UI::forecolor_t = 0;
int UI::transparency_t = 250;


void settings()
{
    for(vector<int>::iterator i = UI::getter().begin(); i!=UI::getter().end(); i++)
        cout<<(*i)<<" ";
    cout<<"Do you want to change the UI? (1 - Yes / 0 - No)"<<endl;
    int temp;
    try
    {
        do
        {
            cin>>temp;
            if(temp < 0 || temp > 1)
                cout<<"You inserted a bad number ... retry"<<endl;
        }
        while(!(temp >=0 && temp <=1));
    }
    catch(std::ios_base::failure &fail) {}

}

void set_window_console()
{
    cout<<"Select one of 5 colors "<<endl;
    cout<<"Yellow (1), Red (2), Green (3), Blue (4), Black (0 - default)"<<endl;
    int s = getline_type<int>(cin);
    int backcolor, forecolor;
    if(s == 1)
    {
        system("color 60");
        backcolor = 6;
        forecolor = 0;
    }
    if(s == 2)
    {
        system("color 47");
        backcolor = 4;
        forecolor = 7;
    }
    if(s == 3)
    {
        system("color 27");
        backcolor = 2;
        forecolor = 7;
    }
    if(s == 4)
    {
        system("color 17");
        backcolor = 1;
        forecolor = 7;
    }
    if(s == 0)
    {
        system("color");
        backcolor = 0;
        forecolor = 7;
    }
    UI* temp = new UI();
    temp->hidden_setter(180, forecolor, backcolor);
    cout<<"Loading the application  "<<endl;
    LONG lRet;
    HWND hWnd = GetConsoleWindow();
    cout<<"Set the console title "<<endl;
    system("timeout 1 > null");
    SetConsoleTitle("Tema 7 - Aplicatie banca by Mihalea Andreas ALPHA V0.0.2");
    cout<<"Set the transparency "<<endl;
    system("timeout 1 > null");
    lRet = SetWindowLong(hWnd, GWL_EXSTYLE,
                         GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    lRet = SetLayeredWindowAttributes(hWnd, 0, 180, LWA_ALPHA);
    if(lRet)
    {
        cout<<"Aplication loaded successfully"<<endl;
    }
    else
    {
        error(__FILE__, __LINE__, GetLastError());
    }
}


int main()
{
    set_window_console();
    std::map <banca::id_cont, banca::logs_t> temp;
    vector <char> care;
    while(true)
    {
        system("cls");
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("Data de azi: %d-%02d-%02d \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        printf("Aplicatie banca STATUS: alpha v0.0.2\n");
        printf("Bun venit!");
        printf("\nMeniu\n1) Creati un cont bancar\n");
        printf("2) Logati va\n");
        printf("3) Settings\n");
        printf("4) Exit\n");
        int s;
        cin.exceptions(std::istream::failbit);
        try
        {
            cin>>s;
        }
        catch(std::ios_base::failure &fail)
        {
            cout<<"You introduced whatever except a integrer number"<<endl;
            cin.clear();
        }

        system("cls");

        if(s == 3)
        {
            settings();
        }
        if(s == 4)
        {
            return 0;
        }
        if(s == 2)
        {
            string temp, temp2;
            int z,l,a, ok = 1;
            cout<<"Introduceti numele:"<<endl;
            cin>>temp;
            cout<<"Introduceti prenumele:"<<endl;
            cin>>temp2;
            cout<<"Introduceti data de nastere"<<endl;
            cin>>z>>l>>a;
            data con(z,l,a);
            int j;
            detinator temp_x(temp, temp2, con);
            for(int i=0; i<data_ep.size(); i++)
            {
                if(data_ep[i] == temp_x)
                {
                    ok = 0;
                    j = i;
                    break;
                }

            }

            if(ok == 0)
            {
                cout<<"Cont detectat"<<endl;
                cout<<"Apasati enter sau asteptati 30 de secunde"<<endl;
                system("timeout 30");
                meniu(j, care[j]);
            }
            else
            {
                cout<<"Cont nedetecat"<<endl;
                system("timeout 30");
            }
        }
        if(s == 1)
        {
            string s, f;
            cout<<"Pentru inceput cum va numiti:"<<endl;
            cout<<"Nume: ";
            cin>>s;
            cout<<"Prenume: ";
            cin>>f;
            cout<<"Data nasterii (z/l/a): ";
            int z,l,a;
            do
            {
                try
                {
                    cin>>z>>l>>a;
                }
                catch(std::ios_base::failure &fail) {}
                if(a > tm.tm_year + 1900 || l > 12 || z > 31)
                    cout<<"Ati introdus gresit data"<<endl;
            }
            while(a > tm.tm_year + 1900 || l > 12 || z > 31);
            if(a > tm.tm_year + 1900 - 18)
                cout<<"Nu aveti 18 ani"<<endl;
            else
            {
                int ok = 1;
                if(a - tm.tm_year == 18)
                    ok = 0;
                if(l > tm.tm_mon && ok == 0)
                    cout<<"Nu aveti 18 ani"<<endl;
                else
                {
                    if(z > tm.tm_mday && ok == 0)
                        cout<<"Nu aveti 18 ani"<<endl;
                    else
                    {
                        ///contul a fost creat in data x
                        data datax(z, l, a);
                        cout<<"Ce cont doriti sa faceti economic sau simplu (E / S): ";
                        char cit;
                        cin>>cit;
                        detinator detinatorx(s, f, datax);
                        cout<<"Pentru ca ati creat un cont veti primi un cadou de la banca de 100 lei!"<<endl;
                        sold* soldx = new sold(0, 100);
                        cout<<"Contul a fost creat cu succes"<<endl;
                        if(cit == 'S' || cit == 's')
                        {
                            data datac(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                            banca::id_cont cont(detinatorx, datac, *soldx);
                            data_ep2.push_back(cont);
                            size_t index = data_ep2.size() - 1;
                            data_ep2[index].insert_data(detinatorx.getter()[0] + " " + detinatorx.getter()[1] + converter(datax, "/"));
                            cont.add();
                        }
                        if(cit == 'E' || cit == 'e')
                        {
                            data datac(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                            banca::id_cont_economie cont(-1, 0, 0, detinatorx, datac, *soldx);
                            data_ep3.push_back(cont);
                            size_t index = data_ep3.size() - 1;
                            data_ep3[index].insert_data(detinatorx.getter()[0] + " " + detinatorx.getter()[1] + converter(datax, "/"));
                            cont.add();
                        }
                        care.push_back(cit);
                        cout<<endl<<endl<<"La logare introduceti numele, prenumele si data de nastere ca sa va logati"<<endl;
                        data_ep.push_back(detinatorx);
                    }
                }
            }
            system("timeout 30");
        }
    }

    return 0;
}

#pragma GCC diagnostic pop


///Cerinte folosite:


///1) Utilizarea STL
///2) Utilizatea functiilor statice, constantelor si statice
///3) Citirea a n obiecte
///4) Tratarea exceptiilor
