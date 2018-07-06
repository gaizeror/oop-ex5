#include "RoundList.h"
#include "students.h"
#include "stlTest.h"
#include <sstream>

/////////////////////////////////////////////////////// test 1
void test1a(){
	Even e;
	int x=2;
	if (!e(x))
		cout << "failed to implement Even (-5)"<<endl;
}

void test1b(){
	Sum<long> s;
	for (int i = 0; i < 10; i++)
		s(10);
	if (s.get() != 100)
		cout << "failed to implement sum (-10)" << endl;
}

void test1c(){ // test 10 points
}

void test1d(){ // test 10 points
}

/////////////////////////////////////////////////////// test 2
void test2a(){
	RoundList<double> ds(1.0);
	bool exp = false;
	try{ ds.remove(ds.begin()); }
	catch (const char* c){ exp = true; }
	if (!exp)
		cout << "did not throw char* for removing head (-5)" << endl;
}

void test2b(){ // test 10 points...
}

void test2c(){ //test 5 points...
}

int sum = 0;
struct MySum{
	void operator()(int x)const{
		sum+= x;
	}
};
void test2d(){
	RoundList<int> ints(9);
	ints.forEach(MySum());
	if (sum != 9)
		cout << "failed to apply Func in forEach (-5)" << endl;
}
void test2e(){ // test 10 points...
}

/////////////////////////////////////////////////////// test 3
void test3(){
	ostringstream str;
	Person p("A", 0);

	Student s(p, "B", 1);
	s.output(str);
	if (str.str().compare("A,0,B,1") != 0)
		cout << "failed to output person (-10)" << endl;
	
	str.str("");str.clear();
	Employee e(p, "C");
	e.output(str);
	if (str.str().compare("A,0,C") != 0)
		cout << "failed to output Employee (-10)" << endl;

	str.str(""); str.clear();
	Intern i(s, e);
	i.output(str);
	if (str.str().compare("A,0,B,1,C") != 0)
		cout << "failed to output Intern (-10)" << endl;

}
int main()
{
	// test1 a-d
	try{ test1a(); } catch (...){ cout << "RE: test1a encountered a runtime exception likely candidate is Even (-5)" << endl; }
	try{ test1b(); } catch (...){ cout << "RE: test1b encountered a runtime exception likely candidate is Sum (-10)" << endl; }
	try{ test1c(); } catch (...){ cout << "RE: test1c encountered a runtime exception likely candidate is filter (-10) + manual check" << endl; }
	try{ test1d(); } catch (...){ cout << "RE: test1c encountered a runtime exception likely candidate is filter (-10) + manual check" << endl; }
	
	// test2 a-e
	try{ test2a(); } catch (...){ cout << "RE: test2a encountered a runtime exception likely candidate is remove() (-5)" << endl; }
	try{ test2b(); } catch (...){ cout << "RE: test2b encountered a runtime exception likely candidate is remove() (-10) + manual check" << endl; }
	try{ test2c(); } catch (...){ cout << "RE: test2c encountered a runtime exception likely candidate is remove()(-5) + manual check" << endl; }
	try{ test2d(); } catch (...){ cout << "RE: test2d encountered a runtime exception likely candidate is forEach() (-5)" << endl; }
	try{ test2e(); } catch (...){ cout << "RE: test2e encountered a runtime exception likely candidate is forEach() (-10) + manual check" << endl; }
	
	// test3
	try{ test3(); }catch (...){ cout << "RE: test3 encountered a runtime exception (-10) + manual check" << endl; }

	cout << "done" << endl;
	
}