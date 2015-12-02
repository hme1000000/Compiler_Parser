#include <iostream>
#include <string>
using namespace std;

void program(string token);
void stmt_sequence(string token);
void statement(string token);
////////////////////////////////////////////////////////////
void error()
{
	cout<<endl<<"Match Error"<<endl<<endl;
	exit(1);
}
//////////////////////////////////////////////////////////
void match(string &token,string expected)
{
	//if(token.substr(0,expected.size()) ==(expected))
	if(token.compare(expected))
	{
		token = token.substr(expected.size(),token.size()-expected.size());
		cout<<endl<<expected<<" found"<<endl;
	}
	else
	{
		error();
	}
}
//////////////////////////////////////////////////////////
void program(string &token)
{
	stmt_sequence(token);
	cout<<endl<<"Program found"<<endl;
}
///////////////////////////////////////////////////////////
void stmt_sequence(string &token)
{
	statement(token);
	while(token.compare(";"))
	{
		match(token,";");
		statement(token);		
	}
	cout<<endl<<"Statement Sequence found"<<endl;
}
/////////////////////////////////////////////////////////
void statement(string &token)
{
	if(token.compare("if"))
	{
		if_stmt(token);
	}
	else if(token.compare("repeat"))
	{
		repeat_stmt(token);
	}
	else if(token.compare("identifier"))
	{
		assign_stmt(token);
	}
	else if(token.compare("read"))
	{
		read_stmt(token);
	}
	else if(token.compare("write"))
	{
		write_stmt(token);
	}
	else
	{
		error();
	}
	cout<<endl<<"Statement found"<<endl;
}
///////////////////////////////////////////////////////////////
void if_stmt(string &token)
{
	match(token,"if");
	exp(token);
	match(token,"then");
	stmt_sequence(token);
	if(token.compare("else"))
	{
		match(token,"else");
		stmt_sequence(token);
	}
	match(token,"end");
	cout<<endl<<"If Statement found"<<endl;
}
//////////////////////////////////////////////////////////////
void repeat_stmt(string &token)
{
	match(token,"repeat");
	stmt_sequence(token);
	match(token,"until");
	exp(token);
	cout<<endl<<"repeat Statement found"<<endl;
}
///////////////////////////////////////////////////////////////
void assign_stmt(string &token)
{
	match(token,"identifier");
	match(token,":=");
	exp(token);
	cout<<endl<<"Assignment Statement found"<<endl;
}
///////////////////////////////////////////////////////////////

void main()
{
	string h = "hussein";
	match(h,"h");
}

