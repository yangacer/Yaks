#ifndef _VARIANT_TYPE_H
#define _VARIANT_TYPE_H
#include "boost/shared_ptr.hpp"
#include "boost/variant.hpp"
#include "yaks/strref.hpp"

#ifdef BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT
#error Can not use recursive record
#endif

namespace Yaks {
	
	
	struct record;

	typedef boost::variant<
		char, unsigned char, 
		int, unsigned int,
		double,
		long long, unsigned long long,
		std::string, str_ref,
		boost::shared_ptr<record>
	> Variant; 
}

#endif 
