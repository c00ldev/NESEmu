#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Cartridge;

class iNES
{
	struct Header
	{
		uint8_t str[4];
		uint8_t programROMpages;
		uint8_t characterROMPages;
		union
		{
			uint8_t flags6;
			struct
			{
				bool mirroring : 1;	// M: Mirroring.  0 = horizontal, 1 = vertical.
				bool batteryBacked : 1;	// B: SRAM at 6000-7FFFh battery backed.  0= no, 1 = yes
				bool trainer : 1;	// T: Trainer.  0 = no trainer present, 1 = 512 byte trainer at 7000-71FFh
				bool fourScreenMode : 1;	// F: Four screen mode. 0 = no, 1 = yes. (When set, the M bit has no effect)
				uint8_t mapperLower : 4;	// N: Lower 4 bits of the mapper number
			};
		};
		union
		{
			uint8_t flags7;
			struct
			{
				bool vs : 1;	// V: Vs. Unisystem.  When set, this is a Vs. game
				bool playchoice10 : 1;	// P: Playchoice 10.  When set, this is a PC-10 game
				uint8_t S : 2;	// S: When equal to binary 10, use NES 2.0 rules; otherwise, use other rules.
				uint8_t mapperUpper : 4;	// N: Upper 4 bits of the mapper number
			};
		};
		union
		{
			uint8_t mapperVariant;
			struct
			{
				uint8_t mapper8_11 : 4;	// M: Bits 11-8 of mapper number.
				uint8_t submapper : 4;	// S: Submapper number.  Mappers not using submappers set this to zero.
			};
		};
		union
		{
			uint8_t romSize;
			struct
			{
				uint8_t PRG_ROM_size : 4;	// P: 4 more PRG ROM size bits
				uint8_t CHR_ROM_size : 4;	// C: 4 more CHR ROM size bits
			};
		};
		union
		{
			uint8_t ramSize;
			struct
			{
				uint8_t notBatteryBackedRAM : 4;	// P: Quantity of PRG RAM which is NOT battery backed
				uint8_t batteryBackedRAM : 4;	// p: Quantity of PRG RAM which is battery backed (or EEPROM)
			};
		};
		union
		{
			uint8_t vramSize;
			struct
			{
				uint8_t notBatteryBackedVRAM : 4;	// P: Quantity of PRG RAM which is NOT battery backed
				uint8_t batteryBackedVRAM : 4;	// p: Quantity of PRG RAM which is battery backed (or EEPROM)
			};
		};
		union
		{
			uint8_t tvSystem;
			struct
			{
				bool PAL : 1;	// P: 0 indicates NTSC mode; 1 is for PAL mode.
				bool both_PAL_NTSC : 1;	// B: When set, indicates this ROM works on both PAL and NTSC machines. Some of the Codemasters games actually will adjust the game depending on if it detects you running on a PAL or NTSC machine - it adjusts the timing of the game and transposes the music. Not many games would have this B flag set; those that do would be labeled (UE) or the like in GoodNES.
			};
		};
		union
		{
			uint8_t vsHardware;
			struct
			{
				uint8_t ppu : 4;	// P: PPU.  There are 13 Vs. PPUs that can be found on the games:
				uint8_t vsMode : 4;	// M: Vs. mode:
			};
		};
		union
		{
			uint8_t miscROMs;
			struct
			{
				uint8_t extra : 2;	// Supply the amount of extra non-PRG/CHR ROMs; (max of 3 at the moment). The mapper or sub-mapper will indicate the sizes of these ROM(s) and their function(s). An example of extra ROMs would be a Mask ROM with audio; such as the M50805 in Family Trainer 3.
			};
		};
		uint8_t reserved;
	} header;
	std::vector<uint8_t> trainer;
	std::vector<uint8_t> PRG_ROM;
	std::vector<uint8_t> CHR_ROM;
//	std::vector<uint8_t> INST_ROM;
//	std::vector<uint8_t> PROM;
//	std::vector<uint8_t> title;
	Cartridge * cartridge;
public:
	iNES();
	~iNES();
	void load(const std::string & is);
	Cartridge * getCartridge() const;
};
