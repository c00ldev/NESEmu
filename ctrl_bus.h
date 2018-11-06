#pragma once

struct CtrlBus
{
	bool reset;
	bool nmi;
	bool nmiEdge;
	bool interrupt;
public:
	CtrlBus();
};
