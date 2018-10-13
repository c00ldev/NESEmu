cmake_minimum_required(VERSION 3.10)
project(NESEmu)

set(CMAKE_CXX_STANDARD 17)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_FLAGS "-g")

add_executable(NESEmu main.cpp instructions.asm instructions.h tickable.h clock.cpp clock.h cpu.cpp cpu.h memory.h nes.cpp nes.h ram.cpp ram.h mem_bus.cpp mem_bus.h reg_memory.cpp reg_memory.h ppu.cpp ppu.h reg_ptr.cpp reg_ptr.h i_nes.cpp i_nes.h cartridge.cpp cartridge.h mappers/nrom.cpp mappers/nrom.h mem_map.cpp mem_map.h cartridge_slot.cpp cartridge_slot.h data_literals.cpp data_literals.h log.h)
