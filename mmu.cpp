#include "mmu.h"

uint8_t MMU::read(uint16_t addr) const
{
	auto [pMem, pAddr] = resolve(addr);
	pMem.read(pAddr);
}

uint8_t MMU::write(uint16_t addr, uint8_t val)
{
	auto [pMem, pAddr] = resolve(addr);
	pMem.write(pAddr, val);
}

uint8_t MMU::write(uint16_t addr, uint8_t val) const
{
	auto [pMem, pAddr] = resolve(addr);
	pMem.write(pAddr, val);
}

size_t MMU::size() const
{
	if (map_.empty())
		return 0;
	return map_.back().first + map_.back().second.size();
}

std::pair<Memory &, uint16_t> MMU::resolve(uint16_t addr) const
{
	auto it = map_.begin();
	while (it != map_.end() && it->first <= addr)
		++it;
	--it;
	return std::pair<Memory &, uint16_t>(it->second, addr - it->first);
}

void MMU::map(uint16_t addr, Memory & mem)
{
	auto it = map_.begin();
	while (it != map_.end() && it->first <= addr)
		++it;
	map_.insert(it, std::pair<uint16_t, Memory &>(addr, mem));
}
