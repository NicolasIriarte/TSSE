#ifndef NEMU_MEMORY_HPP
#define NEMU_MEMORY_HPP

#include "Nemu/NemuExport.h"
#include <cstdint>

namespace Nemu {

/**
 * @brief Type representing a MEMORY type.
 *
 * @details An opaque struct was decided to use to shield its implementation.
 */
struct Memory;

/**
 * @brief Get a raw pointer to a memory offset.
 *
 * @details This function is responsible for returning a raw pointer to a memory
 *          position.
 *
 * @param memory The memory object to get the memory position from.
 * @param offset The offset to get the memory position from.
 *
 * @return     return type
 */
NEMU_EXPORT uint8_t *GetMemoryPosition(Memory *memory, uint64_t offset = 0);


}// namespace Nemu

#endif /* NEMU_MEMORY_HPP */
