// Labwork 2 · reference solution. Base class from the course; append() and split() at the end.
#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>

template <class T>
class DLLNode
{
public:
	DLLNode()
	{
		next = prev = 0;
	}

	DLLNode(const T& el, DLLNode<T>* n = 0, DLLNode<T>* p = 0)
	{
		info = el;
		next = n;
		prev = p;
	}

	T info;
	DLLNode<T> *next, *prev;
};

template <class T>
class DoublyLinkedList
{
public:
	DoublyLinkedList()
	{
		head = tail = 0;
	}

	void addToDLLTail(const T&);
	T deleteFromDLLTail();

	~DoublyLinkedList()
	{
		clear();
	}

	bool isEmpty() const
	{
		return head == 0;
	}

	void clear();

	void setToNull()
	{
		head = tail = 0;
	}

	void addToDLLHead(const T&);
	T deleteFromDLLHead();
	T& firstEl();
	T* find(const T&) const;

	void append(const DoublyLinkedList<T>& el);
	DoublyLinkedList<T>* split();


	void reset_to_zero();
protected:
	DLLNode<T> *head, *tail;

	friend std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& dll)
	{
		for (DLLNode<T>* tmp = dll.head; tmp != 0; tmp = tmp->next)
			out << tmp->info << ' ';
		return out;
	}
};

template <class T>
void DoublyLinkedList<T>::addToDLLHead(const T& el)
{
	if (head != 0)
	{
		head = new DLLNode<T>(el, head, 0);
		head->next->prev = head;
	}
	else head = tail = new DLLNode<T>(el);
}

template <class T>
void DoublyLinkedList<T>::addToDLLTail(const T& el)
{
	if (tail != 0)
	{
		tail = new DLLNode<T>(el, 0, tail);
		tail->prev->next = tail;
	}
	else head = tail = new DLLNode<T>(el);
}

template <class T>
T DoublyLinkedList<T>::deleteFromDLLHead()
{
	T el = head->info;
	if (head == tail)
	{ // if only one DLLNode on the list;
		delete head;
		head = tail = 0;
	}
	else
	{ // if more than one DLLNode in the list;
		head = head->next;
		delete head->prev;
		head->prev = 0;
	}
	return el;
}

template <class T>
T DoublyLinkedList<T>::deleteFromDLLTail()
{
	T el = tail->info;
	if (head == tail)
	{ // if only one DLLNode on the list;
		delete head;
		head = tail = 0;
	}
	else
	{ // if more than one DLLNode in the list;
		tail = tail->prev;
		delete tail->next;
		tail->next = 0;
	}
	return el;
}

template <class T>
T* DoublyLinkedList<T>::find(const T& el) const
{
	DLLNode<T>* tmp = head;
	for (; tmp != 0 && !(tmp->info == el); // overloaded ==
	       tmp = tmp->next);
	if (tmp == 0)
		return 0;
	else return &tmp->info;
}

template <class T>
T& DoublyLinkedList<T>::firstEl()
{
	return head->info;
}

template <class T>
void DoublyLinkedList<T>::clear()
{
	for (DLLNode<T>* tmp; head != 0;)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

template <class T>
void DoublyLinkedList<T>::reset_to_zero()
{
	DLLNode<T>* current = head;

	while (current != nullptr)
	{
		current->info = (T)0;
		current = current->next;
	}
}


// Q1 · copy every element of other to the end of this list.
// New nodes are created, so the two lists stay independent. The number of elements
// is counted first: A.append(A) must stop after copying the original elements.
template <class T>
void DoublyLinkedList<T>::append(const DoublyLinkedList<T>& other)
{
	int n = 0;
	for (DLLNode<T>* p = other.head; p != 0; p = p->next) n++;
	DLLNode<T>* src = other.head;
	for (int i = 0; i < n; i++, src = src->next)
	{
		DLLNode<T>* node = new DLLNode<T>(src->info, 0, tail);
		if (tail == 0) head = node;      // caller was empty
		else tail->next = node;
		tail = node;
	}
}

// Q2 · keep the first ceil(n/2) elements, move the rest (the same nodes) to a new list.
template <class T>
DoublyLinkedList<T>* DoublyLinkedList<T>::split()
{
	DoublyLinkedList<T>* second = new DoublyLinkedList<T>;
	int n = 0;
	for (DLLNode<T>* p = head; p != 0; p = p->next) n++;
	int keep = (n + 1) / 2;
	if (n - keep == 0) return second;    // 0 or 1 element: nothing to move

	DLLNode<T>* last = head;             // last node that stays here
	for (int i = 1; i < keep; i++) last = last->next;

	second->head = last->next;
	second->tail = tail;
	second->head->prev = 0;              // cut both directions
	last->next = 0;
	tail = last;
	return second;
}
#endif
