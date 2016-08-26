#include <iostream>
#include <string>

using namespace std;

int main(void)
{
	string a = "hel";
	string b = "abc";
	string c = "hel";
	cout << (a == b) << endl;
	cout << (b == c) << endl;
	cout << (a == c);
}
