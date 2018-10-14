#pragma once

#include "memory.h"

class Cartridge;

class CartridgeSlot
{
	Cartridge * cartridge;
	friend class PRG_t;
	class PRG_t : public Memory
	{
		friend class CartridgeSlot;
		CartridgeSlot & cartridgeSlot;
		explicit PRG_t(CartridgeSlot & cartridgeSlot);
	public:
		uint8_t read(uint16_t addr) const override;
		uint8_t write(uint16_t addr, uint8_t val) override;
		uint8_t write(uint16_t addr, uint8_t val) const override;
		size_t size() const override;
	} PRG;
	friend class CHR_t;
	class CHR_t : public Memory
	{
		friend class CartridgeSlot;
		CartridgeSlot & cartridgeSlot;
		explicit CHR_t(CartridgeSlot & cartridgeSlot);
	public:
		uint8_t read(uint16_t addr) const override;
		uint8_t write(uint16_t addr, uint8_t val) override;
		uint8_t write(uint16_t addr, uint8_t val) const override;
		size_t size() const override;
	} CHR;
	friend class EXP_t;
	class EXP_t : public Memory
	{
		friend class CartridgeSlot;
		CartridgeSlot & cartridgeSlot;
		explicit EXP_t(CartridgeSlot & cartridgeSlot);
	public:
		uint8_t read(uint16_t addr) const override;
		uint8_t write(uint16_t addr, uint8_t val) override;
		uint8_t write(uint16_t addr, uint8_t val) const override;
		size_t size() const override;
	} EXP;
public:
	explicit CartridgeSlot(Cartridge * cartridge = nullptr);
	void setCartridge(Cartridge * cartridge);
	Memory & getPRG();
	Memory & getCHR();
	Memory & getEXP();

	Memory & getNametable0();
	Memory & getNametable1();
	Memory & getNametable2();
	Memory & getNametable3();
};
