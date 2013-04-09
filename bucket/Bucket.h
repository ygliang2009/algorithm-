/*
 * @author: liangyunge@baidu.com
 * @version: 1.0
 * @date: 2013-04-09
 * @desc: Bucket sort
 */

#ifndef  _BUCKET_H
#define  _BUCKET_H

#define BUCKET_SIZE		10
#define MAX_NUM		1000
#include <iostream>

class IntPointer{
	public:
		int val;
		IntPointer *next;
		IntPointer():val(-1),next(NULL){}
		IntPointer(int value):val(value),next(NULL){}
		virtual ~IntPointer();
};

class Bucket{
	int size;
	IntPointer *head_ptr;
	bool add_node(int val);
	IntPointer* find_node(IntPointer *,int);
	bool delete_node(int val);
	public:
		Bucket();
		int length(){return size;}
		virtual ~Bucket();
		int* collect_node();
		int* bucket_sort(int *,int length);
};

#endif
