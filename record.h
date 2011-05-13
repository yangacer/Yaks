#ifndef _RECORD_H_
#define _RECORD_H_

#include <vector>
#include <string>

#include "boost/mpl/vector.hpp"
#include "boost/variant/variant.hpp"
#include "boost/variant/get.hpp"

#include "rschema.h"
#include "variantType.h"

namespace Record
{
	

	struct rschema;

	class record
	{
	friend struct rschema;
	public:
		record();
		
		record(record const &cp);
		
		~record();
		
		record &
		operator=(record const &cp);
		
		/*
		Variant&
		operator[](char const* field_name);

		Variant&
		operator[](unsigned int i);
		*/

		template<typename T>
		T&
		get(char const* field_name)
		{	return boost::get<T>(vals_[schema_->find(field_name)]); }

		template<typename T>
		T const&
		get(char const* field_name)
		{	return boost::get<T>(vals_[schema_->find(field_name)]); }
		
		template<typename T>
		void
		set(char const* field_name, T const & val)
		{	vals_[schema_->find(field_name)] = val; }

	private:
		std::vector<Variant> vals_;
		rschema *schema_;
		unsigned int schema_ver_;
	};

} // end of namespace Record

#endif
