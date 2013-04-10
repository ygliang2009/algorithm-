/*
 * @author:liangyunge@baidu.com
 * @version:1.0
 * @date:2013-04-10
 * @desc: hobby data structure -- BinaryTree
 */
#include <iostream>

using std::cout;
using std::ends;

template <class T>
class btreenode{
	const T node;
	btreenode<T> *left;
	btreenode<T> *right;	
	public:
		btreenode(T t):node(t),left(NULL),right(NULL){}
		bool setleft(btreenode<T> *leftnode){this->left = leftnode;}
		bool setright(btreenode<T> *rightnode){this->right = rightnode;}
		btreenode* getleft(){return this->left;}
		btreenode* getright(){return this->right;}
		virtual ~btreenode();
		int weight(){return this->node.weight;}
};

template <class T>
class btree{
	int size;
	btreenode<T> *root;
	void printnode(btreenode<T> *node);
	public:
		int length(){return this->size;}
		btree():size(0),root(NULL){}
		virtual ~btree();
		bool addnode(T);
		bool delnode(int);
		btreenode<T> *findnode(int weight);
		void printtree();
};

template <class T>
btreenode<T>::~btreenode(){
};

template <class T>
btree<T>::~btree(){
}

template <class T>
bool btree<T>::addnode(T t){
	if(root == NULL){
		root = new btreenode<T>(t);
		return true;
	}
	btreenode<T> *p = root;
	btreenode<T> *q = p;
	while(p){
		q = p;
		if(t.weight < p->weight()){
			p = p->getleft();
		}else if(t.weight > p->weight()){
			p = p->getright();
		}
		else{
			return false;
		}
	}
	if(t.weight < q->weight()){
		btreenode<T> *left = new btreenode<T>(t);
		q->setleft(left);
	}else{
		btreenode<T> *right = new btreenode<T>(t);
		q->setright(right);
	}
	return true;
}

template <class T>
btreenode<T>* btree<T>::findnode(int weight){
	btreenode<T>* p = root;
	while(p){
		int p_weight = p->weight();
		if(p_weight == weight)
			return p;
		else if(p_weight > weight)
			p = p->getleft();
		else
			p = p->getright();
	}
	return NULL;
}

/* 
 * delete tree node waste little time
 */
template <class T>
bool btree<T>::delnode(int weight){
	btreenode<T> *p = root;
	btreenode<T> *q = p;
	/* 
	 * first of all, find node that match the weight value
	 */
	while(p){
		int p_weight = p->weight();
		if(p_weight == weight)
			break;
		else if(p_weight > weight){
			q = p;
			p = p->getleft();
		}
		else{
			q = p;
			p = p->getright();
		}
	}
	/*
	 * nothing match the weighted node 
	 */
	if(!p)
		return false;
	/*
	 * else find the weighted node, if the node has no left and right child,
	 * delete the node directly, else find the node's left child,replace the rightest
	 * child of the left to the delete node, or find node's right child,replace the 
	 * leftest child of the right.
	 */
	if((!p->getleft())&&(!p->getright())){
		if(q->getleft() == p){
			q->setleft(NULL);
		}else{
			q->setright(NULL);
		}	
		/* delete 操作后，仍然能打印出p的值 */
		delete p;
	}
	else if(p->getleft()){
		btreenode<T> *left = p->getleft();
			/*
			 * deleting node's left child has no right child
			 */
		if(!left->getright()){
			left->setright(p->getright());
			if(q->getleft() == p)
				q->setleft(left);
			else
				q->setright(left);
			if(p == root)
				root = left;
			delete p;
		}else{
			btreenode<T> *left_right = left->getright();
			/*
			 * p_right point to the parent of left_right 
			 */
			btreenode<T> *p_right = left;
			while(left_right->getright()){
				p_right = left_right;
				left_right = left_right->getright();
			}
			p_right->setright(left_right->getleft());
			left_right->setright(p->getright());
			if(q->getleft() == p)
				q->setleft(left_right);
			else
				q->setright(left_right);
			left_right->setleft(p->getleft());
			if(p == root)
				root = left_right;
			delete p;
		}
	}else{
		btreenode<T> *right = p->getright();
			/*
			 * deleting node's right child has no left child
			 */
		if(!right->getleft()){
			right->setleft(NULL);
			if(q->getleft() == p)
				q->setleft(right);
			else
				q->setright(right);
			if(p == root)
				root = right;
			delete p;
		}else{
			btreenode<T> *right_left = right->getleft();
			/*
			 * p_left point to the parent of right_left
			 */
			btreenode<T> *p_left = right;
			while(right_left->getleft()){
				p_left = right_left;
				right_left = right_left->getleft();
			}
			p_left->setleft(right_left->getright());
			right_left->setleft(NULL);
			if(q->getleft() == p)
				q->setleft(right_left);
			else
				q->setright(right_left);
			right_left->setright(p->getright());
			if(p == root)
				root = right_left;
			delete p;
		}
	}
	return true;
}

template <class T>
void btree<T>::printnode(btreenode<T> *node){
	if(node == NULL)
		return;
	printnode(node->getleft());
	std::cout << node->weight() << "\t" << ends;
	printnode(node->getright());
}

template <class T>
void btree<T>::printtree(){
	printnode(root);
	std::cout << std::endl;
}
