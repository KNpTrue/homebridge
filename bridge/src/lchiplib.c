// Copyright (c) 2021-2022 Zebin Wu and homekit-bridge contributors
//
// Licensed under the Apache License, Version 2.0 (the “License”);
// you may not use this file except in compliance with the License.
// See [CONTRIBUTORS.md] for the list of homekit-bridge project authors.

#include <lauxlib.h>
#include <pal/chip.h>

#include "app_int.h"

static const char *(*lchip_get_info_funcs[])() = {
    pal_chip_get_manufacturer,
    pal_chip_get_model,
    pal_chip_get_serial_number,
    pal_chip_get_hardware_version,
};

const char *lchip_info_strs[] = {
    "mfg",
    "model",
    "sn",
    "hwver",
    NULL
};

static int lchip_get_info(lua_State *L) {
    lua_pushstring(L, lchip_get_info_funcs[luaL_checkoption(L, 1, NULL, lchip_info_strs)]());
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
