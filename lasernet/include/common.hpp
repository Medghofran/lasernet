#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

namespace lsnet {
// define the synchonization models here
constexpr uint8_t MAX_QUEUE_SIZE = 255;

// handle multi-threaded file io
template <typename pc,
          std::enable_if<std::tuple_size<pc>::value >= 3> *unused = nullptr>
struct VelodyneMonitor {
  uint8_t fillCount = 0;
  uint8_t emptyCount = MAX_QUEUE_SIZE;
  std::mutex queueMutex;
  std::queue<std::vector<float>> queue;
};

} // namespace lsnet