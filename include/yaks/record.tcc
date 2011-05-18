
namespace Yaks {
	
	template<typename T>
	T&
	record::get(char const* field_name) throw (char const*)
	{	return boost::get<T>(vals_[schema_->find(field_name)]); }

	template<typename T>
	T const&
	record::get(char const* field_name) const throw (char const*)
	{	
		if(!schema_) throw "record: schema is undefined\n";
		return boost::get<T>(vals_[schema_->find(field_name)]); 
	}
	
	template<typename T>
	T&
	record::get(unsigned int off) throw (char const*)
	{	return boost::get<T>(vals_[off]); }

	template<typename T>
	T const&
	record::get(unsigned int off) const throw (char const*)
	{	return boost::get<T>(vals_[off]); }

	template<typename T>
	void
	record::set(char const* field_name, T const & val)
	{	
		if(!schema_) throw "record: schema is undefined\n";
		vals_[schema_->find(field_name)] = val; 
	}
		
	template<typename T>
	void
	record::set(unsigned int off, T const & val)
	{	vals_[off] = val; }
	
	template<typename T>
	int
	record::compare(char const* field_name, T const &rhs) const
	{
		if(get<T>(field_name) < rhs)
			return -1;	
		else if(get<T>(field_name) == rhs)
			return 0;
		return 1;
	}

} // end of Yaks namespace

