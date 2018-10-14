#include "cartridge_slot.h"

#include "cartridge.h"


CartridgeSlot::PRG_t::PRG_t(CartridgeSlot & cartridgeSlot)
	: cartridgeSlot(cartridgeSlot)
{
}

uint8_t CartridgeSlot::PRG_t::read(uint16_t addr) const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getPRG().read(addr);
}

uint8_t CartridgeSlot::PRG_t::write(uint16_t addr, uint8_t val)
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getPRG().write(addr, val);
}

uint8_t CartridgeSlot::PRG_t::write(uint16_t addr, uint8_t val) const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getPRG().write(addr, val);
}

size_t CartridgeSlot::PRG_t::size() const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getPRG().size();
}

CartridgeSlot::CHR_t::CHR_t(CartridgeSlot & cartridgeSlot)
	: cartridgeSlot(cartridgeSlot)
{
}

uint8_t CartridgeSlot::CHR_t::read(uint16_t addr) const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getCHR().read(addr);
}

uint8_t CartridgeSlot::CHR_t::write(uint16_t addr, uint8_t val)
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getCHR().write(addr, val);
}

uint8_t CartridgeSlot::CHR_t::write(uint16_t addr, uint8_t val) const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getCHR().write(addr, val);
}

size_t CartridgeSlot::CHR_t::size() const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getCHR().size();
}

CartridgeSlot::EXP_t::EXP_t(CartridgeSlot & cartridgeSlot)
	: cartridgeSlot(cartridgeSlot)
{
}

uint8_t CartridgeSlot::EXP_t::read(uint16_t addr) const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getEXP().read(addr);
}

uint8_t CartridgeSlot::EXP_t::write(uint16_t addr, uint8_t val)
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getEXP().write(addr, val);
}

uint8_t CartridgeSlot::EXP_t::write(uint16_t addr, uint8_t val) const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getEXP().write(addr, val);
}

size_t CartridgeSlot::EXP_t::size() const
{
	if (!cartridgeSlot.cartridge)
		return 0;
	return cartridgeSlot.cartridge->getEXP().size();
}

CartridgeSlot::CartridgeSlot(Cartridge * cartridge)
	: cartridge(cartridge)
	, CHR(*this)
	, PRG(*this)
	, EXP(*this)
{
}

void CartridgeSlot::setCartridge(Cartridge * cartridge)
{
	this->cartridge = cartridge;
}

Memory & CartridgeSlot::getPRG()
{
	return PRG;
}

Memory & CartridgeSlot::getCHR()
{
	return CHR;
}

Memory & CartridgeSlot::getEXP()
{
	return EXP;
}
