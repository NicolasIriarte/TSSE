#ifndef MEMORYIMPL_H
#define MEMORYIMPL_H


#include "Nemu/Memory.hpp"
#include <cstdint>

namespace Nemu {


struct Memory
{
  Memory(const Memory &) = delete;
  Memory(Memory &&) = delete;
  Memory &operator=(const Memory &) = delete;
  Memory &operator=(Memory &&) = delete;

  explicit Memory(uint32_t sizeKb) noexcept
    : size(sizeKb), data(new uint8_t[sizeKb * 1024])// NOLINT
  {}

  ~Memory() noexcept { delete[] data; }

  uint32_t size;// NOLINT
  uint8_t *data;// NOLINT
};

}// namespace Nemu

#endif /* MEMORYIMPL_H */
