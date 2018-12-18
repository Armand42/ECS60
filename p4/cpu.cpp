// Author: Sean Davis
#include "cpu.h"

#define SIZE 64000

CPU::CPU()
{
  cache = new CacheLine[SIZE];
} // CPU()


void CPU::operation(OpCode &opCode, Instruction &instruction, int &buffer)
{
  unsigned addr1 = instruction.addr1;
  unsigned addr2 = instruction.addr2;
  unsigned addr3 = instruction.addr3;
  
  switch (opCode)
  {
    case ADD : // *addr3 = *addr1 + *addr2
                if (cache[addr1 % SIZE].address != addr1) { // if the mod of table size does not contain address. request from RAM (LOAD)
                    opCode = LOAD;
                }
                else if (cache[addr2 % SIZE].address != addr2) { // or if it does not contain address 2
                  instruction.addr2 = addr1;  // a little confused why we need this
                  instruction.addr1 = addr2;
                  opCode = LOAD;
                }
                else {
                  if (cache[addr3 % SIZE].address != addr3) {
                    instruction.addr1 = addr3;
                    buffer = cache[addr3 % SIZE].value;
                    opCode = STORE;
                  }
                  else {
                      cache[addr3 % SIZE].value = cache[addr1 % SIZE].value + cache[addr1 % SIZE].value;
                  }
                }
    case LOAD :   // buffer contains int requested from RAM
                cache[addr1 % SIZE].value = buffer;
                cache[addr1 % SIZE].address = addr1;

                // CALL RETURN FUNCTION?

    case STORE:  // Sent by RAM after a STORE


    case DONE : //  All ADDs in file have been sent.  Time to STORE dirty cache.

              if (cache[addr1 % SIZE].dirty != addr1) {
                opCode = STORE;
              }
  } // switch



} // operation()



