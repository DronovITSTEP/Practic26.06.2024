#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

void foo(int f) {
    cout << f;
}

class BaseClass {
public:
    virtual void show() = 0;
};
class InnerClass1: public BaseClass {
public:
    void show() {
        cout << "Inner1 class\n";
    }
};
class InnerClass2 : public BaseClass {
public:
    void show() {
        cout << "Inner2 class\n";
    }
};
class InnerClass3{
public:
    void show() {
        cout << "Inner3 class\n";
    }
};


class addNumberFrom {
    int delta; // значение приращения
    int current; // текущее значение

public:
    addNumberFrom(int number, int from = 0) :
        delta{number},
        current {from} {}

    int operator()() {
        return current += delta;
    }
};

// предикат
bool isEvent(int num) {
    return num % 2;
}

/*
Задание №1.
В контейнере типа vector хранится набор целых чисел.
Создайте функторы для решения следующих задач:
■ Поиск минимального значения;
■ Поиск максимального значения;
■ Сортировка данных по убыванию;
■ Сортировка данных по возрастанию;
■ Увеличение значений в контейнере на заданную константу;
■ Уменьшение значений в контейнере на заданную константу;
■ Удаление элементов из контейнера равных искомому значению.
Не забывайте использовать алгоритмы там,где это необходимо.
*/
struct FindMin{
    int operator()(vector<int>& vec) {
        return *min_element(vec.begin(), vec.end());
    }
};
struct FindMax{
    int operator()(vector<int>& vec) {
        return *max_element(vec.begin(), vec.end());
    }
};
bool isSortAsc(int n1, int n2) {
    return n1 < n2;
}
bool isSortDesc(int n1, int n2) {
    return n1 > n2;
}
struct SortDescending{
    void operator()(vector<int>& vec) {
        //sort(vec.begin(), vec.end(), greater<int>());
        sort(vec.begin(), vec.end(), isSortDesc);
    }
};
struct SortAscending{
    void operator()(vector<int>& vec) {
        sort(vec.begin(), vec.end());
    }
};

struct IncrVal{
    int val;
    IncrVal(const int v): val{v}{}

    void operator()(int& num) {
        num += val;
    }
};
struct DecrVal{
    int val;
    DecrVal(const int v) : val{ v } {}
    void operator()(int& num) {
        num -= val;
    }
};

struct RemoveVal {
    int val;
    RemoveVal(const int v) : val{ v } {}
    bool operator()(int& num) {
        return num == val;
    }
};

int main()
{
    /*auto s;
    float f = 6.4;
    auto n = (int)f;
    foo(f);*/

    //const_cast
    /*const int num = 5;
    int* ptr = const_cast<int*>(&num); // const int*
    *ptr = 45;
    cout << num << " " << *ptr;*/

    //dynamic_cast
    /*BaseClass* baseClass[] = {
        new InnerClass1(),
        new InnerClass1(),
        new InnerClass2(),
    };
    BaseClass* baseClass = new InnerClass3(); Error
    InnerClass1* inner1 = dynamic_cast<InnerClass1*>(baseClass);
    for (int i = 0; i < 3; i++) {
        InnerClass1* inner1 = dynamic_cast<InnerClass1*>(baseClass[i]);
        if (inner1)
            inner1->show();
        if (dynamic_cast<InnerClass1*>(baseClass[i]))
            dynamic_cast<InnerClass1*>(baseClass[i])->show();
        if (dynamic_cast<InnerClass2*>(baseClass[i]))
            dynamic_cast<InnerClass2*>(baseClass[i])->show();
    }*/

    //reinterpret_cast
    /*int val = 64;
    char* ptr = reinterpret_cast<char*>(&val);
    cout << *ptr;*/

    //static_cast
    /*double d = 7.54;
    int val = static_cast<int>(d);
    cout << val;*/

    /*InnerClass1* inner = new InnerClass1;
    InnerClass1* inner2 = inner;
    InnerClass1* inner3 = inner2;
    
    delete[] inner2;

    inner3->show();*/

    //unique_ptr<InnerClass1> inner1(new InnerClass1);
    //inner1->show();

    //shared_ptr<InnerClass1> inner2(new InnerClass1);
    //shared_ptr<InnerClass1> inner3(inner2);
    //inner2->show();
    //inner3->show();

    /*shared_ptr<InnerClass2> inner4 = make_shared<InnerClass2>();
    weak_ptr<InnerClass2> weakPtr = inner4;

    if (auto ptr = weakPtr.lock()) {
        ptr->show();
    }
    else {
        cout << "Object delete\n";
    }*/

    // Контейнер
    // Алгоритм
    // Итератор
    // Функтор

    //Аллокатор
    //Предикат

    /*cout << "Table\n----------------------\n";

    for (int i = 1; i <= 10; i++) {
        list<int> l(10);
        generate_n(l.begin(), l.size(), addNumberFrom(i));

        copy(l.begin(), l.end(), ostream_iterator<int>(cout, "\t"));
        cout << endl;
    }*/

    /*list<int> l;
    list<int>::iterator iter;
    for (int i = 1; i <= 10; i++) {
        l.push_back(i);
    }
    copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    iter = remove_if(l.begin(), l.end(), isEvent);
    copy(l.begin(), iter, ostream_iterator<int>(cout, " "));*/


    vector<int> vec = { 7,7,66,3,4,57,4,245,521,4,2,0 };
    FindMax fMax;
    FindMin fMin;
    cout << fMax(vec) << " " << fMin(vec) << endl;

    SortAscending asc;
    SortDescending desc;
    asc(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    desc(vec);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    IncrVal incr(100);
    for_each(vec.begin(), vec.end(), incr);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    DecrVal decr(500);
    for_each(vec.begin(), vec.end(), decr);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    RemoveVal rem(-393);
    vec.erase(remove_if(vec.begin(), vec.end(), rem), vec.end());
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
