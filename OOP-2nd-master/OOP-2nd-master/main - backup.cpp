///Includes...

///==========================================================================================================

#include <iostream> /// pentru cin si cout si namespace ul std
#include <algorithm> /// pentru functia sort
#include <stdio.h> /// pentru printf sau pentru system
#include <stdlib.h> /// pentru system in concordanta cu stdio
#include <cstring> ///pentru strlen, strcmp etc.
#include <windows.h> ///pentru Buffere folosit la clearscreen
#include <vector> ///pentru vectori
#include <complex>
#include <typeinfo>

///==========================================================================================================

///Namespace uri

using namespace std;

///==========================================================================================================

///Define uri

///==========================================================================================================

#define forp(i, n) for(int i=0; i<n; i++) ///scurteaza codul

///==========================================================================================================

///Template type verify

///==========================================================================================================

template<typename T>
struct is_int
{
    static bool const val = false;

};

template <>
struct is_int<int>
{
    static bool const val = true;
};

template<typename T>
struct is_float
{
    static bool const val = false;

};

template <>
struct is_float< float >
{
    static bool const val = true;
};

template<typename T>
struct is_unsigned_t
{
    static bool const val = false;

};

template <>
struct is_unsigned_t<unsigned>
{
    static bool const val = true;
};

template<typename T>
struct is_vector_string
{
    static bool const val = false;

};

template <>
struct is_vector_string< vector<string> >
{
    static bool const val = true;
};

template<typename T>
struct is_string
{
    static bool const val = false;

};

template <>
struct is_string< string >
{
    static bool const val = true;
};

///Functions...

///==========================================================================================================

void clearscreen()
{
    ///cod preluat de la proiectul numarul 1
    ///stable version of system("cls") ...
    DWORD n;
    COORD coord = {0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GCSBI(GSH_S_O_H, &csbi );
    FCOC (GSH_S_O_H, TEXT ( ' ' ), csbi._X * csbi._Y, coord, &n );  ///reseteaza ecranul si duce cursorul la inceput
    GCSBI(GSH_S_O_H, &csbi );
    FCOA (GSH_S_O_H, csbi.wAttributes, csbi._X * csbi._Y, coord, &n );
    SCCP (GSH_S_O_H, coord );

    ///metoda alternative
    ///#1
    ///for(int i=0;i<10;i++) printf("/n/n/n/n/n/n/n/n/n"), sterge ecranul dar duce cursorul la 100 de spatii;

    ///#2
    ///system("cls") -> apeleaza din cmd.exe comanda cls in short (cmd.exe cls)

    ///#3
    ///forp(i, 10) cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl; la fel ca la #1

    /// ...
}


///Function based on template class T

template <class T>
T atoi(const char *s)
{
    ///stable version of atoi(const char *s) ....
    ///complexitatea O(n)
    if(is_unsigned_t<T>::val || is_int<T>::val)
    {
        int ok = 0;
        int len = strlen(s);
        for(int i=0; i < len; i++)
            if (s[i] < '0' || s[i] > '9')
            {
                if(!(s[i]=='-' && (s[i+1] >= '0' && s[i+1] <= '9')))
                {
                    ok = 1;;
                    break;
                }

            }
        if (ok == 0)
        {
            T e = 0, *t = new int[len + 1];
            if (s[0] == '-')
            {
                for (int i=1; i<len; i++)
                {
                    t[i] = int(s[i] - '0');
                    e=e+t[i];
                    e=e*10;
                }
                e = -(e / 10);
                return e;
            }

            else
            {
                for (int i=0; i<len; i++)
                {
                    t[i] = int(s[i] - '0');
                    e=e+t[i];
                    e=e*10;
                }
                e /= 10;

                return e;
            }
        }
        else
        {
            cout<<"Error 001! It doesn't convert to int because is not a number"<<endl;
            perror(NULL);
            return 9999; ///este pentru nu a aparea warning-uri
        }
    }
    /// ...
}

/**template <typename T>
T getline_type(istream &in);

template<>
std::string getline_type<std::string>(istream &in){
    string read;
    getline(in, read);
    return read;
}*/



string split (string& s, string remove_t)
{
    size_t pos_start = 0, pos_end, len = remove_t.length();
    string token, combine;
    while ((pos_end = s.find (remove_t, pos_start)) != string::npos)
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + len;
        combine += token;
    }

    combine += s.substr(pos_start);
    s = combine;
    return combine;
}

bool isNumber(const char* s, char compl1 ='-')
{
    /// Verificare sir de caractere daca formeaza un numar
    int len = strlen(s);
    forp(i, len)
    if (s[i] < '0' || s[i] > '9')
    {
        ///Cazul pt negativ
        if(compl1 == '-')
        {
            if(!(s[i]=='-' && (s[i+1] >= '0' && s[i+1] <= '9')))
                return false;
        }
        else
            return false;
    }

    return true;
    /// ...
}

///==============================================================================================================

template <typename T>
T getline_type(istream &in)
{
    string read;
    in>>read;
    T temp;
    if (is_int<T>::val || is_unsigned_t<T>::val || is_float<T>::val) /// EXPERIMENTAL for float types values
    {
        if(!isNumber(read.c_str(), '-'))
            cout<<"Warning 006: You introduced a string type, it will be converted to 0. Bypass!"<<endl;
    }
    if(is_unsigned_t<T>::val)
    {
        char minus_unsigned = read[0];
        if (minus_unsigned == '-')
        {
            cout<<"Warning 005: You introduced a negative number or a bad string. Bypass!"<<endl;
            string unsigned_convert = split(read, "-");
            std::stringstream convert(unsigned_convert);
            convert >> temp;
        }
        else
        {
            std::stringstream convert(read);
            convert >> temp;
        }
        return temp;
    }

    std::stringstream convert(read);
    convert >> temp;
    return temp;
}

