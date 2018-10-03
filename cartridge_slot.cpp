#include "cartridge_slot.h"

#include "cartridge.h"


CartridgeSlot::CartridgeSlot(Cartridge * cartridge)
	: cartridge(cartridge)
{
}

void CartridgeSlot::setCartridge(Cartridge * cartridge)
{
	this->cartridge = cartridge;
}

uint8_t CartridgeSlot::read(uint16_t addr) const
{
	if (!cartridge)
		return 0;
	return cartridge->read(addr);
}

uint8_t CartridgeSlot::write(uint16_t addr, uint8_t val)
{
	if (!cartridge)
		return 0;
	return cartridge->write(addr, val);
}

uint8_t CartridgeSlot::write(uint16_t addr, uint8_t val) const
{
	if (!cartridge)
		return 0;
	return cartridge->write(addr, val);
}

size_t CartridgeSlot::size() const
{
	if (!cartridge)
		return 0;
	return cartridge->size();
}
