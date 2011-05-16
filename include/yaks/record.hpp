#ifndef _RECORD_HPP_
#define _RECORD_HPP_

#include <vector>
#include <string>
#include <iosfwd>

#include "yaks/variantType.hpp"
#include "boost/variant/get.hpp"

#include "yaks/rschema.hpp"

namespace Yaks
{
	

	struct rschema;

	class record
	{
	friend struct rschema;
	public:
		typedef std::vector<Variant> StorageType;
		typedef StorageType::iterator iterator;
		typedef StorageType::const_iterator const_iterator;

		record();
		
		// --------------- Offset Operators -------------------
		Variant&
		operator[](char const* field_name);

		Variant&
		operator[](unsigned int i);
		
		Variant&
		at(char const* field_name) throw (char const*);
		
		Variant&
		at(unsigned int i) throw (char const*);

		// -------------- Const Offset Operators -------------------
		
		Variant const&
		operator[](char const* field_name) const;

		Variant const&
		operator[](unsigned int i) const;

		Variant const&
		at(char const* field_name) const throw (char const*);
		
		Variant const&
		at(unsigned int i) const throw (char const*);

		// -----------------  Getter of Values' Iterator ----------------

		/** Get begin iterator of fields
		 *  @return iterator
		 */
		iterator
		begin();

		/** Get end iterator of fields
		 *  @return iterator
		 */
		iterator
		end();
		
		const_iterator
		begin() const;

		const_iterator
		end() const;

		/** Get constant begin iterator (deprecated)
		 */
		StorageType::const_iterator
		const_begin() const;

		/** Get constant end iterator (deprecated)
		 */
		StorageType::const_iterator
		const_end() const;
		

		// -----------------  Typed Getters/Setters --------------

		template<typename T>
		T&
		get(char const* field_name) throw (char const*)
		{	return boost::get<T>(vals_[schema_->find(field_name)]); }

		template<typename T>
		T const&
		get(char const* field_name) const throw (char const*)
		{	
			if(!schema_) throw "record: schema is undefined\n";
			return boost::get<T>(vals_[schema_->find(field_name)]); 
		}
		
		template<typename T>
		void
		set(char const* field_name, T const & val)
		{	
			if(!schema_) throw "record: schema is undefined\n";
			vals_[schema_->find(field_name)] = val; 
		}
			
		template<typename T>
		T&
		get(unsigned int off) throw (char const*)
		{	return boost::get<T>(vals_[off]); }

		template<typename T>
		T const&
		get(unsigned int off) const throw (char const*)
		{	return boost::get<T>(vals_[off]); }
		
		template<typename T>
		void
		set(unsigned int off, T const & val)
		{	vals_[off] = val; }
		
		// ----------------- Misc --------------------

		rschema const& schema() const;
		
		
		bool 
		fromString(char const* field_name, char const *cstr, unsigned int size);
		
		bool
		fromString(char const* field_name, char const *cstr);
		
		
		std::string
		toString(char const* field_name) const;
		
		std::ostream&
		writeTo(std::ostream &os, char const* field_name) const;

		
		int
		compare(char const *field_name, record const & rhs) const;
		

		template<typename T>
		int
		compare(char const* field_name, T const &rhs) const
		{
			if(get<T>(field_name) < rhs)
				return -1;	
			else if(get<T>(field_name) == rhs)
				return 0;
			return 1;
		}
		

	private:
		std::vector<Variant> vals_;
		rschema *schema_;
		unsigned int schema_ver_;
	};

} // end of namespace Yaks

#endif