///=============================================================================================================

///Classess

///1) Class nod

///==========================================================================================================

template <class T>
class Nod
{

protected:
    T info;
    Nod<T>* next;

public:
    Nod<T>()
    {
        next = NULL;
    }
    Nod<T>(T temp)
    {
        info = temp;
        next = NULL;
    }
    void setter(T temp)
    {
        info = temp;
    }
    void setnext(Nod<T> *setnext)
    {
        next = setnext;
    }
    Nod<T>* getnext()
    {
        return next;
    }
    T getdata()
    {
        return info;
    }
    template <class U>
    friend istream& operator>>(istream& in, Nod<U>* nod);
    template <class U>
    friend ostream& operator<<(ostream& out, Nod<U>* nod);
};

template <class T>
istream& operator>>(istream& in, Nod<T>* nod)
{
    T info;
    info = getline_type<T>(cin);
    nod->info = info;
    return in;
}

template <class T>
ostream& operator<<(ostream& out, Nod<T>* nod)
{
    T info;
    info = nod->info;
    nod->next = nod;
    out<<info;
    return out;
}

///==========================================================================================================

///2) Class Nod_dublu

///==========================================================================================================

template <class T>
class Nod_dublu: public Nod<T>
{
protected:
    Nod<T> *ante;  ///nodul anterior

public: ///mostenirea
    Nod_dublu<T>():Nod<T>(), ante() { }
    Nod_dublu<T>(T init):Nod<T>(init), ante() { }
    Nod_dublu<T>* convert(Nod<T>* temp)
    {
        Nod_dublu<T>* temp_dublu = new Nod_dublu();
        temp_dublu->setante();
        temp_dublu->setter(temp->getdata());
        temp_dublu->setnext(temp->getnext());
        return temp_dublu;
    }
    Nod<T>* getante()
    {
        return ante;
    }
    void setante(Nod<T>* temp = NULL)
    {
        ante = temp;
    }
    Nod<T>* convert_front(Nod_dublu<T>* temp)
    {
        Nod<T>* gamma = new Nod<T>(temp->getdata());
        T i;
        try
        {
            if(temp == NULL)
            {
                i = temp->getdata();
                throw i;
            }
            else
            {
                gamma->setnext(temp->getnext());
            }
        }
        catch(T i)
        {
            cout<<"Error 002! You tried to convert a double node NULL to a single node"<<endl;
        }
        return gamma;
    }

    Nod_dublu<T>* convert_back(Nod<T>* temp)
    {
        T i;
        try
        {
            if(temp == NULL)
            {
                i = temp->getdata();
                throw i;
            }
            else
            {
                this->setter(temp->getdata());
                this->setnext(temp->getnext());
                this->setante(NULL);
            }
        }
        catch(T i)
        {
            cout<<"Error 003! You tried to convert a double node NULL to a single node"<<endl;
        }
        return this;

    }

    template <class U>
    Nod_dublu<U>* operator=(Nod_dublu<U>* temp)
    {
        if(temp->ante == NULL)
            this->ante = NULL;
        if(temp->next == NULL)
        {
            this->ante = temp->ante;
            this->next = NULL;
            this->info = temp->info;
        }
        else
        {
            if(this->ante == NULL && this->info == NULL)
            {
                perror(ERROR_ACCESS_DENIED);
            }
            else
            {
                this->ante = temp->ante;
                this->info = temp->info;
                this->next = temp->next;
                return this;
            }
        }
    }

    template <class U>
    friend istream& operator>>(istream& in, Nod_dublu<U>* nod);
    template <class U>
    friend ostream& operator<<(ostream& out, Nod_dublu<U>* nod);
};


template <class T>
istream& operator>>(istream& in, Nod_dublu<T>* nod)
{
    T info;
    info = getline_type<T>(cin);
    nod->info = info;
    return in;
}

template <class T>
ostream& operator<<(ostream& out, Nod_dublu<T>* nod)
{
    out<<nod->info;
    return out;
}

///==========================================================================================================

///3) class LDI

template <class T>
class LDI
{
    ///Elementele
    Nod_dublu<T>** elemente;
    int elem;
    static int count_sort;
public:

    ///Meniu:
    LDI<T>(int cate_elemente = 0)
    {
        elem = cate_elemente;
        elemente = new Nod_dublu<T>*[cate_elemente];
    }
    void reset_space(int cate_elemente)
    {
        elemente = new Nod_dublu<T>*[cate_elemente];
        elem = cate_elemente;
    }
    int space()
    {
        return this->elem;
    }
    Nod_dublu<T>** elemente_return()
    {
        return elemente;
    }
    void push(Nod_dublu<T>* head, int i); ///push;
    void push_back(Nod_dublu<T>* back, int i);
    void append(Nod_dublu<T>* append_i, int i);
    void sort_LDI(LDI<T>& obj, bool reverse, bool inserction);
    void sorted(Nod_dublu<T> **cap, Nod_dublu<T> **coada, T key);
    static void get_sorted()
    {
        return count_sort;
    }
    template <class U>
    friend istream& operator>>(istream& in, LDI<U>& ldi);
    template <class U>
    friend ostream& operator<<(ostream& out, LDI<U>& ldi);
    template <class U>
    LDI<U> operator=(LDI<U> ldi)
    {
        this->elem = ldi.elem;
        this->elemente = new Nod_dublu<U>*[ldi.elem];
        for(int i=0; i<elem; i++)
        {
            this->elemente[i] = ldi.elemente[i];
        }
        return *this;
    }
};

