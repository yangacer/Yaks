#include "yaks/strref.hpp"
#include "yaks/record.hpp"
#include "boost/variant/static_visitor.hpp"
#include "boost/variant/apply_visitor.hpp"
#include <cstring>
#include <algorithm>
#include <functional>
#include <ostream>


namespace Private__
{
	struct cp_strref_
	: public boost::static_visitor<>
	{
		cp_strref_(std::string& buf)
		: buffer(buf)
		{}
		
		template<typename T>
		void operator()(T const& val) const
		{}

		void operator()(Yaks::str_ref const &val) const
		{
			buffer.append(val.data_, val.size_);	
		}

		std::string &buffer;
	};


	struct rebuild_ref_
	: public boost::static_visitor<>
	{
		rebuild_ref_(std::string const &buf)
		: buffer(buf), curPos(0)
		{}
		
		
		template<typename T>
		void operator()(T const& val) const
		{}

		void operator()(Yaks::str_ref &val)
		{
			val.data_ = buffer.data() + curPos;
			curPos += val.size_;
		}

		std::string const &buffer;
		unsigned int curPos;
	};
}

namespace Yaks 
{

	str_ref::str_ref()
	: data_(0), size_(0)
	{}

	str_ref::str_ref(char const *data, unsigned int size)
	: data_(data), size_(size)
	{}

	str_ref::str_ref(char const* data_beg, char const* data_end)
	: data_(data_beg), size_(data_end - data_beg)
	{}

	str_ref&
	str_ref::assign(char const* data, unsigned int size)
	{	data_ = data; size_ = size;	}

	str_ref&
	str_ref::assign(char const* data_beg, char const* data_end)
	{	data_ = data_beg; size_ = data_end - data_beg;	}

	char const*
	str_ref::data() const
	{ return data_; }

	unsigned int
	str_ref::size() const
	{ return size_; }

	void
	str_ref::clear()
	{ data_ = 0; size_ = 0; }

	bool 
	str_ref::operator>(str_ref const& rhs) const
	{
		return std::lexicographical_compare(rhs.data_, rhs.data_ + rhs.size_, data_, data_ + size_);
	}

	bool 
	str_ref::operator<(str_ref const& rhs) const
	{

		return std::lexicographical_compare(data_, data_ + size_, rhs.data_, rhs.data_ + rhs.size_);
	}

	bool 
	str_ref::operator>=(str_ref const& rhs) const
	{	return !(*this<rhs);	}

	bool 
	str_ref::operator<=(str_ref const& rhs) const
	{	return !(*this>rhs);	}

	bool 
	str_ref::operator==(str_ref const& rhs) const
	{
		return rhs.size_ == size_ && strncmp(data_, rhs.data_, size_);	
	}

	bool 
	str_ref::operator!=(str_ref const& rhs) const
	{
		return !(*this == rhs);	
	}

	// -------------- comparison between std::string
	bool 
	str_ref::operator>(std::string const& rhs) const
	{
		return std::lexicographical_compare(rhs.begin(), rhs.end(), data_, data_ + size_);
	}

	bool 
	str_ref::operator<(std::string const& rhs) const
	{

		return std::lexicographical_compare(data_, data_ + size_, rhs.begin(), rhs.end());
	}

	bool 
	str_ref::operator>=(std::string const& rhs) const
	{	return !(*this<rhs);	}

	bool 
	str_ref::operator<=(std::string const& rhs) const
	{	return !(*this>rhs);	}

	bool 
	str_ref::operator==(std::string const& rhs) const
	{
		return rhs.size() == size_ && strncmp(data_, rhs.c_str(), size_);	
	}

	bool 
	str_ref::operator!=(std::string const& rhs) const
	{
		return !(*this == rhs);	
	}

	//std::istream &operator>>(std::istream& is, str_ref const& sref)
	//{ return is;}

	std::ostream &operator<<(std::ostream& os, str_ref const& sref)
	{
		os.write(sref.data_, sref.size_);	
		return os;
	}

	
	void
	cp_strref(std::string &buffer, record const &r)
	{
		using Yaks::record;
		record::const_iterator iter = r.begin();
		Private__::cp_strref_ getter(buffer);

		while(iter != r.end()){
			boost::apply_visitor(getter, *iter);
			++iter;
		}
		
	}

	void
	rebuild_ref(std::string const &buffer, record *beg, record *end)
	{
		record *iter = beg;
		record::iterator fIter;
		
		Private__::rebuild_ref_ functor(buffer);

		while(iter != end){
			fIter = iter->begin();
			while(fIter != iter->end()){
				boost::apply_visitor(functor, *fIter);
				++fIter;	
			}
			++iter;	
		}
	}


} // end of Yaks namespace


