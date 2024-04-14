#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

#include <ios>

class ScopeGuard {
public:
  ScopeGuard(std::ios& stream);
  ~ScopeGuard();

private:
  std::ios& stream_;
  std::streamsize precision_;
  std::ios_base::fmtflags flags_;
};

#endif