template <class T>
bool compare(Nod_dublu<T>* a, Nod_dublu<T>* b)
{
    return a->getdata() > b->getdata();
}

template <class T>
bool compare_front(Nod_dublu<T>* a, Nod_dublu<T>* b)
{
    return a->getdata() < b->getdata();
}

template <class T>
void LDI<T>::append(Nod_dublu<T>* append_b, int i)
{
    if (elemente[i] == NULL)
    {
        append_b->setante(NULL);
        elemente[i] = append_b;
        return;
    }
    while (elemente[i]->getnext() != NULL)
        elemente[i] = elemente[i]->convert_back(elemente[i]->getnext());
    elemente[i]->setnext(append_b);
    append_b->setante(elemente[i]);
    return;
}


template <class T>
void LDI<T>::sort_LDI(LDI<T>& obj, bool reverse, bool insertion)
{
    if(insertion == false)
    {
        if(reverse == false)
        {
            sort(obj.elemente, obj.elemente + obj.elem, compare_front<T>);
        }
        else
        {
            sort(obj.elemente, obj.elemente + obj.elem, compare<T>);
        }

    }
    else
    {
        LDI<T> sort_t(elem);
        for(int i=0; i<obj.elem; i++)
        {
            T key;
            int j;
            key = obj.elemente[i]->getdata();
            system("pause");
            j = i - 1;
            while(j>=0 && (obj.elemente[j])->getdata() > key)
            {
                system("pause");
                obj.elemente[j+1]=obj.elemente[j];
                j--;
            }
            obj.elemente[j + 1] = new Nod_dublu<T>(key);
            system("pause");
        }
    }

}

template <class T>
void LDI<T>::push_back(Nod_dublu<T>* back, int i)
{
    try
    {
        if(back == NULL)
            throw i;
    }
    catch(int i)
    {
        cout<<"Error: The double node can't be null"<<endl;
        return;
    }
    Nod_dublu<T>* before = new Nod_dublu<T>();
    before->setter(back->getdata());
    before->setnext(back->getnext());
    if (before->getnext() != NULL)
        before->getante()->setnext(before);
    else
        elemente[i] = before;
}

template <class T>
void LDI<T>::push(Nod_dublu<T>* head, int i)
{
    if(elemente[i] !=NULL)
        elemente[i]->setante(head);

    elemente[i] = head;
}

template <class T>
ostream& operator<<(ostream& out, LDI<T>& ldi)
{

    int e = ldi.elem;
    for(int i=0; i<e; i++)
        cout<<(ldi.elemente[i])<<" ";

    cout<<endl;
    return out;
}

///==========================================================================================================

///4) Class LSI

///==========================================================================================================

template <class T>
class LSI:public LDI<T>
{
    Nod<T>** elemente;
public:
    LSI<T>(int cate_elemente = 0):LDI<T>(cate_elemente) {};
    LSI<T> downgrade(LDI<T> temp)
    {
        int space = temp.space();
        try
        {
            if(space==0)
                throw space;
            else
            {
                this->reset_space(space);
                Nod<T>** elemente_temp = new Nod<T>*[space];
                Nod_dublu<T>** elemente_temp2 = new Nod_dublu<T>*[space];
                elemente_temp2 = temp.elemente_return();
                this->elemente = new Nod<T>*[space];
                for(int i=0; i<space; i++)
                {
                    elemente_temp[i] = elemente_temp2[i]->convert_front(elemente_temp2[i]);
                    this->elemente[i] = elemente_temp[i];
                }
            }
        }

        catch(int elem)
        {
            cout<<"Error 001! You tried to convert something null"<<endl;
            perror("Error");
        }
        return *this;

    }
    LDI<T> upgrade(LSI<T> temp)
    {
        try
        {
            if(temp.elem==0)
                throw temp.elem;
            else
            {
                this->elem = temp.elem;
                Nod_dublu<T>** elemente_temp = new Nod_dublu<T>*[temp.elem];
                elemente_temp = convert_back(temp.elemente);
                this->elemente = elemente_temp;
            }
        }

        catch(int elem)
        {
            cout<<"Error 001! You tried to convert something null"<<endl;
            perror("Error");
        }
        return *this;


    }
    //friend istream& operator>><>(istream& in, LSI<T>&);
    template <class U>
    friend ostream& operator<<(ostream& out, LSI<U>& lsi);
};


template <class T>
ostream& operator<<(ostream& out, LSI<T>& lsi)
{
    int e = lsi.space();
    for(int i=0; i<e; i++)
        cout<<(lsi.elemente[i])<<" ";
    cout<<endl;
    return out;
}

template<typename T>
struct is_LDI
{
    static bool const val = false;

};

template <class U>
struct is_LDI< LDI<U> >
{
    static bool const val = true;
};

template<typename T>
struct is_LSI
{
    static bool const val = false;

};

template <class U>
struct is_LSI< LSI<U> >
{
    static bool const val = true;
};

///==========================================================================================================

///5) Class count_save

///==========================================================================================================

template <class T>
class count_save
{
private:
    vector<T> lista_dubla_finala;
    vector<T> lista_simpla_finala;

public:
    int get_vector_size()
    {
        if(is_LDI<T>::val)
            return lista_dubla_finala.size();
        if(is_LSI<T>::val)
            return lista_simpla_finala.size();
        else
        {
            perror("Fail");
        }
    }
    void set_vector(T type);
    void afisare(T type);
};

