#include "Nemu/ReturnCodes.hpp"
#include "Private/Nemu/MemoryImpl.hpp"
#include <Nemu/Cpu.hpp>
#include <elf.h>
#include <fcntl.h>
#include <gelf.h>
#include <spdlog/spdlog.h>

#define CHECK_CPU_PTR(CPU)                       \
  if ((CPU) == nullptr) {                        \
    spdlog::error("Error invalid CPU pointer."); \
    return ReturnCode::INVALID_CPU_PTR;          \
  }

namespace Nemu {

struct Cpu
{
  Memory ram{ 5 * 1024 };// NOLINT 5Mb
};

Cpu *CreateCpu() { return new Nemu::Cpu(); }

void DestroyCpu(Cpu *cpu) { delete cpu; }

ReturnCode ExecuteInstruction(Cpu *cpu, uint32_t /*instruction*/)
{
  CHECK_CPU_PTR(cpu);

  return ReturnCode::OK;
}

ReturnCode LoadBinary(Cpu *cpu, const char *fileName)
{
  spdlog::info("Loading ELF: {}", fileName);

  if (elf_version(EV_CURRENT) == EV_NONE) {
    spdlog::error("Error initializing libelf: {}", elf_errmsg(-1));
    return ReturnCode::ERROR_LOADING_BINARY;
  }

  int fd = open(fileName, O_RDONLY, 0);
  if (fd < 0) {
    spdlog::error("Could not open file: {}", fileName);
    return ReturnCode::CANNOT_OPEN_FILE;
  }

  Elf *elf_ptr = nullptr;
  GElf_Ehdr ehdr;

  if (nullptr == (elf_ptr = elf_begin(fd, ELF_C_READ, nullptr))) {
    spdlog::error("Error reading ELF: {}", fileName);
    return ReturnCode::ERROR_LOADING_BINARY;
  }

  Elf_Kind ek = elf_kind(elf_ptr);
  std::string_view kind;

  switch (ek) {
  case ELF_K_AR:
    kind = "ar (1) archive";
    break;
  case ELF_K_ELF:
    kind = "elf object";
    break;
  case ELF_K_NONE:
    kind = "data";
    break;
  default:
    kind = "unrecognized";
  };

  spdlog::info("ELF kind: {}", kind);

  if (gelf_getehdr(elf_ptr, &ehdr) == nullptr) {
    spdlog::error("Error obtaining ELF header");
    elf_end(elf_ptr);
    close(fd);
    return ReturnCode::ERROR_LOADING_BINARY;
  }

  spdlog::info(
    "ELF class: {}bit", gelf_getclass(elf_ptr) == ELFCLASS32 ? 32 : 64);

  // Read sections
  char *name = nullptr;
  Elf_Scn *scn = nullptr;
  GElf_Shdr shdr;
  size_t shstrndx = 0;

  if (elf_getshdrstrndx(elf_ptr, &shstrndx) != 0) {
    spdlog::error("Error in elf_getshdrstrndx()");
    return ReturnCode::ERROR_LOADING_BINARY;
  }

  while ((scn = elf_nextscn(elf_ptr, scn)) != nullptr) {
    if (gelf_getshdr(scn, &shdr) != &shdr) {
      spdlog::error("Error in gelf_getshdr()");
      return ReturnCode::ERROR_LOADING_BINARY;
    }

    if ((name = elf_strptr(elf_ptr, shstrndx, shdr.sh_name)) == nullptr) {
      spdlog::error("Error in elf_strptr()");
      return ReturnCode::ERROR_LOADING_BINARY;
    }

    // FIXME!!!
    // Only loads text and data sections, just for quick testing
    auto section_id = elf_ndxscn(scn);
    if ((section_id == 1) || (section_id == 2)) {
      auto *memory_segment = GetRamMemory(cpu);
      auto *mem_ptr = GetMemoryPosition(memory_segment, shdr.sh_addr);

      assert(mem_ptr);
      lseek(fd, static_cast<int64_t>(shdr.sh_offset), SEEK_SET);
      auto ret = read(fd, mem_ptr, shdr.sh_size);

      if (ret != static_cast<ssize_t>(shdr.sh_size)) {
        spdlog::error("Error reading section {}, {}. addr: 0x{:08x}, {} bytes",
          elf_ndxscn(scn),
          name,
          shdr.sh_addr,
          shdr.sh_size);

        elf_end(elf_ptr);
        close(fd);
        return ReturnCode::ERROR_LOADING_BINARY;
      }

      spdlog::info("Loaded Section {}, {}. addr: 0x{:08x}, {} bytes",
        elf_ndxscn(scn),
        name,
        shdr.sh_addr,
        shdr.sh_size);
    } else {
      spdlog::info("Skipped Section {}, {}. addr: 0x{:08x}, {} bytes",
        elf_ndxscn(scn),
        name,
        shdr.sh_addr,
        shdr.sh_size);
    }
  }

  elf_end(elf_ptr);
  close(fd);

  return ReturnCode::OK;
}

Memory *GetRamMemory(Cpu *cpu) { return &cpu->ram; }

}// namespace Nemu
