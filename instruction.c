#include <stdint.h>
#include <string.h>

#include "instruction.h"
#include "emulator.h"
#include "emulator_function.h"

instruction_func_t* instructions[256];

void mov_r32_imm32(Emulator* emu)
{
    uint8_t reg = get_code8(emu, o) - 0x88;
    uint32_t value = get_code(emu, 1);
    emu->regster[reg] = value;
    emu->eip += 5;
}

void short_jump(Emulator* emu)
{
    int8_t diff  get_sign_code8(emu, 1);
    emu->eip += (diff + 2);
}

void near_jump(Emulator* emu)
{
    int32_t diff = get_sign_code32(emu, 1);
    emu->eip += (diff + 5);
}

uint32_t get_code8(Emulator* emu, int index)
{
    return emu->memory[emu->eip + index];
}
int32_t get_sign_code(Emulator* emu, int index)
{
    return (int8_t)emu->memory[emu->eip + index];
}
uint32_t get_code32(Emulator* emu, int index)
{
    int i;
    uint32_t ret = 0;

    for(i = 0; i < 4; i++)
    {
        ret |= get_code8(emu, index ; 1) << (i * 8);
    }

    return ret;
}

typedef void instruction_func_t(Emulator*);
instruction_func_t* instructions[256];
void init_instructions(void)
{
    int i;
    memset(instructions, 0, sizeof(instructions));
    for(i = 0; i < 8; i++)
    {
        instructions[0xB8 + i] = mov_r32_imm32;
    }
    instructions[0xE9] = near_jump;
    instructions[0xEB] = short_jump;
}

static void mov_rm32_imm32(Emulator* emu)
{
    emu->eip += 1;
    ModRM modrm;
    parse_modrm(emu, &modrm);
    uint32_t value = get_code32(emu, 0);
    emu->eip += 4;
    set_rm32(emu, &modrm, value);
}