///==========================================================================================================

///6) Class count_list

///==========================================================================================================

class count_list
{
protected:
    static int count_lista_dubla;
    static int count_lista_simpla;
    static int count_all;
public:
    static void set_count(string which, int e);
    static vector <int> get_count();
};

int count_list::count_lista_dubla;
int count_list::count_lista_simpla;
int count_list::count_all;

vector<int> count_list::get_count()
{
    vector <int> count_list_vec;
    count_list_vec.push_back(count_lista_dubla);
    count_list_vec.push_back(count_lista_simpla);
    count_list_vec.push_back(count_all);
    return count_list_vec;
}

void count_list::set_count(string which, int e)
{

    if(which == "simpla")
        count_lista_simpla =  e;

    if(which == "dubla")
        count_lista_dubla = e;

    count_all = count_lista_simpla + count_lista_dubla;
}

template <class T>
void count_save<T>::set_vector(T type)
{
    if(is_LDI<T>::val)
    {
        lista_dubla_finala.push_back(type);
    }
    else if(is_LSI<T>::val)
    {
        lista_simpla_finala.push_back(type);
    }
    else
    {
        perror("Fail");
    }
    count_list::set_count("simpla", get_vector_size());
}

///==========================================================================================================

///Menu functions...

///1) LSI_menu

///==========================================================================================================

template <class T>
void LSI_meniu()
{
    int n;
    string n_string, string_k;
    do
    {
        cout<<"Cate liste vrei sa citesti?"<<endl;
        cin>>n_string;
        if(!isNumber(n_string.c_str(), '+'))
            cout<<"Warning 007: You inserted a negative number or a string"<<endl;

    }
    while(!isNumber(n_string.c_str(), '+'));
    n = atoi<int>(n_string.c_str());
    cout<<"Vei citi urmatoarele "<<n<<" liste"<<endl;
    vector < LSI<T> > lista;
    for(int i=0; i<n; i++)
    {
        cout<<"Lista "<<i<<":"<<endl;
        int k;
        do
        {
            cout<<"Cat spatiu doriti sa alocati?"<<endl;
            cin>>string_k;
            if(!isNumber(string_k.c_str(), '+'))
                cout<<"Warning 007: You inserted a negative number or a string"<<endl;
        }
        while(!isNumber(string_k.c_str(), '+'));
        k = atoi<int>(string_k.c_str());
        LSI<T> lista_i;
        LDI<T> lista_i_temp;
        if(k==1)
        {
            lista_i.reset_space(k);
            Nod_dublu<T>* nod_d = new Nod_dublu<T>();
            cin>>nod_d;
            lista_i_temp.push_back(nod_d, 0);
        }
        else
        {
            lista_i_temp.reset_space(k);
            for(int j=0; j<k; j++)
            {
                cout<<"Nodul dublu: "<<j<<endl;
                Nod_dublu<T>* nod_d = new Nod_dublu<T>();
                cin>>nod_d;
                lista_i_temp.push_back(nod_d, j);
            }
            string s;
            cout<<"Doriti sa le sortati? (Yes / No)"<<endl;
            cin>>s;
            if(s == "No")
                cout<<"Am terminat"<<endl;
            if(s == "Yes")
            {
                cout<<"Doriti sortarea prin inserctie directa?"<<endl;
                cout<<"1 - pentru da, 0 - pentru nu"<<endl;
                string insertion;
                cin>>insertion;
                if(insertion == "1")
                    lista_i_temp.sort_LDI(lista_i_temp, false, true);
                else
                {
                    cout<<"In ce ordine doriti sa sortati? "<<endl;
                    cout<<"1 - pentru descrescator, 0 - pentru crescator"<<endl;
                    string tru;
                    cin>>tru;
                    if(tru == "1")
                        lista_i_temp.sort_LDI(lista_i_temp, true, false);
                    if(tru == "0")
                        lista_i_temp.sort_LDI(lista_i_temp, false, false);
                }
                cout<<"Sortat cu succes"<<endl;
                cout<<"Am terminat"<<endl;

            }
        }
        lista_i=lista_i.downgrade(lista_i_temp);
        lista.push_back(lista_i);
    }
    cout<<"Ai citit asa listele: "<<endl;
    int lista_size = lista.size();
    for(int i=0; i<lista_size; i++)
    {
        cout<<lista[i];
    }
    cout<<"Apasati enter sau asteptati 60 secunde"<<endl;
    system("timeout 60 > nul");
}

///==========================================================================================================

///2) LDI_menu

///==========================================================================================================

