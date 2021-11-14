#include <iostream>

using namespace std;

void copy (int& a, int& b, int& c){
	a *= 2;
	b *= 2;
	c *= 2;

}

int main(){
	int x=1, y=3, z=7;
	copy(x, y,z);
	cout << x;
	cout << y;
	cout << z;
	return 0;
}