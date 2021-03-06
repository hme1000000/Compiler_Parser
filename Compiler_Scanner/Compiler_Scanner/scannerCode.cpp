#include <iostream>
using namespace std;
# include <string>
#include <fstream>
#include <cstdio>

#define START 0
#define INCOMMENT 1
#define INNUM 2
#define INID 3
#define INASSIGN 4
#define DONE 5


string scan(string &input)
{
	input += '.';
	int state = START;
	int previous;
	string scanned = "";
	string output;
	int i = 0;
	while(i < input.length())
	{
		switch(state)
		{
		case START:
			{
				if(input.substr(i,1) == " " ||input.substr(i,1) == "\n"||input.substr(i,1) == "\t"||input.substr(i,1) == "\r")
				{
					output += input.substr(i,1);
					state = START;
				}
				else if((input.substr(i,1) >= "0" && input.substr(i,1) <= "9"))
				{
					state = INNUM;
					scanned += input.substr(i,1);
				}
				else if ((input.substr(i,1) >= "a"&& input.substr(i,1) <= "z")||(input.substr(i,1) >= "A"&& input.substr(i,1) <= "Z"))
				{
					state = INID;
					scanned += input.substr(i,1);
				}
				else if (input.substr(i,1) == ":")
				{
					state = INASSIGN;
					scanned += input.substr(i,1);
				}
				else if (input.substr(i,1) == "{")
				{
					state = INCOMMENT;
				}
				else
				{
					state = DONE;
					scanned += input.substr(i,1);
				}
				i++;
				previous = START;
				break;
			}

		case INCOMMENT:
			{
				if(input.substr(i,1) != "}")
				{
					state = INCOMMENT;
				}
				else
				{
					state = START;
				}
				previous = INCOMMENT;
				i++;
				break;
			}
		case INNUM:
			{
				if(input.substr(i,1) >= "0" && input.substr(i,1) <= "9")
				{
					state = INNUM;
					scanned += input.substr(i,1);
					i++;
				}
				else
				{
					state = DONE;
				}
				previous = INNUM;
				break;
			}
		case INID:
			{
				if ((input.substr(i,1) >= "a"&& input.substr(i,1) <= "z")||(input.substr(i,1) >= "A"&& input.substr(i,1) <= "Z"))
				{
					state = INID;
					scanned += input.substr(i,1);
					i++;
				}
				else
				{
					state = DONE;
				}
				previous = INID;
				break;
			}
		case INASSIGN:
			{
				if(input.substr(i,1) == "=")
				{
					scanned += input.substr(i,1);
					state = DONE;
					i++;
				}
				else
				{
					state = DONE;
				}
				previous = INASSIGN;
				break;
			}
		case DONE:
			{
				if(previous == START)
				{
					if (scanned == ("+")||scanned ==("-")||scanned ==("*")||scanned ==("/")||scanned ==("(")
						||scanned ==(")")||scanned ==("=")||scanned ==("<")||scanned ==(";"))
					{
						//cout<<endl<<" ("<<scanned<<") : (Special Symbol)"<<endl;						
						output += scanned;
					}
				}
				if(previous == INNUM)
				{
					//cout<<endl<<" ("<<scanned<<") : (number)"<<endl;
					output += "number";
				}
				if(previous == INID)
				{
					if(scanned == ("if")||scanned ==("then")||scanned ==("else")||scanned ==("end")||scanned ==("repeat")
						||scanned ==("until")||scanned ==("read")||scanned ==("write"))
					{
						//cout<<endl<<" ("<<scanned<<") : (Reserved Word)"<<endl;
						output += scanned;
						//input.replace(input.find(scanned,i),6,"number");
					}
					else
						{
						//cout<<endl<<" ("<<scanned<<") : (Identifier)"<<endl;
						output += "identifier";
					}
				}
				if(previous == INASSIGN)
				{
					if(scanned == ":=")
					{
						//cout<<endl<<" ("<<scanned<<") : (Special Symbol)"<<endl;
						output += scanned;
					}
			
					else if (scanned == ("+")||scanned ==("-")||scanned ==("*")||scanned ==("/")||scanned ==("(")
						||scanned ==(")")||scanned ==("=")||scanned ==("<")||scanned ==(";"))
					{
						//cout<<endl<<" ("<<scanned<<") : (Special Symbol)"<<endl;
						output += scanned;
					}
					else
					{
						//cout<<endl<<"Syntax Error"<<endl;
						output += "Syntax Error";
					}
				}
				state = START;
				scanned = "";
				previous = DONE;
				break;
			}
		default:
			{
				i++;
			}
		}		
		
	}
	return output;
}

int main()
{
	ifstream myfile ("tiny_sample_code.txt");
	freopen("scanner_output.txt","w",stdout);
	string line;
	string input = "";
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
		  input += line;;
		}
		myfile.close();
	}
	string output = scan(input);
	cout<<endl<<output<<endl;
}
