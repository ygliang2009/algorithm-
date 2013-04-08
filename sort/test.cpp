#include "Sorter.h"
#include <iostream>
using namespace std;

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
	vector<int> *res_vec = sort_obj.quick_sort();
	cout << res_vec->size() << endl;
	for(int i = 0; i < res_vec->size(); i++)
		cout << res_vec->at(i) << endl;
	delete res_vec;
	return 0;
}
