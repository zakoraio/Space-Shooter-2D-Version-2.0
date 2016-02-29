#ifndef OBJECTPOOL__H
#define OBJECTPOOL__H

#include<list>
#include<string>
#include<algorithm>
#include"comparison.h"

template <class T>
class ObjectPool{
public:

ObjectPool(std::string n):freeList(),useList(),entityName(n){ }

~ObjectPool(){

		resetPool();

	}


void resetPool() {


   	        typename std::list<T *>::iterator itr = freeList.begin();

		while(itr!=freeList.end()){
			delete (*itr);
			itr++;
		}

	        typename std::list<T *>::iterator itr1 = useList.begin();

		while(itr1!=useList.end()){
			delete (*itr1);
			itr1++;
		}

 }


T* getObjectFromPool(){

		if(freeList.size()==0){
			T *f = new T(entityName);
                        f->setId(counter);
                        f->readyToUse();
			counter++;
			useList.push_back(f);
			return f;
		}

		else{
		      typename	std::list<T *>::iterator itr = freeList.begin();
			T *f = *itr;
			freeList.erase(itr);
                        f->readyToUse();
			useList.push_back(f);
			return f;
		}

}


void returnObjToPool(T * f) { 

		f->readyToUse();
		typename std::list<T *>::iterator itr  = std::find_if(useList.begin(),useList.end(),Comparison<T>(*f));
		freeList.push_back((*itr));
		useList.erase(itr);
}

const std::list<T *>* getInUseList() const { return &useList; }
const std::list<T *>* getFreeList() const { return &freeList; }


void returnObjectsToPool() {

		typename std::list<T *> tmp(useList);
	        typename std::list<T *>::iterator itr1 = tmp.begin();
               
		while(itr1!=tmp.end()){
			if((*itr1)->isEligibleToRest()) { 
				returnObjToPool((*itr1));
			}
			itr1++;
		}
}

private:
static int counter;
std::list<T *> freeList;
std::list<T *> useList;
std::string entityName;
};


template <class T>
int ObjectPool<T>::counter=0;
#endif


