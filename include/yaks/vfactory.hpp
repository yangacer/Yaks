#ifndef _VFACTORY_HPP
#define _VFACTORY_HPP

#include <string>
#include "boost/unordered_map.hpp"
#include "loki/Singleton.h"
#include "yaks/export.hpp"
#include "yaks/variant.hpp"

namespace Yaks
{
	class YAKS_EXPORT factory {
	public:
		static Variant const&
		create(char const *type_str);
	};

}// end of namespace Yaks



#endif // end of header guard 

