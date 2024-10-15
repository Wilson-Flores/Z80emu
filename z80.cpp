#include "z80.hpp"
#include "Bus.hpp"
#include "instructions/InstructionTable.hpp"

z80cpu::z80cpu() {
	//TODO: possible issue is refereencing the member functions that lead to the other tables
	using z = z80cpu;
	main_instruction_table = {
        {"00", &NOP_implied }, {"01", &LD_register_immediate_extended_16_bit }, {"02", &LD_register_indirect_register_BC }, {"03", &INC_implied_register_extended }, {"04", &INC_implied_register }, {"05", &DEC_implied_register }, {"06", &LD_register_immediate }, {"07", &RLCA_implied }, {"08", &EX_implied_implied_af }, {"09", &ADD_implied_register_extended }, {"0A", &LD_register_register_indirect_BC }, {"0B", &DEC_implied_register_extended }, {"0C", &INC_implied_register }, {"0D", &DEC_implied_register }, {"0E", &LD_register_immediate }, {"0F", &RRCA_implied },
        {"10", &DJNZ_immediate }, {"11", &LD_register_immediate_extended_16_bit }, {"12", &LD_register_indirect_register_DE }, {"13", &INC_implied_register_extended }, {"14", &INC_implied_register }, {"15", &DEC_implied_register }, {"16", &LD_register_immediate }, {"17", &RLA_implied }, {"18", &JR_relative }, {"19", &ADD_implied_register_extended }, {"1A", &LD_register_register_indirect_DE }, {"1B", &DEC_implied_register_extended }, {"1C", &INC_implied_register }, {"1D", &DEC_implied_register }, {"1E", &LD_register_immediate }, {"1F", &RRA_implied },
        {"20", &JR_cc_relative }, {"21", &LD_register_immediate_extended_16_bit }, {"22", &LD_extended_register_hl }, {"23", &INC_implied_register_extended }, {"24", &INC_implied_register }, {"25", &DEC_implied_register }, {"26", &LD_register_immediate }, {"27", &DAA_implied }, {"28", &JR_cc_relative }, {"29", &ADD_implied_register_extended }, {"2A", &LD_register_extended_hl }, {"2B", &DEC_implied_register_extended }, {"2C", &INC_implied_register }, {"2D", &DEC_implied_register }, {"2E", &LD_register_immediate }, {"2F", &CPL_implied },
        {"30", &JR_cc_relative }, {"31", &LD_register_immediate_extended_16_bit }, {"32", &LD_extended_register }, {"33", &INC_implied_register_extended }, {"34", &INC_implied_register_indirect }, {"35", &DEC_implied_register_indirect }, {"36", &LD_register_indirect_immediate }, {"37", &SCF_implied }, {"38", &JR_cc_relative }, {"39", &ADD_implied_register_extended }, {"3A", &LD_register_extended }, {"3B", &DEC_implied_register_extended }, {"3C", &INC_implied_register }, {"3D", &DEC_implied_register }, {"3E", &LD_register_immediate }, {"3F", &CCF_implied },
        {"40", &LD_register_register }, {"41", &LD_register_register }, {"42", &LD_register_register }, {"43", &LD_register_register }, {"44", &LD_register_register }, {"45", &LD_register_register }, {"46", &LD_register_register_indirect }, {"47", &LD_register_register }, {"48", &LD_register_register }, {"49", &LD_register_register }, {"4A", &LD_register_register }, {"4B", &LD_register_register }, {"4C", &LD_register_register }, {"4D", &LD_register_register }, {"4E", &LD_register_register_indirect }, {"4F", &LD_register_register },
        {"50", &LD_register_register }, {"51", &LD_register_register }, {"52", &LD_register_register }, {"53", &LD_register_register }, {"54", &LD_register_register }, {"55", &LD_register_register }, {"56", &LD_register_register_indirect }, {"57", &LD_register_register }, {"58", &LD_register_register }, {"59", &LD_register_register }, {"5A", &LD_register_register }, {"5B", &LD_register_register }, {"5C", &LD_register_register }, {"5D", &LD_register_register }, {"5E", &LD_register_register_indirect }, {"5F", &LD_register_register },
        {"60", &LD_register_register }, {"61", &LD_register_register }, {"62", &LD_register_register }, {"63", &LD_register_register }, {"64", &LD_register_register }, {"65", &LD_register_register }, {"66", &LD_register_register_indirect }, {"67", &LD_register_register }, {"68", &LD_register_register }, {"69", &LD_register_register }, {"6A", &LD_register_register }, {"6B", &LD_register_register }, {"6C", &LD_register_register }, {"6D", &LD_register_register }, {"6E", &LD_register_register_indirect }, {"6F", &LD_register_register },
        {"70", &LD_register_indirect_register }, {"71", &LD_register_indirect_register }, {"72", &LD_register_indirect_register }, {"73", &LD_register_indirect_register }, {"74", &LD_register_indirect_register }, {"75", &LD_register_indirect_register }, {"76", nullptr }, {"77", &LD_register_indirect_register }, {"78", &LD_register_register }, {"79", &LD_register_register }, {"7A", &LD_register_register }, {"7B", &LD_register_register }, {"7C", &LD_register_register }, {"7D", &LD_register_register }, {"7E", &LD_register_register_indirect }, {"7F", &LD_register_register },
        {"80", &ADD_implied_register }, {"81", &ADD_implied_register }, {"82", &ADD_implied_register }, {"83", &ADD_implied_register }, {"84", &ADD_implied_register }, {"85", &ADD_implied_register }, {"86", &ADD_implied_register_indirect }, {"87", &ADD_implied_register }, {"88", &ADC_implied_register }, {"89", &ADC_implied_register }, {"8A", &ADC_implied_register }, {"8B", &ADC_implied_register }, {"8C", &ADC_implied_register }, {"8D", &ADC_implied_register }, {"8E", &ADC_implied_register_indirect }, {"8F", &ADC_implied_register },
        {"90", &SUB_implied_register }, {"91", &SUB_implied_register }, {"92", &SUB_implied_register }, {"93", &SUB_implied_register }, {"94", &SUB_implied_register }, {"95", &SUB_implied_register }, {"96", &SUB_implied_register_indirect }, {"97", &SUB_implied_register }, {"98", &SBC_implied_register }, {"99", &SBC_implied_register }, {"9A", &SBC_implied_register }, {"9B", &SBC_implied_register }, {"9C", &SBC_implied_register }, {"9D", &SBC_implied_register }, {"9E", &SBC_implied_register_indirect }, {"9F", &SBC_implied_register },
        {"A0", &AND_implied_register }, {"A1", &AND_implied_register }, {"A2", &AND_implied_register }, {"A3", &AND_implied_register }, {"A4", &AND_implied_register }, {"A5", &AND_implied_register }, {"A6", &AND_implied_register_indirect }, {"A7", &AND_implied_register }, {"A8", &XOR_implied_register }, {"A9", &XOR_implied_register }, {"AA", &XOR_implied_register }, {"AB", &XOR_implied_register }, {"AC", &XOR_implied_register }, {"AD", &XOR_implied_register }, {"AE", &XOR_implied_register_indirect }, {"AF", &XOR_implied_register },
        {"B0", &OR_implied_register }, {"B1", &OR_implied_register }, {"B2", &OR_implied_register }, {"B3", &OR_implied_register }, {"B4", &OR_implied_register }, {"B5", &OR_implied_register }, {"B6", &OR_implied_register_indirect }, {"B7", &OR_implied_register }, {"B8", &CP_implied_register }, {"B9", &CP_implied_register }, {"BA", &CP_implied_register }, {"BB", &CP_implied_register }, {"BC", &CP_implied_register }, {"BD", &CP_implied_register }, {"BE", &CP_implied_register_indirect }, {"BF", &CP_implied_register },
        {"C0", nullptr }, {"C1", &POP_register_indirect_register }, {"C2", &JP_cc_immediate }, {"C3", &JP_immediate }, {"C4", nullptr }, {"C5", &PUSH_register_indirect_register }, {"C6", &ADD_implied_immediate }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", &JP_cc_immediate }, {"CB", &z::bit_instructions }, {"CC", nullptr }, {"CD", nullptr }, {"CE", &ADC_implied_immediate }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", &POP_register_indirect_register }, {"D2", &JP_cc_immediate }, {"D3", nullptr }, {"D4", nullptr }, {"D5", &PUSH_register_indirect_register }, {"D6", &SUB_implied_immediate }, {"D7", nullptr }, {"D8", nullptr }, {"D9", &EXX_implied_implied }, {"DA", &JP_cc_immediate }, {"DB", nullptr }, {"DC", nullptr }, {"DD", &z::ix_instructions }, {"DE", &SBC_implied_immediate }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", &POP_register_indirect_register }, {"E2", &JP_cc_immediate }, {"E3", &EX_register_indirect_implied_hl }, {"E4", nullptr }, {"E5", &PUSH_register_indirect_register }, {"E6", &AND_implied_immediate }, {"E7", nullptr }, {"E8", nullptr }, {"E9", &JP_implict }, {"EA", &JP_cc_immediate }, {"EB", &EX_implied_implied }, {"EC", nullptr }, {"ED", &z::misc_instructions }, {"EE", &XOR_implied_immediate }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", &POP_register_indirect_register }, {"F2", &JP_cc_immediate }, {"F3", nullptr }, {"F4", nullptr }, {"F5", &PUSH_register_indirect_register }, {"F6", &OR_implied_immediate }, {"F7", nullptr }, {"F8", nullptr }, {"F9", &LD_register_register_hl }, {"FA", &JP_cc_immediate }, {"FB", nullptr }, {"FC", nullptr }, {"FD", &z::iy_instructions }, {"FE", &CP_implied_immediate }, {"FF", nullptr }
    };

	misc_instruction_table = {
		{"00", nullptr },{ "01", nullptr },{ "02", nullptr },{ "03", nullptr },{ "04", nullptr },{ "05", nullptr },{ "06", nullptr },{ "07", nullptr },{ "08", nullptr },{ "09", nullptr },{ "0A", nullptr },{ "0B", nullptr },{ "0C", nullptr },{ "0D", nullptr },{ "0E", nullptr },{ "0F", nullptr },
		{"10", nullptr },{ "11", nullptr },{ "12", nullptr },{ "13", nullptr },{ "14", nullptr },{ "15", nullptr },{ "16", nullptr },{ "17", nullptr },{ "18", nullptr },{ "19", nullptr },{ "1A", nullptr },{ "1B", nullptr },{ "1C", nullptr },{ "1D", nullptr },{ "1E", nullptr },{ "1F", nullptr },
		{"20", nullptr },{ "21", nullptr },{ "22", nullptr },{ "23", nullptr },{ "24", nullptr },{ "25", nullptr },{ "26", nullptr },{ "27", nullptr },{ "28", nullptr },{ "29", nullptr },{ "2A", nullptr },{ "2B", nullptr },{ "2C", nullptr },{ "2D", nullptr },{ "2E", nullptr },{ "2F", nullptr },
		{"30", nullptr },{ "31", nullptr },{ "32", nullptr },{ "33", nullptr },{ "34", nullptr },{ "35", nullptr },{ "36", nullptr },{ "37", nullptr },{ "38", nullptr },{ "39", nullptr },{ "3A", nullptr },{ "3B", nullptr },{ "3C", nullptr },{ "3D", nullptr },{ "3E", nullptr },{ "3F", nullptr },
		{"40", nullptr },{ "41", nullptr },{ "42", &SBC_implied_register_extended },{ "43", &LD_extended_register_16_bit },{ "44", &NEG_implied },{ "45", nullptr },{ "46", nullptr },{ "47", &LD_implied_register_I },{ "48", nullptr },{ "49", nullptr },{ "4A", &ADC_implied_register_extended },{ "4B", &LD_register_extended_16_bit },{ "4C", nullptr },{ "4D", nullptr },{ "4E", nullptr },{ "4F", &LD_implied_register_R },
		{"50", nullptr },{ "51", nullptr },{ "52", &SBC_implied_register_extended },{ "53", &LD_extended_register_16_bit },{ "54", nullptr },{ "55", nullptr },{ "56", nullptr },{ "57", &LD_register_implied_I },{ "58", nullptr },{ "59", nullptr },{ "5A", &ADC_implied_register_extended },{ "5B", &LD_register_extended_16_bit },{ "5C", nullptr },{ "5D", nullptr },{ "5E", nullptr },{ "5F", &LD_register_implied_R },
		{"60", nullptr },{ "61", nullptr },{ "62", &SBC_implied_register_extended },{ "63", &LD_extended_register_16_bit },{ "64", nullptr },{ "65", nullptr },{ "66", nullptr },{ "67", &RRD_implied },{ "68", nullptr },{ "69", nullptr },{ "6A", &ADC_implied_register_extended },{ "6B", &LD_register_extended_16_bit },{ "6C", nullptr },{ "6D", nullptr },{ "6E", nullptr },{ "6F", &RLD_implied },
		{"70", nullptr },{ "71", nullptr },{ "72", &SBC_implied_register_extended },{ "73", &LD_extended_register_16_bit },{ "74", nullptr },{ "75", nullptr },{ "76", nullptr },{ "77", nullptr },{ "78", nullptr },{ "79", nullptr },{ "7A", &ADC_implied_register_extended },{ "7B", &LD_register_extended_16_bit },{ "7C", nullptr },{ "7D", nullptr },{ "7E", nullptr },{ "7F", nullptr },
		{"80", nullptr },{ "81", nullptr },{ "82", nullptr },{ "83", nullptr },{ "84", nullptr },{ "85", nullptr },{ "86", nullptr },{ "87", nullptr },{ "88", nullptr },{ "89", nullptr },{ "8A", nullptr },{ "8B", nullptr },{ "8C", nullptr },{ "8D", nullptr },{ "8E", nullptr },{ "8F", nullptr },
		{"90", nullptr },{ "91", nullptr },{ "92", nullptr },{ "93", nullptr },{ "94", nullptr },{ "95", nullptr },{ "96", nullptr },{ "97", nullptr },{ "98", nullptr },{ "99", nullptr },{ "9A", nullptr },{ "9B", nullptr },{ "9C", nullptr },{ "9D", nullptr },{ "9E", nullptr },{ "9F", nullptr },
		{"A0", &LDI_register_indirect_register_indirect },{ "A1", &CPI_register_indirect },{ "A2", nullptr },{ "A3", nullptr },{ "A4", nullptr },{ "A5", nullptr },{ "A6", nullptr },{ "A7", nullptr },{ "A8", &LDD_register_indirect_register_indirect },{ "A9", &CPD_register_indirect },{ "AA", nullptr },{ "AB", nullptr },{ "AC", nullptr },{ "AD", nullptr },{ "AE", nullptr },{ "AF", nullptr },
		{"B0", &LDIR_register_indirect_register_indirect },{ "B1", &CPIR_register_indirect },{ "B2", nullptr },{ "B3", nullptr },{ "B4", nullptr },{ "B5", nullptr },{ "B6", nullptr },{ "B7", nullptr },{ "B8", &LDDR_register_indirect_register_indirect },{ "B9", &CPDR_register_indirect },{ "BA", nullptr },{ "BB", nullptr },{ "BC", nullptr },{ "BD", nullptr },{ "BE", nullptr },{ "BF", nullptr },
        {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

	ix_instruction_table = {
        {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", nullptr }, {"07", nullptr }, {"08", nullptr }, {"09", &ADD_implied_register_extended_ix }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", nullptr }, {"0F", nullptr },
        {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", nullptr }, {"17", nullptr }, {"18", nullptr }, {"19", &ADD_implied_register_extended_ix }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", nullptr }, {"1F", nullptr },
        {"20", nullptr }, {"21", &LD_register_immediate_extended_ix }, {"22", &LD_extended_register_ix }, {"23", &INC_implied_register_extended_ix }, {"24", nullptr }, {"25", nullptr }, {"26", nullptr }, {"27", nullptr }, {"28", nullptr }, {"29", &ADD_implied_register_extended_ix }, {"2A", &LD_register_extended_ix }, {"2B", &DEC_implied_register_extended_ix }, {"2C", nullptr }, {"2D", nullptr }, {"2E", nullptr }, {"2F", nullptr },
        {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", &INC_implied_indexed_ix }, {"35", &DEC_implied_indexed_ix }, {"36", &LD_indexed_ix_immediate }, {"37", nullptr }, {"38", nullptr }, {"39", &ADD_implied_register_extended_ix }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", nullptr }, {"3F", nullptr },
        {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", &LD_register_indexed_ix }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", &LD_register_indexed_ix }, {"4F", nullptr },
        {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", &LD_register_indexed_ix }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", &LD_register_indexed_ix }, {"5F", nullptr },
        {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", &LD_register_indexed_ix }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", &LD_register_indexed_ix }, {"6F", nullptr },
        {"70", &LD_indexed_ix_register }, {"71", &LD_indexed_ix_register }, {"72", &LD_indexed_ix_register }, {"73", &LD_indexed_ix_register }, {"74", &LD_indexed_ix_register }, {"75", &LD_indexed_ix_register}, {"76", nullptr }, {"77", &LD_indexed_ix_register }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", &LD_register_indexed_ix }, {"7F", nullptr },
        {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", &ADD_implied_indexed_ix }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", &ADC_implied_indexed_ix }, {"8F", nullptr },
        {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", &SUB_implied_indexed_ix }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", &SBC_implied_indexed_ix }, {"9F", nullptr },
        {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", &AND_implied_indexed_ix }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", &XOR_implied_indexed_ix }, {"AF", nullptr },
        {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", &OR_implied_indexed_ix }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", &CP_implied_indexed_ix }, {"BF", nullptr },
        {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", &ix_bit_instructions }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", &POP_register_indirect_register_ix }, {"E2", nullptr }, {"E3", &EX_register_indirect_implied_ix }, {"E4", nullptr }, {"E5", &PUSH_register_indirect_register_ix }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", &JP_implict_ix }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", &LD_register_register_ix }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

	iy_instruction_table = {
        {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", nullptr }, {"07", nullptr }, {"08", nullptr }, {"09", &ADD_implied_register_extended_iy }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", nullptr }, {"0F", nullptr },
        {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", nullptr }, {"17", nullptr }, {"18", nullptr }, {"19", &ADD_implied_register_extended_iy }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", nullptr }, {"1F", nullptr },
        {"20", nullptr }, {"21", &LD_register_immediate_extended_iy }, {"22", &LD_extended_register_iy }, {"23", &INC_implied_register_extended_iy }, {"24", nullptr }, {"25", nullptr }, {"26", nullptr }, {"27", nullptr }, {"28", nullptr }, {"29", &ADD_implied_register_extended_iy }, {"2A", &LD_register_extended_iy }, {"2B", &DEC_implied_register_extended_iy }, {"2C", nullptr }, {"2D", nullptr }, {"2E", nullptr }, {"2F", nullptr },
        {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", &INC_implied_indexed_iy }, {"35", &DEC_implied_indexed_iy }, {"36", &LD_indexed_iy_immediate }, {"37", nullptr }, {"38", nullptr }, {"39", &ADD_implied_register_extended_iy }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", nullptr }, {"3F", nullptr },
        {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", &LD_register_indexed_iy }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", &LD_register_indexed_iy }, {"4F", nullptr },
        {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", &LD_register_indexed_iy }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", &LD_register_indexed_iy }, {"5F", nullptr },
        {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", &LD_register_indexed_iy }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", &LD_register_indexed_iy }, {"6F", nullptr },
        {"70", &LD_indexed_iy_register }, {"71", &LD_indexed_iy_register }, {"72", &LD_indexed_iy_register }, {"73", &LD_indexed_iy_register }, {"74", &LD_indexed_iy_register }, {"75", &LD_indexed_iy_register }, {"76", nullptr }, {"77", &LD_indexed_iy_register }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", &LD_register_indexed_iy }, {"7F", nullptr },
        {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", &ADD_implied_indexed_iy }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", &ADC_implied_indexed_iy }, {"8F", nullptr },
        {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", &SUB_implied_indexed_iy }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", &SBC_implied_indexed_iy }, {"9F", nullptr },
        {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", &AND_implied_indexed_iy }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", &XOR_implied_indexed_iy }, {"AF", nullptr },
        {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", &OR_implied_indexed_iy }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", &CP_implied_indexed_iy }, {"BF", nullptr },
        {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", &iy_bit_instructions }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", &POP_register_indirect_register_iy }, {"E2", nullptr }, {"E3", &EX_register_indirect_implied_iy }, {"E4", nullptr }, {"E5", &PUSH_register_indirect_register_iy }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", &JP_implict_iy }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", &LD_register_register_iy }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

	bit_instruction_table = {
            {"00", &RLC_implied }, {"01", &RLC_implied }, {"02", &RLC_implied }, {"03", &RLC_implied }, {"04", &RLC_implied }, {"05", &RLC_implied }, {"06", &RLC_indirect }, {"07", &RLC_implied }, {"08", &RRC_implied }, {"09", &RRC_implied }, {"0A", &RRC_implied }, {"0B", &RRC_implied }, {"0C", &RRC_implied }, {"0D", &RRC_implied }, {"0E", &RRC_indirect }, {"0F", &RRC_implied },
            {"10", &RL_implied }, {"11", &RL_implied }, {"12", &RL_implied }, {"13", &RL_implied }, {"14", &RL_implied }, {"15", &RL_implied }, {"16", &RL_indirect }, {"17", &RL_implied }, {"18", &RR_implied }, {"19", &RR_implied  }, {"1A", &RR_implied  }, {"1B", &RR_implied  }, {"1C", &RR_implied  }, {"1D", &RR_implied  }, {"1E", &RR_indirect  }, {"1F", &RR_implied  },
            {"20", &SLA_implied }, {"21", &SLA_implied }, {"22", &SLA_implied }, {"23", &SLA_implied }, {"24", &SLA_implied }, {"25", &SLA_implied }, {"26", &SLA_indirect }, {"27", &SLA_implied }, {"28", &SRA_implied }, {"29", &SRA_implied }, {"2A", &SRA_implied }, {"2B", &SRA_implied }, {"2C", &SRA_implied }, {"2D", &SRA_implied }, {"2E", &SRA_indirect }, {"2F", &SRA_implied },
            {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", nullptr }, {"37", nullptr }, {"38", &SRL_implied }, {"39", &SRL_implied }, {"3A", &SRL_implied }, {"3B", &SRL_implied }, {"3C", &SRL_implied }, {"3D", &SRL_implied }, {"3E", &SRL_indirect }, {"3F", &SRL_implied },
            {"40", &BIT_implied }, {"41", &BIT_implied }, {"42", &BIT_implied }, {"43", &BIT_implied }, {"44", &BIT_implied }, {"45", &BIT_implied }, {"46", &BIT_indirect }, {"47", &BIT_implied }, {"48", &BIT_implied }, {"49", &BIT_implied }, {"4A", &BIT_implied }, {"4B", &BIT_implied }, {"4C", &BIT_implied }, {"4D", &BIT_implied }, {"4E", &BIT_indirect }, {"4F", &BIT_implied },
            {"50", &BIT_implied }, {"51", &BIT_implied }, {"52", &BIT_implied }, {"53", &BIT_implied }, {"54", &BIT_implied }, {"55", &BIT_implied }, {"56", &BIT_indirect }, {"57", &BIT_implied }, {"58", &BIT_implied }, {"59", &BIT_implied }, {"5A", &BIT_implied }, {"5B", &BIT_implied }, {"5C", &BIT_implied }, {"5D", &BIT_implied }, {"5E", &BIT_indirect }, {"5F", &BIT_implied },
            {"60", &BIT_implied }, {"61", &BIT_implied }, {"62", &BIT_implied }, {"63", &BIT_implied }, {"64", &BIT_implied }, {"65", &BIT_implied }, {"66", &BIT_indirect }, {"67", &BIT_implied }, {"68", &BIT_implied }, {"69", &BIT_implied }, {"6A", &BIT_implied }, {"6B", &BIT_implied }, {"6C", &BIT_implied }, {"6D", &BIT_implied }, {"6E", &BIT_indirect }, {"6F", &BIT_implied },
            {"70", &BIT_implied }, {"71", &BIT_implied }, {"72", &BIT_implied }, {"73", &BIT_implied }, {"74", &BIT_implied }, {"75", &BIT_implied }, {"76", &BIT_indirect }, {"77", &BIT_implied }, {"78", &BIT_implied }, {"79", &BIT_implied }, {"7A", &BIT_implied }, {"7B", &BIT_implied }, {"7C", &BIT_implied }, {"7D", &BIT_implied }, {"7E", &BIT_indirect }, {"7F", &BIT_implied },
            {"80", &RES_implied }, {"81", &RES_implied }, {"82", &RES_implied }, {"83", &RES_implied }, {"84", &RES_implied }, {"85", &RES_implied }, {"86", &RES_indirect }, {"87", &RES_implied }, {"88", &RES_implied }, {"89", &RES_implied }, {"8A", &RES_implied }, {"8B", &RES_implied }, {"8C", &RES_implied }, {"8D", &RES_implied }, {"8E", &RES_indirect }, {"8F", &RES_implied },
            {"90", &RES_implied }, {"91", &RES_implied }, {"92", &RES_implied }, {"93", &RES_implied }, {"94", &RES_implied }, {"95", &RES_implied }, {"96", &RES_indirect }, {"97", &RES_implied }, {"98", &RES_implied }, {"99", &RES_implied }, {"9A", &RES_implied }, {"9B", &RES_implied }, {"9C", &RES_implied }, {"9D", &RES_implied }, {"9E", &RES_indirect }, {"9F", &RES_implied },
            {"A0", &RES_implied }, {"A1", &RES_implied }, {"A2", &RES_implied }, {"A3", &RES_implied }, {"A4", &RES_implied }, {"A5", &RES_implied }, {"A6", &RES_indirect }, {"A7", &RES_implied }, {"A8", &RES_implied }, {"A9", &RES_implied }, {"AA", &RES_implied }, {"AB", &RES_implied }, {"AC", &RES_implied }, {"AD", &RES_implied }, {"AE", &RES_indirect }, {"AF", &RES_implied },
            {"B0", &RES_implied }, {"B1", &RES_implied }, {"B2", &RES_implied }, {"B3", &RES_implied }, {"B4", &RES_implied }, {"B5", &RES_implied }, {"B6", &RES_indirect }, {"B7", &RES_implied }, {"B8", &RES_implied }, {"B9", &RES_implied }, {"BA", &RES_implied }, {"BB", &RES_implied }, {"BC", &RES_implied }, {"BD", &RES_implied }, {"BE", &RES_indirect }, {"BF", &RES_implied },
            {"C0", &SET_implied }, {"C1", &SET_implied }, {"C2", &SET_implied }, {"C3", &SET_implied }, {"C4", &SET_implied }, {"C5", &SET_implied }, {"C6", &SET_indirect }, {"C7", &SET_implied }, {"C8", &SET_implied }, {"C9", &SET_implied }, {"CA", &SET_implied }, {"CB", &SET_implied }, {"CC", &SET_implied }, {"CD", &SET_implied }, {"CE", &SET_indirect }, {"CF", &SET_implied },
            {"D0", &SET_implied }, {"D1", &SET_implied }, {"D2", &SET_implied }, {"D3", &SET_implied }, {"D4", &SET_implied }, {"D5", &SET_implied }, {"D6", &SET_indirect }, {"D7", &SET_implied }, {"D8", &SET_implied }, {"D9", &SET_implied }, {"DA", &SET_implied }, {"DB", &SET_implied }, {"DC", &SET_implied }, {"DD", &SET_implied }, {"DE", &SET_indirect }, {"DF", &SET_implied },
            {"E0", &SET_implied }, {"E1", &SET_implied }, {"E2", &SET_implied }, {"E3", &SET_implied }, {"E4", &SET_implied }, {"E5", &SET_implied }, {"E6", &SET_indirect }, {"E7", &SET_implied }, {"E8", &SET_implied }, {"E9", &SET_implied }, {"EA", &SET_implied }, {"EB", &SET_implied }, {"EC", &SET_implied }, {"ED", &SET_implied }, {"EE", &SET_indirect }, {"EF", &SET_implied },
            {"F0", &SET_implied }, {"F1", &SET_implied }, {"F2", &SET_implied }, {"F3", &SET_implied }, {"F4", &SET_implied }, {"F5", &SET_implied }, {"F6", &SET_indirect }, {"F7", &SET_implied }, {"F8", &SET_implied }, {"F9", &SET_implied }, {"FA", &SET_implied }, {"FB", &SET_implied }, {"FC", &SET_implied }, {"FD", &SET_implied }, {"FE", &SET_indirect }, {"FF", &SET_implied }
    };

	ix_bit_instruction_table = {
            {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", &RLC_indexed_ix }, {"07", nullptr }, {"08", nullptr }, {"09", nullptr }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", &RRC_indexed_ix}, {"0F", nullptr },
            {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", &RL_indexed_ix }, {"17", nullptr }, {"18", nullptr }, {"19", nullptr }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", &RR_indexed_ix }, {"1F", nullptr },
            {"20", nullptr }, {"21", nullptr }, {"22", nullptr }, {"23", nullptr }, {"24", nullptr }, {"25", nullptr }, {"26", &SLA_indexed_ix }, {"27", nullptr }, {"28", nullptr }, {"29", nullptr }, {"2A", nullptr }, {"2B", nullptr }, {"2C", nullptr }, {"2D", nullptr }, {"2E", &SRA_indexed_ix }, {"2F", nullptr },
            {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", nullptr }, {"37", nullptr }, {"38", nullptr }, {"39", nullptr }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", &SRL_indexed_ix }, {"3F", nullptr },
            {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", &BIT_indexed_ix }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", &BIT_indexed_ix }, {"4F", nullptr },
            {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", &BIT_indexed_ix }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", &BIT_indexed_ix }, {"5F", nullptr },
            {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", &BIT_indexed_ix }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", &BIT_indexed_ix }, {"6F", nullptr },
            {"70", nullptr }, {"71", nullptr }, {"72", nullptr }, {"73", nullptr }, {"74", nullptr }, {"75", nullptr }, {"76", &BIT_indexed_ix }, {"77", nullptr }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", &BIT_indexed_ix }, {"7F", nullptr },
            {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", &RES_indexed_ix }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", &RES_indexed_ix }, {"8F", nullptr },
            {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", &RES_indexed_ix }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", &RES_indexed_ix }, {"9F", nullptr },
            {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", &RES_indexed_ix }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", &RES_indexed_ix }, {"AF", nullptr },
            {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", &RES_indexed_ix }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", &RES_indexed_ix }, {"BF", nullptr },
            {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", &SET_indexed_ix }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", &SET_indexed_ix }, {"CF", nullptr },
            {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", &SET_indexed_ix }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", &SET_indexed_ix }, {"DF", nullptr },
            {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", &SET_indexed_ix }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", &SET_indexed_ix }, {"EF", nullptr },
            {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", &SET_indexed_ix }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", &SET_indexed_ix }, {"FF", nullptr }
    };

	iy_bit_instruction_table = {
            {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", &RLC_indexed_iy }, {"07", nullptr }, {"08", nullptr }, {"09", nullptr }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", &RRC_indexed_iy }, {"0F", nullptr },
            {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", &RL_indexed_iy }, {"17", nullptr }, {"18", nullptr }, {"19", nullptr }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", &RR_indexed_iy }, {"1F", nullptr },
            {"20", nullptr }, {"21", nullptr }, {"22", nullptr }, {"23", nullptr }, {"24", nullptr }, {"25", nullptr }, {"26", &SLA_indexed_iy }, {"27", nullptr }, {"28", nullptr }, {"29", nullptr }, {"2A", nullptr }, {"2B", nullptr }, {"2C", nullptr }, {"2D", nullptr }, {"2E", &SRA_indexed_iy }, {"2F", nullptr },
            {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", nullptr }, {"37", nullptr }, {"38", nullptr }, {"39", nullptr }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", &SRL_indexed_iy }, {"3F", nullptr },
            {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", &BIT_indexed_iy }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", &BIT_indexed_iy }, {"4F", nullptr },
            {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", &BIT_indexed_iy }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", &BIT_indexed_iy }, {"5F", nullptr },
            {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", &BIT_indexed_iy }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", &BIT_indexed_iy }, {"6F", nullptr },
            {"70", nullptr }, {"71", nullptr }, {"72", nullptr }, {"73", nullptr }, {"74", nullptr }, {"75", nullptr }, {"76", &BIT_indexed_iy }, {"77", nullptr }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", &BIT_indexed_iy }, {"7F", nullptr },
            {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", &RES_indexed_iy }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", &RES_indexed_iy }, {"8F", nullptr },
            {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", &RES_indexed_iy }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", &RES_indexed_iy }, {"9F", nullptr },
            {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", &RES_indexed_iy }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", &RES_indexed_iy }, {"AF", nullptr },
            {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", &RES_indexed_iy }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", &RES_indexed_iy }, {"BF", nullptr },
            {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", &SET_indexed_iy }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", &SET_indexed_iy }, {"CF", nullptr },
            {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", &SET_indexed_iy }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", &SET_indexed_iy }, {"DF", nullptr },
            {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", &SET_indexed_iy }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", &SET_indexed_iy }, {"EF", nullptr },
            {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", &SET_indexed_iy }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", &SET_indexed_iy }, {"FF", nullptr }
    };

	register_table = {
		&B_register, // B = 0b000
		&C_register, // C = 0b001
		&D_register, // D = 0b010
		&E_register, // E = 0b011
		&H_register, // H = 0b100
		&L_register, // L = 0b101
		nullptr,     // No register has 0b110 for a bit value
		&accumulator // A = 0b111
	};

    alt_register_table = {
        &alt_B_register,
        &alt_C_register,
        &alt_D_register,
        &alt_E_register,
        &alt_H_register,
        &alt_L_register,
        nullptr,
        &alt_accumulator
    };

    register_pair_table_qq = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {&H_register, &L_register}, // HL = 0b10
            {&accumulator, &flag_register} // AF = 0b11
    };

    register_pair_table_ss = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {&H_register, &L_register}, // HL = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer) + 1,
             reinterpret_cast<uint8_t*>(&stack_pointer)} // SP = 0b11
    };

    register_pair_table_pp = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {reinterpret_cast<uint8_t*>(&index_register_x) + 1,
                    reinterpret_cast<uint8_t*>(&index_register_x)}, // IX = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer) + 1,
                          reinterpret_cast<uint8_t*>(&stack_pointer)} // SP = 0b11
    };

    register_pair_table_rr = {
            {&B_register, &C_register}, // BC = 0b00
            {&D_register, &E_register}, // DE = 0b01
            {reinterpret_cast<uint8_t*>(&index_register_y) + 1,
                          reinterpret_cast<uint8_t*>(&index_register_y)}, // IY = 0b10
            {reinterpret_cast<uint8_t*>(&stack_pointer) + 1,
                          reinterpret_cast<uint8_t*>(&stack_pointer)} // SP = 0b11
    };
}


