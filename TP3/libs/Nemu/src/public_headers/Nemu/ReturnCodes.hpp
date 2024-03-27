#ifndef RETURNCODES_H
#define RETURNCODES_H

namespace Nemu {
enum class ReturnCode {
  OK = 0,
  CANNOT_CREATE_CPU = 1,
  INVALID_CPU_PTR = 2,
  ERROR_LOADING_BINARY = 10,
  CANNOT_OPEN_FILE = 11,
  INVALID_BINARY_FILE = 12,
};
}// namespace Nemu

#endif /* ERRORCODES_H */
