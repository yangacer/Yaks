#ifndef _RECORD_HPP_
#define _RECORD_HPP_

#include <vector>
#include <string>
#include <iosfwd>

#include "yaks/variantType.hpp"
#include "boost/variant/get.hpp"

#include "yaks/rschema.hpp"
#include "yaks/export.hpp"

namespace Yaks
{
	

	struct rschema;

	class YAKS_EXPORT record
	{
	friend struct rschema;
	public:
		typedef std::vector<Variant> StorageType;
		typedef StorageType::iterator iterator;
		typedef StorageType::const_iterator const_iterator;

		record();
		
		operator bool() const;

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
		get(char const* field_name) throw (char const*);

		template<typename T>
		T const&
		get(char const* field_name) const throw (char const*);

		template<typename T>
		T&
		get(unsigned int off) throw (char const*);

		template<typename T>
		T const&
		get(unsigned int off) const throw (char const*);
		
		template<typename T>
		void
		set(char const* field_name, T const & val);
			
		template<typename T>
		void
		set(unsigned int off, T const & val);

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
		compare(char const* field_name, T const &rhs) const;

	private:
		std::vector<Variant> vals_;
		rschema const*schema_;
		unsigned int schema_ver_;
	};
	
} // end of namespace Yaks

#include "yaks/record.tcc"

#endif
