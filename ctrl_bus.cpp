#include "ctrl_bus.h"


CtrlBus::CtrlBus()
	: reset(true)
	, nmi(false)
	, nmiEdge(false)
	, interrupt(false)
{
}
