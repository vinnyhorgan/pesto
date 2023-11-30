#include "api.h"

static const luaL_Reg functions[] = {
    { NULL, NULL }
};

int luaopen_rres(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "rres");

    return 1;
}