template <class T>
void LDI_meniu()
{
    int n;
    cout<<"Cate liste vrei sa citesti?"<<endl;
    cin>>n;
    cout<<"Vei citi urmatoarele "<<n<<" liste"<<endl;
    vector < LDI<T> > lista;
    for(int i=0; i<n; i++)
    {
        cout<<"Lista "<<i<<":"<<endl;
        string k_ver;
        int k;
        do
        {
            cout<<"Cat spatiu doriti sa alocati?"<<endl;
            cin>>k_ver;
            if(!isNumber(k_ver.c_str()))
                cout<<"Warning 001: You inserted a string"<<endl;
        }
        while(!isNumber(k_ver.c_str()));
        k = atoi(k_ver.c_str());
        if(k==1)
        {
            LDI<T> lista_i(1);
            Nod_dublu<T>* nod_d = new Nod_dublu<T>();
            cin>>nod_d;
            string type_read;
            do
            {

                cout<<"Doriti sa bagati numarul in fata sau in spate?"<<endl;
                cout<<"0 - fata, 1 - spate"<<endl;
                cin>>type_read;
                if(!isNumber(type_read.c_str()))
                    cout<<"Warning 001: You inserted a string"<<endl;
                else
                {

                    if(atoi<int>(type_read.c_str()) > 1 || atoi<int>(type_read.c_str()) < 0)
                        cout<<"Warining 008: You inserted a bad number"<<endl;
                }
            }
            while(!isNumber(type_read.c_str()) || atoi<int>(type_read.c_str()) > 1 || atoi<int>(type_read.c_str()) < 0);
            if(type_read == "0")
                lista_i.append(nod_d,0);
            else
            {
                lista_i.push_back(nod_d, 0);
            }
            lista.push_back(lista_i);
        }
        else
        {
            LDI<T> lista_i(k);
            for(int j=0; j<k; j++)
            {
                cout<<"Nodul dublu: "<<j<<endl;
                Nod_dublu<T>* nod_d = new Nod_dublu<T>();
                cin>>nod_d;
                string type_read;
                do
                {

                    cout<<"Doriti sa bagati numarul in fata sau in spate?"<<endl;
                    cout<<"0 - fata, 1 - spate"<<endl;
                    cin>>type_read;
                    if(!isNumber(type_read.c_str()))
                        cout<<"Warning 001: You inserted a string"<<endl;
                    else
                    {

                        if(atoi<int>(type_read.c_str()) > 1 || atoi<int>(type_read.c_str()) < 0)
                            cout<<"Warining 008: You inserted a bad number"<<endl;
                    }
                }
                while(!isNumber(type_read.c_str()) || atoi<int>(type_read.c_str()) > 1 || atoi<int>(type_read.c_str()) < 0);
                if(type_read == "0")
                    lista_i.append(nod_d,0);
                else
                {
                    lista_i.push_back(nod_d, 0);
                }
            }
            cout<<"Ai citit:"<<endl;
            cout<<lista_i<<endl;
            string s;
            cout<<"Doriti sa le sortati? (Yes / No)"<<endl;
            cin>>s;
            if(s == "No")
                cout<<"Am terminat"<<endl;
            if(s == "Yes")
            {
                cout<<"Doriti sortarea prin inserctie directa?"<<endl;
                cout<<"1 - pentru da, 0 - pentru nu"<<endl;
                string insertion;
                cin>>insertion;
                if(insertion == "1")
                    lista_i.sort_LDI(lista_i, false, true);
                else
                {
                    cout<<"In ce ordine doriti sa sortati? "<<endl;
                    cout<<"1 - pentru descrescator, 0 - pentru crescator"<<endl;
                    string tru;
                    cin>>tru;
                    if(tru == "1")
                        lista_i.sort_LDI(lista_i, true, false);
                    if(tru == "0")
                        lista_i.sort_LDI(lista_i, false, false);
                }
                cout<<"Sortat cu succes"<<endl;
                cout<<"Am terminat"<<endl;

            }
            lista.push_back(lista_i);
        }

    }
    ///To clear warning....
    cout<<"Listele dublu inlantuite sunt: "<<endl;
    int lista_size = lista.size();
    for(int i=0; i<lista_size; i++)
        cout<<lista[i];
    cout<<"Apasati enter sau asteptati 60 secunde"<<endl;
    system("timeout 60 > nul");
}

///==========================================================================================================

///3) LDI_selected

///==========================================================================================================

template <class T>
void LDI_selected(string selected)
{
    cout<<"Ai selectat lista dubla cu "<<selected<<endl;
    cout<<"Acum vei citi nodurile in "<<selected<<endl;
    string k_ver;
    int k;
    do
    {
        cout<<"Cat spatiu doriti sa alocati?"<<endl;
        cin>>k_ver;
        if(!isNumber(k_ver.c_str()))
            cout<<"Warning 001: You inserted a string"<<endl;
    }
    while(!isNumber(k_ver.c_str()));
    k = atoi(k_ver.c_str());
    LDI<T> lista(k);
    for(int i=0; i<k; i++)
    {
        cout<<"Nodul "<<i<<" :"<<endl;
        Nod_dublu<T>* temp = new Nod_dublu<T>();
        cin>>temp;
        lista.push_back(temp, i);
    }
    string s;
    cout<<"Doriti sa le sortati? (Yes / No)"<<endl;
    cin>>s;
    if(s == "No")
        cout<<"Am terminat"<<endl;
    if(s == "Yes")
    {
        cout<<"Doriti sortarea prin inserctie directa?"<<endl;
        cout<<"1 - pentru da, 0 - pentru nu"<<endl;
        string insertion;
        cin>>insertion;
        if(insertion == "1")
            lista.sort_LDI(lista, false, true);
        else
        {
            cout<<"In ce ordine doriti sa sortati? "<<endl;
            cout<<"1 - pentru descrescator, 0 - pentru crescator"<<endl;
            string tru;
            cin>>tru;
            if(tru == "1")
                lista.sort_LDI(lista, true, false);
            if(tru == "0")
                lista.sort_LDI(lista, false, false);
        }
        cout<<"Sortat cu succes"<<endl;
        cout<<"Am terminat"<<endl;

    }
    count_save < LDI <T> > obj;
    obj.set_vector(lista);
    return;
}

///==========================================================================================================

///4) LSI_selected

