#include <sstream>
#include <ostream>
#include <cstring>
#include "yaks/strref.hpp"
#include "yaks/record.hpp"
#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/static_visitor.hpp"

struct strstream_in
: public boost::static_visitor<std::stringstream&>
{
	strstream_in(std::stringstream &is): is_(is){}
	
	template<typename T>
	std::stringstream& operator()(T& val)
	{
		is_>>val;
		return is_;
	}

	std::stringstream& operator()(std::string &val)
	{
		val = is_.str();
		is_.str("");
		return is_;
	}
private:
	std::stringstream &is_;
};

struct str_in
: public boost::static_visitor<bool>
{
	str_in(char const* cstr, unsigned int size)
	: cstr_(cstr), size_(size)
	{}

	template<typename T>
	bool operator()(T& val)
	{
		std::stringstream cvt;
		cvt.write(cstr_, size_);
		cvt>>val;
		return (bool)cvt;
	}

	bool operator()(std::string &val)
	{
		val.assign(cstr_, size_);
		return true;
	}

	bool operator()(Yaks::str_ref &val)
	{
		val.assign(cstr_, size_);
		return true;
	}
private:
	char const *cstr_;
	unsigned int size_;
};

struct strstream_out
: public boost::static_visitor<std::stringstream&>
{
	strstream_out(std::stringstream &os): os_(os){}
	
	template<typename T>
	std::stringstream& operator()(T const& val)
	{
		os_<<val;
		return os_;
	}

private:
	std::stringstream &os_;
};


namespace Yaks
{

	record::record()
	: schema_(0)
	{}
	
	record::operator bool() const
	{ return 0 != schema_; }

	Variant&
	record::operator[](char const* field_name)
	{
		return vals_[schema_->find(field_name)];
	}

	Variant&
	record::operator[](unsigned int i)
	{	return vals_[i]; }
	
	Variant const&
	record::operator[](char const* field_name) const
	{
		return vals_[schema_->find(field_name)];
	}

	Variant const&
	record::operator[](unsigned int i) const
	{	return vals_[i]; }


	Variant&
	record::at(char const* field_name) throw (char const*)
	{
		if(!schema_) throw "record: schema is undefined\n";
		return vals_.at(schema_->find(field_name));
	}
	
	Variant&
	record::at(unsigned int i) throw (char const*)
	{
		if(!schema_) throw "record: schema is undefined\n";
		return vals_.at(i);
	}

	Variant const&
	record::at(char const* field_name) const throw (char const*) 
	{
		if(!schema_) throw "record: schema is undefined\n";
		return vals_.at(schema_->find(field_name));
	}
	
	Variant const&
	record::at(unsigned int i) const throw (char const*)
	{
		if(!schema_) throw "record: schema is undefined\n";
		return vals_.at(i);
	}

	// -----------------  Getter of Values' Iterator ----------------
	
	record::iterator
	record::begin()
	{ return vals_.begin(); }

	record::iterator
	record::end()
	{ return vals_.end();	}
	
	record::const_iterator
	record::begin() const
	{ return vals_.begin(); }

	record::const_iterator
	record::end() const
	{ return vals_.end();	}

	record::const_iterator
	record::const_begin() const
	{ return vals_.begin(); }

	record::const_iterator
	record::const_end() const
	{ return vals_.end();	}

	// ----------------- Misc --------------------
	
	rschema const&
	record::schema() const
	{ return *schema_; } 

	bool
	record::fromString(char const* field_name, char const *cstr, unsigned int size)
	{
		if(!schema_) throw "record: schema is undefined\n";
		str_in cvt_visitor(cstr, size);
		return boost::apply_visitor(cvt_visitor, at(field_name));
	}

	bool
	record::fromString(char const* field_name, char const *cstr)
	{
		return fromString(field_name, cstr, std::strlen(cstr));
	}
	
	std::string
	record::toString(char const* field_name) const
	{
		if(!schema_) throw "record: schema is undefined\n";
		std::stringstream cvt;
		strstream_out cvt_visitor(cvt);
		
		boost::apply_visitor(cvt_visitor, (*this)[field_name]);
		return cvt.str();
	}

	std::ostream&
	record::writeTo(std::ostream &os, char const* field_name) const
	{
		if(!schema_) throw "record: schema is undefined\n";
		return os<<at(field_name);
	}


	int
	record::compare(char const *field_name, record const & rhs) const
	{
		if(at(field_name) < rhs.at(field_name))
			return -1;
		else if(at(field_name) == rhs.at(field_name))
			return 0;
		return 1;
	}

} // end of namespace Yaks
