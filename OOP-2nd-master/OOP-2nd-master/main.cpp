///Includes...

///==========================================================================================================

#include <iostream> /// pentru cin si cout si namespace ul std
#include <stdio.h> /// pentru printf sau pentru system
#include <vector> ///pentru vectori
#include <complex> ///pentru stringstream convert (C++0x)

///==========================================================================================================

///Using standard functions ...

using std::cin;  ///for cin
using std::cout;  ///for cout
using std::vector; ///for vector
using std::string;  ///for string
using std::endl;  ///for endline
using std::istream; ///for istream
using std::ostream; ///for ostream

///==========================================================================================================

///First namespace created ...

namespace verify ///I can use only one from all 5 classes (2 / 10) thanks to verify::class_name
{
    ///the namespace verify class defines

///FALSE MODE RESPONSE
#define load_false static const bool val = false;\
public:\
    static const bool get()\
    {return val;}

///TRUE MODE RESPONSE (IF TEMPLATE T IS TRULLY T type is the same like std::is_same<T>::value)
#define load_true static const bool val = true;\
public:\
    static const bool get()\
    {return val;}


#define nothing is just for comment ....

///NESTED NAMESPACE (e.g verify::type_int::is_int<T>::get())
        namespace type_int
        {
                template<typename T>
                class is_int
                {
                    load_false
                };

                template<>
                class is_int<int>
                {
                    load_true
                };
        };

        namespace type_float   /// NESTED NAMESPACE FOR FLOAT
        {
                template<typename T>
                class is_float
                {
                    load_false
                };

                template<>
                class is_float<float>
                {
                    load_true
                };
        };

            namespace type_unsigned  ///NESTED NAMESPACE FOR UNSIGNED
            {
                template<typename T>
                class is_unsigned_t
                {
                    load_false
                };

                template<>
                class is_unsigned_t<unsigned>
                {
                    load_true
                };
            };
            namespace type_string ///NESTED NAMESPACE FOR STRING AKA VECTOR <CHAR>
            {
                template<typename T>
                class is_string
                {
                    load_false
                };

                template<>
                class is_string<string>
                {
                    load_true
                };
            };
            namespace type_char ///NESTED NAMESPACE FOR CHAR
            {
                    template<typename T>
                    class is_char
                    {
                        load_false
                    };

                    template<>
                    class is_char<char>
                    {
                        load_true
                    };
            }
};

///Define uri

///==========================================================================================================


#define timeout 0
#define new_verify 1
#define forp(i, n) for(int i=0; i<n; i++)
#define clearscreen_t 1

///Macro programming
///==========================================================================================================
///If C++ is C++11 it will enable the chrono.h header otherwise we use system("timeout");
#if timeout == 1
    #if __cplusplus > 201103L
        #include <chrono>
        #include <thread>
        #define sleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
    #else
    #define timeout 0
        #define sleep(x) \
        int gamma = x; \
        string call = static_cast<ostringstream*>( &(ostringstream() << gamma) )->str(); \
        string timeout = "timeout " + call + " >null";
        #warning This file requires compiler and library support for the \
        ISO C++ 2011 standard. This support is currently experimental, and must be \
        enabled with the -std=c++11 or -std=gnu++11 compiler options.
    #endif
#endif

#if timeout == 0
        #define sleep(x) \
        int gamma = x; \
        string call = static_cast<std::ostringstream*>( &(std::ostringstream() << gamma) )->str(); \
        string timeout_temp = "timeout " + call + " >null";\
        system(timeout_temp.c_str());
#endif

#if new_verify == 1
        #define is_int(T)       verify::type_int::is_int<T>::get()
        #define is_float(T)     verify::type_float::is_float<T>::get()
        #define is_unsigned(T)  verify::type_unsigned::is_unsigned_t<T>::get()
        #define is_char(T)      verify::type_char::is_char<T>::get()
        #define is_string(T)    verify::type_string::is_string<T>::get()

///e.g if(verify::is_int(T) == false) ///is not, otherwise it is
#else
        using namespace verify::type_char;
        using namespace verify::type_float;
        using namespace verify::type_int;
        using namespace verify::type_string;
        using namespace verify::type_unsigned;
#endif // new_verify


