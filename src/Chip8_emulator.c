#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>

#include "Chip8_emulator.h"

static const uint8_t chip8_default_character_set[] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

static int Chip8_WaitForKeyPress(Chip8_Emulator *chip8)
{
    SDL_Event event;

    while (SDL_WaitEvent(&event)) {
        if (event.type != SDL_EVENT_KEY_DOWN)
            continue;

        int key = Chip8_MapKey(event.key.scancode);
        if (key != -1)
            return key;
    }
}

static void Chip8_LoadIntoMemory(Chip8_Emulator *chip8, const uint8_t *buf, size_t size)
{
    if ((size + CHIP8_PROGRAM_LOAD_ADDRESS) >= CHIP8_MEMORY_SIZE)
    {
        fprintf(stderr, "Program exceeds maximum memory size!\n");
        exit(EXIT_FAILURE);
    }
    memcpy(&chip8->memory.memory[CHIP8_PROGRAM_LOAD_ADDRESS], buf, size);
    chip8->registers.PC = CHIP8_PROGRAM_LOAD_ADDRESS;
}

static void Chip8_LoadBCD(Chip8_Emulator *chip8, uint8_t val)
{
    // Hundreds digit: divide by 100
    chip8->memory.memory[chip8->registers.I] = val / 100;
    
    // Tens digit: divide by 10, then get the remainder of 10
    chip8->memory.memory[chip8->registers.I + 1] = (val / 10) % 10;
    
    // Ones digit: get the remainder of 10
    chip8->memory.memory[chip8->registers.I + 2] = val % 10;
}

