#pragma once

#include <cstddef>
#include <memory>
#include <string_view>

#include "grid.hpp"
#include "rules/claiming_pair.hpp"
#include "rules/hidden_pair.hpp"
#include "rules/hidden_single.hpp"
#include "rules/naked_single.hpp"
#include "rules/pointing_elimination.hpp"
#include "rules/rule.hpp"

struct MaxDepth {
  size_t value;
};

struct VerbalSteps {
  bool value;
};

class Solver {
 public:
  Solver() = delete;
  Solver(std::string_view line, const MaxDepth max_depth,
         const VerbalSteps verbal_steps)
      : grid_(line),
        max_depth_(max_depth.value),
        verbal_steps_(verbal_steps.value) {
    rules_.emplace_back(std::make_unique<HiddenSingle>());
    rules_.emplace_back(std::make_unique<NakedSingle>());
    rules_.emplace_back(std::make_unique<PointingElimination>());
    rules_.emplace_back(std::make_unique<HiddenPair>());
    rules_.emplace_back(std::make_unique<ClaimingPair>());
  };

  auto solve() noexcept -> void;
  auto step() noexcept -> bool;
  auto print_grid() const noexcept { grid_.print(); }

 private:
  const size_t max_depth_{0uz};
  const bool verbal_steps_{false};
  std::vector<std::unique_ptr<Rule>> rules_{};
  Grid grid_;
};
