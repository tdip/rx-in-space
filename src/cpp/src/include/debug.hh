#ifdef _DEBUG

#include <assert.h>

#define ASSERT_EVAL(COND, MSG) if(!COND){printf("%s\n", MSG); assert(COND);}

#else

#define ASSERT_EVAL(COND, MSG) COND

#endif