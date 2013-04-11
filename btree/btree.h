#ifndef _BTREE_H
#define	_BTREE_H
#include <string>

typedef std::string posindex;

struct record{
	int weight;
	std::string value;
};

class btreenode{
	record *content;
   	static const int length = 100;
	posindex *index;
	bool isleaf;
	int size;	
	public:
		int getsize(){return size;}
		btreenode();
		virtual ~btreenode();
		bool addnode();
			
};

/*
 * record的增删改查
 */
class btree{
	int size;
	std::string path;
	bool root_init();
	public:
		int getsize(){return this->size;}
		btree(std::string);
		virtual ~btree();
		btreenode *root;
		bool insert_record(record *rc);		
		record* find_record(int weight);
		bool delete_record(int weight);
		bool update_record(record *rc);
};
#endif
