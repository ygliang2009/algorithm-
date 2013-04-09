/*
 *@author:liangyunge@baidu.com
 *@version:1.0
 *@date:2013-04-07
 */

#ifndef _SORTER_H
#define _SORTER_H
#include <vector>
#include <algorithm>

using std::vector;

class Sorter{
	int size;
	vector<int> primary_data;
	vector<int>* merge(vector<int>*);
	void quick(vector<int> *,int,int);
	public:
		Sorter(vector<int> &primary):size(primary.size()),primary_data(primary){}
		virtual ~Sorter();
		/* 归并排序 */
		vector<int>* merge_sort();
		/* 插入排序 */
		vector<int>* insert_sort();
		/* 快速排序 */
		vector<int>* quick_sort();	
		int length(){return this->size;}
};

#endif
