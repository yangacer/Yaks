#ifndef _VARIANT_TYPE_H
#define _VARIANT_TYPE_H
#include "boost/variant/variant.hpp"
#include "yaks/export.hpp"
#include "yaks/strref.hpp"

namespace Yaks {
	
	typedef boost::variant <
		char, unsigned char, 
		int, unsigned int,
		double,
		long long, unsigned long long,
		std::string, str_ref 
			> Variant; 
}

#endif 
