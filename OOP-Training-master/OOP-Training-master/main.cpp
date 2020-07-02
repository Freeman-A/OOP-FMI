#include <iostream>
using namespace std;

template <class T>
class stiva
{

private:
    T* elemente;
    int f_size;
    int i;
    int begin_t;
public:
    stiva(){
    }
    virtual ~stiva(){
      delete elemente;
    }
    stiva(int size)
    {
        elemente = new T[size + 1];
        f_size = size;
        i = 0;
        begin_t = 0;
    }
    void set_ind(int index){
       begin_t = index;
    }
    stiva& operator=(const stiva &obj){
         f_size = obj.f_size;
         i = obj.i;
         elemente = new T[f_size + 1];
         begin_t = obj.begin_t;
         for(int j=0; j<i; j++)
              elemente[j] = obj.elemente[j];

         return *this;
    }
    void push(T temp)
    {
        if(i >= f_size)
            return;
        else
        {
            elemente[i] = temp;
            i++;
        }
    }
    void pop(int which)
    {
        if(which < i)
        {
            return;
        }
        else
        {
            i--;
            for (int j=which; j<i; j++)
                elemente[j] = elemente[j+1];
        }

    }
    int face(){
        return begin_t;
    }
    int begin()
    {
        return begin_t;
    }
    int end()
    {
        return i;
    }
    int size()
    {
        return i;
    }
    T front()
    {
        return elemente[i-1];
    }
    T operator[](int care)
    {
        return elemente[care];
    }
    virtual T get_node(int care)
    {
        return elemente[care];
    }
    virtual void afisare()
    {

    }
};

namespace andreas
{

template <class T>
class iterator
{
    int index;
    stiva<T> temp_t;
public:
    iterator(stiva<T> tempt)
    {
       index = 0;
       temp_t = tempt;
    }
    stiva<T> retrieve(){
       return temp_t;
    }
    T get(){
       return temp_t[index];
    }
    int get_index(){
       return index;
    }
    void operator++(int)
    {
        index++;
    }
    iterator<T> operator=(iterator<T>& temp)
    {
        iterator<T> temp1(temp.get(), temp.size());
        return temp1;
    }
    template <class U>
    friend ostream& operator<<(ostream& out, iterator<U>& temp);
};

template <class T>
ostream& operator<<(ostream& out, iterator<T>& temp)
{
    cout<<temp.temp_t[temp.index];
    temp.temp_t.pop(temp.index);
    return out;
}



};

template <class T>
bool operator != (andreas::iterator<T> &temp1, int temp2)
{
    int e = temp1.get_index();
    return e != temp2;
}


int main()
{
    stiva<int>* temp3 = new stiva<int>(4);
    temp3->push(1);
    temp3->push(2);
    temp3->push(3);
    for(andreas::iterator<int>* i = new andreas::iterator<int>(*temp3); *i != temp3->end(); (*i)++)
    {
        cout<<*i<<endl;
    }
    delete temp3;
    stiva <string>* temp = new stiva<string>(4);
    temp->push("ana");
    temp->push("are");
    temp->push("mere");
    temp->push("gamma");
    temp->push("epsilon");

    for(andreas::iterator<string>* i = new andreas::iterator<string>(*temp); *i != temp->end(); (*i)++)
    {
        cout<<*i<<endl;
    }
    delete temp;
    return 0;
}
