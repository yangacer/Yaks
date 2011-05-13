#ifndef _VFACTORY_H
#define _VFACTORY_H

// #include <map>
#include <string>
#include "boost/variant/variant.hpp"
#include "boost/unordered_map.hpp"
#include "loki/Singleton.h"
#include "variantType.h"

namespace Record
{
	struct factory_
	{
		typedef boost::unordered_map<std::string, Variant> Storage;

		factory_();
		
		template<typename T>
		void join(char const *type_str)
		{
			if( storage_.end() != storage_.find(type_str) )
				return;
			storage_[type_str] = T(); 
	
		}

		Variant const&
		create(char const *type_str) const throw (char const*);

	private:
		Storage storage_;
	};

	typedef Loki::SingletonHolder<factory_> factory;

	/*
	static boost::unordered_map<std::string, Variant> factory;
	
	template<typename T>
	void 
	factory_register(char const *type_str)
	{
		if( factory.end() != factory.find(type_str) )
			return;
		factory[type_str] = T(); 
	}
	
	
	void
	register_default()
	{
		if(factory.size()) return;

		factory_register<int>("INT");
		
		
		factory_register<unsigned int>("UINT");
		
		factory_register<char>("CHAR");

		factory_register<unsigned char>("UCHAR");
		
		factory_register<double>("DOUBLE");

		
		factory_register<long long>("LLONG");

		factory_register<unsigned long long>("ULLONG");

		factory_register<std::string>("CHAR[]");
		factory_register<std::string>("STR");
		
	}
	

	inline Variant const&
	factory_create(char const *type_str) throw (char const*)
	{
		//register_default();
		
		boost::unordered_map<std::string, Variant>::iterator iter;

		if( factory.end() == (iter = factory.find(type_str)) )	
			throw "factory: unkown type\n";
		return iter->second;
	}
	*/

}// end of namespace Record

#endif // end of header guard 

