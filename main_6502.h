//
// Created by nava on 18/08/23.
//

#include <iostream>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;
using s32 = signed int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024*64;
    Byte Data[MAX_MEM];

    void Initialise()
    {
        for(u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i] = 0;
        }
    }

    // read 1 byte
    Byte operator[](u32 Address) const
    {
        return Data[Address];
    }

    // write 1 byte
    Byte &operator[](u32 Address)
    {
        return Data[Address];
    }

    // write 2 bytes
    void WriteWord(Word Value, u32 Address, s32 &Cycles)
    {
        Data[Address]     = Value & 0xFF;
        Data[Address + 1] = (Value >> 8);
        Cycles-=2;
    }
};

struct CPU
{
    Word PC;    // Program Counter
    Word SP;    // Stack Pointer

    // Registers
    Byte A;     // register A
    Byte X;     // register X
    Byte Y;     // register Y

    // Processor Status
    Byte C : 1; // Carry flag
    Byte Z : 1; // Zero flag
    Byte I : 1; // Interrupt disable
    Byte D : 1; // Decimal mode
    Byte B : 1; // Break command
    Byte V : 1; // oVerflow flag
    Byte N : 1; // Negative flag

    void Reset( Mem &memory )
    {
        PC = 0xFFFC;
        SP = 0x0100;
        C = 0;
        Z = 0;
        I = 0;
        D = 0;
        B = 0;
        V = 0;
        N = 0;
        A = 0;
        X = 0;
        Y = 0;

        memory.Initialise();
    }

    Byte FetchByte( s32 &Cycles, Mem &memory)
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;

        return Data;
    }

    Word FetchWord(s32 &Cycles, Mem &memory)
    {
        // 6502 is little endian
        Word Data = memory[PC];
        PC++;

        Data |= (memory[PC] << 8);
        PC++;

        Cycles-=2;

        return Data;
    }

    Byte ReadByte(s32 &Cycles, Byte Address, Mem &memory)
    {
        Byte Data = memory[Address];
        Cycles--;

        return Data;
    }

    Word ReadWord(s32 &Cycles, Word Address, Mem &memory)
    {
        Byte LoByte = ReadByte(Cycles, Address, memory);
        Byte HiByte = ReadByte(Cycles, Address + 1, memory);

        return LoByte | (HiByte << 8);
    }

    // Opcodes
    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0x45;
    static constexpr Byte INS_LDA_ZPX = 0xB5;
    static constexpr Byte INS_LDA_ABS = 0xAD;
    static constexpr Byte INS_LDA_ABSX = 0xBD;
    static constexpr Byte INS_LDA_ABSY = 0xB9;
    static constexpr Byte INS_LDA_INDX = 0xA1;
    static constexpr Byte INS_LDA_INDY = 0xB1;
    static constexpr Byte INS_JSR = 0x20;

    void LDASetStatus()
    {
        Z = (A == 0);
        N = (A & 0b10000000) > 0;
    }

    s32 Execute(s32 Cycles, Mem &memory)
    {
        const s32 CyclesRequested = Cycles;
        while(Cycles > 0)
        {
            Byte Ins = FetchByte( Cycles, memory);

            switch(Ins)
            {
                case INS_LDA_IM: {
                    Byte value = FetchByte(Cycles, memory);
                    A = value;
                    LDASetStatus();
                }
                    break;
                case INS_LDA_ZP: {
                    Byte ZeroPageAddress = FetchByte(Cycles, memory);

                    A = ReadByte(Cycles, ZeroPageAddress, memory);
                    LDASetStatus();
                }
                    break;
                case INS_LDA_ZPX: {
                    Byte ZeroPageAddress = FetchByte(Cycles, memory);
                    ZeroPageAddress += X;
                    Cycles--;
                    A = ReadByte(Cycles, ZeroPageAddress, memory);
                    LDASetStatus();
                }
                    break;
                case INS_LDA_ABS: {
                    Word AbsAddress = FetchWord(Cycles, memory);
                    A = ReadByte(Cycles, AbsAddress, memory);
                }
                    break;
                case INS_LDA_ABSX: {
                    Word AbsAddress = FetchWord(Cycles, memory);
                    Word AbsAddressX = AbsAddress += X;
                    A = ReadByte(Cycles, AbsAddressX, memory);
                    if(AbsAddressX - AbsAddress >= 0xff)
                    {
                        Cycles--;
                    }
                }
                    break;
                case INS_LDA_ABSY: {
                    Word AbsAddress = FetchWord(Cycles, memory);
                    Word AbsAddressY = AbsAddress += Y;
                    A = ReadByte(Cycles, AbsAddressY, memory);
                    if(AbsAddressY - AbsAddress >= 0xff)
                    {
                        Cycles--;
                    }
                }
                    break;
                case INS_LDA_INDX: {
                    Byte ZPAddress = FetchByte(Cycles, memory);
                    ZPAddress += X;
                    Cycles--;
                    Word EffectiveAddr = ReadWord(Cycles, ZPAddress, memory);
                    A = ReadByte(Cycles, EffectiveAddr, memory);
                }
                    break;
                case INS_LDA_INDY: {
                    Byte ZPAddress = FetchByte(Cycles, memory);
                    Word EffectiveAddr = ReadWord(Cycles, ZPAddress, memory);
                    Word EffectiveAddrY = EffectiveAddr + Y;
                    A = ReadByte(Cycles, EffectiveAddrY, memory);
                    if(EffectiveAddrY - EffectiveAddr >= 0xff)
                    {
                        Cycles--;
                    }
                }
                    break;
                case INS_JSR: {
                    Word SubAddr = FetchWord(Cycles, memory);
                    memory.WriteWord( PC - 1, SP, Cycles);
                    SP += 2;
                    PC = SubAddr;
                    Cycles--;
                }
                    break;
                default:
                    std::cout << "Instruction not handled " << Ins << std::endl;
                    throw -1;
            }
        }

        const s32 NumCyclesUsed = CyclesRequested - Cycles;
        return NumCyclesUsed;
    }
};

