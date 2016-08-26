// To build a program to find address of a substring in a string

#include <iostream>
#include <string>

using namespace std;

void find_addresses(string str, string substr);
void match_at_address(string str, string substr, int index);
bool compare_two_strings(string str, string substr, int at, int length);

int main(void)
{
	// Accept string
	cout << "Input a string please:" << endl;
	string str;
	getline(cin, str);
	// cout << str;

	// Accept substring
	cout << "Input a sub string to search for:" << endl;
	string substr;
	getline(cin, substr);
	// cout << substr;

	// Find addresses
	find_addresses(str, substr);
}

void find_addresses(string str, string substr)
{
	for (int i = 0; i <= str.length() - substr.length(); i++)
	{
		if (compare_two_strings(str, substr, i, substr.length()))
		{
			cout << "Found match at position: " << i << endl;
		}
	}
}

void match_at_address(string str, string substr, int index)
{
	// cout << "Current index = " << index << endl;
	if (compare_two_strings(str, substr, index, substr.length()))
	{
		cout << "Found match at position: " << index << endl;
	}
}

bool compare_two_strings(string str, string substr, int at, int length)
{
	if ((at != 0) && str[at-1] != ' ')
	{
		return false;
	}
	for (int i = 0; i < length; i++)
	{
		// cout << substr[i] <<  << endl;
		if (substr[i] != str[i+at])
		{
			return false;
		}
	}
	if (((at+length) != (str.length())) && (str[at+length] != ' '))
	{
		return false;
	}
	return true;
}
