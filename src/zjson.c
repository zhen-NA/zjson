#include "zsjon.h"
#include <assert.h>
#include <stdlib.h>

#define CHECK_HEAD(c, ch)         \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
    } while (0)

typedef struct
{
    const char *json;
} zjson_context;

static void _zjson_parse_whitespace(IN zjson_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        p++;
    }
    c->json = p;
    return;
}

static int _zjson_parse_null(IN zjson_context *context, OUT zjson_value *value)
{
    CHECK_HEAD(context, 'n');
    if (context->json[1] != 'u' || context->json[2] != 'l' || context->json[3] != 'l')
    {
        return ZJ_PARSE_INVALID_VALUE;
    }
    context->json += 4; /* 判断结尾用 */
    value->type = ZJ_NULL;
    return ZJ_PARSE_OK;
}

static int _zjson_parse_false(IN zjson_context *context, OUT zjson_value *value)
{
    CHECK_HEAD(context, 'f');
    if (context->json[1] != 'a' || context->json[2] != 'l' || context->json[3] != 's' || context->json[3] != 'e')
    {
        return ZJ_PARSE_INVALID_VALUE;
    }
    context->json += 5; /* 判断结尾用 */
    value->type = ZJ_FALSE;
    return ZJ_PARSE_OK;
}

static int _zjson_parse_true(IN zjson_context *context, OUT zjson_value *value)
{
    CHECK_HEAD(context, 't');
    if (context->json[1] != 'r' || context->json[2] != 'u' || context->json[3] != 'e')
    {
        return ZJ_PARSE_INVALID_VALUE;
    }
    context->json += 4; /* 判断结尾用 */
    value->type = ZJ_TRUE;
    return ZJ_PARSE_OK;
}

static int _zjson_parse_value(IN zjson_context *context, OUT zjson_value *value)
{
    switch (*context->json)
    {
    case 'n':
        return _zjson_parse_null(context, value);
    case 'f':
        return _zjson_parse_false(context, value);
    case 't':
        return _zjson_parse_true(context, value);
    default:
        return ZJ_PARSE_INVALID_VALUE;
    }
}

int zjson_parse(IN zjson_value *value, OUT const char *jsonStr)
{
    zjson_context context;
    int ret;
    assert(NULL != value);
    context.json = jsonStr;
    value->type = ZJ_NULL;

    _zjson_parse_whitespace(&context);
    if ((ret = _zjson_parse_value(&context, value)) == ZJ_PARSE_OK)
    {
        _zjson_parse_whitespace(&context);
        if ('\0' != *context.json) /* 判断结尾 */
        {
            ret = ZJ_PARSE_EXPECT_VALUE;
        }
    }

    return ret;
}
