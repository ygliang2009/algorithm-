#ifndef _SERILIZER_H
#define _SERILIZER_H

#include <iostream>

class serial_node{
	public:
		char a;
		int b;
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
