#include "BinaryTree.h"
#include <string>

using namespace std;

class testtree{
	public:
		int weight;
		string value;
};

int main(){
	btree<testtree> bt;	

	testtree node1;
	node1.weight = 20;
	node1.value = "node1";
	bt.addnode(node1);

	testtree node2;
	node2.weight = 25;
	node2.value = "node2";
	bt.addnode(node2);

	testtree node3;
	node3.weight = 18;
	node3.value = "node3";
	bt.addnode(node3);

	testtree node4;
	node4.weight = 89;
	node4.value = "node4";
	bt.addnode(node4);

	testtree node5;
	node5.weight = 76;
	node5.value = "node5";
	bt.addnode(node5);

	testtree node6;
	node6.weight = 33;
	node6.value = "node6";
	bt.addnode(node6);
	
	bt.delnode(20);

	bt.printtree();
	return 0;
}
