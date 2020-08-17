#include "pc_utils.hpp"
#include <chrono>
#include <iostream>


int main() {
  std::string pointCloudFile =
      "/home/loukil/Documents/Projects/LaserNet/example/000000.bin";
  // test loading a point cloud
  using pc = std::array<float, 4>;
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i++ < 10000;) {
    std::vector<float> cont;
    lsnet::utils::parseVelodyneFile<pc>(pointCloudFile, cont);
  }
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - start);
  std::cout << "operation done in :" << (float)duration.count() / 10000
            << "(ms)" << std::endl;
}