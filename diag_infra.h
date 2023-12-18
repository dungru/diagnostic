#ifndef __DIAG_INFRA_H__
#define __DIAG_INFRA_H__

#include "redismodule.h"


typedef struct {
    char name[32];
    int  (*handler)(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);
} DIAG_ACTION_CMD_T;

typedef struct {
    DIAG_ACTION_CMD_T *ptr_table;
    uint32_t table_entry_num;
} DIAG_TABLE_INFO_T; 

typedef int (*DIAG_GET_TABLE_INFO_FUNC_PTR)(DIAG_TABLE_INFO_T *ptr_info);

typedef struct {
    char name[32];
    DIAG_GET_TABLE_INFO_FUNC_PTR get_table_info;
} DIAG_MODULE_CMD_T;


#endif /* __DIAG_INFRA_H__ */