///==========================================================================================================

template <class T>
void LSI_selected(string selected)
{
    cout<<"Ai selectat lista dubla cu "<<selected<<endl;
    cout<<"Acum vei citi nodurile in "<<selected<<endl;
    string k_ver;
    int k;
    do
    {
        cout<<"Cat spatiu doriti sa alocati?"<<endl;
        cin>>k_ver;
        if(!isNumber(k_ver.c_str()))
            cout<<"Warning 001: You inserted a string"<<endl;
    }
    while(!isNumber(k_ver.c_str()));
    k = atoi<int>(k_ver.c_str());
    LDI<T> lista(k);
    LSI<T> lista_convert(k);
    for(int i=0; i<k; i++)
    {
        cout<<"Nodul "<<i<<" :"<<endl;
        Nod_dublu<T>* temp = new Nod_dublu<T>();
        cin>>temp;
        lista.push_back(temp, i);
    }
    string s;
    cout<<"Doriti sa le sortati? (Yes / No)"<<endl;
    cin>>s;
    if(s == "No")
        cout<<"Am terminat"<<endl;
    if(s == "Yes")
    {
        cout<<"Doriti sortarea prin inserctie directa?"<<endl;
        cout<<"1 - pentru da, 0 - pentru nu"<<endl;
        string insertion;
        cin>>insertion;
        if(insertion == "1")
            lista.sort_LDI(lista, false, true);
        else
        {
            cout<<"In ce ordine doriti sa sortati? "<<endl;
            cout<<"1 - pentru descrescator, 0 - pentru crescator"<<endl;
            string tru;
            cin>>tru;
            if(tru == "1")
                lista.sort_LDI(lista, true, false);
            if(tru == "0")
                lista.sort_LDI(lista, false, false);
        }
        cout<<"Sortat cu succes"<<endl;
        cout<<"Am terminat"<<endl;
    }
    system("pause");
    lista_convert.downgrade(lista);
    cout<<lista_convert<<endl;
    system("pause");
    count_save< LSI<T> >obj1;
    obj1.set_vector(lista_convert);
    return;
}

///==========================================================================================================


///5) combinations LDI


///==========================================================================================================

void combinatie_tipuri_lista_dubla()
{
    cout<<"Ai selectat combinatie lista dubla"<<endl;
    vector < LDI <string > > trick_complet;
    string count_t;
    do
    {
        cout<<"Cate liste de combinatii doresti sa citesti?"<<endl;
        cin>>count_t;
        if(!isNumber(count_t.c_str(), 'a'))
            cout<<"Warning 007: You introduced a bad number or a string. Bypass!"<<endl;
    }
    while(!isNumber(count_t.c_str(), 'a'));
    int n = atoi(count_t.c_str());
    forp(i, n)
    {
        LDI <string> trick; ///The trick is that a string supports every type of values (it's so powerful)
        string j_string;
        do
        {
            cout<<"Cat spatiu doriti sa alocati per lista?"<<endl;
            cin>>j_string;
            if(!isNumber(j_string.c_str(), 'a'))
                cout<<"Warning 007: You introduced a bad number or a string. Bypass!"<<endl;
        }
        while(!isNumber(j_string.c_str(), 'a'));
        int k = atoi<int>(j_string.c_str());
        forp(j, k)
        {
            string in;
            cout<<"Introduceti un tip de variabila din lista de mai jos"<<endl;
            cout<<"String, Float, Int, Unsigned si Char sau Exit pentru a iesi"<<endl;
            cin>>in;
            string node;
            if(in == "String") ///Basically is the same, no problems ....
            {
                cin>>node;
                cout<<"Nod creat"<<endl;
            }
            if(in == "Float") ///We have some problems here
            {
                cin>>node; ///Didn't create a number verify
                cout<<"Nod creat"<<endl;
            }
            if(in == "Int") ///We have some problems here
            {
                do
                {
                    cin>>node;
                    if(!isNumber(node.c_str(), '-'))
                        cout<<"Warning 006: You inserted a string"<<endl;
                }
                while(!isNumber(node.c_str(), '-'));
                cout<<"Nod creat"<<endl;
            }
            if(in == "Unsigned")
            {
                do
                {
                    cin>>node;
                    if(!isNumber(node.c_str(), '+'))
                        cout<<"Warning 006: You inserted a string or a negative number"<<endl;
                }
                while(!isNumber(node.c_str(), '+'));
                cout<<"Nod creat"<<endl;
            }
            if(in == "Char") ///We don't have problems because a string is the same like vector <char> so it's fine
            {
                do
                {
                    cin>>node;
                    if(node.length() > 2 || node.length() < 0)
                    {
                        cout<<"You inserted a string characted not a char"<<endl;

                    }
                }
                while(node.length() > 2 || node.length() < 0);
                cout<<"Nod creat"<<endl;
            }
            Nod_dublu<string>* node_string  = new Nod_dublu<string>(node);
            trick.push_back(node_string, j);
            if(in == "Exit")
                break;
        }
        cout<<"Doriti sa sortati?"<<endl;
        cout<<"Yes pentru da, orice altceva pentru nu"<<endl;
        string gamma;
        cin>>gamma;
        if(gamma == "Yes")
        {
            string test;
            cout<<"Doriti sa fie sortarea prin inserctie sau simpla (0 - nu / 1 - da)?"<<endl;
            do
            {
                cin>>test;
                if(!isNumber(test.c_str()) || atoi(test.c_str()) > 1 || atoi(test.c_str()) < 0)
                    cout<<"Warning 007: You inserted a string or a bad number! Bypass..."<<endl;
            }
            while (!isNumber(test.c_str()) || atoi(test.c_str()) > 1 || atoi(test.c_str()) < 0);
            if(test == "0")
            {

                cout<<"Sortarea se face prin qsort"<<endl;
                cout<<"Doriti sa fie reverse sau nu? (Yes - pentru da, orice altceva pt nu)"<<endl;
                string yes;
                cin>>yes;
                if(yes=="Yes")
                {
                    trick.sort_LDI(trick, true, false);
                }
                else
                {
                    trick.sort_LDI(trick, false, false);
                }
            }
            else
            {
                trick.sort_LDI(trick, false, true);
            }
            cout<<"Sortat cu succes"<<endl;
            cout<<"Am terminat"<<endl;
        }
        else
        {
            cout<<"Ai selectat sa nu sortezi"<<endl;
            cout<<"Am terminat"<<endl;
        }
        trick_complet.push_back(trick);
    }
    int space = trick_complet.size(); /// to escape the warning
    for(int i=0; i<space; i++)
    {
        cout<<trick_complet[i];
    }
    cout<<"Ai 30 de secunde la dispoztie sau apasa enter"<<endl;
    system("timeout 30 > null");
}

