/*
 * 队列实现
 * @author:liangyunge
 * @date:2013-04-06
 */
#ifndef _QUEUE_H
#define	_QUEUE_H

#define 	NULL	0

template <class T>
class Node
{
	public:
		const T& val;
		Node<T> *next;
		Node(const T &t):val(t),next(NULL){}	
		virtual ~Node();
};

template <class T>
class Queue
{
		int size;
		Node<T> *head;
		Node<T> *tail;
	public:
		/* 构造函数 */
		Queue():size(0){this->head = this->tail = NULL;}
		/* 析构函数 */
		virtual ~Queue();
		Node<T>& getHead(){return this->head;}
		Node<T>& getTail(){return this->tail;}
		int length(){return this->size;}
		void enqueue(const T &t_obj);
   		const T& dequeue();
};

template <class T>
Node<T>::~Node()
{}

template <class T>
Queue<T>::~Queue()
{}

/* 从队尾入队 */
template <class T>
void Queue<T>::enqueue(const T &t_obj)
{
	Node<T> *node = new Node<T>(t_obj);
	/* 这里报了个bug，类的const成员只能在构造函数中赋值 */
	//node->val = t_obj;
	if(this->size == 0)
	{
		this->head = this->tail = node; 
	}
	else{
		this->tail->next = node;
		this->tail = node;
	}
	this->size++;
}

template <class T>
const T& Queue<T>::dequeue()
{
	if(this->size == 0)
	{
		return NULL;
	}
	else if(--this->size == 0)
	{
		const T& t_obj = this->head->val;	
		this->head = this->tail = NULL;
		return t_obj;
	}
	else{
		Node<T> *head = this->head;
		const T& t_obj = head->val;
		this->head = head->next;
		return t_obj;		
	}
}
#endif
