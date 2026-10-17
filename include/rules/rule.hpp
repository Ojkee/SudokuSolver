#pragma once

#include <string>

#include "../grid.hpp"

class Rule {
 public:
  virtual ~Rule() = default;
  [[nodiscard]] virtual auto name() const noexcept -> const std::string = 0;
  [[nodiscard]] virtual auto apply(Grid& grid) const noexcept -> bool = 0;
};