///==========================================================================================================


///6) combinations LSI


///==========================================================================================================

void combinatie_tipuri_lista_simpla()
{
    cout<<"Ai selectat combinatie lista dubla"<<endl;
    vector < LSI <string > > trick_complet;
    string count_t;
    do
    {
        cout<<"Cate liste de combinatii doresti sa citesti?"<<endl;
        cin>>count_t;
        if(!isNumber(count_t.c_str(), 'a'))
            cout<<"Warning 007: You introduced a bad number or a string. Bypass!"<<endl;
    }
    while(!isNumber(count_t.c_str(), 'a'));
    int n = atoi(count_t.c_str());
    forp(i, n)
    {
        LDI <string> trick; ///The trick is that a string supports every type of values (it's so powerful)
        string j_string;
        do
        {
            cout<<"Cat spatiu doriti sa alocati per lista?"<<endl;
            cin>>j_string;
            if(!isNumber(j_string.c_str(), 'a'))
                cout<<"Warning 007: You introduced a bad number or a string. Bypass!"<<endl;
        }
        while(!isNumber(j_string.c_str(), 'a'));
        int k = atoi<int>(j_string.c_str());
        forp(j, k)
        {
            string in;
            cout<<"Introduceti un tip de variabila din lista de mai jos"<<endl;
            cout<<"String, Float, Int, Unsigned si Char sau Exit pentru a iesi"<<endl;
            cin>>in;
            string node;
            if(in == "String") ///Basically is the same, no problems ....
            {
                cin>>node;
                cout<<"Nod creat"<<endl;
            }
            if(in == "Float") ///We have some problems here
            {
                cin>>node; ///Didn't create a number verify
                cout<<"Nod creat"<<endl;
            }
            if(in == "Int") ///We have some problems here
            {
                do
                {
                    cin>>node;
                    if(!isNumber(node.c_str(), '-'))
                        cout<<"Warning 006: You inserted a string"<<endl;
                }
                while(!isNumber(node.c_str(), '-'));
                cout<<"Nod creat"<<endl;
            }
            if(in == "Unsigned")
            {
                do
                {
                    cin>>node;
                    if(!isNumber(node.c_str(), '+'))
                        cout<<"Warning 006: You inserted a string or a negative number"<<endl;
                }
                while(!isNumber(node.c_str(), '+'));
                cout<<"Nod creat"<<endl;
            }
            if(in == "Char") ///We don't have problems because a string is the same like vector <char> so it's fine
            {
                do
                {
                    cin>>node;
                    if(node.length() > 2 || node.length() < 0)
                    {
                        cout<<"You inserted a string characted not a char"<<endl;

                    }
                }
                while(node.length() > 2 || node.length() < 0);
                cout<<"Nod creat"<<endl;
            }
            Nod_dublu<string>* node_string  = new Nod_dublu<string>(node);
            trick.push_back(node_string, j);
            if(in == "Exit")
                break;
        }
        cout<<"Doriti sa sortati?"<<endl;
        cout<<"Yes pentru da, orice altceva pentru nu"<<endl;
        string gamma;
        cin>>gamma;
        if(gamma == "Yes")
        {
            string test;
            cout<<"Doriti sa fie sortarea prin inserctie sau simpla (0 - nu / 1 - da)?"<<endl;
            do
            {
                cin>>test;
                if(!isNumber(test.c_str()) || atoi(test.c_str()) > 1 || atoi(test.c_str()) < 0)
                    cout<<"Warning 007: You inserted a string or a bad number! Bypass..."<<endl;
            }
            while (!isNumber(test.c_str()) || atoi(test.c_str()) > 1 || atoi(test.c_str()) < 0);
            if(test == "0")
            {

                cout<<"Sortarea se face prin qsort"<<endl;
                cout<<"Doriti sa fie reverse sau nu? (Yes - pentru da, orice altceva pt nu)"<<endl;
                string yes;
                cin>>yes;
                if(yes=="Yes")
                {
                    trick.sort_LDI(trick, true, false);
                }
                else
                {
                    trick.sort_LDI(trick, false, false);
                }
            }
            else
            {
                trick.sort_LDI(trick, false, true);
            }
            cout<<"Sortat cu succes"<<endl;
            cout<<"Am terminat"<<endl;
        }
        else
        {
            cout<<"Ai selectat sa nu sortezi"<<endl;
            cout<<"Am terminat"<<endl;
        }
        LSI<string> var;
        trick_complet.push_back(var.downgrade(trick));
    }
    int space = trick_complet.size(); /// to escape the warning
    for(int i=0; i<space; i++)
    {
        cout<<trick_complet[i];
    }
    cout<<"Ai 30 de secunde la dispoztie sau apasa enter"<<endl;
    system("timeout 30 > null");
}

