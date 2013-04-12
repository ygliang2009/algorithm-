#ifndef _SERILIZER_H
#define _SERILIZER_H

#include <iostream>

class serial_node{
	public:
		char a;
		int b;
		int s_len;
		char *s;
		serial_node():a(0),b(0),s_len(0),s(NULL){}
		virtual ~serial_node();
};

class serial_class{
	public:
		const static int length = LENGTH;
		serial_node serial_array[length];
		bool size(){
			return this->length;
		}
		bool serialize(std::string path);
		serial_node* unserialize(std::string path);
		serial_class(int length);
};
#endif
