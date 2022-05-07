#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;

struct MyData {
  uint16_t x;
  uint16_t y;
  std::vector<uint32_t> samples;
};

void serialize(std::vector<MyData> indata) {
  size_t size{0};

  size += sizeof(size_t); // add space for array of MyData
  size += sizeof(time_t); // add space for a time stamp too just in case
  for (const auto &item : indata) {
    // clang-format off
    size += sizeof(MyData::x) + sizeof(MyData::y) + item.samples.size() * sizeof(uint32_t);
    // clang-format on
    size += sizeof(size_t); // need to add space for array lenght too..
  }
  cout << "Total size = " << size << endl;

  uint8_t *buffer = new uint8_t[size];
  memset(buffer, 0, size);
  size_t offset = 0;

  *((size_t *)buffer) = indata.size();
  offset += sizeof(size_t);

  // add optional timestamp here..
  for (auto const &item : indata) {
    *((uint16_t *)(buffer + offset)) = item.x;
    offset += sizeof(MyData::x);
    *((uint16_t *)(buffer + offset)) = item.y;
    offset += sizeof(MyData::y);

    *((size_t *)(buffer + offset)) = item.samples.size();
    offset += sizeof(size_t);

    for (auto const &sample : item.samples) {
      *((uint32_t *)(buffer + offset)) = sample;
      offset += sizeof(uint32_t);
    }
  }

  cout << "Offset = " << offset << " size = " << size << endl;
  for (size_t index = 0; index < size; index++) {
    cout << std::hex << " 0x" << (uint64_t)buffer[index] << endl;
  }

  ofstream outfile;
  outfile.open("data.bin", ios::out | ios::binary);

  if (outfile) {
    outfile.write((char *)buffer, size);
  }
  delete[] buffer;
}

int main() {
  cout << "Serializer!" << endl;
  std::vector<MyData> data{
      {.x = 0x1234,
       .y = 0x5678,
       .samples{0x1234aabb, 0x34ffeeff, 0x5612, 0x7812, 0x9012}},
      {.x = 0x12,
       .y = 0x13,
       .samples{0x12aabbcc, 0x34ddeeff, 0x56, 0x78, 0x90}}};

  serialize(data);
  return 0;
}
