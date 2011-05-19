#ifndef _VFACTORY_HPP
#define _VFACTORY_HPP

// #include <map>
#include <string>
#include "boost/variant/variant.hpp"
#include "boost/unordered_map.hpp"
#include "yaks/export.hpp"
#define LOKI_SINGLETON_EXPORT YAKS_EXPORT
#include "loki/Singleton.h"
#include "yaks/variantType.hpp"

namespace Yaks
{
	
	struct YAKS_EXPORT factory_
	{
		template<class T> friend struct Loki::CreateUsingNew;

		typedef boost::unordered_map<std::string, Variant> Storage;

		
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
		factory_();
		factory_(factory_ const &cp);
		factory_& operator = (factory_ const &cp);

		Storage storage_;
	};

	typedef Loki::Singleton<factory_> factory;


}// end of namespace Yaks



#endif // end of header guard 

