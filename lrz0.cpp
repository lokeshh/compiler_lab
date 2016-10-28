#include <bits/stdc++.h>
using namespace std;
//S->AA
//A->aA
//A->b
char sdash='Z';
int termct = 0, ntermct=0;
int states = 6;

//pair<char,int> action[states+1][termct];
//int got[states+1][ntermct];


string p[10];
char pfirstchar[10];
int np;
map<char,int> nterm;
map<char,int> term;
map<char,int> :: iterator itr;
vector<char> ntermvec;
vector<char> termvec;
int ndfa = 1;
struct dfaa
{
	char dfap[20][50];
	int nprod; //number of productions in this state of dfa
	void dfazero();
	void maketr();
	void displayprod(int num);
}dfa[20];

void dfaa:: dfazero()
{
	// make dfa[0]
	nprod = 0;
	dfap[nprod][0] = 'Z'; dfap[nprod][1] = '-'; dfap[nprod][2] = '>';
	dfap[nprod][3] = ntermvec[0]; //start symbol
	nprod++;
	for(int i=0;i<np;i++)
	{
		int ind=0;
		for(int j=0;j<p[i].size();j++) // production i's characters
		{
			dfap[nprod][ind++] = p[i][j]; 
			if(p[i][j] == '>')
				dfap[nprod][ind++] = '.';			
		}
		nprod++;
	}
}
void dfaa:: maketr()
{
	// transitions for non-terminals
	
	for(int i=0;i<ntermct;i++)
	{
		dfaa temp;
		temp.nprod = 0;
		char sym = ntermvec[i];
		for(int j = 0; j<nprod;j++) // check all production for symbol after .
		{
			int len = strlen(dfap[j]), flag=0; // length of jth production
			// flag =1 means the production has . at the end
			// flag = 2 means the production has this nonterminal after dot
			// flag 0 means its contains something else after .
			for(int k=0;k<len;k++)
			{
				// now check for symbol after .
				if(dfap[j][k] == '.')
				{
					if(k == len-1) flag = 1; 
					else if(dfap[j][k+1] == sym) flag = 2;
					break;
				}
			}
			if(flag == 2)
			{
				// copy the production in temp with . shifted
				for(int k=0;k<len;k++)
				{
					temp.dfap[temp.nprod][k] = dfap[j][k];
					if(dfap[j][k-1] == '.') swap(temp.dfap[temp.nprod][k],temp.dfap[temp.nprod][k-1]);
				}
				temp.nprod++;
			}
		}
		// add the production of all non terminals(closure)
		vector<char> closure;
		for(int ii=0;ii<temp.nprod;ii++)
		{
			int flag=0, len= strlen(temp.dfap[ii]);
			char clossym;
			for(int j=0;j<len;j++)
			{
				if(temp.dfap[ii][j] == '.')
				{
					if(j == len-1) flag=0;
					else
					{
						clossym = dfap[ii][j+1];
						flag=1; // found
					}
					break;
				}
			}
			if(flag == 1)
			{
				if (find(closure.begin(), closure.end(),clossym)==closure.end()) // not present
					closure.push_back(clossym);
			}
		}
		for(int ii= 0;ii<closure.size();ii++)
		{
			char clossym = closure[ii];
			for(int j=0;j<np;j++)
			{
				if(clossym == pfirstchar[j])
				{
					// then add this production to temp with dot
					int ind=0;
					for(int k = 0;k<p[j].size();k++)
					{
						temp.dfap[temp.nprod][ind++]= p[j][k];
						if(p[j][k] == '>')
							temp.dfap[temp.nprod][ind++] = '.';
					}
					temp.nprod++;
				}
			}
		}
					
		// check if this state is already present or not
		int pflag=0;
		for(int j=0;j<ndfa;j++)
		{
			int present = 1;
			// compare dfa[j] with temp
			if(dfa[j].nprod == temp.nprod) 
			{
				for(int k=0;k<temp.nprod;k++) 
				{
					int notpresent=1;
					for(int l=0;l<dfa[j].nprod;l++)
					{
						if(strcmp(dfa[j].dfap[l], temp.dfap[l])==0 ) 
						{
							notpresent = 0;
							break;
						}
					}
					if(notpresent ==1)
					{
						present= 0; // this production is not present in this dfa
						break;
					}
				}
			}
			if(present == 1)
			{
				pflag = 1; break;
			}
		}
		if(pflag == 0) // it item set not present in dfa, add it
		{
			dfa[ndfa].nprod = temp.nprod;
			for(int j = 0;j<temp.nprod;j++)
			{
				strcpy(dfa[ndfa].dfap[j], temp.dfap[j] );	
			}
			ndfa++;
		}

	}
}
void dfaa:: displayprod(int num)
{
	cout<<"ITEM SET: "<<num<<endl;
	for(int i=0;i<nprod;i++)
	{
		cout<<dfap[i]<<endl;
	}
	cout<<endl;
}

int main()
{
	cout<<"Enter the number of productions followed by production rules:\n"; cin>>np;
	//string p[np+1];
	for(int i=0;i<np;i++)
	{
		cin>> p[i];
		pfirstchar[i] = p[i][0];
		for(int j=0;j<p[i].size();j++)
		{
			
			if( (p[i][j]>='a' && p[i][j]<='z') )
			{
				//its a terminal
				itr = term.find(p[i][j]);
				if(itr == term.end()) //terminal not found 
				{
					term[p[i][j]] = termct++;
					termvec.push_back(p[i][j]);
				}
			}
			else if(p[i][j]>='A' && p[i][j]<='Z')
			{
				itr = nterm.find(p[i][j]);
				if(itr == nterm.end()) //non terminal not found
				{
					nterm[p[i][j]] = ntermct++;
					ntermvec.push_back(p[i][j]);
				}
			}
		}
	}
	cout<<"Total Non-terminals = "<<ntermct<<endl;
	cout<<"Total terminals = "<<termct<<endl;
	termvec['$'] = termct+1;
	dfa[0].dfazero();
	dfa[0].displayprod(0);

	for(int i=0;i<ndfa;i++)
	{
		dfa[i].maketr();
	}
	cout<<ndfa<<endl;
	for(int i=0; i<ndfa;i++)
	{
		dfa[i].displayprod(i);
	}
	
	return 0;
}