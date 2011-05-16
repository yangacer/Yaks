#include "record.hpp"
#include "rschema.hpp"

#include <vector>
#include <iostream>

int
main()
{
	using std::cout;
	using std::vector;
	using Yaks::record;
	using Yaks::rschema;

	rschema schema;
	record r;
	
	schema.define_field("name", "STR");
	schema.define_field("age", "UINT");
	
	schema.make(r);

	vector<record> rv(3, r);
	
	rv[0].fromString("name", "acer");
	rv[0].fromString("age", "21");
	rv[1].fromString("name", "yang");
	rv[1].fromString("age", "24");

	int b = rv[0].compare("age", 21u);
	cout<<b<<"\n";
	
	b = rv[0].compare("age", rv[1]);
	cout<<b<<"\n";

	cout<<rv[0]["name"]<<" "<<
		rv[0]["age"]<<"\n";
	
	return 0;	
}
