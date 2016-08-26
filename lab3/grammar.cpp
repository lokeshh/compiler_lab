#include <iostream>

using namespace std;

int main(void)
{
  cout << "Grammar: " << endl;
  cout << "E -> E+T | T";
  cout << "T -> T*F | F";
  cout << "F -> (E) | id";


}

bool id()
{
  
}