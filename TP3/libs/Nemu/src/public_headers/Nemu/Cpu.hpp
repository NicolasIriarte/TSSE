#ifndef NEMU_CPU_HPP
#define NEMU_CPU_HPP

#include "Nemu/NemuExport.h"
#include "Nemu/ReturnCodes.hpp"

#include <cstdint>

namespace Nemu {

struct Memory;

/**
 * @brief Type representing a CPU type.
 *
 * @details An opaque struct was decided to use to shield its implementation.
 */
struct Cpu;

/**
 * @brief Create a new CPU.
 *
 * @details Create a new CPU instance. This function is responsible for
 *          allocating memory for the CPU and initializing it.
 *
 * @return Returns a pointer to the newly created CPU.
 *
 * @note The caller is responsible for freeing the returned CPU.
 */
NEMU_EXPORT Cpu *CreateCpu();


/**
 * @brief Destroy a CPU.
 *
 * @details Destroy a CPU instance. This function is responsible for freeing the
 *          memory allocated for the CPU.
 *
 * @param cpu The CPU to be destroyed.
 */
NEMU_EXPORT void DestroyCpu(Cpu *cpu);


/**
 * @brief Execute a single instruction manually.
 *
 * @details This function is responsible for executing a single instruction
 *          on the CPU. The instruction is passed as a 32-bit unsigned integer.
 *
 * @param cpu The CPU to execute the instruction on.
 * @param instruction The instruction to be executed.
 *
 * @return Returns -1 if the instruction is invalid, -2 if an error occurred
 *         during execution, 0 or greater if the instruction was executed
 *         successfully.
 */

NEMU_EXPORT ReturnCode ExecuteInstruction(Cpu *cpu, uint32_t instruction);

/**
 * @brief Load a binary file into the CPU.
 *
 * @details This function is responsible for loading a binary file into the CPU.
 *          The given file must have the following criteria:
 *             - The file must exist.
 *
 * @param cpu The CPU to load the binary file into.
 * @param fileName The name of the binary file to load.
 *
 * @return Returns -1 if the file does not exist or invalid pointer, 0 if the
 *         file was loaded.
 */

NEMU_EXPORT ReturnCode LoadBinary(Cpu *cpu, const char *fileName);

/**
 * @brief Get a Memory object from the CPU.
 *
 * @details This function returns a pointer to the Memory object from the CPU.
 *
 * @param cpu The CPU to get the Memory object from.
 *
 * @return Returns a pointer to the Memory object.
 */

NEMU_EXPORT Memory *GetRamMemory(Cpu *cpu);


}// namespace Nemu

#endif /* NEMU_CPU_HPP */
