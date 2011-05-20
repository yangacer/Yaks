#include "yaks/vfactory.hpp"
#include "yaks/strref.hpp"
#include "yaks/record.hpp"
#include "loki/Singleton.h"

// LOKI_SINGLETON_INSTANCE_DEFINITION(Loki::SingletonHolder<Yaks::factory_>)

namespace Yaks
{
	struct factory_
	{
		template<class T> friend struct Loki::CreateUsingNew;

		typedef boost::unordered_map<std::string, Variant> Storage;

		
		template<typename T>
		void join(char const *type_str)
		{
			if( storage_.end() != storage_.find(type_str) )
				return;
			storage_[type_str] = T(); 
		}

		Variant const&
		create(char const *type_str) const throw (char const*);

	private:
		factory_();
		factory_(factory_ const &cp);
		factory_& operator = (factory_ const &cp);

		Storage storage_;
	};
	factory_::factory_()
	: storage_()
	{
		join<int>("INT");
		join<unsigned int>("UINT");
		join<char>("CHAR");
		join<unsigned char>("UCHAR");
		join<double>("DOUBLE");
		join<long long>("LLONG");
		join<unsigned long long>("ULLONG");
		join<std::string>("CHAR[]");
		join<std::string>("STR");
		join<str_ref>("STRREF");
	}
	

	Variant const&
	factory_::create(char const *type_str) const throw (char const*)
	{
		Storage::const_iterator	iter;
		
		if( storage_.end() == (iter = storage_.find(type_str)) )	
			throw "storage_: unkown type\n";
		return iter->second;

	}
	
	/*
	factory_* factory::Instance()
	{ return &Loki::SingletonHolder<factory_>::Instance(); }
	*/
	
	typedef Loki::SingletonHolder<factory_> factoryImpl;

	Variant const &
	factory::create(char const* type_str)
	{ return factoryImpl::Instance().create(type_str); }
}// end of Yaks namespace

//template class Loki::Singleton<Yaks::factory_>;
