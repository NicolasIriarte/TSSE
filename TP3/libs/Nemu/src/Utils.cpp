#include "Nemu/Utils.h"
#include "Nemu/CMake/Config.hpp"

#ifdef __cplusplus
extern "C" {
#endif

const char *get_version(void) { return Nemu::CMake::PROJECT_VERSION.data(); }

const char *get_short_sha1(void) { return Nemu::CMake::GIT_SHORT_SHA1.data(); }

#ifdef __cplusplus
}
#endif
