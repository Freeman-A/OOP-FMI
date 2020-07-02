///Problema 8 creat de Andreas Mihalea, multumiri forumului Stack Overflow si forumului cplusplus.com

///includes

#include <iostream> /// pentru cin si cout si namespace ul std
#include <algorithm> /// pentru functia sort
#include <stdio.h> /// pentru printf sau pentru system
#include <stdlib.h> /// pentru system in concordanta cu stdio
#include <cstring> ///pentru strlen, strcmp etc.
#include <windows.h> ///pentru Buffere folosit la clearscreen

///defines

#define MAX 100
#define forp(i, n) for(int i=0; i<n; i++) ///scurteaza codul
#define sort_a(a,n) sort(a, a+n) ///scurteaza codul neintroducand operatorul '+'
#define size_a(a) sizeof(a) / sizeof(a[0]) ///spatiul unui vector


/// folosit pentru clearscreen din <windows.h>
/// http://www.cplusplus.com/forum/articles/10515/
/// aceste definuri sunt date de mine.
///==================================================

#define _X dwSize.X
#define _Y dwSize.Y
#define GCSBI GetConsoleScreenBufferInfo
#define FCOC  FillConsoleOutputCharacter
#define FCOA  FillConsoleOutputAttribute
#define SCCP  SetConsoleCursorPosition
#define GSH_S_O_H   GetStdHandle (STD_OUTPUT_HANDLE)

///===================================================
/// ...

///namespaces

using namespace std;
/// namespace ul std din headerul iostream
/// folosit pentru cin, cout si sort

/// ....

