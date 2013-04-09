#include "Bucket.h"
#include <iterator>
#include <algorithm>
using std::copy;
using std::cout;
using std::cerr;
using std::endl;
using std::ostream_iterator;

IntPointer::~IntPointer(){
}

Bucket::Bucket():size(0){
	/* head值初始化为 -1 */
	head_ptr = new IntPointer[BUCKET_SIZE];
}

Bucket::~Bucket(){
	delete[] head_ptr;
}

IntPointer* Bucket::find_node(IntPointer *head_ptr,int val){
		/* 无法二分法查找，因为没有记录每个桶的大小 */
		if(head_ptr->val == -1){
			return head_ptr;
		}
		IntPointer *tmp_ptr = head_ptr;
		IntPointer *p = tmp_ptr;	
		while(tmp_ptr != NULL && tmp_ptr->val < val){
			p = tmp_ptr;
			tmp_ptr = tmp_ptr->next;
		}
		return p;
}

bool Bucket::add_node(int val){
	if(val > MAX_NUM)
		return false;
	IntPointer *int_ptr = new IntPointer(val);
	int idx = val/100;
	IntPointer *idx_head = this->head_ptr + idx;
	IntPointer* ip = find_node(idx_head,val);
	if(ip->next&&ip->next->val == val)		
		return false;
	/* 头结点中的第一个元素 */
	if(idx_head == ip)
		idx_head->val = 0;
	IntPointer *ip_next = ip->next;
	IntPointer *ip_new = new IntPointer(val);
	ip->next =	ip_new;
   	ip_new->next = ip_next;
	size++;
	return true;	
}

bool Bucket::delete_node(int val){
	int idx = val/100;
	IntPointer *idx_head = head_ptr + idx;
	if(idx_head->val == -1)
		return false;
	IntPointer *p = idx_head->next;
	IntPointer *q = idx_head;
	while(p->val){
		if(p->val == val){
			this->size--;
			q->next = p->next;
			delete(p);
			/* 仅有的一个元素被删除 */
			if(q->next == NULL && q == idx_head){
				q->val = -1;
			}
			return true;			
		}	
		q = p;
		p = p->next;
	}
	return false;
}

int* Bucket::bucket_sort(int *p,int length){
	for(int i = 0; i < length; i++){
		bool res = add_node(*(p + i));
		if(res == false)
			cerr << "add_node error for node value " << *(p + i) << endl;
	}	
	int *res = collect_node();	
	return res;
}

int* Bucket::collect_node(){
	int *res = new int[size];
	int j = 0;
	for(int i = 0; i < BUCKET_SIZE; i++){
		if((head_ptr + i)->val == -1)
			continue;
		IntPointer *idx_first = (head_ptr + i)->next;
		IntPointer *idx_ptr = idx_first;
		while(idx_ptr != NULL){
			*(res + (j++)) = idx_ptr->val;
			idx_ptr = idx_ptr->next;
		}
	}
	return res;
}

int main(){
	Bucket bucket;
	int primary_array[] = {232,43,231,542,19,845,185,68,97};
	int length = 9;
	int* res_array = bucket.bucket_sort(primary_array,length);
	bucket.delete_node(231);
	int* res_array2 = bucket.bucket_sort(primary_array,bucket.length());
	copy(res_array2,res_array2 + length,ostream_iterator<int>(cout,"\n"));
	return 0;
}
