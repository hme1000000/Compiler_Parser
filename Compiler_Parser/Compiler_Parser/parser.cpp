#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
using namespace std;

void program(string &token);
void stmt_sequence(string &token);
void statement(string &token);
void if_stmt(string &token);
void repeat_stmt(string &token);
void assign_stmt(string &token);
void read_stmt(string &token);
void write_stmt(string &token);
void exp(string &token);
void comparison_op(string &token);
void simple_exp(string &token);
void addop(string &token);
void term(string &token);
void mulop(string &token);
void factor(string &token);
////////////////////////////////////////////////////////////
void error()
{
	cout<<endl<<"Match Error"<<endl<<endl;
	exit(1);
}
//////////////////////////////////////////////////////////
void match(string &token,string expected)
{
	if(token.substr(0,expected.size()) ==(expected))
	{
		if(token.size()>expected.size())
		{
			token = token.substr(expected.size(),token.size()-expected.size());
		}
		//cout<<endl<<expected<<" found"<<endl;
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
	while(token.substr(0,1)==(";"))
	{
		match(token,";");
		statement(token);		
	}
	//cout<<endl<<"Statement Sequence found"<<endl;
}
/////////////////////////////////////////////////////////
void statement(string &token)
{
	if(token.substr(0,2) ==("if"))
	{
		if_stmt(token);
	}
	else if(token.substr(0,6) ==("repeat"))
	{
		repeat_stmt(token);
	}
	else if(token.substr(0,10) ==("identifier"))
	{
		assign_stmt(token);
	}
	else if(token.substr(0,4) ==("read"))
	{
		read_stmt(token);
	}
	else if(token.substr(0,5) ==("write"))
	{
		write_stmt(token);
	}
	else
	{
		error();
	}
	//cout<<endl<<"Statement found"<<endl;
}
///////////////////////////////////////////////////////////////
void if_stmt(string &token)
{
	match(token,"if");
	exp(token);
	match(token,"then");
	stmt_sequence(token);
	if(token.substr(0,4) ==("else"))
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
void read_stmt(string &token)
{
	match(token,"read");
	match(token,"identifier");
	cout<<endl<<"Read Statement found"<<endl;
}
///////////////////////////////////////////////////////////////
void write_stmt(string &token)
{
	match(token,"write");
	exp(token);
	cout<<endl<<"Write Statement found"<<endl;
}
//////////////////////////////////////////////////////////////
void exp(string &token)
{
	simple_exp(token);
	if(token.substr(0,1) ==("<")||(token.substr(0,1) ==("=")))
	{
		comparison_op(token);
		simple_exp(token);
	}
	//cout<<endl<<"Expression found"<<endl;
}
////////////////////////////////////////////////////////////////
void comparison_op(string &token)
{
	if(token.substr(0,1)==("<"))
	{
		match(token,"<");
	}
	else
	{
		match(token,"=");
	}
	//cout<<endl<<"Comparison Operator found"<<endl;
}
///////////////////////////////////////////////////////////////////
void simple_exp(string &token)
{
	term(token);
	while(token.substr(0,1)==("+")||token.substr(0,1)==("-"))
	{
		addop(token);
		term(token);
	}
	//cout<<endl<<"Simple Expression found"<<endl;
}
//////////////////////////////////////////////////////////////////
void addop(string &token)
{
	if(token.substr(0,1)==("+"))
	{
		match(token,"+");
	}
	else
	{
		match(token,"-");
	}
	//cout<<endl<<"Add Operator found"<<endl;
}
//////////////////////////////////////////////////////////////////
void term(string &token)
{
	factor(token);
	while(token.substr(0,1)==("*")||token.substr(0,1)==("/"))
	{
		mulop(token);
		factor(token);
	}
	//cout<<endl<<"Term found"<<endl;
}
//////////////////////////////////////////////////////////////////
void mulop(string &token)
{
	if(token.substr(0,1)==("*"))
	{
		match(token,"*");
	}
	else
	{
		match(token,"/");
	}
	//cout<<endl<<"Multiplication Operator found"<<endl;
}
///////////////////////////////////////////////////////////////////
void factor(string &token)
{
	if(token.substr(0,1)==("("))
	{
		match(token,"(");
		exp(token);
		match(token,")");
	}
	else if(token.substr(0,6)==("number"))
	{
		match(token,"number");
	}
	else if(token.substr(0,10)==("identifier"))
	{
		match(token,"identifier");
	}
	else
	{
		error();
	}
	//cout<<endl<<"Factor found"<<endl;
}
///////////////////////////////////////////////////////////////
void remove_spaces(string &input)
{
	string output = "";
	for(int i=0 ; i<input.size();i++)
	{
		if(input.substr(i,1) != " " && input.substr(i,1) !="\n" && input.substr(i,1) !="\t" && input.substr(i,1) !="\r")
		{
			output += input.substr(i,1);
		}
	}
	input = output;
}
///////////////////////////////////////////////////////////////


void main()
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
	remove_spaces(input);
	program(input);
}

