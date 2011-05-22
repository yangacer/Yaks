#ifndef _RECORD_HPP_
#define _RECORD_HPP_

#include <vector>
#include <string>
#include <iosfwd>

#include "yaks/variantType.hpp"

#include "yaks/rschema.hpp"
#include "yaks/export.hpp"

namespace Yaks
{

	struct rschema;

	struct YAKS_EXPORT record
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
		
		/** Get constant begin iterator
		 */
		const_iterator
		begin() const;

		/** Get constant end iterator
		 */
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
		
		/** Set field value from a serialized string.
		 *  @param field_name 
		 *  @param cstr C-string
		 *  @param size
		 *  @return ture/false for sucess of deserialization.
		 *  @remark This method allows client to change value 
		 *  of a field without changing type of the field.
		 */
		bool 
		fromString(char const* field_name, char const *cstr, unsigned int size);
		
		/** Set field value from a null-terminated and serialized string.
		 *  @param field_name 
		 *  @param cstr C-string
		 *  @param size
		 *  @return ture/false for sucess of deserialization.
		 */
		bool
		fromString(char const* field_name, char const *cstr);
		
		/** Serialize field value.
		 *  @return Human readable text.
		 */
		std::string
		toString(char const* field_name) const;
		
		/** Serialize filed value to specific output stream
		 *  @param os Output stream
		 *  @param field_name
		 *  @return The output stream
		 */
		std::ostream&
		writeTo(std::ostream &os, char const* field_name) const;

		/** Compare a field of two records.
		 *  @param field_name
		 *  @param rhs
		 *  @return -1 for this < rhs, 0 for equal, and 1 for greater
		 */
		int
		compare(char const *field_name, record const & rhs) const;
		
		/** Compare a feild with typed value.
		 *  @param field_name
		 *  @param rhs
		 *  @return -1 for this < rhs, 0 for equal, and 1 for greater
		 */
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
