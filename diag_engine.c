#include <stdlib.h>
#include "diag_infra.h"
#include "diag_regs.h"
#include "diag_utils.h"

static DIAG_MODULE_CMD_T diag_module_vec[] = {
    {"nsys.regs", diag_regs_get_table_info},
};

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (RedisModule_Init(ctx, "diag_engine.so", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    for (uint32_t i = 0; i < ARRAY_SIZE(diag_module_vec); i++) {
        DIAG_MODULE_CMD_T *mc = &diag_module_vec[i];
        DIAG_TABLE_INFO_T info;
        mc->get_table_info(&info);
        if (RedisModule_CreateCommand(ctx, mc->name, NULL, "", 0, 0, 0) == REDISMODULE_ERR)
            return REDISMODULE_ERR;
        RedisModuleCommand *parent = RedisModule_GetCommand(ctx, mc->name);
        for (uint32_t j = 0; j < info.table_entry_num; j++) {
            DIAG_ACTION_CMD_T *ac = &info.ptr_table[j];
            if (RedisModule_CreateSubcommand(parent, ac->name, ac->handler, "", 0, 0, 0) == REDISMODULE_ERR)
                return REDISMODULE_ERR;
        }
    }

    return REDISMODULE_OK;
}

void RedisModule_OnUnload(RedisModuleCtx *ctx)
{
    // Perform cleanup or release resources when the module is unloaded
    RedisModule_Log(ctx, "warning", "Unloading mymodule");
    // Additional cleanup code goes here
}