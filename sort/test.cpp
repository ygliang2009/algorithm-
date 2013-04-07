#include "Sorter.h"
#include <iostream>
using namespace std;

int main()
{
	vector<int> vec;
	vec.push_back(34);
	vec.push_back(25);
	vec.push_back(18);
	vec.push_back(60);
	vec.push_back(49);
	Sorter sort_obj(vec);
	vector<int> *res_vec = sort_obj.insert_sort();
	for(int i = 0; i < res_vec->size(); i++)
		cout << res_vec->at(i) << endl;
	delete res_vec;
	return 0;
}
