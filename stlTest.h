#include <iostream>
#include <string.h> // change to <string> for visual studio. don't forget to change it back before you submit
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

template<class  Iterator, class func, class type>
void filter(Iterator begin, Iterator end, const func& f, type& t){
    for (; begin != end; begin++){
        if (f(*begin)){
            t.push_back(*begin);
        }
    }
}

struct Even{
    template<class T>
    bool operator()(T& obj) const {
        if (obj % 2 == 0)
            return true;
        return false;
    }

};
struct PrintMe{
private:
    string s;

public:
    PrintMe(string seperator): s(seperator) {};
    template<class T>
    void operator()(T& obj) const {
        cout << obj << s;
    }
};
//
//
template<class T>
class Sum{
	T sum;
public:
    Sum(): sum(0) {};
    void operator()(const T& obj){
        this->sum+=obj;
    }
    T& get(){
        return this->sum;
    }
};

int mainAPISTL()
{
    vector<int> ints;
    for (int i = 0; i<10; i++)
        ints.push_back(i);

    list<int> evenInts;
    filter(ints.begin(), ints.end(), Even(), evenInts);
    cout << "hi" << endl;
    for_each(evenInts.begin(), evenInts.end(), PrintMe(",")); // 0,2,4,6,8,
    cout << endl;

    Sum<int> sum;
    sum = for_each(evenInts.begin(), evenInts.end(), sum);
    cout << sum.get() << endl; // 20
    return 0;
}
