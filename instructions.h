#pragma once

#include <cstdint>

extern "C"
{

void OP_ADC(uint8_t & A, uint8_t M, uint8_t & P);
void OP_AND(uint8_t & A, uint8_t M, uint8_t & P);
void OP_ASL(uint8_t & AM, uint8_t & P);
void OP_BIT(uint8_t & A, uint8_t M, uint8_t & P);
void OP_CMP(uint8_t & R, uint8_t M, uint8_t & P);
void OP_DEC(uint8_t & RM, uint8_t & P);
void OP_EOR(uint8_t & A, uint8_t M, uint8_t & P);
void OP_INC(uint8_t & RM, uint8_t & P);
void OP_LD(uint8_t & R, uint8_t RM, uint8_t & P);
void OP_LSR(uint8_t & AM, uint8_t & P);
void OP_ORA(uint8_t & A, uint8_t M, uint8_t & P);
void OP_ROL(uint8_t & AM, uint8_t & P);
void OP_ROR(uint8_t & AM, uint8_t & P);

}
