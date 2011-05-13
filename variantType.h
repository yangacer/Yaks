#ifndef _VARIANT_TYPE_H
#define _VARIANT_TYPE_H

namespace Record {

	typedef boost::variant<
		char, unsigned char, 
		int, unsigned int,
		double,
		long long, unsigned long long,
		std::string 
			> Variant; 
}

#endif 
