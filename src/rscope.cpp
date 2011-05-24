#include "yaks/rscope.hpp"
#include "yaks/rschema.hpp"
#include <deque>

static std::deque<Yaks::rschema const*> scope_chain_;

namespace Yaks
{
	global_scope::StorageType global_scope::store_;

	void 
	global_scope::define(rschema const* rs)
	{
		store_[rs->name()] = rs;	
	}

	void
	global_scope::undefine(rschema const* rs)
	{	
		StorageType::iterator iter;
		if(store_.end() == ( iter = store_.find(rs->name()) ) )
			return;
		store_.erase(iter);
	}
	
	rschema const*
	global_scope::find(char const *name)
	{
		StorageType::iterator iter;
		if(store_.end() == (iter = store_.find(name)))
			return 0;
		return iter->second;
	}


	rscope::rscope(rschema const* rs)
	{
		scope_chain_.push_front(rs);
	}

	rscope::~rscope()
	{
		scope_chain_.pop_front();	
	}

	rschema const*
	rscope::schema()
	{
		if(scope_chain_.empty()) 
			return 0;
		return scope_chain_.front();	
	}

} //end of Yaks namespace
