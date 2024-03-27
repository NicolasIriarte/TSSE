#include <Private/Nemu/MemoryImpl.hpp>

namespace Nemu {

/**
 * TODO:
 * - Check boundaries
 */
uint8_t *GetMemoryPosition(Memory *memory, uint64_t offset)
{
  return &memory->data[offset];// NOLINT
}

}// namespace Nemu
