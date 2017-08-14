#ifndef POINTER_H_
#define POINTER_H_

#include <iostream>
using namespace std;

/**
 * Reference represents a counter that will be incremented or decremented as
 * the number of references to a pecticular pointer is made;
 *
 * where data means: a symbol used to point to, or associate to another object
 */
class ReferenceCounter{
private:
    int counter;
public:
    ReferenceCounter(){
        counter=0;  //initially set to zero
    }
    void increase(){
        counter++;  //increase it
    }
    int decrease(){
        --counter;  //decrease it
        if(counter<0){
            cout << "ReferenceCouner is < 0"<<endl;
        }
        return counter; //return its current value
    }
    int getCount(){
        return counter; //simply return the current value
    }
};


template<class T>
/**
 * Behaves as a smart pointer
 */
class Pointer {
    T* data;
    ReferenceCounter* dataReferenceCounter;
public:
	//Initialize
    Pointer() : data(NULL), dataReferenceCounter(NULL){
        //set everything to null but allocate a new reference counter
        dataReferenceCounter = new ReferenceCounter();
        dataReferenceCounter->increase();
    }

	//Assign internal 'T' data to a smart pointer using constructor
    Pointer(T* xReference) : data(xReference), dataReferenceCounter(NULL){
        dataReferenceCounter = new ReferenceCounter();
        dataReferenceCounter->increase();
    }

	//Copy constructor
    Pointer(const Pointer<T> &copy) : data(copy.data), dataReferenceCounter(copy.dataReferenceCounter){
        dataReferenceCounter->increase();
    }
    /**
     * Assignment operator
     */
    Pointer<T>& operator=(const Pointer<T> &other) {
        //prevent self assignment
        if(this != &other){
            //decrease this current instances counter because we are about to override it
            if(dataReferenceCounter->decrease()==0){
                delete data;
                delete dataReferenceCounter;
            }
            data = other.data;
            dataReferenceCounter   = other.dataReferenceCounter;  //Now other reference Counter can be changed through this reference counter
            dataReferenceCounter->increase();
        }
        return *this;
    }

    virtual ~Pointer(){
        //!Only delete the data if and only if no other smart pointer
        //!has a data this to data
        if(dataReferenceCounter->decrease() == 0){
            delete data;
            delete dataReferenceCounter;
        }
    }

    T& operator*(){
        return *data;
    }
    T* operator->(){
        return data;
    }
};
#endif

class A
{
public:
	int x;
	A(int x){this->x = x;}
	void print(){cout << " x is "<<x<<endl;}
};

int main(){

	Pointer<A> p(new A(3));
	p->print();
	if(true)
	{
		Pointer<A> g;
		g = p;
		cout<<"g is";g->print();
	}
	p->print();

	system("pause");
	return 0;
}

