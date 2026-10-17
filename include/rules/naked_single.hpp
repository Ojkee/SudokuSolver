#pragma once

#include "../grid.hpp"
#include "rule.hpp"

class NakedSingle final : public Rule {
 public:
  [[nodiscard]] auto name() const noexcept -> const std::string override {
    return "naked_single";
  }
  [[nodiscard]] auto apply(Grid& grid) const noexcept -> bool override;
};
