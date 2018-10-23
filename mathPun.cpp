#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	string startNum;
	string current;
	string next = "";
	
	int iteration;
	
	cout << "Starting Number: ";
	cin >> startNum;
	cout << "Iterations: ";
	cin >> iteration;
	
////////////////////////////////////////////////////////////////////////
	
	current = startNum;
	cout <<"0: " << startNum << endl;
	
////////////////////////////////////////////////////////////////////////	
	
	char first = ' ';
	char cnum;
	
	int count;
	
	for(int iter = 0; iter < iteration; iter++)
	{
		int currentL = current.length();
		cout << iter + 1 << ": ";
		
		for(int i = 0; i <= currentL; i++)
		{
			cnum = current[i];
			
		
			if(i == 0)
			{
				first = cnum;
				count = 0;
			}
			
			if(cnum == first)
			{
				count++;
			}
			
			if(cnum != first)
			{
				stringstream ss;
				ss << count;
				string str = ss.str();
					
				next += str;
				next += first;
				count = 1;
				first = cnum;
			}
		}
		cout << next << endl;
		current = next;
		next = "";
	}
	
	return 0;
}
