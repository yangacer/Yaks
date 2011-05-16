#include "yaks/rschema.hpp"
#include "yaks/record.hpp"
#include "yaks/vfactory.hpp"
#include <istream>
#include <ostream>

namespace Yaks
{

	std::ostream& 
	operator<<(std::ostream& os, rschema &rs)
	{
		rschema::Index::iterator iter = rs.idx_.begin();

		os<<"name "<<rs.name()<<"\n";
		os<<"version "<<rs.version()<<"\n";
		os<<"fields_count "<<rs.idx_.size()<<"\n";

		while(iter != rs.idx_.end()){
			os<<iter->first<<"\t"<<
				rs.types_[iter->second]<<"\n";
			++iter;	
		}
		return os;
	}

	std::istream& 
	operator>>(std::istream& is, rschema &rs)
	{
		unsigned int fcnt(0), version(0);
		std::string sch_name, field_name, type;

		// ignore "name "
		is.ignore(5);
		getline(is, sch_name);
		rs.name(sch_name.c_str());

		// ignore "version "
		is.ignore(8);
		is>>version;
		// ignore "fields_count "
		is.ignore(13);
		is>>fcnt;
		is.ignore(1);

		while(fcnt){
			getline(is, field_name, '\t');
			getline(is, type);
			rs.define_field(field_name.c_str(), type.c_str());
			--fcnt;
		}
		rs.version_ = version;
		return is;
	}

	rschema::rschema()
	: proto_(new record), version_(0)
	{
		proto_->schema_ = this;	
	}


	rschema::rschema(char const *name)
	: proto_(new record), name_(name), version_(0)
	{
		proto_->schema_ = this;	
	}

	char const *
	rschema::name() const		
	{ return name_.c_str(); }

	rschema&
	rschema::name(char const *name)
	{ name_ = name; return *this; }

	rschema&
	rschema::define_field(char const* field_name, char const* type_str)
	{
		try{	
			Index::iterator iter = idx_.find(field_name);
			if(iter != idx_.end()){
				std::string msg("rschema: redefine field ");
				msg += field_name ;
				msg += " - ";
				msg += type_str;
				throw msg.c_str();
			}
			
			// add typed variant to proto_
			proto_->vals_.push_back(factory::Instance().create(type_str));
			
			// update indices
			idx_[field_name] = proto_->vals_.size() - 1;
			ridx_[(FIELD_INDEX)proto_->vals_.size() - 1].assign(field_name);
			types_[(FIELD_INDEX)proto_->vals_.size() - 1].assign(type_str);

			version_++;
		}catch(...){
			throw "rschema: defin_field failed";	
		}

	}

	bool
	rschema::isSameSchema(record const &r) const
	{ return r.schema_ == this && r.schema_ver_ == version_; }

	rschema&
	rschema::undefine_field(char const* field_name)
	{
		Index::iterator iter = idx_.find(field_name);
		if(iter == idx_.end())
			return *this;
		proto_->vals_.erase(proto_->vals_.begin() + iter->second);
		ridx_.erase(iter->second);
		types_.erase(iter->second);
		idx_.erase(iter);
		version_++;
		return *this;
	}

	FIELD_INDEX
	rschema::find(std::string const& field_name) const
	{
		Index::const_iterator iter = idx_.find(field_name);
		if(iter == idx_.end()){
			std::string msg("rschema: non-exist field name(");
			msg += field_name;
			msg += ")";
			throw msg.c_str();
		}
		return iter->second;	
	}

	char const*
	rschema::find(FIELD_INDEX field_index) const
	{
		InvertIndex::const_iterator iter = ridx_.find(field_index);
		if(iter == ridx_.end())
			throw "rschema: non-exist field index";
		return iter->second.c_str();
	}

	void
	rschema::make(record& r) const
	{	r = *proto_; r.schema_ver_ = version();	}

	unsigned int
	rschema::field_count() const
	{ return proto_?proto_->vals_.size():0; }

	unsigned int
	rschema::version() const
	{ return version_; }

	rschema::iterator
	rschema::begin() const
	{ return idx_.begin(); }

	rschema::iterator
	rschema::end() const
	{ return idx_.end(); }


}
