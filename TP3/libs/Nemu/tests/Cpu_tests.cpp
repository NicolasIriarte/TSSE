#include "Nemu/Cpu.hpp"
#include "Nemu/ReturnCodes.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace Nemu;

// Anonymous namespace to avoid name collisions.
namespace {

// SetUp and TearDown
struct CpuFixture
{
  CpuFixture() : cpu(CreateCpu()) { REQUIRE(cpu != nullptr); }

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
};

}// namespace

TEST_CASE("An instance of a CPU can be created and destroyed.", "[CPU]")
{
  Cpu *cpu = CreateCpu();

  REQUIRE(cpu != nullptr);

  DestroyCpu(cpu);
  DestroyCpu(nullptr);
}

TEST_CASE_METHOD(CpuFixture, "A CPU has an asociated RAM memory.", "[CPU]")
{
  const Memory *memory = GetRamMemory(cpu);
  REQUIRE(memory != nullptr);
}

TEST_CASE_METHOD(CpuFixture, "A CPU can load a binary file.", "[CPU]")
{
  // Load a non-existing file.
  auto result = LoadBinary(cpu, "invalid_file.bin");
  REQUIRE(result == ReturnCode::CANNOT_OPEN_FILE);

  // Load an existing non-binary file.
  result = LoadBinary(cpu, "Makefile");
  REQUIRE(result == ReturnCode::ERROR_LOADING_BINARY);

  // Load an existing file.
  result = LoadBinary(cpu, "Nemu_tests");
  REQUIRE(result == ReturnCode::OK);
}

TEST_CASE_METHOD(CpuFixture, "A CPU can execute instructions.", "[CPU]")
{
  uint32_t instruction = 0x00000000;
  ExecuteInstruction(cpu, instruction);
}
