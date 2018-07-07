#include <iostream>
#include <string.h>  // change to <string> for visual studio. don't forget to change it back before you submit
using namespace std;

class Person{
    string name;
    int id;
public:
    Person(string inputName, int inputId): name(inputName), id(inputId) {};
    Person(Person& p): name(p.name), id(p.id) {};

    virtual void output(ostream& out){
        out << name << "," << id;
    }

};

class Employee : virtual public Person{
    string jobTitle;
public:
    Employee(Person P, string inputJobTitle): Person(P), jobTitle(inputJobTitle){};

    Employee(Employee& e) : Person(e), jobTitle(e.jobTitle){};

    virtual void output(ostream& out) {
        Person::output(out);
        out << "," << jobTitle;
    }

    string getJobTitle() {
        return jobTitle;
    }
};

class Student : virtual public Person{
    string major;
    int year;
public:
    Student(Person p, string degreeTitle, int inputYear) : Person(p), major(degreeTitle), year(inputYear) {};
    Student(Student& s) : Person(s), major(s.major), year(s.year){};

    virtual void output(ostream& out) {
        Person::output(out);
        out << "," << major;
        out << "," << year;
    }
};

class Intern : virtual public Employee, virtual public Student{
public:
    Intern(Student& s, Employee& e): Person(s), Student(s), Employee(e) {};
    virtual void output(ostream& out) {
        Student::output(out);
        out << "," << getJobTitle();
    }
};

int mainAPIStudent()
{
    Person p("israel israeli", 123456789);

    Student s(p, "computer science", 1);
    s.output(cout);
    cout << endl; //israel israeli,123456789,computer science,1

    Employee e(p, "developer");
    e.output(cout);
    cout << endl;// israel israeli,123456789,developer

    Intern i(s, e);
    i.output(cout);
    cout << endl; //israel israeli,123456789,computer science,1,develope
    return 0;
}
