

#include<bits/stdc++.h>
#include<ctype.h>
using namespace std;
vector<string> ax,ay;
map<int,map<char,string> > m;

void initialise()
{
ax.push_back("S");
ax.push_back("AA");
ax.push_back("aA");
ax.push_back("b");

ay.push_back("S");
ay.push_back("S");
ay.push_back("A");
ay.push_back("A");


m[0]['a']="S3";
m[0]['b']="S4";
m[0]['$']="X";
m[0]['S']="1";
m[0]['A']="2";

m[1]['a']="X";
m[1]['b']="X";
m[1]['$']="C";
m[1]['S']="X";
m[1]['A']="X";

m[2]['a']="S6";
m[2]['b']="S7";
m[2]['$']="X";
m[2]['S']="X";
m[2]['A']="5";

m[3]['a']="S3";
m[3]['b']="S4";
m[3]['$']="X";
m[3]['S']="X";
m[3]['A']="8";

m[4]['a']="R3";
m[4]['b']="R3";
m[4]['$']="X";
m[4]['S']="X";
m[4]['A']="X";

m[5]['a']="X";
m[5]['b']="X";
m[5]['$']="R1";
m[5]['S']="X";
m[5]['A']="X";

m[6]['a']="S6";
m[6]['b']="S7";
m[6]['$']="X";
m[6]['S']="X";
m[6]['A']="9";

m[7]['a']="X";
m[7]['b']="X";
m[7]['$']="R3";
m[7]['S']="X";
m[7]['A']="X";

m[8]['a']="R2";
m[8]['b']="R2";
m[8]['$']="X";
m[8]['S']="X";
m[8]['A']="X";

m[9]['a']="X";
m[9]['b']="X";
m[9]['$']="R2";
m[9]['S']="X";
m[9]['A']="X";




}
int main()
{ vector<int> stack1;
vector<char> stack2;
string a;
char c='n';
int ip=0;
cout<<"\n enter the string to be parsed ";
cin>>a;
a.append("$");


initialise();


a.append("$");

stack1.push_back(0);
cout<<"\n Stack1 \t stack2 \t action ";
while(c=='n')
{
cout<<"\n";
for(int i=0;i<stack1.size();i++)
cout<<stack1[i];
cout<<"\t\t";
for(int j=0;j<stack2.size();j++)
cout<<stack2[j];
int state=stack1.back();
char curChar=a[ip];
string b=m[state][curChar];
if(b[0]=='S')
{
int x=b[1]-'0';
stack2.push_back(a[ip++]);
stack1.push_back(x);
cout<<"\t\t"<<"Shift";

}
else
if(b[0]=='R')
{
int x=b[1]-'0';
string p=ax[x];
int len=p.size();
for(int i=0;i<len;i++)
{
stack1.pop_back();
stack2.pop_back();

}
string aay=ay[x];
stack2.push_back(aay[0]);
string ch=m[stack1.back()][aay[0]];


int ch1=ch[0]-'0';
stack1.push_back(ch1);
cout<<"\t\t Reduce ";

}
else
if(b[0]=='C')
{
cout<<"\n string parsed ";
c=='y';
break;
}
else
if(b[0]=='X')
{
cout<<"\n string can not be parsed ";
return 0;
}





}
return 0;



}





