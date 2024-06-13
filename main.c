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

void update_flags(uint16_t r) {
  if (reg[r] == 0) {
    reg[R_COND] = FL_ZRO;
  } else if (reg[r] >> 15) { // If high bit is 1, the result is negative.
    reg[R_COND] = FL_NEG;
  } else {
    reg[R_COND] = FL_POS;
  }
}

// Sign extend a negative number to 16 bits.
uint16_t sign_extend(uint16_t x, int bit_count) {
  if ((x >> (bit_count - 1)) & 1) { // If the high bit, up to bit_count, is 1,
                                    // the number is a negative number and must
                                    // be treated as such during sign extension.
    x |= (0xFFFF << bit_count);     // Sign extend, setting high bits to 1
                                    // for negative.
  }
  return x;
}

// ADD DR, SR1, SR2
// ADD DR, SR1, imm5
void op_add(uint16_t instr) {
  uint16_t dr = (instr >> 9) & 0x7;       // The dest register is bits 11-9 (3).
  uint16_t sr1 = (instr >> 6) & 0x7;      // The src register is bits 8-6 (3).
  uint16_t imm_mode = (instr >> 5) & 0x1; // imm mode flag is bit 5 (1).

  if (imm_mode) {
    // If imm mode is set, sr2 is obtained by sign-extending imm5 (5) to 16
    // bits.
    uint16_t imm5 = sign_extend(instr & /*0b0000000000011111=*/0x1F, 5);
    reg[dr] = reg[sr1] + imm5;
  } else {
    uint16_t sr2 = instr & 0x7;
    reg[dr] = reg[sr1] + reg[sr2];
  }

  update_flags(dr);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("vm [program] ..\n");
    exit(2);
  }

  // TODO: Load program into memory.

  reg[R_COND] = FL_ZRO; // Default start condition flag.
  reg[R_PC] = 0x3000;   // Default start program counter address.

  int running = TRUE;
  while (running) {
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12; // The opcode is bits 15-12 (4).

    switch (op) {
    case OP_BR:
      break;
    case OP_ADD:
      op_add(instr);
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
