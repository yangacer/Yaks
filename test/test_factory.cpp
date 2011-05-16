#include "yaks/vfactory.hpp"
#include <iostream>


int main()
{
	using Yaks::Variant;
	using Yaks::factory;

	//Yaks::factory_register<std::string>("STR");
	//Yaks::Variant v (Yaks::factory_create("STR"));
	
	Variant v (factory::Instance().create("STR"));
	
	std::cout<<v<<"\n";
	
	return 0;	
}
