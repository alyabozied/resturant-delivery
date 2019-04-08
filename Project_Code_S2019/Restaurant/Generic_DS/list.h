#include <vector>
template < class T>

class LinkedList 
{
private :
Node<T>* headPtr; 
Node<T>* tailPtr; 
int itemCount;
Node<T>* getNodeAt( int position) const ;
public :
LinkedList();
LinkedList( const LinkedList<T>& aList);
~LinkedList();
bool isEmpty() const ;
int getLength() const ;
bool insert( int newPosition, const T& newEntry);
bool remove( int position , T& item);
void clear();
std::vector<T> ToVector();
T getEntry( int position) const ;
int search(T item);
};


template < class T>
LinkedList<T>::LinkedList() : headPtr( nullptr), itemCount(0),tailPtr(nullptr)
{
}

template <class T>
int LinkedList<T>::search(T item){
	Node<T>* P=headPtr;
	int i =1;
	while(P){
		if(*P->getItem()==*item){
			
			return i ;
		}
		P=P->getNext();
		i++;
		
	}
	return -1;
}





template < class T>
T LinkedList<T>::getEntry( int position) const
{
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)	
	{
		Node<T>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
}



template < class T>
Node<T>* LinkedList<T>::getNodeAt( int position) const
{
	if(position<1)
		return nullptr;
	Node<T>* curPtr = headPtr;
	for ( int skip = 1; skip < position; skip++)	
		curPtr = curPtr->getNext();
	return curPtr ;
}


template < class T>
bool LinkedList<T>::insert( int newPosition,const T& newEntry)
{
	bool ableToInsert = (newPosition >= 1) &&(newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		if (newPosition == 1)
		{
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
			tailPtr = newNodePtr;
		}
		else if( newPosition ==itemCount+1) 
		{
			tailPtr->setNext(newNodePtr);
			tailPtr=newNodePtr;
		}
		else
		{
		
			Node<T>* prevPtr = getNodeAt(newPosition - 1);	
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		} 
		itemCount++; 
	} 
		return ableToInsert;
} 

template < class T>
bool LinkedList<T>::remove( int position, T& item)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);

	if (ableToRemove)
	{
		Node<T>* curPtr = nullptr ;
		if (position == 1)
		{
			curPtr = headPtr; 
			headPtr = headPtr->getNext();
		}
		else if(position == itemCount)
		{
			Node<T>*tmp = getNodeAt(position-1);
			tmp->setNext(nullptr);
			delete tailPtr;
			tailPtr=tmp;
		}

		else
		{
			Node<T>* prevPtr = getNodeAt(position - 1);
			curPtr = prevPtr->getNext();
			prevPtr->setNext(curPtr->getNext());
		} 	
		curPtr->setNext( nullptr );
		item=curPtr->getItem();
		delete curPtr;
		curPtr = nullptr ;
		itemCount--; 
	} 
	return ableToRemove;
} 
template < class T>
bool LinkedList<T>::isEmpty()const
{
	if(headPtr==nullptr)
		return true;
	return false;
}


template < class T>
void LinkedList<T>::clear()
{
	T tmp;
while (!isEmpty())
	remove(1,tmp);
} 

template<class T>
LinkedList<T>::~LinkedList()
{
	clear();

}
template<class T>
int LinkedList<T>::getLength()const
{
	return itemCount;
}



template < class T>
LinkedList<T>::LinkedList( const LinkedList<T>& LIST)
{
	itemCount = LIST->itemCount;
	Node<T>* origChainPtr = LIST->headPtr
	
		if (origChainPtr == nullptr )
		{
			headPtr = nullptr ;
			tailPtr = nullptr ;
		}
		else
		{
			headPtr = new Node<T>();
			tailPtr = headPtr;
			headPtr->setItem(origChainPtr->getItem());
			while (origPtr != nullptr )
			{
				origChainPtr = origChainPtr ->getNext(); 
				T nextItem = origChainPtr->getItem();
				Node<T>* newNodePtr = new Node<T>(nextItem);
				tailPtr->setNext(newNodePtr);
				tailPtr = tailPtr->getNext();
			} 
			tailPtr->setNext( nullptr ); 
		} 
} 
template<class T>
std::vector<T> LinkedList<T>::ToVector(){
	std::vector<T> n;
	Node<T>* p=headPtr;
	while(p){
		n.push_back(p->getItem());
		p=p->getNext();
	}
	return n;
}
