#include "yaks/record.hpp"
#include "yaks/rschema.hpp"

#include <vector>
#include <iostream>

#include <cstdio>
#include <algorithm>
#include <functional>
#include "boost/variant/apply_visitor.hpp"

template<template <class> class Op>
struct rcmp
: public boost::static_visitor<bool>
{

	template<typename T>
	bool operator()(T const& lhs, T const& rhs) const
	{
		return Op<T>()(lhs, rhs);	
	}

	template<typename T,typename U>
	bool operator()(T const& lhs, U const& rhs) const
	{ return false; }
};

template<template <class> class Op>
struct getAge
{
	bool operator()(Yaks::record const &lhs, Yaks::record const &rhs) const
	{
		return boost::apply_visitor(rcmp<Op>(), lhs["age"], rhs["age"]);
	}
};


template<template <class> class Op>
struct getName
{
	bool operator()(Yaks::record const &lhs, Yaks::record const &rhs) const
	{
		return boost::apply_visitor(rcmp<Op>(), lhs["name"], rhs["name"]);
	}
};

int
main()
{
	using boost::apply_visitor;
	using std::less;
	using std::greater;
	using std::equal_to;
	using std::sort;
	using std::cout;
	using std::vector;
	using Yaks::record;
	using Yaks::rschema;

	rschema schema;
	record r;
	
	schema.define_field("name", "STR");
	schema.define_field("age", "UINT");
	
	schema.make(r);

	
	const unsigned int recordCnt = 10000;
	vector<record> rv;
	
	char name[20];
	for(unsigned int i=0; i < recordCnt; ++i){
		sprintf(name, "%c%d", 'a' + i % 26, i);
		r["name"] = name;
		r["age"] = recordCnt - i;
		rv.push_back(r);
	}
	
	sort(rv.begin(), rv.end(), getName<greater>() );
	
	for(unsigned int i=0; i < recordCnt; ++i)
		cout<<rv[i]["name"]<<"\n";
	
	
	/*
	rv[0].fromString("name", "acer");
	rv[0].fromString("age", "21");
	rv[1].fromString("name", "yang");
	rv[1].fromString("age", "24");
	
	int b = rv[0].compare("age", 21u);
	cout<<b<<"\n";
	
	b = rv[0].compare("age", rv[1]);
	cout<<"Should be -1: "<<b<<"\n";

	b = rv[1].compare("age", rv[0]);
	cout<<"Should be 1: "<<b<<"\n";

	cout<<rv[0]["name"]<<" "<<
		rv[0]["age"]<<"\n";

	Yaks::Variant const &v1(rv[0]["name"]), &v2(rv[1]["name"]);

	cout<<boost::apply_visitor(rcmp<less>(), rv[0]["name"], v2)<<"\n";
	cout<<boost::apply_visitor(rcmp<greater>(), v1, v2)<<"\n";
	cout<<boost::apply_visitor(rcmp<equal_to>(), v1, v2)<<"\n";
	*/
	

	return 0;	
}
