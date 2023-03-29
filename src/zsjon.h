#ifndef __ZJSON_H__
#define __ZJSON_H__

#include "commom.h"

typedef enum
{
    ZJ_NULL,
    ZJ_FALSE,
    ZJ_TRUE,
    ZJ_NUMBER,
    ZJ_STRING,
    ZJ_ARRAY,
    ZJ_OBJRCT,
    ZJ_BUTT
} zjson_type;

enum
{
    ZJ_PARSE_OK = 0,
    ZJ_PARSE_EXPECT_VALUE,
    ZJ_PARSE_INVALID_VALUE
};

typedef struct
{
    zjson_type type;
} zjson_value;

int zjson_parse(IN zjson_value *value, OUT const char *jsonStr);

zjson_type zjson_get_type(IN const zjson_value *value);

#endif /* __ZJSON_H__ */