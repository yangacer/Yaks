#ifndef _STRREF_HPP
#define _STRREF_HPP

#include <iosfwd>
#include <cstring>
#include <string>
#include "yaks/export.hpp"

#define SIX_BOOL_OP_DECL(C,X) bool operator X (C const& rhs)const
#define GLOBAL_SBOP_FUNC(T,U,X,Y) bool operator X \
	(T const &lhs, U const &rhs){ return rhs Y lhs; }

namespace Yaks
{
	
	struct YAKS_EXPORT str_ref
	{
		str_ref();
		str_ref(char const* data, unsigned int size);
		str_ref(char const* data_beg, char const* data_end);
		
		SIX_BOOL_OP_DECL(str_ref,>);
		SIX_BOOL_OP_DECL(str_ref,<);
		SIX_BOOL_OP_DECL(str_ref,>=);
		SIX_BOOL_OP_DECL(str_ref,<=);
		SIX_BOOL_OP_DECL(str_ref,==);
		SIX_BOOL_OP_DECL(str_ref,!=);
		
		SIX_BOOL_OP_DECL(std::string,>);
		SIX_BOOL_OP_DECL(std::string,<);
		SIX_BOOL_OP_DECL(std::string,>=);
		SIX_BOOL_OP_DECL(std::string,<=);
		SIX_BOOL_OP_DECL(std::string,==);
		SIX_BOOL_OP_DECL(std::string,!=);

		str_ref&
		assign(char const* data, unsigned int size);

		str_ref&
		assign(char const* data_beg, char const* data_end);

		void
		clear();

		char const* data() const;

		unsigned int size() const;

		char const* data_;
		unsigned int size_;
	};

	inline GLOBAL_SBOP_FUNC(std::string,str_ref,>,<)
	inline GLOBAL_SBOP_FUNC(std::string,str_ref,<,>)
	inline GLOBAL_SBOP_FUNC(std::string,str_ref,>=,<=)
	inline GLOBAL_SBOP_FUNC(std::string,str_ref,<=,>=)
	inline GLOBAL_SBOP_FUNC(std::string,str_ref,==,==)
	inline GLOBAL_SBOP_FUNC(std::string,str_ref,!=,!=)


	std::ostream YAKS_EXPORT &operator<<(std::ostream& os, str_ref const& sref);

	struct record;

	void YAKS_EXPORT
	cp_strref(std::string &buffer, record const&r);

	void YAKS_EXPORT
	rebuild_ref(std::string const &buffer, record *beg, record *end);
} // end of Yaks namespace



/*
void
rebuild_ref(std::string &buffer, record *beg, record *end);

template<>
class field<str_ref> : public absField, public Loki::SmallObject<>
{
	friend unsigned int referenced_count(record const& r);
	friend unsigned int cp_chg_referenced(char *buf, record &r);
	friend void cp_strref(std::string &buffer, record &r);
	friend void rebuild_ref(std::string &buffer, record *beg, record *end);

private: // Client never creates field object directly
	friend class record;
	template<class T1> friend struct create_field;

	typedef str_ref value_type;

	field()
	: val_()
	{}

	field(field const &cp)
	: val_(cp.val_)
	{}

	~field()
	{}

	field* 
	Clone() const
	{ return new field(*this); }

	
	void
	Clone(absField* f) const
	{ new (f) field<str_ref>(*this); }
	

	int 
	compare(absField const* rhs, bool sameType = false) const throw(char const*)
	{
		field* p = (sameType) ? 
			static_cast<field*>(const_cast<absField*>(rhs))
			: dynamic_cast<field*>(	const_cast<absField*>(rhs));

		if(0 == p)
			return -2;
		if(val_ < p->val_)
			return -1;
		if(val_ > p->val_)
			return 1;
		return 0;
	}
	

	int 
	compare(absField const* rhs, void* compare, bool sameType = false) const throw(char const*)
	{
		return this->compare(rhs, sameType);	
	}

	bool 
	fromString(char const *cstr, size_t size)
	{
		val_.data_ = cstr;
		val_.size_ = size;
		return true;
	}

	bool 
	fromString(char const *str)
	{
		val_.data_ = str;
		val_.size_ = std::strlen(str);
		return true;
	}


	std::string 
	toString() const 
	{
		return std::string(val_.data_, val_.size_);
	}

	std::ostream&
	writeTo(std::ostream& os) const
	{	
		os.write(val_.data_, val_.size_);
		return os;
	}

	str_ref val_;
};
*/
#endif // end of header guard
