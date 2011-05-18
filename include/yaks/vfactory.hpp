#ifndef _VFACTORY_HPP
#define _VFACTORY_HPP

// #include <map>
#include <string>
#include "boost/variant/variant.hpp"
#include "boost/unordered_map.hpp"
#include "loki/Singleton.h"
#include "yaks/variantType.hpp"

namespace Yaks
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

	// TODO: deal with DLL/share lib
	typedef Loki::SingletonHolder<factory_> factory;


}// end of namespace Yaks

#endif // end of header guard 