static void Chip8_DecodeExecute(Chip8_Emulator *chip8, uint16_t opcode)
{
    uint8_t x = CHIP8_NIBBLE_X(opcode);
    uint8_t y = CHIP8_NIBBLE_Y(opcode);
    uint8_t n = CHIP8_NIBBLE_N(opcode);
    uint8_t nn = CHIP8_NIBBLE_NN(opcode);
    uint16_t nnn = CHIP8_NIBBLE_NNN(opcode);

    switch (0xf000 & opcode) {

    /* 1nnn - JP addr: Jump to location nnn */
    case 0x1000:
        chip8->registers.PC = nnn;
    break;

    /* 2nnn - CALL addr: Call subroutine at nnn. */
    case 0x2000:
        Chip8_Push(chip8, chip8->registers.PC);
        chip8->registers.PC = nnn;
    break;

    /* 3xnn - SE V[x], byte: Skip next instruction if V[x] == nn. */
    case 0x3000:
        if (chip8->registers.V[x] == nn)
            chip8->registers.PC += 2;
    break;

    /* 4xnn - SNE V[x], byte: Skip next instruction if V[x] != nn */
    case 0x4000:
        if (chip8->registers.V[x] != nn)
            chip8->registers.PC += 2;
    break;
    
    /* 5xy0 - SE V[x], V[y]: Skip next instruction if V[x] == V[y] */
    case 0x5000:
        if(chip8->registers.V[x] == chip8->registers.V[y])
            chip8->registers.PC += 2;
    break;

    /* 6xnn - LD V[x], byte: puts the value nn into register V[x] */
    case 0x6000:
        chip8->registers.V[x] = nn;
    break;

    /* 7xnn - ADD V[x], byte: Adds the value nn to the value of register V[x], then stores the result in V[x] */
    case 0x7000:
        chip8->registers.V[x] += nn;
    break;

    /* Bitwise operations */
    case 0x8000:
        switch(n) {

        /* 8xy0 - LD Vx, Vy: Set Vx = Vy*/
        case 0x00:
            chip8->registers.V[x] = chip8->registers.V[y];
        break;

        /* 8xy1 - OR V[x], V[y]: Set V[x] = V[x] OR V[y] */
        case 0x01:
            chip8->registers.V[x] |= chip8->registers.V[y];
        break;
        
        /* 8xy2 - AND V[x], V[y]: Set V[x] = V[x] AND V[y] */
        case 0x02:
            chip8->registers.V[x] &= chip8->registers.V[y];
        break;

        /* 8xy3 - XOR V[x], V[y]: Set V[x] = V[x] XOR V[y] */
        case 0x03:
            chip8->registers.V[x] ^= chip8->registers.V[y];
        break;
        
        /* 8xy4 - ADD V[x], V[y]: Set V[x] = V[x] + V[y], set V[F] = carry */    
        case 0x04:
            chip8->registers.V[CHIP8_VF] = (chip8->registers.V[x] + chip8->registers.V[y]) > 0xff;
            chip8->registers.V[x] += chip8->registers.V[y];
        break;

        /* 8xy5 - SUB V[x], V[y]: Set V[x] = V[x] - V[y], set V[F] = NOT borrow. */
        case 0x05:
            chip8->registers.V[CHIP8_VF] = chip8->registers.V[x] > chip8->registers.V[y];
            chip8->registers.V[x] -= chip8->registers.V[y];
        break;

        /* 8xy6 - SHR V[x] {, Vy}: Set V[x] = V[x] SHR 1 */
        case 0x06:
            chip8->registers.V[CHIP8_VF] = chip8->registers.V[x] & 0x01;
            chip8->registers.V[x] /= 2;
        break;

        /* 8xy7 - SUBN V[x], V[y]: Set V[x] = V[y] - V[x], set V[F] = NOT borrow */
        case 0x07:
            chip8->registers.V[CHIP8_VF] = chip8->registers.V[y] > chip8->registers.V[x];
            chip8->registers.V[x] = chip8->registers.V[y] - chip8->registers.V[x];
        break;

        /* 8xyE - SHL Vx {, Vy}: Set Vx = Vx SHL 1 */
        case 0x0e:
            chip8->registers.V[CHIP8_VF] = (chip8->registers.V[x] & 0x80) >> 7;
            chip8->registers.V[x] *= 2;
        break;
        }
    break;

    /* 9xy0 - SNE V[x], V[y]: Skip next instruction if V[x] != [Vy] */
    case 0x9000:
        if (chip8->registers.V[x] != chip8->registers.V[y])
            chip8->registers.PC += 2;
    break;

    /* Annn - LD I, addr: The value of register I is set to nnn */
    case 0xa000:
        chip8->registers.I = nnn;
    break;

    /* Bnnn - JP V[0], addr: Jump to location nnn + V[0] */
    case 0xb000:
        chip8->registers.PC = nnn + chip8->registers.V[0];
    break;

    /* Cxkk - RND V[x], byte: Set V[x] = random byte AND nn */
    case 0xc000:
        chip8->registers.V[x] = SDL_rand(256) & nn;
    break;

    /* Dxyn - DRW V[x], V[y], nibble: Display n-byte sprite starting at memory location I at (V[x], V[y]), set VF = collision */
    case 0xd000:
        chip8->registers.V[CHIP8_VF] = Chip8_DrawSprite(
            &chip8->display,
            chip8->registers.V[x],
            chip8->registers.V[y],
            &chip8->memory.memory[chip8->registers.I], n);
    break;

    case 0xe000:
        switch(nn) {

        /* Ex9E - SKP V[x]: Skip next instruction if key with the value of V[x] is pressed */
        case 0x9e:
            if (Chip8_KeyIsDown(&chip8->keyboard, chip8->registers.V[x]))
                chip8->registers.PC += 2;
         break;

        /* ExA1 - SKNP V[x]: Skip next instruction if key with the value of V[x] is not pressed */
        case 0xa1:
            if (!Chip8_KeyIsDown(&chip8->keyboard, chip8->registers.V[x]))
                chip8->registers.PC += 2;
        break;
        }
    break;

    /* Keyboard, sound, and drawing */
    case 0xf000:
        switch(nn) {

        /* Fx07 - LD V[x], DT: Set V[x] = delay timer value */
        case 0x07:
            chip8->registers.V[x] = chip8->registers.DT;
            break;

        /* Fx0A - LD V[x], K: Wait for a key press, store the value of the key in V[x] */
        case 0x0a:
            int key = Chip8_WaitForKeyPress(chip8);
            chip8->registers.V[x] = key;
            break;
        
        /* Fx15 - LD DT, V[x]: Set delay timer = V[x] */
        case 0x15:
            chip8->registers.DT = chip8->registers.V[x];
            break;

        /* Fx18 - LD ST, V[x]: Set sound timer = V[x] */
        case 0x18:
            chip8->registers.ST = chip8->registers.V[x];
            break;

        /* Fx1E - ADD I, V[x]: Set I = I + V[x] */
        case 0x1e:
            chip8->registers.I += chip8->registers.V[x];
            break;

        /* Fx29 - LD F, Vx: Set I = location of sprite for digit Vx */
        case 0x29:
            chip8->registers.I = (chip8->registers.V[x] & 0x0f) * 5;
            break;

        /* Fx33 - LD B, Vx: Store BCD representation of Vx in memory locations I, I+1, and I+2. */
        case 0x33:
            Chip8_LoadBCD(chip8, chip8->registers.V[x]);
            break;
        
        /* Fx55 - LD [I], V[x]: Store registers V[0] through V[x] in memory starting at location I */
        case 0x55:
            for (int i = 0; i <= x; i++) {
                Chip8_SetMemory(&chip8->memory, chip8->registers.I + i, chip8->registers.V[i]);
            }
            break;
        
        /* Fx65 - LD Vx, [I]: Read registers V[0] through V[x] from memory starting at location I */
        case 0x65:
            for (int i = 0; i <= x; i++) {
                chip8->registers.V[i] = Chip8_GetMemory(&chip8->memory, chip8->registers.I + i);
            }
            break;
        }
    }
}

void Chip8_Init(Chip8_Emulator *chip8)
{
    memset(chip8, 0, sizeof(Chip8_Emulator));
    memcpy(&chip8->memory.memory, chip8_default_character_set, sizeof(chip8_default_character_set));
    Chip8_InitializeAudio(&chip8->audio);
}

size_t Chip8_Load(Chip8_Emulator *chip8, char *fname)
{
    errno = 0;
    FILE *f = fopen(fname, "r");

    if (!f)
    {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 0;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t buffer[CHIP8_MEMORY_SIZE];
    int res = fread(buffer, fsize, 1, f);
    if (res != 1)
    {
        fclose(f);
        return 0;
    }
    fclose(f);
    Chip8_LoadIntoMemory(chip8, buffer, fsize);

    return fsize;
}

uint16_t Chip8_Fetch(Chip8_Emulator *chip8)
{
    uint16_t opcode = Chip8_GetOpcode(&chip8->memory, chip8->registers.PC);
    chip8->registers.PC += 2;
    return opcode;
}

void Chip8_Execute(Chip8_Emulator *chip8, uint16_t opcode)
{
    switch (opcode)
    {

    /* CLS: Clear the display */
    case 0x00E0:
        Chip8_ClearDisplay(&chip8->display);
        break;

    /* RET: Return from a subroutine */
    case 0x00EE:
        chip8->registers.PC = Chip8_Pop(chip8);
        break;
    default:
        Chip8_DecodeExecute(chip8, opcode);
    }
}