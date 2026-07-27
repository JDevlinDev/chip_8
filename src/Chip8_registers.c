#include <string.h>
#include <stdio.h>

#include "Chip8_registers.h"

void Chip8_VRegToString(const Chip8_Registers *reg, char *str, size_t size)
{
   snprintf(str, size,
      "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
      reg->V[0], reg->V[1], reg->V[2], reg->V[3],
      reg->V[4], reg->V[5], reg->V[6], reg->V[7],
      reg->V[8], reg->V[9], reg->V[10], reg->V[11],
      reg->V[12], reg->V[13], reg->V[14], reg->V[15]);
}