#if clearscreen_t == 0
#include <windows.h> ///for clearscreen
#define _X dwSize.X
#define _Y dwSize.Y
#define GCSBI GetConsoleScreenBufferInfo
#define FCOC  FillConsoleOutputCharacter
#define FCOA  FillConsoleOutputAttribute
#define SCCP  SetConsoleCursorPosition
#define GSH_S_O_H   GetStdHandle (STD_OUTPUT_HANDLE)
#define clear_all;      DWORD n; \
    COORD coord = {0}; \
    CONSOLE_SCREEN_BUFFER_INFO csbi; \
    GCSBI(GSH_S_O_H, &csbi ); \
    FCOC (GSH_S_O_H, TEXT ( ' ' ), csbi._X * csbi._Y, coord, &n ); \
    GCSBI(GSH_S_O_H, &csbi ); \
    FCOA (GSH_S_O_H, csbi.wAttributes, csbi._X * csbi._Y, coord, &n ); \
    SCCP (GSH_S_O_H, coord );
#else
#include <stdlib.h>
#define clear_all system("cls")
#endif

///==========================================================================================================

///Functions ...

void enter()
{
    printf("Te rog sa apesi enter sau sa astepti 30 de secunde \n");
   // system("timeout 30 > null");
    sleep(30);
}


void clearscreen(){clear_all;}



///for unsigned
string split (string& s, string which)
{
    size_t pos_start = 0, pos_end, len = which.length();
    string token, combine;
    while ((pos_end = s.find (which, pos_start)) != string::npos)
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + len;
        combine += token;
    }

    combine += s.substr(pos_start);
    s = combine;
    return combine;
}

int strlen(const char* s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        i++;
    }
    return i;
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

void nicely_intro()
{
    cout<<"User@>";
}

void error(int e)
{
    switch(e)
    {
    case 1:
        printf("Error 001: You inserted a string in a number variable!");
        break;

    case 2:
        printf("Error 002: You inserted a negative number!");
        break;

    case 3:
        printf("Error 003: You want to compare something NULL");
        break;

    case 4:
        printf("Error 004: You inserted a bad number");
        break;

    default:
        break;
    }
    exit(e);
}


void warning(int e)
{
    switch(e)
    {
    case 1:
        printf("Warning 001: You introduced a string type, it will be converted to 0. Bypass!\n");
        break;

    case 2:
        printf("Warning 002: You inserted a negative number, it will be converted to positive number!\n");
        printf("e.g -3 => 3\n");
        break;

    case 3:
        printf("Warning 003: You inserted a bad number!\n");
        break;

    default:
        break;
    }
}


