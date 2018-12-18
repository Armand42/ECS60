#ifndef CPURUNNER_H
#define CPURUNNER_H

typedef enum{
  ADD, LOAD, STORE, DONE    // opCode - can be one of the four 0 1 2 3
} OpCode;

typedef struct
{
  unsigned addr1;
  unsigned addr2;
  unsigned addr3;
} Instruction;    // 3 addresses - each address is a nonnegative integer 

#endif

