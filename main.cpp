#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

/*
this is called RAII - Resource Acquisition Is Initialization 
(Constructor acquire resources & Destructors releases resources)

in a simplified way, constructors declares the thread
and destructors executes them 
this process is called RAII
*/

class thread_guard {
	thread& T;

public:
	//explicit keyword's job is to tell the compiler that it is a must to pass a certain as a parameter of the object, in this case, it is a must to pass a thread as a parameter
	explicit thread_guard(thread& t) :T(t) {}
	
	~thread_guard() {
		if (T.joinable()) {
			T.join();
		}
	}
		//deleting the copy constructor - means deleting the possibility of a thread being copied
		thread_guard(thread_guard& const) = delete;
	
		//deleting the = operator - means deleting the possibility of a thread being assigned to another object thread
		thread_guard& operator=(thread_guard& const) = delete;
};

void foo() {
	cout << "Hello from foo" << endl;
}

void other_operations() {
	cout << "This is other operation \n" << endl;

	//if you wanna make the thread delay its execution then:
	this_thread::sleep_for(chrono::milliseconds(50));
	
	throw runtime_error("This is a runtime error");
}

int main() {

	

	try {
		thread t1(foo);
		t1.join();

		//we gonna try executing t2, it executes through destructor, which checks if it is joinable or not, so in case it is joinable, then the try block will execute :)
		thread_guard t2(t1); 
	}
	catch (size_t temp) {
		other_operations();
		temp = NULL;
	}
}
