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
  unsigned tag1 = addr1 % SIZE;
  unsigned addr2 = instruction.addr2;
  unsigned tag2 = addr2 % SIZE;
  unsigned addr3 = instruction.addr3;
  unsigned tag3 = addr3 % SIZE;
  
  switch (opCode)
  {
    case ADD : // *addr3 = *addr1 + *addr2
                if (cache[tag1].address != addr1) { // if the mod of table size does not contain address. request from RAM (LOAD)
                    opCode = LOAD;
                }
                else if (cache[tag2].address != addr2) { // or if it does not contain address 2
                  //instruction.addr2 = addr1;  // a little confused why we need this
                  instruction.addr1 = addr2;
                  opCode = LOAD;
                }
                else {
                  if (cache[tag3].address != addr3 && cache[tag3].dirty) {
                    instruction.addr1 = addr3;
                    buffer = cache[tag3].value;
                    opCode = STORE;
                  }
                  else {
                      cache[addr3 % SIZE].value = cache[addr1 % SIZE].value + cache[addr1 % SIZE].value;
                  }
                }
    case LOAD :   // buffer contains int requested from RAM
                if (cache[tag1].dirty) {
                   opCode = STORE;
                }
                cache[tag1].value = buffer;
                cache[tag1].address = addr1;
                if (cache[tag2] != addr2) {
                    instruction.addr1 = addr2;
                    opCode = LOAD;
                }
                else{
                    if (cache[tag3].address != addr3 && cache[tag3].dirty){
                       instruction.addr1 = addr3;
                       buffer = cache[tag3].value;
                       opCode = STORE;
                    }
                    cache[tag3].value = cache[tag1].value + cache[tag2].value;
                }

                // CALL RETURN FUNCTION?

    case STORE:  // Sent by RAM after a STORE


    case DONE : //  All ADDs in file have been sent.  Time to STORE dirty cache.

              if (cache[addr1 % SIZE].dirty != addr1) {
                opCode = STORE;
              }
  } // switch



} // operation()
