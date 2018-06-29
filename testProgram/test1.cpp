// this is check whether variable and function can be the same name, result: NO!!


#include<iostream>
using namespace std;

class T{
  private:
	  int num;
  public:
	  T(int n): num(n) {}
	  int getNum(void) const { return num; }
};

int main(){
	T t1(5);
	cout << t1.getNum() << endl;
}
