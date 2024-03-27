#ifndef NEMU_UTILS_H
#define NEMU_UTILS_H

#include "Nemu/NemuExport.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get Nemu version.
 *
 * @details Get Nemu version as const char* string. This is really useful to
 *          identify the current version of the software.
 *
 * @return Returns a pointer to the version string.
 *
 * @note The caller is @b NOT responsible for freeing the returned string.
 */
NEMU_EXPORT const char *get_version(void);

/**
 * @brief Get Nemu git sha code.
 *
 * @details Get Nemu git sha code as const char* string. This is really useful
 *          to identify and track specific versions and builds of the software.
 *
 * @return Returns a pointer to the git sha code.
 */
NEMU_EXPORT const char *get_short_sha1(void);

#ifdef __cplusplus
}
#endif

#endif /* NEMU_UTILS_H */
