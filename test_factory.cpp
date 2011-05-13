#include "vfactory.h"
#include <iostream>


int main()
{
	using Record::Variant;
	using Record::factory;

	//Record::factory_register<std::string>("STR");
	//Record::Variant v (Record::factory_create("STR"));
	
	Variant v (factory::Instance().create("STR"));
	
	std::cout<<v<<"\n";
	
	return 0;	
}
