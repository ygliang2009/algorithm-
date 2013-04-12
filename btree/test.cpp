#include <cstdio>
#include <iostream>

using namespace std;

class Test{
	public:
		char b;
		void seta(short a){this->a = a;}
		Test():b(0),c(0),a(0){}
		short a;
		char c;
};

int main(){
	{
		Test test[5];
		for(int i = 0; i < 5; i++){
			test[i].seta(i);
			test[i].b = 67 + i;
			test[i].c = i + 5;
		}
		//test.b = 'c';
		FILE* fp = fopen("test.cc","w+");
		fwrite(test,sizeof(Test),5,fp);
		//fseek(fp,SEEK_SET)
		fclose(fp);
	}
	Test test_p[5];
	FILE* fp = fopen("test.cc","r");
	fread(test_p,sizeof(Test),5,fp);
	int i = 0;
	for(int i = 0; i < 5;i++)
		cout << (test_p + i)->b  << endl;
	cout << sizeof(Test) << endl;
	return 0;
}
