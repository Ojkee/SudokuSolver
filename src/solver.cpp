#include "solver.hpp"

auto Solver::solve() noexcept -> void {
  for (auto depth{0uz}; !grid_.solved() && depth < max_depth_; ++depth) {
    const auto changed = step();
    if (changed && verbal_steps_) {
      grid_.print();
    }
  }
}

auto Solver::step() noexcept -> bool {
  for (const auto& rule : rules_) {
    const auto changed = rule->apply(grid_);
    if (changed) return true;
  }
  return false;
}
