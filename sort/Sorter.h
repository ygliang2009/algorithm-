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
	public:
		Sorter(vector<int> &primary):size(primary.size()),primary_data(primary){}
		virtual ~Sorter();
		vector<int>* merge_sort();
		vector<int>* insert_sort();	
		int length(){return this->size;}
};

Sorter::~Sorter(){
}

vector<int>* Sorter::merge_sort(){
	vector<int> *res_vec = this->merge(&(this->primary_data));
	return res_vec; 
}

vector<int>* Sorter::insert_sort(){
	vector<int>* res_vec = new vector<int>;
	for(int i = 0; i < this->primary_data.size(); i++){
		int var_i = this->primary_data.at(i);
		int k = res_vec->size();
		for(int j = 0; j < res_vec->size();j++){
			if(var_i > res_vec->at(j))
				continue;
			else{
				k = j;
				break;
			}
		}
		res_vec->insert(res_vec->begin() + k ,var_i);	
		//copy(res_vec->begin(),res_vec->end(),ostream_iterator<int>(cout,"\n"));
	}
	return res_vec;	
}

vector<int>* Sorter::merge(vector<int> *vec)
{
	int vec_size = vec->size();
	if(vec_size == 1)
		return vec;
	vector<int> sub_vec_left;
	vector<int> sub_vec_right;
	copy(vec->begin(),vec->begin() + vec_size/2,back_inserter(sub_vec_left));
	copy(vec->begin() + vec_size/2,vec->end(),back_inserter(sub_vec_right));
	vector<int> *res_vec_left = merge(&sub_vec_left);
	vector<int> *res_vec_right = merge(&sub_vec_right);
	vector<int> *res_vec = new vector<int>;
	int i = 0, j = 0;
	for(; i < res_vec_left->size() && j < res_vec_right->size();)
	{
		if(res_vec_left->at(i) < res_vec_right->at(j))
			res_vec->push_back(res_vec_left->at(i++));
		else
			res_vec->push_back(res_vec_right->at(j++));
	}
	if(i == res_vec_left->size())
		for(;j < res_vec_right->size();j++)
			res_vec->push_back(res_vec_right->at(j));	
	else
		for(;i < res_vec_left->size();i++)
			res_vec->push_back(res_vec_left->at(i));	
	/* 这里为啥会报错 */
	//delete res_vec_left;
	//delete res_vec_right;
	return res_vec;
}
#endif
