#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

class Test{
	public:
		int a;
		string b;
		string *c;
		Test(string s):a(0),b("chemical"){c = new string(s);}
		~Test(){delete c;}
};

int main(){
	{
		Test test("abc");
		FILE* fp = fopen("test.cc","w+");
		fwrite(&test,sizeof(test),1,fp);
		fclose(fp);
	}
	Test *test_p = NULL;
	FILE* fp = fopen("test.cc","r");
	fread(test_p,sizeof(Test),1,fp);
	cout << *(test_p->c) << endl;
	return 0;
}
