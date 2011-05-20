#ifndef _VFACTORY_HPP
#define _VFACTORY_HPP

#include <string>
#include "boost/unordered_map.hpp"
#include "loki/Singleton.h"
#include "yaks/export.hpp"
#include "yaks/variantType.hpp"

namespace Yaks
{
	/*
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
	*/

	class YAKS_EXPORT factory {
	public:
		static Variant const&
		create(char const *type_str);
	};

}// end of namespace Yaks



#endif // end of header guard 

