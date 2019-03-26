
#include "Node.h"
#pragma once
template<class T>
class list{
private:
	Node<T>* head;
	int count;
	Node<T>*tail;
	void deleteptr(Node<T>*ptr);
public:
	list();
	~list();
	void insert(T item);
	T gethead();
	T* search(T item);
	int size();
	void deletenode(T item);

};
template<class T>
list<T>::list(){
count=0;
head=nullptr;
tail=nullptr;
}
template<class T>
int list<T>::size(){
return count;
}



template<class T>
void list<T>::insert(T item){
Node<T>* N=new Node<T>;
	if(count==0){
		head=N;
		tail=N;
	}
	else{
	tail->setNext(N);
	tail=N;
	}
	
	N->setItem(item);
	count++;
}

template<class T>
T list<T>:: gethead(){
	if(count==0)
		return 0 ;
	Node<T>*R=head;
	T value=head->getItem();
	head=head->getNext();
	delete R;
	count--;
	return value;

}

template<class T>
void list<T>::deletenode(T item){
	Node<T>*P=head;
	Node<T>*pervous=head;
	while(P){
		if(P->getItem()==item){
			if(P==head&&P==tail){
				delete P;
				count--;
				return;
			}
			else if(P==head){
				head=head->getNext();
				count--;
				delete P;
				return;
			}	
			else if(tail==P){
				tail=pervous;
				count--;
				delete P;
				return;
			}
			else{
				pervous->setNext(P->getNext());
				count--;
				delete P;
				return;
			}
		}
		pervous=P;
		P=P->getNext();
	}

}
template <class T>
void list<T>::deleteptr(Node<T>*ptr){
	if(!ptr->getNext())
		delete ptr;
	else deleteptr(ptr->getNext());
}

template <class T>
list<T>::~list(){
	if(count!=0)
	deleteptr(head);
}

template <class T>
T* list<T>::search(T item){
	Node<T>*P=head;
	
	while(P){
		if(*P->getItem()==item){
			return P;
		}
		P=P->getNext();
		
	}
}
