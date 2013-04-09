/*
 * @author:liangyunge@baidu.com
 * @version:1.0
 * @date:2013-04-08
 * @desc:堆，堆排序算法 这里堆的形式为整数数组
 */
#ifndef _HEAP_H
#define _HEAP_H

#define	LITTLE_HEAP		0
#define	HEAVY_HEAP		1
#define	BUFSIZ			1024

class Heap{
	int flag;
	int size;
	int *data;
	bool build_heap();
	public:
		int length(){return this->size;}
		int *get_data(){return this->data;}
		Heap(int,int *);
		virtual ~Heap();
		bool add_node(int val);
		bool remove_node(int val);
		bool heap_sort();
};

#endif