uint8_t z80cpu::rom_read(uint16_t address) {
	return bus->rom_read(address);
}


uint8_t z80cpu::ram_read(uint16_t address) {
    return bus->ram_read(address);
}


void z80cpu::ram_write(uint16_t address, uint8_t data) {
    bus->ram_write(address, data);
}


void z80cpu::set_flag(FLAGSZ80 flag, bool set_flag) {
	if (set_flag) {
		flag_register |= flag;
	}
	else {
		flag_register &= ~flag;
	}
}

uint8_t z80cpu::get_flag(z80cpu::FLAGSZ80 flag) const {
    return ((flag_register & flag) > 0) ? 1 : 0;
}


void z80cpu::memory_refresh_counter() {
	if (((memory_refresh_register + 1) & 0x7F) < 0x7F) {
		memory_refresh_register++;
	}
	else {
		memory_refresh_register &= 0x80;
	}
}


void z80cpu::instruction_cycle() {
	// when t cycles reach 0, we are ready to read next instruction
	opcode = rom_read(program_counter);

    // increment program counter
    program_counter++;

	//memory refresh register increments after pulling an opcode
	memory_refresh_counter();

	// begin going through the main instruction table
	(this->*main_instruction_table[opcode].instruction)();
}


// Function Tables
void z80cpu::misc_instructions() {
	opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

	(this->*misc_instruction_table[opcode].instruction)();
}


void z80cpu::ix_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*ix_instruction_table[opcode].instruction)();
}


void z80cpu::iy_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*iy_instruction_table[opcode].instruction)();
}

void z80cpu::bit_instructions() {
    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*bit_instruction_table[opcode].instruction)();
}


void z80cpu::ix_bit_instructions() {
    // DDCB opcodes have a displacement value placed before the final opcode
    // ex DD CB d 06
    displacement = rom_read(program_counter);
    program_counter++;

    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*ix_bit_instruction_table[opcode].instruction)();
}


void z80cpu::iy_bit_instructions() {
    displacement = rom_read(program_counter);
    program_counter++;

    opcode = rom_read(program_counter);
    program_counter++;
    memory_refresh_counter();

    (this->*iy_bit_instruction_table[opcode].instruction)();
}