template <typename T>
T getline_type(istream &in)
{
    string read;
    in>>read;
    T temp;
    if (is_int(T) || is_unsigned(T) || is_float(T))
        if(!isNumber(read.c_str(), '-'))
            warning(1);
    if(is_unsigned(T))
    {
        char minus_unsigned = read[0];
        if (minus_unsigned == '-')
        {
            warning(2);
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
    ~Nod_dublu<T>()
    {
        delete ante;
    }
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
            error(3);
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
            error(3);
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
                error(1);
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
    Nod_dublu<T>** elemente;
    int elem;
    int i; ///evidence for push_back and push_front
public:
    LDI<T>(int cate_elemente = 0)
    {
        elem = cate_elemente;
        i = 0;
        elemente = new Nod_dublu<T>*[cate_elemente];
    }
    ~LDI<T>()
    {

    }
    void reset_space(int cate_elemente)
    {
        elemente = new Nod_dublu<T>*[cate_elemente];
        elem = cate_elemente;
        i = 0;
    }
    int space()
    {
        return this->elem;
    }
    Nod_dublu<T>** elemente_return()
    {
        return elemente;
    }
    void push_front(Nod_dublu<T>* head); ///push;
    void push_back(Nod_dublu<T>* back);
    void sort_LDI();
    virtual void citire(istream& in, Nod_dublu<T>* inserter);
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
            this->elemente[i] = ldi.elemente[i];
        return *this;
    }
    int size()
    {
        int i=0;
        while(elemente[i]!=NULL)
            i++;
        return i;
    }
};


template <class T>
void LDI<T>::citire(istream &in, Nod_dublu<T>* inserter)
{

    cout<<"Doriti sa bagati numarul in fata sau in spate?"<<endl;
    cout<<"1 - fata, 2 - spate"<<endl;
    int type_read;
    type_read = getline_type<int>(cin);
    if(type_read == 1)
        push_front(inserter);
    else if(type_read == 2)
        push_back(inserter);
    else
        error(2);
}

template <class T>
istream& operator>>(istream& in, LDI<T>& ldi)
{
    ldi.reset_space(ldi.elem);
    for(int i=0; i<ldi.elem; i++)
    {
        cout<<"Nodul "<<i<<" :"<<endl;
        Nod_dublu<T>* temp = new Nod_dublu<T>();
        cin>>temp;
        ldi.citire(cin, temp);
    }
    return in;
}


template <class T>
void LDI<T>::sort_LDI()
{
    LDI<T> sort_t(elem);
    for(int i=0; i<elem; i++)
    {
        T key;
        int j;
        key = elemente[i]->getdata();
        j = i - 1;
        while(j>=0 && (elemente[j])->getdata() > key)
        {
            elemente[j+1]=elemente[j];
            j--;
        }
        elemente[j + 1] = new Nod_dublu<T>(key);
    }
}

template <class T>
void LDI<T>::push_back(Nod_dublu<T>* back)
{
    if(back == NULL)
        error(3);
    Nod_dublu<T>* before = new Nod_dublu<T>();
    before->setter(back->getdata());
    before->setnext(back->getnext());
    if (before->getnext() != NULL)
        before->getante()->setnext(before);
    else
        elemente[i++] = before;
}

template <class T>
void LDI<T>::push_front(Nod_dublu<T>* head)
{
    LDI<T> temp(elem);
    temp.push_back(head);
    for(int j=0; j<i; j++)
        temp.push_back(elemente[j]);
    i++;
    elemente = temp.elemente;
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

template <class T>
class LSI:public LDI<T>
{
    static int all;
public:
    LSI<T>(int cate_elemente = 0):LDI<T>(cate_elemente) {};
    void citire(istream& in, Nod_dublu<T>* temp)
    {
        this->push_back(temp);
    }
    template <class U>
    friend istream& operator>>(istream& in, LSI<U>& lsi);
};

template <class T>
istream& operator>>(istream& in, LSI<T>& lsi)
{
    for(int i=0; i<lsi.space(); i++)
    {
        cout<<"Nodul "<<i<<": "<<endl;
        Nod_dublu<T>* temp = new Nod_dublu<T>();
        cin>>temp;
        lsi.citire(cin, temp);
    }
    return in;
}


template <class T>
void sort_list(LDI<T>& lista)
{
    lista.sort_LDI();
    cout<<"Sortat cu succes"<<endl;
    cout<<"Am terminat"<<endl;
}



class count_list
{
    static int list_linked; ///to count the linked list
    static int list_double; /// to count the double linked list
    static int list_simple; ///to count the simple linked list
public:
    static void set_evidence(int e, string h)
    {
        if(h == "d")
            list_double = e;
        if(h == "s")
            list_simple = e;
        list_linked = (list_simple + list_double);
    }
    static vector<int> get()
    {
        vector<int> get_ve;
        get_ve.push_back(list_double);
        get_ve.push_back(list_simple);
        get_ve.push_back(list_linked);
        return get_ve;
    }
};

int count_list::list_linked = 0; ///to count the linked list
int count_list::list_double = 0; /// to count the double linked list
int count_list::list_simple = 0; ///to count the simple linked lis

template <class T>
class count_vector
{
    static vector < LDI<T> > double_list;
    static int counter;
    static vector < LDI<T> > single_list;
    static int counter1;

public:
    static void setter(LDI<T> temp, int ok = 1)
    {
        if(ok == 1)
        {
            double_list.push_back(temp);
            counter++;
        }
        if(ok == 2)
        {
            single_list.push_back(temp);
            counter1++;
        }
    }
    static void double_list_print()
    {
        cout<<"Size: "<<counter;
        printf("\n");
        cout<<"Listele citite sunt: "<<endl;
        for(int i = 0; i<counter; i++)
        {
            cout<<"Lista "<<i<<":\n";
            cout<<double_list[i];
        }
    }
    static void single_list_print()
    {
        cout<<"Size: "<<counter1;
        printf("\n");
        cout<<"Listele citite sunt: "<<endl;
        for(int i = 0; i<counter1; i++)
        {
            cout<<"Lista "<<i<<":\n";
            cout<<single_list[i];
        }
    }
    static int counter_1()
    {
        return counter1;
    }
    static int counter_0()
    {
        return counter;
    }
};

template<typename T>
vector < LDI<T> > count_vector<T>::double_list; // only change here
template<typename T>
vector < LDI<T> > count_vector<T>::single_list; // only change here
template <typename T>
int  count_vector<T>::counter1 = 0;
template <typename T>
int  count_vector<T>::counter = 0;

/// in c++11


template <class T>
void LI_meniu(int x)
{
    int n;
    cout<<"Cate liste vrei sa citesti?"<<endl;
    n = getline_type<unsigned>(cin);
    if(n == 0)
        error(1);
    cout<<"Vei citi urmatoarele "<<n<<" liste"<<endl;
    int d = 0; ///for double
    int s = 0; ///for simple
    forp(i, n)
    {
        cout<<"Lista "<<i<<":"<<endl;
        int k;
        cout<<"Introduceti spatiul pentru lista "<<endl;
        k = getline_type<unsigned>(cin);
        if (k == 0)
            error(1);
        LDI<T>* lista_i;
        if (x == 2)
        {
            lista_i = new LSI<T>(k);
            s++;
            count_list::set_evidence(s, "s");
        }
        if (x == 1)
        {
            lista_i = new LDI<T>(k); ///Cast
            d++;
            count_list::set_evidence(d, "d");
        }
        cin>>*lista_i;
        string s;
        cout<<"Doriti sa le sortati? (Yes / No)"<<endl;
        cin>>s;
        if(s == "No")
            cout<<"Am terminat"<<endl;
        if(s == "Yes")
            sort_list<T>(*lista_i);
        count_vector<T>::setter(*lista_i, x);
    }
    enter();
}


void menu_database(int n)
{
    clearscreen();
    if(n == 3)
        cout<<"Ai selectat lista dubla sau simpla"<<endl;
    if(n == 1)
        cout<<"Ai selectat lista dubla inlantuita"<<endl;
    if(n == 2)
        cout<<"Ai selectat lista simpla inlantuita"<<endl;
    printf("1) Int\n");
    printf("2) Unsigned\n");
    printf("3) Char\n");
    printf("4) String\n");
    printf("5) Float\n");
    printf("7) Back\n");
}

template <class T>
void database_type()
{
    if(is_int(T))
    {
        printf("=====================================================");
        printf("\nInt\n");
    }
    else if(is_float(T))
    {
        printf("=====================================================");
        printf("\nFloat\n");

    }
    else if(is_unsigned(T))
    {
        printf("=====================================================");
        printf("\nUnsigned\n");

    }
    else if(is_string(T))
    {
        printf("=====================================================");
        printf("\nString\n");

    }
    else if(is_char(T))
    {
        printf("=====================================================");
        printf("\nChar\n");

    }
}

template <class T>
void afisare(int n)
{
    if(n == 0)
        if(count_vector<T>::counter_0() != 0)
        {
            database_type<T>();
            count_vector<T>::double_list_print();
        }

    if(n == 1)
    {
        if(count_vector<T>::counter_1() != 0)
        {
            database_type<T>();
            count_vector<T>::single_list_print();
        }
    }

}

#define testmode 0
#if testmode == 1
#define startup clearscreen(); \
        printf("Test mode on\nStatus: Complexity = O(n^2), Time of debugging and programming = 24 hours, Headers = 0, Lines = 900");\
        printf("\nNumber of Classes: 16, Functions: 54, Templates: 60, Namespaces: 11");
#else
#define startup clearscreen(); \
        printf("Test mode off");
#endif // testmode


int main()
{
    int n;
    while(true)
    {
        startup
        printf("\nRealizat de Mihalea Andreas, tema 1!\nSelectati:\n1) Liste dublu inlantuite \n2) Liste simplu inlantuite \n3) Cate liste dublu / simple inlantuite au fost citite!\n4) Exit\n"); ///To optimise the code
        nicely_intro();
        n = getline_type<int>(cin);
        if(n == 1 || n == 2)
        {
            menu_database(n);
            int k;
            nicely_intro();
            k = getline_type<int>(cin);
            switch(k)
            {
            case 1:
                LI_meniu<int>(n);
                break;
            case 2:
                LI_meniu<unsigned>(n);
                break;
            case 3:
                LI_meniu<char>(n);
                break;
            case 4:
                LI_meniu<string>(n);
                break;
            case 5:
                LI_meniu<float>(n);
                break;
            default:
                break;
            }
        }
        if(n == 3)
        {
            clearscreen();
            printf("Numarul listelor citite:\n");
            vector<int> ep = count_list::get();
            int ld = ep[0], ls = ep[1];
            printf("Liste inlantuite duble: %d\nListe inlantuite simple: %d\nIn total: %d\n", ls, ld, ls+ld);
            if(ld!=0)
            {
                printf("Listele duble inlantuite citite sunt:\n");
                afisare<int>(0);
                afisare<float>(0);
                afisare<unsigned>(0);
                afisare<char>(0);
                afisare<string>(0);
                printf("=====================================================\n");
            }
            if(ls!=0)
            {
                printf("Listele simpla inlantuite citite sunt:\n");
                afisare<int>(1);
                afisare<float>(1);
                afisare<unsigned>(1);
                afisare<char>(1);
                afisare<string>(1);
                printf("=====================================================\n");
            }
            enter();
        }
        if(n == 4)
        {
            clearscreen();
            printf("Ai iesit din program\n");
            exit(0);
        }

    }
}
