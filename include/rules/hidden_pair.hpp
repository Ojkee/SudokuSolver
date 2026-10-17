#pragma once

#include "../grid.hpp"
#include "rule.hpp"

class HiddenPair final : public Rule {
 public:
  [[nodiscard]] auto name() const noexcept -> const std::string override {
    return "hidden_pair";
  }
  [[nodiscard]] auto apply(Grid& grid) const noexcept -> bool override;
};
