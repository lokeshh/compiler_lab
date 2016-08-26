// Replace a word by another word

#include <iostream>
#include <string>

using namespace std;

void match_and_replace(string str, string substr, string replace_word);
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

	cout << "Input the replacing word: " << endl;
	string replace_word;
	getline(cin, replace_word);

  match_and_replace(str, substr, replace_word);
}

void match_and_replace(string str, string substr, string replace_word)
{
	string new_str;
	new_str = "";
	int i = 0;
	while (i <= (str.length() - substr.length()))
		{
		if (compare_two_strings(str, substr, i, substr.length()))
		{
			cout << "Found match at position: " << i << endl;
			i += substr.length();
			new_str = new_str + replace_word;
		}
		else
		{
			new_str = new_str + str[i];
			i += 1;
		}
		// cout << new_str << endl;
	}

	while (i < str.length())
	{
		new_str += str[i];
		i += 1;
	}
	cout << new_str << endl;
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