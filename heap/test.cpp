#include "Heap.h"
#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

int main(){
	int primary_array[] = {23,15,18,20,9,27,6};
	Heap heap(7,primary_array);
	heap.add_node(24);
	heap.add_node(5);
	heap.add_node(1);
	heap.add_node(10);
	heap.heap_sort();
	int *res_data = heap.get_data();
	copy(res_data,res_data + heap.length(),ostream_iterator<int>(cout,"\n"));
	//delete[] res_data;
	return 0;
}
