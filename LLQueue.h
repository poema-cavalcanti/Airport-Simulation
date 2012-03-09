/********************************************************************
*	Title: LLQueue.h												*
*	Abstract: Template for linked list implementation of a queue.	*
*	Author: Poema Cavalcanti										*
*	Date: 12/11/2011												*
********************************************************************/

#include <iostream>
using namespace std;

#ifndef LLQUEUE
#define LLQUEUE

template <typename QueueElementType>
class LLQueue
{
private:
	class Node {
	public:
		QueueElementType data;
		Node * next;
		Node(QueueElementType value, Node * link = 0)
		{
			data = value;
			next = link;
		}
	};

	Node * qFront; // points to the first element in the queue
	Node * qRear;  // points to the last element in the queue

public:
    LLQueue(); // default constructor
	LLQueue(const LLQueue & original); // copy constructor
	~LLQueue(); // destructor
	const LLQueue &operator= (const LLQueue & rhs); // assignment
    bool empty() const; // return true if the queue is empty, false otherwise
	bool full() const; // returns true if the queue is full, false otherwise
    void enqueue(const QueueElementType & value); // adds an element to the queue
	void dequeue(); // removes an element from the queue
	void updateQueue(); // Cannot be used with element types with no update() function.
						// This function assumes QueueElementType has an update() function.
						// It traverses the queue and calls update() for all elements in queue.
    void display(ostream & out) const; // displays data in all elements of queue
    QueueElementType front() const; // returns data at front of the queue
	int size() const; // returns number of elements in the queue
};

#endif

// DEFAULT CONSTRUCTOR
template <typename QueueElementType>
LLQueue<QueueElementType>::LLQueue()
{
    qFront = qRear = 0;
}

// BOOL EMPTY
template <typename QueueElementType>
bool LLQueue<QueueElementType>::empty() const
{
    return (qFront == 0);
}

// VOID ENQUEUE (QUEUE ELEMENT TYPE)
template <typename QueueElementType>
void LLQueue<QueueElementType>::enqueue(const QueueElementType & value)
{
	Node * newNode = new Node(value, NULL);
	if(newNode == 0) {
		cerr << "Insufficient Memory for new Node\n";
		exit(1);
	}
	if(empty()) { // When queue is empty the element is placed at the front and becomes the new qFront
		qFront = newNode;
		qRear = newNode;
	}
	else { // In all other cases element is added to the back of the queue and becomes the new qRear
		qRear->next = newNode;
		qRear = newNode;
	}
}

// VOID DISPLAY ( OSTREAM & )
template <typename QueueElementType>
void LLQueue<QueueElementType>::display(ostream &out) const
{
	Node * current = qFront;  // displays queue elements in order they were inserted
	while(current != NULL) {
		out << current->data << " "; 
		current = current->next;
	}
	out << endl;
}

// QUEUEELEMENTTYPE FRONT ( )
template <typename QueueElementType>
QueueElementType LLQueue<QueueElementType>::front() const
{
    if(!empty()) {
        return qFront -> data;  // data in the first element of the queue
    }
    else { // since the queue is empty the function cannot return a value
        cerr << "Queue Empty!\n";
        exit(1);
    }
}

// VOID DEQUEUE ( )
template <typename QueueElementType>
void LLQueue<QueueElementType>::dequeue()
{
    if(!empty()) {
		Node * temp = qFront;
		qFront = qFront->next;
		delete temp;
		// If Queue is empty, qRear is set back to NULL
		if(qFront == 0) {
			qRear = 0;
		}
    }
    else
    {
        cerr << "Can't remove from empty queue!\n";
    }
}

// VOID UPDATE QUEUE ( )
template <typename QueueElementType>
void LLQueue<QueueElementType>::updateQueue()
{
	Node * current = qFront;
	while(current != NULL)
	{
		(current->data).update(); // This line will generate an error if QueueElementType does
		current = current->next;  //							not have an update() function.
	}
	return;
}

// INT SIZE ( )
template <typename QueueElementType>
int LLQueue<QueueElementType>::size() const
{
	int size = 0;
	Node * current = qFront;
	while(current != NULL)
	{
		size++; // size will not increment if queue is empty because qFront would equal NULL 
		current = current->next;
	}
	return size;
}

// DESTRUCTOR
template <typename QueueElementType>
LLQueue<QueueElementType>::~LLQueue()
{
	Node * current = qFront;
	Node * temp;
	while (current != NULL)
	{
		temp = current->next;
		delete current;
		current = temp;
	}
}

// ASSIGNMENT OPERATOR OVERLOAD
template <typename QueueElementType>
const LLQueue<QueueElementType> & LLQueue<QueueElementType>::operator=(const LLQueue & rhs)
{
	if(this != &rhs)
	{
		this->~LLQueue();
		if(rhs.empty())
		{
			qFront = qRear = 0;
		}
		else
		{
			Node * newNode = new Node(rhs.front());
			qFront = qRear = newNode;

			Node * currentNode = rhs.qFront->next;
			while(currentNode != 0)
			{
				qRear->next = new Node(currentNode->data);
				qRear = qRear->next;
				currentNode = currentNode->next;
			}
		}
	}

	return *this;
}

// COPY CONSTRUCTOR
template <typename QueueElementType>
LLQueue<QueueElementType>::LLQueue(const LLQueue & original)
{
	qFront = qRear = 0;
	if(!original.empty())
	{
		Node * newNode = new Node(original.front());
		qFront = qRear = newNode;

		Node * currentNode = original.qFront->next;
		while(currentNode != 0)
		{
			qRear->next = new Node(currentNode->data);
			qRear = qRear->next;
			currentNode = currentNode->next;
		}
	}
}