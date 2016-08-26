#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string remove_comments(string program)
{
	string new_program;
	int i = 0;
	// Remove comments
	while (i < program.length())
	{
		if ((program[i] == '/') && (program[i+1] == '/'))
		{
			while (program[i] != '\n')
			{
				i += 1;
			}
		}
		else
		{
			new_program += program[i];
		}
		i++;
	}
	return new_program;
}

string convert_tab_new_lines_to_spaces(string program)
{
	string new_program;
	int i = 0;
	while (i < program.length())
	{
		if ((program[i] == '\t') || (program[i] == '\n'))
		{
			new_program += ' ';
		}
		else
		{
			new_program += program[i];
		}
		i++;
	}
	return new_program;
}

string remove_redundant_spaces(string program)
{
	string new_program;
	// cout << program;
	int i = 0;
	while (i < program.length())
	{
		if (program[i] == ' ')
		{
			while (((i+1) < program.length()) && (program[i+1] == ' '))
			{
				i++;
			}
			new_program += ' ';
		}
		else
		{
			new_program += program[i];
		}
		i++;
	}
	return new_program;
}

string sub(string program, int i, int j)
{
	string sub_string;
	for (int x = i; x <= j; x++)
	{
		sub_string += program[i];
	}
	return sub_string;
}

bool is_number(string program, int i, int j)
{
	// True if program from i to j is numeric
	int x = i;
	while (x <= j)
	{
		if (!(('0' <= program[x]) && (program[x] <= '9')))
		{
			return false;
		}
		x++;
	}
	return true;

}

bool is_keyword(string program, int i, int j)
{
	// True if program from i to j is keyword
	string sub_string = sub(program, i, j);
	return ((sub_string == "if") ||
		(sub_string == "else") ||
		(sub_string == "else if")
	);
}

bool is_identifier(string program, int i, int j)
{
	// cout << i << ' ' << j << endl;
	int x = i;
	while (x <= j)
	{
		if (!(('a' <= program[x]) && (program[x] <= 'z')))
		{
			return false;
		}
		x++;
	}
	// cout << program[j] << endl;
	return true;
}

bool is_brackets(string program, int i, int j)
{
	return ((i == j) && ((program[i] == '(') ||
		(program[i] == ')'))
	);
}

bool is_operator(string program, int i, int j)
{
	return ((i == j) && ((program[i] == '+') ||
	 (program[i] == '-')||
	 (program[i] == '*')||
	 (program[i] == '/'))
	);
}

bool is_semi_colon(string program, int i, int j)
{
	return ((i == j) && (program[i] == ';'));
}

bool is_white_space(string program, int i, int j)
{
	return ((i == j) && (program[i] == ' '));
}

bool is_assignment(string program, int i, int j)
{
	return ((i == j) && (program[i] == '='));
}

bool is_comparison(string program, int i, int j)
{
	string s = sub(program, i, j);
	return ((s == "==") ||
		(s == "<=")||
		(s == "<") ||
		(s == ">") ||
		(s == ">=")
	);
}

void write_token(string program, int i, int j, string type)
{
	cout << '<' << type << ":\"";
	for (int x = i; x <= j; x++)
	{
		cout << program[x];
	}
	cout << "\">" << endl;
}

int main(void)
{
	fstream in_file("prog.raw");
	fstream out_file("prog.res");
  string program, line;
  while (!in_file.eof())
  {
  	getline(in_file, line);
  	program += '\n';
  	program += line;
  }
  program = ' ' + program + ' ';
  // Remove comments
  program = remove_comments(program);
  // convert newline and tabs to single space;
  program = convert_tab_new_lines_to_spaces(program);
  // cout << program << endl;
  // Remove redundant spaces;
  program = remove_redundant_spaces(program);

  string new_program;
  for (int i = 1; i < program.length()-1; i++)
  {
  	new_program += program[i];
  }
  program = new_program;

  cout << program << endl << endl << endl;

  int i = 0;
  int n = program.length()-1;
  int j = n;

  while (j >= i)
  {
  	// cout << i << ' ' << j << endl;
  	// Check for a keyword first
  	if (is_keyword(program, i, j))
  	{
  		write_token(program, i, j, "Keyword");
  		i = j+1;
  		j = n;
  	}

  	// Check for a number
  	else if (is_number(program, i, j))
  	{
  		write_token(program, i, j, "Number");
  		i = j+1;
  		j = n;
  	}

  	// Check for identifier
  	else if (is_identifier(program, i, j))
  	{
  		write_token(program, i, j, "Identifier");
  		i = j+1;
  		j = n;
  	}

  	// Check for comparison
  	else if (is_comparison(program, i, j))
  	{
  		write_token(program, i, j, "Comparison");
  		i = j+1;
  		j = n;
  	}

  	// Check for assignment
  	else if (is_assignment(program, i, j))
  	{
  		write_token(program, i, j, "Assignment");
  		i = j+1;
  		j = n;
  	}

  	// Check for operator
  	else if (is_operator(program, i, j))
  	{
  		write_token(program, i, j, "Operator");
  		i = j+1;
  		j = n;  		
  	}  	

  	// Check for brackets
  	else if (is_brackets(program, i, j))
  	{
  		write_token(program, i, j, "Brackets");
  		i = j+1;
  		j = n;  		
  	}

  	// Check for semicolon
  	else if (is_semi_colon(program, i, j))
  	{
  		write_token(program, i, j, "Semi Colon");
  		i = j+1;
  		j = n;    		
  	}

  	// Check for whitespace
  	else if (is_white_space(program, i, j))
  	{
  		write_token(program, i, j, "Whitespace");
  		i = j+1;
  		j = n;
   	}
  	else
  	{
  		j--;
  	}
  }
}

