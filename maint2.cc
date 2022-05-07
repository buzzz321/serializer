#include "bitsery/adapter/buffer.h"
#include "bitsery/bitsery.h"
#include "bitsery/traits/string.h"
#include "bitsery/traits/vector.h"
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

struct MyData {
  uint16_t x;
  uint16_t y;
  std::vector<uint32_t> samples;
};

template <typename S> void serialize(S &s, MyData &o) {
  s.value2b(o.x);
  s.value2b(o.y);
  s.container4b(o.samples, 1000);
}

using MyDatas = std::vector<MyData>;

template <typename S> void serialize(S &s, MyDatas &o) { s.container(o, 1000); }

// some helper types
using Buffer = std::vector<uint8_t>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;

void serialize(std::vector<MyData> indata) {
  Buffer buffer;
  auto writtenSize = bitsery::quickSerialization(OutputAdapter{buffer}, indata);

  std::cout << "Size: " << std::hex << writtenSize << std::endl;

  for (size_t index = 0; index < writtenSize; index++) {
    cout << std::hex << " 0x" << (uint64_t)buffer[index] << endl;
  }
}

int main() {
  cout << "Serializer!" << endl;
  std::vector<MyData> data{
    {.x = 0x1234,
     .y = 0x5678,
     .samples{0x1234aabb, 0x34ffeeff, 0x5612, 0x7812, 0x9012}},
    {.x = 0x12, .y = 0x13, .samples{0x12aabbcc, 0x34ddeeff, 0x56, 0x78, 0x90}}};

  serialize(data);
  return 0;
}
