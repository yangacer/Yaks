#include "yaks/record.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <typeinfo>
#include <cstdio>

int
stricmp(std::string const &lhs, std::string const &rhs)
{
	/*
	std::string::size_type i = 0;
		n = lhs.size() > rhs.size() ? rhs.size() : lhs.size();

	const int diff = 'a' - 'A';
	int result = 0;
	while(i<n && lhs[i] == rhs[i]){
		result = lhs[i] - rhs[i];

		i++;
	}
	*/
	
}

int main()
{
	using namespace std;
	using namespace Yaks;

	try{

		rschema schema;
		record r;

		// setup schema
		schema.define_field("@U:", "STR");
		schema.define_field("@s:", "INT");
		
		// let record r use the schema just 
		schema.make(r);

		// set value when you know the types
		r.get<std::string>("@U:") = "abd";
		r.get<int>("@s:") = 1234;
		
		r.set<std::string>("@U:", "abd"); // equalevent
		r.set<int>("@s:", 1234);
		
		// output
		cout<<"record is initiated by abd, 1234\n";
		cout<<"@U:"<<r.toString("@U:")<<endl;
		cout<<"@s:"<<r.toString("@s:")<<endl;
		
		// set value when type is unknown
		cout<<"record is updated as def, 4567\n";
		r.fromString("@U:", "def");
		r.fromString("@s:", "4567");
		
		// output via write to ostream directly
		cout<<"@U:";
		r.writeTo(cout, "@U:");
		cout<<"\n";
		cout<<"@s:";
		r.writeTo(cout, "@s:");
		cout<<"\n";
		
		// compare methods
		bool cmpRt;
		cout<<"@s field is less than value 123"<<endl;
		cmpRt = r.compare<int>("@s:", 123) > 0; // cmpRt == true
		cout<<"compare result: "<<cmpRt<<endl;
		
		cout<<"compare @s field is equal to itself\n";
		cmpRt = r.compare("@s:", r) == 0; // cmpRt == true
		cout<<"compare result: "<<cmpRt<<endl;

		// schema serialization test
		stringstream ss;
		cout<<"serialized scheam\n"<<schema;
		ss<<schema;
		cout<<"deserialzation\n";
		rschema tmpSch;
		ss>>tmpSch;
		cout<<tmpSch;

	}catch(char const* msg){
		printf(msg);

	}
	

}
