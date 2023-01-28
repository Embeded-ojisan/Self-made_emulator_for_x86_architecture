#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdint.h>

enum Regsters
{
    EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI, REFISTERS_COUNT
};

typedef struct
{
    uint32_t    registers[REFISTERS_COUNT];
    uint32_t    eflags;
    uint8_t*    memory;
    uint32_t    eip;
} Emulator;

#endif