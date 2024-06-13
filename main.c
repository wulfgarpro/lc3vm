// vm.c
// A LC-3 (Little Computer) Virtual Machine (VM).
// See: https://en.wikipedia.org/wiki/Little_Computer_3.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// LC-3 is 16-bit addressable, with 65536 memory locations, addressing a total
// of 16*2^16 = 128KB of data.
#define MEMORY_MAX (1 << 16)

// LC-3 has 10 16-bit registers:
// * 8 general-purpose
// * 1 program counter, the next instruction to execute
// * 1 condition flag, info. about the most recently executed calc.
enum {
  R_R0 = 0, // General Purpose
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC,   // Program Counter
  R_COND, // Condition Flag
  R_COUNT,
};

// LC-3 has 16 opcodes.
// Background: something like Intel x86 is a "Complex Instruction Set Computer"
// (CISC), with hundreds of opcodes, while LC-3 is a "Reduced Instruction Set
// Computer" (RISC). More opcodes doesn't mean more functionality. It means
// writing complex functinality is simpler.
enum {
  OP_BR = 0, // Branch
  OP_ADD,    // Add
  OP_LD,     // Load
  OP_ST,     // Store
  OP_JSR,    // Jump Register
  OP_AND,    // Bitwise AND
  OP_LDR,    // Load Register
  OP_STR,    // Store Register
  OP_RTI,    // UNUSED
  OP_NOT,    // Bitwise NOT
  OP_LDI,    // Load Indirect
  OP_STI,    // Store Indirect
  OP_JMP,    // Jump
  OP_RES,    // UNUSED
  OP_LEA,    // Load Effective Address
  OP_TRAP    // Execute Trap
};

// LC-3 has 3 condition flags that can be stored in the R_COND. These flags
// provide information about the last executed calculation so programs can
// check logical conditions like `if (x > 0) { ... }`.
enum {
  FL_POS = 1 << 0, // Positive
  FL_ZRO = 1 << 1, // Zero
  FL_NEG = 1 << 2, // Negative
};

// Memory storage
uint16_t memory[MEMORY_MAX];
// Register storage
uint16_t reg[R_COUNT];

uint16_t mem_read(uint16_t addr) { return 0; }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("l3cvm [program] ..\n");
    exit(2);
  }

  // TODO: Read image file into memory.

  reg[R_COND] = FL_ZRO; // Default start condition flag.
  reg[R_PC] = 0x3000;   // Default start program counter address.

  int running = TRUE;
  while (running) {
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op =
        instr >> 12; // Right shift 12 to read the first 4 bits, the opcode.

    switch (op) {
    case OP_BR:
      break;
    case OP_ADD:
      break;
    case OP_LD:
      break;
    case OP_ST:
      break;
    case OP_JSR:
      break;
    case OP_AND:
      break;
    case OP_LDR:
      break;
    case OP_STR:
      break;
    case OP_NOT:
      break;
    case OP_LDI:
      break;
    case OP_STI:
      break;
    case OP_JMP:
      break;
    case OP_LEA:
      break;
    case OP_TRAP:
      break;
    // UNUSED
    case OP_RTI:
    case OP_RES:
    default:
      // Invalid opcode.
      break;
    }
  }

  return 0;
}
