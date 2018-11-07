#include "instruction_decoder.h"

#include <cstdint>


template<uint16_t Opcode> std::vector<size_t> decode();

void combine(std::vector<size_t> & lhs, const std::vector<size_t> & rhs);


#define c(n) decode<0x##n>(),decode<0x##n+1>(),
#define o(n) c(n)c(n+2)c(n+4)c(n+6)
const std::array<std::vector<size_t>, 0x108> InstructionDecoder::instructions = {
	o(00)o(08)o(10)o(18)o(20)o(28)o(30)o(38)
	o(40)o(48)o(50)o(58)o(60)o(68)o(70)o(78)
	o(80)o(88)o(90)o(98)o(A0)o(A8)o(B0)o(B8)
	o(C0)o(C8)o(D0)o(D8)o(E0)o(E8)o(F0)o(F8) o(100)
};
#undef o
#undef c

template<uint16_t Opcode> std::vector<size_t> decode()
{
	std::vector<size_t> res;

	constexpr unsigned o8 = Opcode / 8u;
	constexpr unsigned o8m = 1u << (Opcode % 8u);

#define t(s,...) { constexpr unsigned i = o8m & (s[o8]>90 ? (130+" (),-089<>?BCFGHJLSVWZ[^hlmnxy|}"[s[o8]-94]) \
					: (s[o8]-" (("[s[o8]/39])); if constexpr (i != 0) combine(res,{ __VA_ARGS__ }); }

	/* Decode address operand */
	t("                                !", 1) // NMI vector location
	t("                                *", 2) // Reset vector location
	t("!                               ,", 3) // Interrupt vector location
	t("zy}z{y}zzy}zzy}zzy}zzy}zzy}zzy}z ", 57, 65, 0, 62, 66)
	t("2 yy2 yy2 yy2 yy2 XX2 XX2 yy2 yy ", 5) // register index
	t("  62  62  62  62  om  om  62  62 ", 6)
	t("2 y 2 y 2 y 2 y 2 y 2 y 2 y 2 y  ", 7, 0)              // add zeropage-index
	t(" y z!y z y z y z y z y z y z y z ", 8, 57, 65, 0, 63, 66)       // absolute address
	t("3 6 2 6 2 6 286 2 6 2 6 2 6 2 6 /", 58, 65, 0, 62, 66, 59, 65, 0, 63, 66)// indirect w/ page wrap
	t("  *Z  *Z  *Z  *Z      6z  *Z  *Z ", 72) // abs. load: extra misread when cross-page
	t("  4k  4k  4k  4k  6z      4k  4k ", 60, 65, 0, 66)// abs. store: always issue a misread
	/* Load source operand */
	t("aa__ff__ab__,4  ____ -  ____     ", 12) // Many operations take A or X as operand. Some try in
	t("                knnn     4  99   ", 13) // error to take both; the outcome is an AND operation.
	t("                9989    99       ", 14) // sty,dey,iny,tya,cpy
	t("                       4         ", 15) // tsx, las
	t("!!!!  !!  !!  !!  !   !!  !!  !!/", 16)// php, flag test/set/clear, interrupts
	t("_^__dc___^__            ed__98   ", 17)        // save as second operand
	t("vuwvzywvvuwvvuwv    zy|zzywvzywv ", 61, 65, 0, 64, 66) // memory operand
	t(",2  ,2  ,2  ,2  -2  -2  -2  -2   ", 57, 65, 0, 64, 66)   // immediate operand
	/* Operations that mogrify memory operands directly */
	t("    88                           ", 20) // bit
	t("    nink    nnnk                 ", 21)       // rol,rla, ror,rra,arr
	t("nnnknnnk     0                   ", 22) // rol,rla, asl,slo,[arr,anc]
	t("        nnnknink                 ", 23) // lsr,sre, ror,rra,asr
	t("ninknink                         ", 24)
	t("        nnnknnnk                 ", 25)
	t("                 !      kink     ", 26)  // dec,dex,dey,dcp
	t("                         !  khnk ", 27)  // inc,inx,iny,isb
	/* Store modified value (memory) */
	t("kgnkkgnkkgnkkgnkzy|J    kgnkkgnk ", 61, 69, 67, 65, 0, 68, 66)
	t("                   q             ", 60, 70, 67, 65, 0, 68, 66) // [shx,shy,shs,sha?]
	/* Some operations used up one clock cycle that we did not account for yet */
	t("rpstljstqjstrjst - - - -kjstkjst/", 0) // nop,flag ops,inc,dec,shifts,stack,transregister,interrupts
	/* Stack operations and unconditional jumps */
	t("     !  !    !                   ", 0, 74, 65, 0, 77, 66)                        // pla,plp,rti
	t("        !   !                    ", 57, 65, 0, 66, 74, 65, 0, 78, 66, 74, 65, 0, 79, 66) // rti,rts
	t("            !                    ", 57, 65, 0, 66)  // rts
	t("!   !                           /", 34, 73, 76, 67, 65, 0, 68, 66, 73, 75, 67, 65, 0, 68, 66)      // jsr, interrupts
	t("!   !    8   8                  /", 35) // jmp, jsr, interrupts
	t("!!       !                      /", 73, 69, 67, 65, 0, 68, 66)   // pha, php, interrupts
	/* Bitmasks */
	t("! !!  !!  !!  !!  !   !!  !!  !!/", 37)
	t("  !   !                   !!  !! ", 38)
	t("! !   !   !!  !!       !   !   !/", 39)
	t("  !   !   !   !        !         ", 40)
	t("   !       !           !   !____ ", 41) // sbc, isb,      clear flag
	t("`^__   !       !               !/", 42)  // ora, slo,      set flag
	t("  !!dc`_  !!  !   !   !!  !!  !  ", 43)  // and, bit, rla, clear/test flag
	t("        _^__                     ", 44)  // eor, sre
	/* Conditional branches */
	t("      !       !       !       !  ", 45, 0, 80, 35)
	t("  !       !       !       !      ", 46, 0, 80, 35)
	/* Addition and subtraction */
	t("            _^__            ____ ", 47)
	t("                        ed__98   ", 48) // cmp,cpx,cpy, dcp, sbx
	/* Store modified value (register) */
	t("aa__aa__aa__ab__ 4 !____    ____ ", 49)
	t("                    nnnn 4   !   ", 50) // ldx, dex, tax, inx, tsx,lax,las,sbx
	t("                 !  9988 !       ", 51) // ldy, dey, tay, iny
	t("                   4   0         ", 52) // txs, las, shs
	t("!  ! ! !!  !   !       !   !   !/", 53) // plp, rti, flag set/clear
	/* Generic status flag updates */
	t("wwwvwwwvwwwvwxwv 5 !}}||{}wv{{wv ", 54)
	t("wwwv||wvwwwvwxwv 5 !}}||{}wv{{wv ", 55)
	t("             0                   ", 56)         // [arr]
	/* All implemented opcodes are cycle-accurate and memory-access-accurate.
	 * [] means that this particular separate rule exists only to provide the indicated unofficial opcode(s).
	 */
	return res;
}

void combine(std::vector<size_t> & lhs, const std::vector<size_t> & rhs)
{
	lhs.reserve(lhs.size() + rhs.size());
	for (size_t i : rhs)
		lhs.push_back(i);
}