///==========================================================================================================

///7) LSD_LDI based on 5 and 6

///==========================================================================================================

void LSI_LDI()
{
    string s;
    while(true)
    {
        clearscreen();
        cout<<"Ai select lista dublu inlantuite sau simplu inlantuie. Selecteaza una dintre varinate apoi tipul listei"<<endl;
        cout<<"1) Int"<<endl;
        cout<<"2) Unsigned"<<endl;
        cout<<"3) Char"<<endl;
        cout<<"4) String"<<endl;
        cout<<"5) Float"<<endl;
        cout<<"6) Combinatie (EXPERIMENTAL)"<<endl;
        cout<<"7) Back"<<endl;
        cout<<"8) Detalii liste citite / afisare"<<endl;
        cin>>s;
        if(s == "8")
        {
            clearscreen();
            cout<<"Detalii despre listele citite sunt:"<<endl;
            vector <int> temp = count_list::get_count();
            cout<<"Numarul de liste dublu inlantuite:"<<endl;
            cout<<temp[0]<<endl;
            cout<<"Numarul de liste simplu inlantuite:"<<endl;
            cout<<temp[1]<<endl;
            cout<<"Numarul de liste in total:"<<endl;
            cout<<temp[2]<<endl;
            cout<<"Ai 30 de secunde sa te uiti"<<endl;
            system("timeout 30 > nul");
        }
        else
        {
            clearscreen();
            string tip;
            cout<<"Selecteaza tipul listei (0 - lista_dubla) (1 - lista simpla)"<<endl;
            cin>>tip;
            if(tip == "1")
            {
                if(s == "1")
                    LSI_selected<int>("Int");
                if(s == "2")
                    LSI_selected<unsigned>("Unsigned");
                if(s == "3")
                    LSI_selected<char>("Char");
                if(s == "4")
                    LSI_selected<string>("String");
                if(s == "5")
                    LSI_selected<float>("Float");
                if(s == "6")
                    cout<<"In constructie"<<endl;
                if(s == "7")
                    break;
            }
            if(tip == "0")
            {
                if(s == "1")
                    LDI_selected<int>("Int");
                if(s == "2")
                    LDI_selected<unsigned>("Unsigned");
                if(s == "3")
                    LDI_selected<char>("Char");
                if(s == "4")
                    LDI_selected<string>("String");
                if(s == "5")
                    LDI_selected<float>("Float");
                if(s == "6")
                    cout<<"In constructie"<<endl;
                if(s == "7")
                    break;
            }
        }
    }
}

///==========================================================================================================

/// The main of the program

///==========================================================================================================

int main()
{

    int n;
    while(true)
    {
        printf("Bun venit la meniu! Realizat de Mihalea Andreas, tema 1! '60%' din program realizat ('70%' din tema)\n"); ///To optimise the code
        printf("Selectati:\n");
        printf("1) Liste dublu inlantuite\n");
        printf("2) Liste simplu inlantuite\n");
        printf("3) Combinatii liste simplu / dublu inlantuie\n");
        printf("4) Exit\n");
        scanf("%d", &n);
        if(n == 1)
        {
            clearscreen();
            printf("Ai select lista dublu inlantuite\n");
            printf("1) Int\n");
            printf("2) Unsigned\n");
            printf("3) Char\n");
            printf("4) String\n");
            printf("5) Float\n");
            printf("6) Combinatie (EXPERIMENTAL)\n");
            printf("7) Back");
            int k;
            cin>>k;
            if(k == 1)
                LDI_meniu<int>();
            if(k == 2)
                LDI_meniu<unsigned>();
            if(k == 3)
                LDI_meniu<char>();
            if(k == 4)
                LDI_meniu<string>();
            if(k == 5)
                LDI_meniu<float>();
            if(k == 7)
            {
                clearscreen();
                continue;
            }
            if(k == 6)
            {
                clearscreen();
                combinatie_tipuri_lista_dubla();
            }
        }
        if(n == 2)
        {
            clearscreen();
            printf("Ai select lista simplu inlantuite\n");
            printf("1) Int\n");
            printf("2) Unsigned\n");
            printf("3) Char\n");
            printf("4) String\n");
            printf("5) Float\n");
            printf("6) Combinatie (EXPERIMENTAL)\n");
            printf("7) Back");
            int k;
            cin>>k;
            if(k == 1)
                LSI_meniu<int>();
            if(k == 1)
                LSI_meniu<int>();
            if(k == 2)
                LSI_meniu<unsigned>();
            if(k == 3)
                LSI_meniu<char>();
            if(k == 4)
                LSI_meniu<string>();
            if(k == 5)
                LSI_meniu<float>();
            if(k == 7)
            {
                clearscreen();
                continue;
            }
            if(k == 6)
            {
                clearscreen();
                combinatie_tipuri_lista_simpla();
            }
        }
        if(n == 3)
        {
            clearscreen();
            LSI_LDI();
        }
        if(n == 4)
        {
            clearscreen();
            printf("Ai iesit din program\n");
            return 0;
        }
    }
}
