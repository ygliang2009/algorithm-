#include "Sorter.h"
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

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

vector<int>* Sorter::merge(vector<int> *vec){
	int vec_size = vec->size();
	if(vec_size == 1){
		vector<int> *vec_small = new vector<int>();
		copy(vec->begin(),vec->end(),back_inserter(*vec_small));
		return vec_small;
	}
	vector<int> sub_vec_left;
	vector<int> sub_vec_right;
	copy(vec->begin(),vec->begin() + vec_size/2,back_inserter(sub_vec_left));
	copy(vec->begin() + vec_size/2,vec->end(),back_inserter(sub_vec_right));
	vector<int> *res_vec_left = merge(&sub_vec_left);
	vector<int> *res_vec_right = merge(&sub_vec_right);
	vector<int> *res_vec = new vector<int>;
	int i = 0, j = 0;
	for(; i < res_vec_left->size() && j < res_vec_right->size();){
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
	delete res_vec_left;
	delete res_vec_right;
	return res_vec;
}

vector<int>* Sorter::quick_sort(){
	vector<int> *res_vec = new vector<int>;
	copy(primary_data.begin(),primary_data.end(),back_inserter(*res_vec));
	quick(res_vec,0,size - 1);	
	return res_vec;
}

void Sorter::quick(vector<int> *vec,int start,int end){
	if(start >= end)
		return;
	int base_idx = end;
	int base = vec->at(base_idx);	
	int i = start, j = end;
	while(i < j){
		while(vec->at(i) <= base && i < j)
			i++;
		if(i < j){
			int tmp_data = base;
			(*vec)[base_idx] = vec->at(i);
			(*vec)[i] = tmp_data;	
			base_idx = i;
		}
		else{
			break;
		}
		while(vec->at(j) >= base && j > i)
			j--;
		if(j > i){
			int tmp_data = base;
			(*vec)[base_idx] = vec->at(j);
			(*vec)[j] = tmp_data;
			base_idx = j;
		}else{
			break;
		}
	}
	quick(vec,start,base_idx - 1);
	quick(vec,base_idx + 1,end);
}


int main()
{
	vector<int> vec;
	vec.push_back(34);
	vec.push_back(25);
	vec.push_back(18);
	vec.push_back(55);
	vec.push_back(28);
	vec.push_back(19);
	Sorter sort_obj(vec);
	vector<int> *res_vec = sort_obj.merge_sort();
	cout << res_vec->size() << endl;
	for(int i = 0; i < res_vec->size(); i++)
		cout << res_vec->at(i) << endl;
	delete res_vec;
	return 0;
}
