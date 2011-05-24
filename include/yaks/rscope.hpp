#ifndef _RSCOPE_HPP_
#define _RSCOPE_HPP_

#include <string>
#include "boost/unordered_map.hpp"
#include "yaks/export.hpp"

namespace Yaks
{
	struct rschema;
	
	class YAKS_EXPORT global_scope
	{
		typedef boost::unordered_map<std::string, rschema const*> StorageType;
	public:
		static void 
		define(rschema const* rs);

		static void
		undefine(rschema const* rs);
		
		static rschema const*
		find(char const *name);
		
	private:	
		static StorageType store_;
	};

	class YAKS_EXPORT rscope
	{
	public:
		rscope(rschema const* rs);
		~rscope();

		static 
		rschema const*
		schema();
	private:
		rscope(rscope const& cp);
		rscope& operator=(rscope const& cp);
	};
	
} // end of Yaks namespace

#endif // end of header guard

