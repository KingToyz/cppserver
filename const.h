#pragma once
#include <stdint.h>
const int ReadEvent = 0x12345;
const int WriteEvent = 0x12346;
const int MAX = 1024;
const uint32_t ACCPET = 0;
const uint32_t READ = 1;
const uint32_t WRITE = 2;
const uint32_t DEL = 3;
const int MAX_BUF = 10 * 1024;