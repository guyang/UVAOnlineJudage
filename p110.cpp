#include <iostream>
#include <string>
#include <list>
#include <cstdio>
using namespace std;

void _gen(list<char> &l, const string &s, int at);
void gen(int m);

int main()
{
	int n, m;
	cin >> n;

	for(int i = 0; i < n; i++)
	{
		cin >> m;
		gen(m);

		if (i != n-1)
			printf("\n");
	}

	return 0;
}

char chartable[] = "abcdefghijklmnopqrstuvwxyz";

/*
program sort(input,output);
var
a,b,c : integer;
begin
  readln(a,b,c);
  if a < b then
    if b < c then
      writeln(a,b,c)
    else if a < c then
      writeln(a,c,b)
    else
      writeln(c,a,b)
  else
    if a < c then
      writeln(b,a,c)
    else if b < c then
      writeln(b,c,a)
    else
      writeln(c,b,a)
end.
*/
void gen(int m)
{
	printf("%s", "program sort(input,output);\nvar\n");
	string dec(1,chartable[0]);
	for(int i = 1; i < m; i++) dec += "," + string(1,chartable[i]);
	printf("%s : integer;\nbegin\n  readln(%s);\n", dec.c_str(), dec.c_str());
	list<char> l;
	_gen(l, string(chartable, m), 0);
	printf("end.\n");
}

void _gen(list<char> &l, const string &s, int at)
{
	if(at >= s.length())
	{
		printf("%s", string(at+1, ' ').c_str());
		list<char>::iterator it = l.begin();
		printf("writeln(%c", *it);
		it++;
		for(; it != l.end(); it++) printf(",%c", *it);
		printf(")\n");
	}
	else
	{
		list<char>::iterator it = l.begin();

		while(1)
		{
			if(l.size() != 0)
			{
				printf("%s", string(at+1, ' ').c_str());
				if(it == l.begin())
					printf("if %c < %c then\n", s.at(at), *it);
				else if (it != l.end())
					printf("else if %c < %c then\n", s.at(at), *it);
				else
					printf("else\n");
			}

			l.insert(it, s.at(at));
			_gen(l, s, at+1);
			it = l.erase(--it);
			
			if (it == l.end())
				break;
			else
				it++; // points to next
		}
	}
}