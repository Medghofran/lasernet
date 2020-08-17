#pragma once

#include "common.hpp"
#include <array>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

namespace lsnet {
namespace utils {

// stop function
template <std::size_t ind = 0, typename tp>
inline typename std::enable_if<std::tuple_size<tp>::value == ind, void>::type
parsePoint(std::istream &stream, tp &tup, std::vector<float> &container) {}

// recurse over all tuple elements in compile time
template <std::size_t ind = 0, typename tp>
    inline typename std::enable_if <
    ind<std::tuple_size<tp>::value, void>::type
    parsePoint(std::istream &stream, tp &tup, std::vector<float> &container) {
  // parse the value into a float
  float value;
  stream.read((char *)(&value), sizeof(std::get<ind>(tup)));
  container.push_back(value);

  parsePoint<ind + 1, tp>(stream, tup, container);
}

// parses a file given a well defined structure describing the cloud format
template <typename pc,
          std::enable_if<std::tuple_size<pc>::value >= 3> *unused = nullptr>
void parseVelodyneFile(std::string path, std::vector<float> &container) {
  // create an exemplary tuple
  pc tup;
  std::ifstream stream(path);
  if (stream.fail()) {
    std::cout << "failed to load file" << std::endl;
    return;
  }

  // interpret all bytes as values (no header info)
  while (!stream.eof()) {
    parsePoint(stream, tup, container);
  }
}

// start point cloud file parsing coroutines
template <typename pc,
          std::enable_if<std::tuple_size<pc>::value >= 3> *unused = nullptr>
void startProducer(std::string path, VelodyneMonitor<pc> &mon,
                   int threadCount = 1) {
  // devide the files contained within that directory across the number of
  // threads passed as argument
  mon.emptyCount--;
  std::unique_lock(mon.queueMutex);
  mon.queue.emplace(parseVelodyneFile(path));
  mon.fillCount++;
}

} // namespace utils
} // namespace lsnet