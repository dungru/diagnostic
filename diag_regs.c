#include "diag_regs.h"

static int diag_regs_get(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    long long a, b;
    if (argc < 4) {
        return RedisModule_WrongArity(ctx);
    }

    if (RedisModule_StringToLongLong(argv[2], &a) != REDISMODULE_OK ||
        RedisModule_StringToLongLong(argv[3], &b) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx, "Invalid arguments");
    }

    RedisModule_ReplyWithLongLong(ctx, a + b);
    return REDISMODULE_OK;
}

static int diag_regs_set(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc < 3) {
        return RedisModule_WrongArity(ctx);
    }
    RedisModule_ReplyWithString(ctx, argv[2]);
    return REDISMODULE_OK;
}

static DIAG_ACTION_CMD_T diag_regs_vec[] = {
    {"set", diag_regs_get},
    {"get", diag_regs_set},
};

int diag_regs_get_table_info(DIAG_TABLE_INFO_T *ptr_info)
{
    ptr_info->ptr_table = diag_regs_vec;
    ptr_info->table_entry_num = ARRAY_SIZE(diag_regs_vec);
    return 0;
}