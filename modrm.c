
void parse_modrm(Emulator* emu, ModRM* modrm)
{
    uint8_t code;

    memset(modrm, 0, sizeof(ModRM));

    code = get_code8(emu, 0);
    modrm->mod = ((code & 0xC0) >> 6);
    modrm->opecode = ((code & 0x38) >> 3);
    modrm->rm = code & 0x07;

    emu->eip += 1;

    if(modrm->mod != 3 && modrm->rm == 4)
    {
        modrm->sib = get_code8(emu, 0);
        emu->eip += 1;
    }

    if( 
        (
            modrm->mod == 0 
            && modrm->rm == 5
        )
        || 
        (modrm->mod == 2)
    )
    {
        modrm->disp32 = get_sign_code32(emu, 0);
        emu->eip += 4;
    }
    else if(modrm->mod == 1)
    {
        modrm->disp8 = get_sign_code8(emu, 0);
        emu->eip += 1;
    }
}