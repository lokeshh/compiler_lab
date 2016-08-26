#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void)
{
  int n;
  cout << "Enter number of productions in grammar: " << endl;
  cin >> n;
  cin.ignore();
  for (int t = 0; t < n; t++)
  {
    string input;
    getline(cin, input);
    string left;
    vector<string> right(2, "");
    int z = 0;
    left = input[0];
    for (int i = 1; i < input.length(); i++)
    {
      if ((input[i] != '|') && (input[i] != ' ') && (input[i] != '-') &&
          (input[i] != '>'))
      {
        right[z] += input[i];
      }
      else if (input[i] == '|')
      {
        z++;
      }
    }
    // Check for Left factoring
    cout << "\n" << endl;
    if (left[0] == right[0][0])
    {
      cout << "Production is left recursive." << endl;
      cout << "Producation with removed left recursion is: " << endl;
      cout << left[0] << " -> " << right[1] << left[0] << "'" << endl;
      right[0].erase(right[0].begin());
      cout << left[0] << "'" << " -> " << right[0] << left[0] << "'" <<
        " | _" << endl;
    }
    else
    {
      cout << "This production is left recursive free." << endl;
    }

    // Check for Left Recursion
    cout << "\n" << endl;
    if (right[0][0] == right[1][0])
    {
      cout << "Production is left factored." << endl;
      cout << "Production with removed left factoring is: " << endl;
      int c = 0;
      string common;
      while (right[0][c] == right[1][c])
      {
        common += right[0][c];
        c++;
        right[0].erase(right[0].begin());
        right[1].erase(right[1].begin());
        if ((c == right[0].length()) || (c == right[1].length()))
        {
          break;
        }        
      }
      c--;
      cout << left[0] << " -> " << common << left[0] << "'" << endl;
      cout << left[0] << "'" << " -> " << right[0] << " | " << right[1] << endl;
    }
    else
    {
      cout << "This production is left factoring free." << endl;
    }
  }
}