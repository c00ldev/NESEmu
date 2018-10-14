#include "nrom.h"

#include "../data_literals.h"
#include "../null_memory.h"

#include <functional>
#include <utility>


NROM<Mirroring::Vertical>::PRG_t::PRG_t(NROM<Mirroring::Vertical> & nrom)
	: nrom(nrom)
{
}

uint8_t NROM<Mirroring::Vertical>::PRG_t::read(uint16_t addr) const
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.read(pAddr);
}

uint8_t NROM<Mirroring::Vertical>::PRG_t::write(uint16_t addr, uint8_t val)
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.write(pAddr, val);
}

uint8_t NROM<Mirroring::Vertical>::PRG_t::write(uint16_t addr, uint8_t val) const
{
	auto [pMem, pAddr] = resolve(addr);
	return pMem.write(pAddr, val);
}

size_t NROM<Mirroring::Vertical>::PRG_t::size() const
{
	return 0xA000;
}

std::pair<Memory &, uint16_t> NROM<Mirroring::Vertical>::PRG_t::resolve(uint16_t addr)
{
	auto [pMem, pAddr] = static_cast<const NROM &>(nrom).PRG.resolve(addr);
	return std::pair(std::ref(const_cast<Memory &>(pMem)), pAddr);
}

std::pair<const Memory &, uint16_t> NROM<Mirroring::Vertical>::PRG_t::resolve(uint16_t addr) const
{
	if (0x0000u <= addr && addr < 0x2000u)
		return std::pair(std::ref(nrom.PRG_RAM), addr - 0x0000u);
	if (0x2000u <= addr && addr < 0xA000u)
		return std::pair(std::ref(nrom.PRG_ROM), (addr - 0x2000u) % nrom.PRG_ROM.size());
	return std::pair(std::ref(nrom.PRG_ROM), (addr - 0x2000u) % nrom.PRG_ROM.size());
}

NROM<Mirroring::Vertical>::NROM(Type type)
	: PRG_ROM(size_t(type) * 16_KiB)
	, PRG_RAM(8_KiB)
	, CHR(8_KiB)
	, PRG(*this)
{
}

Memory & NROM<Mirroring::Vertical>::getPRG()
{
	return PRG;
}

Memory & NROM<Mirroring::Vertical>::getCHR()
{
	return CHR;
}

Memory & NROM<Mirroring::Vertical>::getEXP()
{
	return NullMemory::nullMemory;
}

void NROM<Mirroring::Vertical>::load(std::vector<uint8_t> PRG_ROM, std::vector<uint8_t> CHR)
{
	this->PRG_ROM.setContents(std::move(PRG_ROM));
	this->CHR.setContents(std::move(CHR));
}
