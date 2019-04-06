template < class T>
class LinkedList 
{
private :
Node<T>* headPtr; 
int itemCount; 
Node<T>* getNodeAt( int position) const ;
public :
LinkedList();
LinkedList( const LinkedList<T>& aList);
~LinkedList();
bool isEmpty() const ;
int getLength() const ;
bool insert( int newPosition, const T& newEntry);
bool remove( int position);
void clear();

T getEntry( int position) const ;

void setEntry( int position, const T& newEntry)
};


template < class T>
LinkedList<T>::LinkedList() : headPtr( nullptr), itemCount(0)
{
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
	assert ( (position >= 1) && (position <= itemCount) );
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
bool LinkedList<T>::remove( int position)
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
		else
		{
			Node<T>* prevPtr = getNodeAt(position - 1);
			curPtr = prevPtr->getNext();
			prevPtr->setNext(curPtr->getNext());
		} 	
		curPtr->setNext( nullptr );
		delete curPtr;
		curPtr = nullptr ;
		itemCount–-; 
	} 
	return ableToRemove;
} 
template < class T>
bool LinkedList<T>::isEmpty()const
{
	if(headPtr==NULL)
		return true;
	return false;
}


template < class T>
void LinkedList<T>::clear()
{
while (!isEmpty())
	remove(1);
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
			headPtr = nullptr ; 
		else
		{
			headPtr = new Node<T>();
			headPtr->setItem(origChainPtr ->getItem());
			Node<T>* newChainPtr = headPtr; 
			while (origPtr != nullptr )
			{
				origChainPtr = origChainPtr ->getNext(); 
				T nextItem = origChainPtr->getItem();
				Node<T>* newNodePtr = new Node<T>(nextItem);
				newChainPtr->setNext(newNodePtr);
				newChainPtr = newChainPtr->getNext();
			} 
			newChainPtr->setNext( nullptr ); 
		} 
} 