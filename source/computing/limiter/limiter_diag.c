#include "limiter_diag.h"

#include <stdio.h>
#include "shared_array.h"

const char* Limiter2Str(const Limiter_t* const Node){
	snprintf(text,sizeof(text),"Foo:%p,Call:%u",
			Node->function,
			Node->call_cnt);
	return text;
}

