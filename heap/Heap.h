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

#include <iostream>
#include <algorithm>
#include <iterator>
using std::cerr;
using std::endl;
using std::cout;
using std::ostream_iterator;
using std::copy;
using std::find;

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
/* 默认为小顶堆 */
Heap::Heap(int length,int *primary_data):flag(LITTLE_HEAP){
	if(length <= 0)
		cerr << "Heap Size must be above zero" << endl;
	data = new int[BUFSIZ];
	copy(primary_data,primary_data + length,data);	
	size = length;
	if(this->build_heap() == false)
		size = 0;
}

Heap::~Heap(){
	delete []data;
}

/* build heap, filled with data param using this function */
bool Heap::build_heap(){
	if(this->size <= 0)
		return false;
	int tmp_data[size];
	copy(data,data + size,tmp_data);
	/* 自底向上建堆,堆编号从1开始 */
	for(int i = 0,j = 0; i < size; i++,j++){
		int r = tmp_data[i];
		data[j] = r;
		if(j == 0)
			continue;
		//堆编号
		int k = j + 1;
		while(k != 1){
			int parent_idx = (k>>1) -1;
			if(data[parent_idx] > data[k-1]){
				//swap i and i/2 
				int tmp_val = data[parent_idx];
				data[parent_idx] = data[k-1];
				data[k-1] = tmp_val;
				k >>= 1;
			}else{
				break;
			}
		}
	}
	return true;
}

bool Heap::add_node(int val){
	if(this->size > BUFSIZ)
	{
		return false;
	}
	//堆编号
	data[size++] = val;
	int k = size;
	while(k != 1){
		int parent_idx = (k>>1) -1;
		if(data[parent_idx] > data[k-1]){
			//swap i and i/2 
			int tmp_val = data[parent_idx];
			data[parent_idx] = data[k-1];
			data[k-1] = tmp_val;
			k >>= 1;
		}else{
			break;
		}
	}
	return true;
}

bool Heap::remove_node(int val){
	/* swap val with the last element*/
	/* find函数返回指向正确元素的节点，如果没有找到，则指向容器的末端 */
	int *idx_ptr = find(data,data+size,val);
	int idx = idx_ptr - data;
	if(idx < size){	
		int heap_idx = idx + 1;	
		data[heap_idx - 1] = data[size - 1];
		size --;
		while((heap_idx << 1) <= size){
			int left_child = (heap_idx << 1),right_child = (heap_idx << 1) + 1;
			/* 和左孩子右孩子中最小的元素交换 */
			int min = -1;
			if(data[left_child - 1] < data[right_child - 1])
				min = left_child;
			else
				min = right_child;
			if((data[heap_idx - 1] > data[min - 1])){
				int tmp = data[heap_idx - 1];
				data[heap_idx - 1] = data[min - 1];
				data[min - 1] = tmp;
				heap_idx = min;
				continue;
			}else{
				break;
			}
		}
	}
	else{
		return false;
	}
	return true;
}

bool Heap::heap_sort(){
	int tmp_array[size];
	int sort_size = size;
	for(int i = 0; i < sort_size; i++)
	{
		tmp_array[i] = data[0];
		this->remove_node(data[0]);
	}	
	copy(tmp_array,tmp_array + sort_size,data);	
	size = sort_size;
	return true;
}
#endif
