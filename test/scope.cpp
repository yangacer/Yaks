#include "yaks/record.hpp"
#include "yaks/rscope.hpp"
#include "yaks/rschema.hpp"
#include <iostream>

using namespace Yaks;
using namespace std;

void func()
{
	record r;
	if(!r){
		cerr<<"record's schema is undefined\n";	
		return;
	}

	r["name"] = "acer";
	r["age"] = 18;
	
	cout<<r["name"]<<" "<<r["age"]<<endl;

}

int main()
{
	rschema	rs;
	rs.define_field("name", "STR");
	rs.define_field("age", "UINT");
	
	func();  

	rscope scope(&rs);
	func();

	return 0;
}
