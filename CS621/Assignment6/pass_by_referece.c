#include <iostream>

using namespace std;

void copy (int& a, int& b, int& c){
	a *= 2;
	b *= 2;
	c *= 2;

}

void q9(){
	int x = 20;
	int y = 60;
	int *p1 = &x;
	int *p2 = &y;
	p1 = p2;
	cout << *p1 << " " << *p2 << endl;
}

int main(){
	int x=1, y=3, z=7;
	copy(x, y,z);
	cout << x;
	cout << y;
	cout << z;
	cout << endl;
	q9();
	return 0;
}