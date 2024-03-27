#include "Nemu/Cpu.hpp"
#include "Nemu/Memory.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace Nemu;

// Anonymous namespace to avoid name collisions.
namespace {

// SetUp and TearDown
struct CpuFixture
{
  CpuFixture() : cpu(CreateCpu())
  {
    REQUIRE(cpu != nullptr);

    memory = GetRamMemory(cpu);
    REQUIRE(memory != nullptr);
  }

  ~CpuFixture()
  {
    DestroyCpu(cpu);
    cpu = nullptr;
  }

  // Delete copy and move constructors.
  CpuFixture(const CpuFixture &) = delete;
  CpuFixture(CpuFixture &&) = delete;
  CpuFixture &operator=(const CpuFixture &) = delete;
  CpuFixture &operator=(CpuFixture &&) = delete;

  Cpu *cpu{};// NOLINT
  Memory *memory{};// NOLINT
};

}// namespace


TEST_CASE("A Memory pointer can be obtained from the CPU.", "[Memory]")
{
  auto *cpu = CreateCpu();
  auto *memory = GetRamMemory(cpu);
  REQUIRE(memory != nullptr);

  DestroyCpu(cpu);
}

TEST_CASE_METHOD(CpuFixture, "Memory can be readed and written.", "[Memory]")
{
  auto *raw_mem_ptr = GetMemoryPosition(memory, 0);

  uint8_t value_1 = 0x01;
  raw_mem_ptr[0] = value_1;
  REQUIRE(raw_mem_ptr[0] == value_1);

  uint8_t value_2 = 0x02;
  raw_mem_ptr[0] = value_2;
  REQUIRE(raw_mem_ptr[0] == value_2);
}
