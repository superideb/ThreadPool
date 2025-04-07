#include <iostream>
using namespace std;
void func_1(int& i)
{
	int j = i;
	for (; j < 2 * i; ++j)
	{
		cout << j << endl;
	}
	cout << "-----------------------" << endl;
	i = j;
}
int main() {

}