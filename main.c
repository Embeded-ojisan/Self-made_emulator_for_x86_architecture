typedef struct 
{
    uint32_t registers[REGISTER_COUNT];

    uint32_t eflags;

    uint8_t* memory;

    uint32_t eip;
}Emulator;

Emulator* create_emu(size_t size, uint32_t eip, uint32_t esp)
{
    Emulator* emu = malloc(sizeof(Emulator));
    emu->memory = malloc(size);

    memset(emu->registers, 0, sizeof(emu->registers));

    emu->eip = eip;
    emu->registers[ESP] = esp;

    return emu;
}

void destroy_emy(Emulator* emu)
{
    free(emu->memory);
    free(emu);
}

int main(int argc, char* argv[])
{
    FILE* binary;
    Emulator* emu;

    if(argc != 2)
    {
        printf("usage: px86 filename\n");
        return 1;
    }

    emu = create_emu(MEMORY_SIZE, 0x7c00, 0x7c00);

    binary = fopen(argv[1], "rb");
    if(NULL == binary)
    {
        printf("%sファイルが開けません\n", argv[1]);
        return 1;
    }

    fread(emu->memory + 0x7c00, 1, 0x200, binary);
    fclose(binary);

    init_instructions();

    while(emu->eip < MEMORY_SIZE)
    {
        uint8_t code = get_code8(emu, 0);
        if(NULL == instructions[code])
        {
            printf("\n\nNot Implemented: %x\n\n");
            break;
        }

        instructions[code](emu);
        if(emu->eip == 0x00)
        {
            printf("\n\nend of program.\n\n");
            break;
        }
    }

    dump_registers(emu);
    destroy_emu(emu);
    return 0;
}