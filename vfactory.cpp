#include "vfactory.h"

namespace Yaks
{
	factory_::factory_()
	: storage_()
	{
		join<int>("INT");
		join<unsigned int>("UINT");
		join<char>("CHAR");
		join<unsigned char>("UCHAR");
		join<double>("DOUBLE");
		join<long long>("LLONG");
		join<unsigned long long>("ULLONG");
		join<std::string>("CHAR[]");
		join<std::string>("STR");
	}
	

	Variant const&
	factory_::create(char const *type_str) const throw (char const*)
	{
		Storage::const_iterator	iter;
		
		if( storage_.end() == (iter = storage_.find(type_str)) )	
			throw "storage_: unkown type\n";
		return iter->second;

	}
	
}// end of Yaks namespace
