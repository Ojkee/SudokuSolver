#include <fstream>
#include <iostream>

#include "../include/solver.hpp"

auto line_of_file(const std::string file_path) {
  auto file = std::ifstream(file_path);
  if (!file.is_open()) std::cerr << "Couldn't load the file\n";

  std::string line;
  getline(file, line);
  file.close();
  return line;
}

auto main() -> int {
  const auto line = line_of_file("examples/hidden_pair.txt");
  Solver solver{
      line,
      MaxDepth{1000uz},
      VerbalSteps{false},
  };

  solver.print_grid();
  solver.solve();
  solver.print_grid();

  return EXIT_SUCCESS;
}
