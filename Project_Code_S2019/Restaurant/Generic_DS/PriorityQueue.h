#pragma once
#include "../Defs.h"
template <typename T>
class priorityQueue
{
private:
  //an array to store the data
  T* tree;
  //count:var. for number of objects,size:var for size of the array
  int count,size;
  //utility functions
  void shiftup(int index);
  void shiftdown(int index);
  void swap(int index1,int index2);
  int maximum(int index1,int index2);
public:
  //defualt consturctor
  priorityQueue();
  //copy consturctor
  //priorityQueue(priorityQueue<T> queue);
  void insert(T item);
  //get max and delete it
  T extractMax();
  //changepriority of an object
  void changepriority(T item,int priority);
  void remove(T item);
  int  search(T item);
  T getmax()const;
  int getcount()const;
  const T* ToArray();
  //dustructor for pervent memory leak
  ~priorityQueue();

};
template <typename T>
priorityQueue<T>::priorityQueue(){
	size=2;
	count=0;
	tree =new T[size];
}
template <typename T>
void priorityQueue<T>::shiftdown(int index){
	

    int largest = index; // Initialize largest as root 
    int l = 2*index + 1; // left = 2*i + 1 
    int r = 2*index + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
	if (l < getcount() && *tree[l] > *tree[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
	if (r < getcount() && *tree[r] > *tree[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != index) 
    { 
        swap(index, largest); 
  
        // Recursively heapify the affected sub-tree 
		shiftdown( largest); 
    } 

}
template <typename T>
void priorityQueue<T>:: shiftup(int index)
{
	if(*tree[(index-1)/2] < *tree[index])
	{
			swap(index,(index-1)/2);
			shiftup((index-1)/2);
	}
	
}
template <class T>
int priorityQueue<T>::maximum(int index1,int index2){
	if(*tree[index1] > *tree[index2])
		return index1;
	return index2;
}
template <class T>
void priorityQueue<T>::swap(int index1,int index2){
	T temp=tree[index1];
	tree[index1]=tree[index2];
	tree[index2]=temp;
}
template <typename T>
void priorityQueue<T>::insert(T item){
	if(count==size){
		size*=2;
		T* arr=new T[size];
		for (int i = 0; i < count; i++)
		{
			arr[i]=tree[i];
		}
		delete[] tree;
		tree=arr;
	}
	tree[count]=item;
	shiftup(count);
	count++;
}
template <typename T>
T priorityQueue<T>::extractMax(){
	T result=tree[0];
	tree[0]=tree[count-1];
	count--;
	shiftdown(0);
	return result;
}
template <typename T>
int priorityQueue<T>::getcount()const{
	return count;
}
template <typename T>
void priorityQueue<T>::remove(T item){
	int index=search(item);
	if(index==-1)
		return;
	T removeditem = tree[index];
	swap(index,count);
	count--;
	if(*removeditem > *tree[index])
	shiftdown(index);
	else shiftup(index);
}

template <typename T>
void priorityQueue<T>::changepriority(T item,int priority){
	int index=search(item);
	if(index == -1)
		return;
	tree[index] = priority;
	if(*priority > *tree[index])
		shiftdown(index);
	else 
		shiftup(index);
}
template <typename T>
T priorityQueue<T>::getmax()const	{
	return tree[0];
}
template <typename T>
priorityQueue<T>::~priorityQueue(){
	delete[] tree;
}

template <typename T>
int priorityQueue<T>::search(T item){
	for (int i = 0; i <getcount() ; i++)
	{
		if(*tree[i] == *item)
			return i;
	}
	return -1;
}


template <typename T>
// remember to delete it after using it
const T* priorityQueue<T>::ToArray(){

	T* n = new T[count];
	for (int i = 0; i < count; i++)
	{
		n[i] = tree[i];
	}
	return n;
	
}