#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: expr_gen <output_directory>" << std::endl;
    return 64;
  }

  std::string output_dir{argv[1]};

  std::cout << "writing to " << output_dir << "..." << std::endl;

  defineAst(output_dir

  std::cout << "done." << std::endl;

  return 0;
}
