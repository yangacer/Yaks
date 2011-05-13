#ifndef _VARIANT_TYPE_H
#define _VARIANT_TYPE_H
#include "boost/variant/variant.hpp"

namespace Yaks {

	typedef boost::variant<
		char, unsigned char, 
		int, unsigned int,
		double,
		long long, unsigned long long,
		std::string 
			> Variant; 
}

#endif 
