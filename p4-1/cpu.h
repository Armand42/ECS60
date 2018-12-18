// Author: Sean Davis
#ifndef cpuH
#define cpuH

#include "CPURunner.h"

typedef struct        // cache struct for table of 64000 bytes
{
  int value;
  bool dirty;
  unsigned address;
} CacheLine;

class CPU
{
  CacheLine* cache;
public:
  CPU();
  void operation(OpCode &opCode, Instruction &instruction, int &buffer);
};
#endif
