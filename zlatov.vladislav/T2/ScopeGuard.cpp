#include "ScopeGuard.h"

ScopeGuard::ScopeGuard(std::ios& stream) : stream_(stream) {
  precision_ = stream_.precision();
  flags_ = stream_.flags();
}

ScopeGuard::~ScopeGuard() {
  stream_.precision(precision_);
  stream_.flags(flags_);
}
