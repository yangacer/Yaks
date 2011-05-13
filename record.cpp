#include "record.h"

namespace Record
{

	record::record()
	: schema_(0)
	{}

	record::record(record const &cp)
	: schema_(cp.schema_), schema_ver_(cp.schema_ver_)
	{
		if(this != &cp)
			vals_ = cp.vals_;	
	}

	record& 
	record::operator=(record const &cp)
	{
		if(this == &cp)
			return *this;

		schema_ = cp.schema_;
		schema_ver_ = cp.schema_ver_;

		vals_ = cp.vals_;

		return *this;
	}

	record::~record()
	{}

} // end of namespace Record
