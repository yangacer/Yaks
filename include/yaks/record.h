#ifndef _C_RECORD_H
#define _C_RECORD_H

#include "export.hpp"

#ifdef __cplusplus
extern "C" {
#endif

struct record;
struct variant;

YAKS_EXPORT struct record *
record_new();

YAKS_EXPORT void
record_free(struct record* rec);

YAKS_EXPORT int
from_str(struct record* rec, char const* field, char const* text, int size);

YAKS_EXPORT int
get_int(struct record* rec, char const* field);

YAKS_EXPORT char const*
get_str(struct record* rec, char const* field);

YAKS_EXPORT double
get_double(struct record* rec, char const* field);

YAKS_EXPORT int
set_int(struct record* rec, char const* field, int val);

YAKS_EXPORT int
set_str(struct record* rec, char const* field, char const* val);

YAKS_EXPORT int
set_double(struct record* rec, char const* field, double val);


#ifdef __cplusplus
} // end of extern "C"
#endif

#endif // end of header guard
