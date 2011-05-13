#ifndef _RSCHEMA_H
#define _RSCHEMA_H

#include <string>
#include <vector>
#include <iosfwd>
#include "boost/unordered_map.hpp"

typedef unsigned char FIELD_INDEX;


namespace Yaks
{
	struct record;
	struct rschema;

	std::ostream& operator<<(std::ostream& os, rschema &rs);
	std::istream& operator>>(std::istream& is, rschema &rs);


	struct rschema 
	{	
		friend std::ostream& operator<<(std::ostream& os, rschema &rs);
		friend std::istream& operator>>(std::istream& is, rschema &rs);

		template <class T, class U>
		struct IndexCont
		{
			typedef boost::unordered_map<T,U> Type;
		};

		typedef IndexCont<std::string, FIELD_INDEX>::Type Index;
		typedef IndexCont<FIELD_INDEX, std::string>::Type InvertIndex;
		typedef Index::const_iterator iterator;

		rschema();

		rschema(char const *name);

		rschema&
		define_field(char const* field_name, char const* type_str);

		rschema&
		undefine_field(char const* field_name);

		bool
		isSameSchema(record const &r) const;

		char const*
		name() const;

		rschema&
		name(char const*);

		FIELD_INDEX
		find(std::string const& field_name) const;

		char const*
		find(FIELD_INDEX field_index) const;

		void
		make(record& r) const;

		unsigned int
		field_count() const;

		unsigned int
		version() const;

		Index::const_iterator
		begin() const;

		Index::const_iterator
		end() const;
		
	private:
		Index idx_;
		InvertIndex ridx_, 
			    types_;	// type strings are for information only
		// they will not be used by record
		record *proto_;
		std::string name_;
		unsigned int version_;
	};

} // endof Yaks namespace

#endif
