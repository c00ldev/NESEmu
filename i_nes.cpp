#include "i_nes.h"

#include <fstream>

#include "data_literals.h"
#include "cartridge.h"
#include "mappers/nrom.h"


iNES::iNES()
	: header{ {}, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	, cartridge(nullptr)
{
}

iNES::~iNES()
{
	delete cartridge;
}

void iNES::load(const std::string & is)
{
	delete cartridge;

	std::ifstream fin(is, std::ios::binary);

	fin.read((char *)&header, sizeof(header));

	if (header.trainer)
	{
		trainer.resize(512);
		fin.read((char *)&trainer[0], trainer.size());
	}

	size_t prgROM_size = header.programROMpages | ((uint16_t)header.PRG_ROM_size << 8u);
	std::vector<uint8_t> PRG_ROM(prgROM_size * 16_KiB);
	fin.read((char *)&PRG_ROM[0], PRG_ROM.size());

	size_t chrROM_size = header.characterROMPages | ((uint16_t)header.CHR_ROM_size << 8u);
	std::vector<uint8_t> CHR_ROM(chrROM_size * 8_KiB);
	fin.read((char *)&CHR_ROM[0], CHR_ROM.size());

	size_t mapper = 0;

	switch (mapper)
	{
	case 0:
	{
		auto * nrom = new NROM<Mirroring::Vertical>(NROM<Mirroring::Vertical>::Type(prgROM_size));
		nrom->load(std::move(PRG_ROM), std::move(CHR_ROM));
		cartridge = nrom;
		break;
	}
	default:
		break;
	}
}

Cartridge * iNES::getCartridge() const
{
	return cartridge;
}
