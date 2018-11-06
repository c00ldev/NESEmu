#include "instructions.h"

#include "cpu.h"


template<uint16_t Opcode> void instruction(CPU & cpu);

#define c(n) instruction<0x##n>,instruction<0x##n+1>,
#define o(n) c(n)c(n+2)c(n+4)c(n+6)
std::array<std::function<void(CPU &)>, 0x108> Instructions::table = {
	o(00)o(08)o(10)o(18)o(20)o(28)o(30)o(38)
	o(40)o(48)o(50)o(58)o(60)o(68)o(70)o(78)
	o(80)o(88)o(90)o(98)o(A0)o(A8)o(B0)o(B8)
	o(C0)o(C8)o(D0)o(D8)o(E0)o(E8)o(F0)o(F8) o(100)
};
#undef o
#undef c

void Instructions::operator()(uint16_t opcode, CPU & cpu)
{
	table[opcode](cpu);
}

template<uint16_t Opcode> void instruction(CPU & cpu)
{
	unsigned addr = 0;
	unsigned d = 0;
	unsigned t = 0xFF;
	unsigned c = 0;
	unsigned sb = 0;
	unsigned pbits = Opcode < 0x100 ? 0x30 : 0x20;

	constexpr unsigned o8 = Opcode / 8u;
	constexpr unsigned o8m = 1u << (Opcode % 8u);

#define t(s,code) { constexpr unsigned i = o8m & (s[o8]>90 ? (130+" (),-089<>?BCFGHJLSVWZ[^hlmnxy|}"[s[o8]-94]) \
					: (s[o8]-" (("[s[o8]/39])); if constexpr (i != 0) cpu.instr.push([&]{ code; }); }

	/* Decode address operand */
	t("                                !", addr = 0xFFFA) // NMI vector location
	t("                                *", addr = 0xFFFC) // Reset vector location
	t("!                               ,", addr = 0xFFFE) // Interrupt vector location
	t("zy}z{y}zzy}zzy}zzy}zzy}zzy}zzy}z ", addr = cpu.read(cpu.PC++))
	t("2 yy2 yy2 yy2 yy2 XX2 XX2 yy2 yy ", d = cpu.X) // register index
	t("  62  62  62  62  om  om  62  62 ", d = cpu.Y)
	t("2 y 2 y 2 y 2 y 2 y 2 y 2 y 2 y  ", addr=uint8_t(addr+d); d=0; cpu.waitTick())              // add zeropage-index
	t(" y z!y z y z y z y z y z y z y z ", addr=uint8_t(addr);   addr+=256*cpu.read(cpu.PC++))       // absolute address
	t("3 6 2 6 2 6 286 2 6 2 6 2 6 2 6 /", addr=cpu.read(c=addr); addr+=256*cpu.read(cpu.wrap(c,c+1)))// indirect w/ page wrap
	t("  *Z  *Z  *Z  *Z      6z  *Z  *Z ", cpu.misfire(addr, addr+d)) // abs. load: extra misread when cross-page
	t("  4k  4k  4k  4k  6z      4k  4k ", cpu.read(cpu.wrap(addr, addr+d)))// abs. store: always issue a misread
	/* Load source operand */
	t("aa__ff__ab__,4  ____ -  ____     ", t &= cpu.A) // Many operations take A or X as operand. Some try in
	t("                knnn     4  99   ", t &= cpu.X) // error to take both; the outcome is an AND operation.
	t("                9989    99       ", t &= cpu.Y) // sty,dey,iny,tya,cpy
	t("                       4         ", t &= cpu.S) // tsx, las
	t("!!!!  !!  !!  !!  !   !!  !!  !!/", t &= cpu.P|pbits; c = t)// php, flag test/set/clear, interrupts
	t("_^__dc___^__            ed__98   ", c = t; t = 0xFF)        // save as second operand
	t("vuwvzywvvuwvvuwv    zy|zzywvzywv ", t &= cpu.read(addr+d)) // memory operand
	t(",2  ,2  ,2  ,2  -2  -2  -2  -2   ", t &= cpu.read(cpu.PC++))   // immediate operand
	/* Operations that mogrify memory operands directly */
	t("    88                           ", cpu.V = t & 0x40; cpu.N = t & 0x80) // bit
	t("    nink    nnnk                 ", sb = cpu.C)       // rol,rla, ror,rra,arr
	t("nnnknnnk     0                   ", cpu.C = t & 0x80) // rol,rla, asl,slo,[arr,anc]
	t("        nnnknink                 ", cpu.C = t & 0x01) // lsr,sre, ror,rra,asr
	t("ninknink                         ", t = (t << 1) | (sb * 0x01))
	t("        nnnknnnk                 ", t = (t >> 1) | (sb * 0x80))
	t("                 !      kink     ", t = uint8_t(t - 1))  // dec,dex,dey,dcp
	t("                         !  khnk ", t = uint8_t(t + 1))  // inc,inx,iny,isb
	/* Store modified value (memory) */
	t("kgnkkgnkkgnkkgnkzy|J    kgnkkgnk ", cpu.write(addr+d, t))
	t("                   q             ", cpu.write(cpu.wrap(addr, addr+d), t &= ((addr+d) >> 8))) // [shx,shy,shs,sha?]
	/* Some operations used up one clock cycle that we did not account for yet */
	t("rpstljstqjstrjst - - - -kjstkjst/", cpu.waitTick()) // nop,flag ops,inc,dec,shifts,stack,transregister,interrupts
	/* Stack operations and unconditional jumps */
	t("     !  !    !                   ", cpu.waitTick(); t = cpu.pop())                        // pla,plp,rti
	t("        !   !                    ", cpu.read(cpu.PC++); cpu.PC = cpu.pop(); cpu.PC |= (cpu.pop() << 8)) // rti,rts
	t("            !                    ", cpu.read(cpu.PC++))  // rts
	t("!   !                           /", d = cpu.PC + (Opcode ? -1 : 1); cpu.push(d>>8); cpu.push(d))      // jsr, interrupts
	t("!   !    8   8                  /", cpu.PC = addr) // jmp, jsr, interrupts
	t("!!       !                      /", cpu.push(t))   // pha, php, interrupts
	/* Bitmasks */
	t("! !!  !!  !!  !!  !   !!  !!  !!/", t = 1)
	t("  !   !                   !!  !! ", t <<= 1)
	t("! !   !   !!  !!       !   !   !/", t <<= 2)
	t("  !   !   !   !        !         ", t <<= 4)
	t("   !       !           !   !____ ", t = uint8_t(~t)) // sbc, isb,      clear flag
	t("`^__   !       !               !/", t = c | t)  // ora, slo,      set flag
	t("  !!dc`_  !!  !   !   !!  !!  !  ", t = c & t)  // and, bit, rla, clear/test flag
	t("        _^__                     ", t = c ^ t)  // eor, sre
	/* Conditional branches */
	t("      !       !       !       !  ", if(t)  { cpu.waitTick(); cpu.misfire(cpu.PC, addr = int8_t(addr) + cpu.PC); cpu.PC=addr; })
	t("  !       !       !       !      ", if(!t) { cpu.waitTick(); cpu.misfire(cpu.PC, addr = int8_t(addr) + cpu.PC); cpu.PC=addr; })
	/* Addition and subtraction */
	t("            _^__            ____ ", c = t; t += cpu.A + cpu.C; cpu.V = (c^t) & (cpu.A^t) & 0x80; cpu.C = t & 0x100)
	t("                        ed__98   ", t = c - t; cpu.C = ~t & 0x100) // cmp,cpx,cpy, dcp, sbx
	/* Store modified value (register) */
	t("aa__aa__aa__ab__ 4 !____    ____ ", cpu.A = t)
	t("                    nnnn 4   !   ", cpu.X = t) // ldx, dex, tax, inx, tsx,lax,las,sbx
	t("                 !  9988 !       ", cpu.Y = t) // ldy, dey, tay, iny
	t("                   4   0         ", cpu.S = t) // txs, las, shs
	t("!  ! ! !!  !   !       !   !   !/", cpu.P = t & ~0x30) // plp, rti, flag set/clear
	/* Generic status flag updates */
	t("wwwvwwwvwwwvwxwv 5 !}}||{}wv{{wv ", cpu.N = t & 0x80)
	t("wwwv||wvwwwvwxwv 5 !}}||{}wv{{wv ", cpu.Z = uint8_t(t) == 0)
	t("             0                   ", cpu.V = (((t >> 5)+1)&2))         // [arr]
	/* All implemented opcodes are cycle-accurate and memory-access-accurate.
	 * [] means that this particular separate rule exists only to provide the indicated unofficial opcode(s).
	 */
}
