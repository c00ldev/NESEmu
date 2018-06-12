cmake_minimum_required(VERSION 3.10)
project(NESEmu)

set(CMAKE_CXX_STANDARD 17)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_FLAGS "-g")

add_executable(NESEmu main.cpp instructions.asm instructions.h tickable.h clock.cpp clock.h cpu.cpp cpu.h memory.h nes.cpp nes.h ram.cpp ram.h mmu.cpp mmu.h reg_memory.cpp reg_memory.h nrom.cpp nrom.h)
