#include <iostream>

using namespace std;

template<class T>
class RoundList{

    template<class E>
    class Item{
        Item<E>* next;
        E data;
    public:

        Item() :next(NULL){}
        Item(const E& pdata) :next(NULL), data(pdata){}

        void setNext(Item<E>* next){ this->next = next; }
        Item<E>* getNext(){ return next; }
        void setData(const E& data){ this->data = data; }
        E& getData(){ return data; }
    };

    Item<T>* head;
    int size;

public:

    RoundList(const T& item) :head(new Item<T>(item)), size(1){ head->setNext(head); }

    class Iterator{
        Item<T>* p;
    public:
        Iterator(Item<T>* pt = NULL) :p(pt){}
        Iterator operator++(int){
            Iterator temp = *this;
            p = p->getNext();
            return temp;
        }
        Iterator& operator++(){
            p = p->getNext();
            return *this;
        }
        T& operator*(){ return p->getData(); }
        friend class RoundList;

        int operator!=(Iterator& other){
            return this->p != other;
        }
    };

    Iterator begin() { return head; }

    void insert(const T& newItem, Iterator it){
        Item<T>* pNewItem = new Item<T>(newItem);
        pNewItem->setNext(it.p->getNext());
        it.p->setNext(pNewItem);
        size++;
    }

    int getSize(){
        return size;
    }

    Iterator remove(Iterator it){

        RoundList* tmpRoundList = new RoundList(this->head->getData());
        Iterator tmpIterator = this->begin();
        if(tmpIterator.p == it.p){
            char* errorMessage = (char*)"cannot remove head";
            throw errorMessage;
        }

        while(tmpIterator.p->getNext() && tmpIterator.p->getNext() != it.p){
            tmpIterator++;
        }
        tmpIterator.p->setNext(it.p->getNext());
        delete(it.p);
        return tmpIterator;


    }

    template<class func>
    void forEach(const func& f){
        Iterator tmp = this->begin();
        if(tmp.p)
        {
            f(tmp.p->getData());
            tmp++;
            while(tmp.p != this->begin().p)
            {
                f(tmp.p->getData());
                tmp++;
            }
        }
    }

    ~RoundList(){
        cout << "Dtor action:" << endl;
        Iterator headIndex = begin();
        headIndex++;
        while( headIndex.p != begin().p ) {
            Iterator next = headIndex.p->getNext();
            cout << "deleting " << headIndex.p->getData() << endl;
            remove(headIndex);
            headIndex = next;
        }
        cout << "deleting head " << head->getData() << endl;
        delete head;
    }

};


struct Print{
    template<class T>
    void operator()(T& printable) const{
        cout << printable << "->";
    }
};

int mainAPIRoundList()
{
    RoundList<int> list(5);
    for (int i = 1; i<5; i++)
        list.insert(i, list.begin());

    RoundList<int>::Iterator it = list.begin();
    for (int i = 0; i<list.getSize() + 3; i++){
        cout << *it << "->";
        it++;
    }
    cout << endl; // 5->4->3->2->1->5->4->3->

    cout << "item to be removed: " << *it << endl; // 2

    RoundList<int>::Iterator prev = list.remove(it);

    // note: in windows / visual studio *it should be a garbage value since it has already been released from memory
    cout << "previous to " << *it << " is " << *prev << endl; // (*it = 2) *prev = 3
    cout << "result:" << endl;

    list.forEach(Print()); // 5->4->3->1->
    cout << endl;

    return 0;
    /*
    Dtor action:
    deleting 4
    deleting 3
    deleting 1
    deleting head 5
    */
};
