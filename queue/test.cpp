#include "Queue.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	Queue<string> queue;
	string s = "aa";
	string s2 = "bb";
	string s3 = "cc";
	queue.enqueue(s);
	queue.enqueue(s2);
	queue.enqueue(s3);
	while(queue.length() > 0)
		cout << queue.dequeue() << endl;; 
	return 0;
}