int atoi(const char *s)
{
    ///stable version of atoi(const char *s) ....
    ///complexitatea O(n)
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
        int e = 0, *t = new int[len + 1];
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
    /// ...
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


///classes
class multime
{
private:

    ///variabile private, n pentru spatiul lui a, iar e un vector de spatii n (declarat doar la transformare)
    int n, *a;

public:

    ///functii pe baza metodei publice

    multime(int a1[]=0, int len = 0, int ok = 0);
    void destructor();
    void transformare(int &n);
    void cout_multime(const char *mesaj = NULL, int ele = -1);
    void afisare_arr(int a[], int n, const char *s);

    void getter_array(int retur[]);
    int getter_n()
    {
        return n;
    }
    /// ...

    ///Pot accesa variabilele private

    friend multime operator +(multime const &, multime const &);
    friend multime operator *(multime const &, multime const &);
    friend multime operator -(multime const &, multime const &);
    friend multime operator>>(std::istream & in, multime & read);
    friend multime operator<<(std::ostream & out, multime const &);
    /// ...
};

void multime::transformare(int &n)
{
    sort_a(a, n); ///Se sorteaza vectorul
    if (n!=0 && n!=1)
    {
        int j = 0;
        forp(i, n-1)
        if (a[i] != a[i+1])
            a[j++] = a[i];

        a[j++] = a[n-1];
        n=j;
    }
}

multime operator>>(std::istream & in, multime &read)
{
    read.a = new int[read.n];
    forp(j, read.n)
    {
        char temp[MAX];
        do{
        scanf("%s", temp);
        if(!isNumber(temp))
            {cout<<"Warning: you introduced a character"<<endl;
            cin.clear();}
        }
        while(!isNumber(temp));
        read.a[j] = atoi(temp);
    }
    sort_a(read.a, read.n);
    read.transformare(read.n);
    return read;
}

void multime::cout_multime(const char *mesaj, int ele)
{
    ///Metode de afisare pe ecran

    if(strcmp(mesaj, "out")==0)
        afisare_arr(a, n, "out");
    if(strcmp(mesaj, "+")==0)
    {
        if(ele == -1)
            cout<<"Reuninea este: ";
        else
            cout<<"Reuniunea a "<<ele<<" multimi citite este :";
        afisare_arr(a, n,"endl");
    }
    if(strcmp(mesaj, "-")==0)
    {
        if(ele == -1)
            cout<<"Diferenta este: ";
        else
            cout<<"Diferenta celor "<<ele<<" multimi citite este :";
        afisare_arr(a, n,"endl");
    }
    if(strcmp(mesaj, "*")==0)
    {
        if(ele == -1)
            cout<<"Intersectia este: ";
        else
            cout<<"Intersectia celor "<<ele<<" multimi citite este :";
        afisare_arr(a, n,"endl");
    }
    if(strcmp(mesaj, "m")==0) ///mesaj pentru multime finala
    {
        cout<<"Multimea citita este: ";
        afisare_arr(a, n,"endl");
    }
    /// ...
}



multime operator<<(std::ostream & out, multime & print)
{
    print.cout_multime("out", 0);
    return print;
}

void multime::afisare_arr(int a[], int n, const char *s)
{
    /// E pentru a afisa in aceasta forma {a1, a2, ... , an}

    cout<<"{";
    forp(i, n)
    {
        if(i == n-1)
            cout<<a[i];
        else
            cout<<a[i]<<" ";
    }
    if(strcmp(s, "endl")==0) ///endl stabileste daca sa afiseaza endl dupa multimea ce se va afisa, de mai sus sau nu...
        cout<<"}"<<endl;
    else
        cout<<"}";


    /// ...
}

multime operator -(multime const &c1, multime const &c2)
{
    multime diferenta;
    ///definim spatiul si un vector temporar v (am selectat sa fie maxim 100)
    int k=0, v[MAX];
    forp(i, c1.n)
    {
        int f=0;
        forp(j, c2.n)
        if(c1.a[i]==c2.a[j])
            f=1;
        if(!f)
        {
            v[k] = c1.a[i];
            k++;
        }
    }

    ///aloca dinamic vectorul a din obiectul diferenta
    diferenta.a = new int[k];

    ///sortam si copiem de pe v in a
    sort_a(v, k);
    forp(i, k) diferenta.a[i] = v[i];

    ///redimensionam spatiul lui v la o variabila
    realloc(v, sizeof(int));

    ///anunatam ca spatiul lui a este k asadar n = k
    diferenta.n = k;

    ///eliminam duplicatele
    diferenta.transformare(diferenta.n);
    return diferenta;
}

multime operator *(multime const &c1, multime const &c2)
{
    multime intersectie;
    int k=0;

    ///#1 Se mai putea scrie asa:
    /// for (int i=0; i<c1.n; i++)
    ///    for(int j=0; j<c2.n; j++)
    /// cod
    ///numaram pentru a stabi spatiul intersectie.a
    forp(i, c1.n)
    forp(j, c2.n)
    if(c1.a[i]==c2.a[j])
        k++;
    intersectie.a = new int[k]; ///stabilirea spatiului
    intersectie.n = k;
    k = 0;
    forp(i, c1.n)
    forp(j, c2.n)
    if(c1.a[i] == c2.a[j])
    {
        intersectie.a[k] = c1.a[i];
        k++;
    }

    ///Eliminam duplicatele ...
    sort_a(intersectie.a, intersectie.n);
    intersectie.transformare(intersectie.n);
    return intersectie;
}


///Operatorul suma (g = g1 + g2 <=> g = g1 U g2)
multime operator +(multime const &c1, multime const &c2)
{
    ///Alocam spatiul fara sa folosim polimorfism

    multime sum;
    sum.n = c1.n + c2.n;
    sum.a = new int[sum.n + 1];
    int i=0;
    ///...


    ///Reuniunea
    forp(k, c1.n)
    {
        sum.a[i] = c1.a[k];
        i++;
    }
    forp(j, c2.n)
    {
        sum.a[i] = c2.a[j];
        i++;
    }

    /// ...

    ///Sortam si eliminam duplicatele daca se pune cazul

    sort_a(sum.a, sum.n);
    sum.transformare(sum.n);

    /// ...

    return sum;
}

///Polimorfism, a1 = vectorul temporar (default NULL), len = lungimea (default 0), ok = reprezinta introducerea sau neintroducerea datelor
///in multime.... (default 0)

multime::multime(int a1[], int len, int ok)
{
    a = new int[len];
    n = len;
    if (ok == 1)
    {
        forp(i, n) a[i] = a1[i];
        transformare(n);
    }
}
/// ...

void multime::getter_array(int retur[])
{
    forp(i, n) retur[i] = a[i];
}

///Sterge spatiul alocat pentru pointerul a
void multime::destructor()
{
    delete[] a;
    printf("\n");
}
/// ...




/// ...

///functions
void clearscreen()
{

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

void calculator(multime* g, char* simboluri)
{
    ///Calculator basic in functie de simboluri
    ///Complexitate O(n)
    multime gn(g[0]);

    ///#1 se mai putea scrie forp(i, strlen(simboluri) .... forp = forma scurta definita la define
    ///#2 se mai putea scrie for(int i=0; i<strlen(simboluri); i++) dar apare warning deci mai bine am declarat o variabila int

    int len = strlen(simboluri);
    for(int i=0; i<len; i++)
    {
        switch(simboluri[i]) ///verificam simbolurile folosind switch
        {
        case '+':
            ///daca simboluri[i] = '+'
        {
            gn = gn + g[i+1];
            break;
        }
        case '*':
            ///daca simboluri[i] = '*'
        {
            gn = gn * g[i+1];
            break;
        }
        case '-':
            ///daca simboluri[i] = '-'
        {
            gn = gn - g[i+1];
            break;
        }
        default:
            ///nu se intampla nimic
            break;
        }
    }
    int len_arr = gn.getter_n();
    int *alpha = new int[len_arr];
    gn.getter_array(alpha);
    /// ...
    cout<<"Multimea rezultata este:"<<endl;
    cout<<"{";
    for(int i=0; i<len_arr; i++)
    {
        if(alpha[i]!=0)
        {
            if(i == len_arr - 1)
                cout<<alpha[i];
            else
                cout<<alpha[i]<<" ";
        }
    }

    cout<<"}"<<endl;
    delete[] alpha;
    /// stergem multimea finala
    gn.destructor();
    /// ...
}

void special_gamma(char *e)
{
    char copy_e[strlen(e)];
    char copy_temp[strlen(e)];
    int len = strlen(e), j=0;
    forp(i, len)
    if(e[i] <= '9' && e[i] >= '0')
    {
        copy_temp[j] = e[i];
        j++;
    }
    if(j!=0)
        strcpy(e, copy_temp);
    else
        strcpy(e, copy_e);
}

void meniu()
{
    ///Complexitate O(x * n * len)
    multime *g; ///Pointer de obiecte
    int n, ok=0; ///Variabile folositoare necesare introducerii de multimii
    cout<<"Problem 8 made by Mihalea Andreas for OOP. Thanks to Stack Overflow and Cplusplus.com community!"<<endl;
    for(;;) /// while(true)
    {
        if (ok == 0) ///Reprezinta prima parte a meniului
        {
            char read[2];
            int read1;
            do
            {
                cout<<"1. Citeste minim 2 multimi (poate sa fie in orice ordine etc)"<<endl;
                cout<<"2. Calculator de multimi (EXPERIMENTAL)"<<endl;
                cout<<"3. Exit"<<endl;
                cin>>read;
                if (!isNumber(read, 'a'))
                {
                    clearscreen();
                    cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                }
            }
            while(!isNumber(read,'a'));
            read1 = atoi(read);
            if(read1 == 3)
            {
                clearscreen();
                break;
            }
            if(read1 == 1) ///Citeste o serie de multimi si duce la meniul #2
            {
                int tempfull;
                clearscreen();
                char tempn[MAX];
                do
                {
                    cin.clear();
                    cout<<"Cate multimi vrei sa citesti?"<<endl;
                    cin>>tempn;
                    if(!isNumber(tempn,'a'))
                        cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                    else
                    {
                        tempfull = atoi(tempn);
                        if(tempfull < 2)
                            cout<<"Warning: You can't insert only one array. Bypass"<<endl;
                    }
                }
                while(!isNumber(tempn,'a') || tempfull < 2);
                n = atoi(tempn);
                g = new multime[n];
                forp(i, n)
                {
                    int len;
                    char len1[MAX];
                    do
                    {
                        cout<<"Cat de mare e multimea "<<i+1<<":"<<endl;
                        scanf("%s", len1);
                        if(!isNumber(len1,'a'))
                            cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                    }
                    while(!isNumber(len1,'a'));
                    len = atoi(len1);
                    cout<<"Introduceti in ordine elementele multimii"<<endl;
                    multime h(0, len);
                    cin>>h;
                    /*forp(j, len)
                    {
                        char temp[MAX];
                        do
                        {
                            cout<<"Elementul "<<j+1<<":";
                            cin>>temp;
                            if(!isNumber(temp))
                                cout<<endl<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                        }
                        while(!isNumber(temp));
                        a[j] = atoi(temp);
                    }
                    multime h(a, len, 1);*/
                    g[i] = h;
                    cin.clear();
                    cout<<g[i];
                    cout<<endl;
                }
                ok = 1;
                clearscreen();
            }
            if(read1 == 2) ///Calculator de matrici. Spatiul este O(MAX^2 + 2MAX)
            {
                clearscreen();
                cout<<"Cititi in ordine: Multime simbol multime etc.... pana la introducerea literei 'e'"<<endl;
                cout<<"Ex: 1 2 3 4 + 2 4 5 6 - 3 5 6 - 2 1 5 e => OUTPUT: {4} "<<endl;
                multime calculator1[MAX];
                char simboluri[MAX];
                char verify;
                int i=0, j=0, k=0, a[MAX][MAX], ok1=1;
                int ver = 0;
                while(true)
                {
                    char e[20];
                    int load=0;
                    while (true)
                    {
                        char temp;
                        scanf("%c", &temp);
                        if (temp<='9' && temp >='1')
                        {
                            e[load]=temp;
                            load++;
                        }
                        else
                        {
                            if(temp=='+' || temp=='-' || temp=='*')
                            {
                                if(e[load-1]<='9' && e[load-1] >='1')
                                {
                                    e[load]='\0';
                                    break;
                                }
                                else
                                {
                                    e[load] = temp;
                                    load++;
                                }

                            }
                            if(temp == 'e')
                            {
                                e[load] = temp;
                                if(e[load-1]<='9' && e[load-1] >='1')
                                    e[load] = '\0';
                                else
                                {
                                    load++;
                                    e[load] = '\0';
                                }
                            }
                            e[load]='\0';
                            break;
                        }
                    }
                    if(strlen(e)==0)
                        continue;
                    else
                    {
                        ///terminare loop la introducerea lui end
                        if(e[0] == 'e')
                        {
                            ver = 1;
                            multime h(a[j], size_a(a[j]), 1);
                            calculator1[j] = h;
                            break;
                        }

                        ///.....

                        ///Introduce numerele intr un vector si apoi creaza o multime
                        int loading;
                        if (isNumber(e))
                        {
                            ok1 = 0;
                            loading = atoi(e);
                            a[j][i] = loading;
                            i++;
                        }
                        ///....
                        else
                        {
                            ///Se introduce in multime daca caracterele sunt + - si * altfel se vor afisa warning uri
                            if(strlen(e)==1 && (strcmp(e, "+")==0 || strcmp(e, "-")==0 || strcmp(e, "*")==0))
                            {
                                if(ok1 == 0 || verify == '{' || verify == '}')
                                {
                                    if(strcmp(e, "+")==0 || strcmp(e, "-")==0 || strcmp(e, "*")==0)
                                    {
                                        simboluri[k] = e[0];
                                        k++;
                                        multime h(a[j], size_a(a[j]), 1);
                                        calculator1[j] = h;
                                        j++;
                                        ok1=1;
                                    }
                                }
                                else
                                {
                                    if(e[0] == '{' || e[0] == '}'  || e[0] == ',')
                                    {
                                        ok1 = 0;
                                        verify = e[0];
                                        continue;
                                    }
                                    else
                                        cout<<"Warning: You had inserted, more than only one operation, bypass!"<<endl;
                                }
                                /// ...
                            }
                            else
                            {
                                ///eroare ...
                                if(e[0] == '{' || e[0] == '}'  || e[0] == ',')
                                    continue;
                                else
                                    cout<<"Warning: You inserted a bad character, bypass!"<<endl;
                            }
                            /// ...
                        }
                    }

                }
                if(ver == 1)
                    ///apelam functia calculator
                    calculator(calculator1, simboluri);
                /// ...

                ///realocam spatiile
                realloc(calculator1, sizeof(int));
                realloc(simboluri, sizeof(char));
                realloc(a, sizeof(char)*sizeof(char));
                /// ...
            }
            realloc(read, sizeof(char));
        }

        /// Meniul #2
        else
        {
            char read[2];
            do
            {
                ///Afiseaza mereu multimiile citite la fiecare buton introdus
                cout<<"Ai citit urmatoarele multimi"<<endl;
                cout<<"{";
                forp(i, n)
                {
                    g[i].cout_multime("out");
                    if(i != n - 1)
                        cout<<", ";
                }
                cout<<"}";
                cout<<endl<<"1. Reuninea a maxim "<<n <<" multimi"<<endl;
                cout<<"2. Intersectia a maxim "<< n<<" multumi"<<endl;
                cout<<"3. Diferenta a maxim "<<n<<" multimi"<<endl;
                cout<<"4. Back"<<endl;
                cin>>read;
                if (!isNumber(read, 'a'))
                {
                    clearscreen();
                    cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                }
            }
            while(!isNumber(read, 'a'));
            int read1 = atoi(read);
            realloc(read, sizeof(char));
            if(read1 == 4)
            {
                delete[] g;
                clearscreen();
                cout<<"Sters cu succes"<<endl;
                ok = 0;
            }

            ///Reuninea a cel putin n multimi
            if(read1 == 1)
            {
                int numar;
                if(n !=2)
                {
                    char numar1[10];
                    cout<<"Cate multimi vrei sa iei in calcul stiind ca ai maxim "<< n <<" elemente?"<<endl;
                    cin>>numar1;
                    do
                    {
                        if(!isNumber(numar1, 'a'))
                            cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                        else
                        {
                            numar = atoi(numar1);
                            if(numar > n)
                                cout<<"Warning: You had inserted a number higher than normal. Bypass"<<endl;


                        }
                    }
                    while(!isNumber(numar1, 'a') || (numar > n));
                    realloc(numar1, sizeof(char));
                }
                else
                    numar = n;
                clearscreen();
                multime gn(g[0]);
                forp(i, numar) gn = gn + g[i];
                gn.cout_multime("+", numar);
                gn.destructor();
            }
            /// ...

            ///Intersectia a cel putin n multimi
            if(read1 == 2)
            {
                int numar;
                if(n !=2)
                {
                    char numar1[10];
                    cout<<"Cate multimi vrei sa iei in calcul stiind ca ai maxim "<< n <<" elemente?"<<endl;
                    cin>>numar1;
                    do
                    {
                        if(!isNumber(numar1, 'a'))
                            cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                        else
                        {
                            numar = atoi(numar1);
                            if(numar > n)
                                cout<<"Warning: You had inserted a number higher than normal. Bypass"<<endl;


                        }
                    }
                    while(!isNumber(numar1, 'a') || (numar > n));
                    realloc(numar1, sizeof(char));
                }
                else
                    numar = n;
                clearscreen();
                multime gn(g[0]);
                forp(i, numar) gn = gn * g[i];
                gn.cout_multime("*", numar);
                gn.destructor();
            }
            /// ...

            ///Diferenta a cel putin n multimi
            if(read1 == 3)
            {
                int numar;
                if(n !=2)
                {
                    char numar1[10];
                    cout<<"Cate multimi vrei sa iei in calcul stiind ca ai maxim "<< n <<" elemente?"<<endl;
                    cin>>numar1;
                    do
                    {
                        if(!isNumber(numar1, 'a'))
                            cout<<"Warning: You had inserted a character or more characters. Bypass"<<endl;
                        else
                        {
                            numar = atoi(numar1);
                            if(numar > n)
                                cout<<"Warning: You had inserted a number higher than normal. Bypass"<<endl;


                        }
                    }
                    while(!isNumber(numar1, 'a') || (numar > n));
                    realloc(numar1, sizeof(char));
                }
                else
                    numar = n;
                clearscreen();
                multime gn(g[0]);
                for(int i=1; i<numar; i++)
                    gn = gn - g[i];
                gn.cout_multime("-", numar);
                gn.destructor();
            }

            /// ...
        }
    }
}
/// ...

int main() ///kernelul programului
{
    meniu(); ///functia de apelare
    return 0;
}
