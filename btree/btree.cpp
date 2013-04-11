#include "btree.h"

btreenode::btreenode():isleaf(true){
	content = new record[length];
	index  = new posindex[length];
}

btreenode::~btreenode(){
	if(index)
		delete[] index;
	if(content)
		delete[] content;
}

btree::btree(std::string pt){
	this->size = 0;
	this->path = pt;
	this->root = NULL;
}

btree::~btree(){
}

bool btree::root_init(){
	return false;
}

bool btree::insert_record(record *rc){
	btreenode *bt_p = root;
	int *offset = NULL;
	while(offset = bina_search(rc.weight,bt_p)){
		if(*offset == rc->weight){
			return false;
		}
		if(!bt_p->isleaf())
			bt_p = this->load_node(index + *offset);	
		else
			this->insert_data(rc);
	}	
}

record* find_record(int weight){
	return NULL;
}

bool delete_record(int weight){
	return false;
}

bool update_record(record *rc){
	return false;
}

int main(){
	btreenode bt_node;
	return 0;
}
