// Copyright (c) 2021 KNpTrue and homekit-bridge contributors
//
// Licensed under the MIT License.
// You may not use this file except in compliance with the License.
// See [CONTRIBUTORS.md] for the list of homekit-bridge project authors.

#include <lauxlib.h>
#include <pal/chip.h>

#include "app_int.h"

typedef enum {
    LCHIP_MFG,
    LCHIP_MODEL,
    LCHIP_SN,
    LCHIP_HW_VER,
} lchip_info_type;

static const char *(*lchip_get_info_funcs[])() = {
    [LCHIP_MFG] = pal_chip_get_manufacturer,
    [LCHIP_MODEL] = pal_chip_get_model,
    [LCHIP_SN] = pal_chip_get_serial_number,
    [LCHIP_HW_VER] = pal_chip_get_hardware_version,
};

static int lchip_get_info(lua_State *L) {
    lua_pushstring(L, lchip_get_info_funcs[luaL_checkoption(L, 1, NULL, (const char *[]) {
        [LCHIP_MFG] = "mfg",
        [LCHIP_MODEL] = "model",
        [LCHIP_SN] = "sn",
        [LCHIP_HW_VER] = "hwver",
    })]());
    return 1;
}

static const luaL_Reg lchip_funcs[] = {
    {"getInfo", lchip_get_info},
    {NULL, NULL},
};

LUAMOD_API int luaopen_chip(lua_State *L) {
    luaL_newlib(L, lchip_funcs);
    return 1;
}