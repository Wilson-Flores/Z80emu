#include "z80.hpp"
#include "Bus.hpp"


z80cpu::z80cpu() {
	using z = z80cpu;
	main_instruction_table = {
        {"00", &z::NOP_implied }, {"01", &z::LD_register_immediate_extended_16_bit }, {"02", &z::LD_register_indirect_register }, {"03", &z::INC_implied_register_extended }, {"04", &z::INC_implied_register }, {"05", &z::DEC_implied_register }, {"06", &z::LD_register_immediate }, {"07", &z::RLCA_implied }, {"08", &z::EX_implied_implied_af }, {"09", &z::ADD_implied_register_extended }, {"0A", &z::LD_register_register_indirect }, {"0B", &z::DEC_implied_register_extended }, {"0C", &z::INC_implied_register }, {"0D", &z::DEC_implied_register }, {"0E", &z::LD_register_immediate }, {"0F", &z::RRCA_implied },
        {"10", nullptr }, {"11", &z::LD_register_immediate_extended_16_bit }, {"12", &z::LD_register_indirect_register }, {"13", &z::INC_implied_register_extended }, {"14", &z::INC_implied_register }, {"15", &z::DEC_implied_register }, {"16", &z::LD_register_immediate }, {"17", &z::RLA_implied }, {"18", nullptr }, {"19", &z::ADD_implied_register_extended }, {"1A", &z::LD_register_register_indirect }, {"1B", &z::DEC_implied_register_extended }, {"1C", &z::INC_implied_register }, {"1D", &z::DEC_implied_register }, {"1E", &z::LD_register_immediate }, {"1F", &z::RRA_implied },
        {"20", nullptr }, {"21", &z::LD_register_immediate_extended_16_bit }, {"22", &z::LD_extended_register_hl }, {"23", &z::INC_implied_register_extended }, {"24", &z::INC_implied_register }, {"25", &z::DEC_implied_register }, {"26", &z::LD_register_immediate }, {"27", &z::DAA_implied }, {"28", nullptr }, {"29", &z::ADD_implied_register_extended }, {"2A", &z::LD_register_extended_hl }, {"2B", &z::DEC_implied_register_extended }, {"2C", &z::INC_implied_register }, {"2D", &z::DEC_implied_register }, {"2E", &z::LD_register_immediate }, {"2F", &z::CPL_implied },
        {"30", nullptr }, {"31", &z::LD_register_immediate_extended_16_bit }, {"32", &z::LD_extended_register }, {"33", &z::INC_implied_register_extended }, {"34", &z::INC_implied_register_indirect }, {"35", &z::DEC_implied_register_indirect }, {"36", &z::LD_register_indirect_immediate }, {"37", &z::SCF_implied }, {"38", nullptr }, {"39", &z::ADD_implied_register_extended }, {"3A", &z::LD_register_extended }, {"3B", &z::DEC_implied_register_extended }, {"3C", &z::INC_implied_register }, {"3D", &z::DEC_implied_register }, {"3E", &z::LD_register_immediate }, {"3F", &z::CCF_implied },
        {"40", &z::LD_register_register }, {"41", &z::LD_register_register }, {"42", &z::LD_register_register }, {"43", &z::LD_register_register }, {"44", &z::LD_register_register }, {"45", &z::LD_register_register }, {"46", &z::LD_register_register_indirect }, {"47", &z::LD_register_register }, {"48", &z::LD_register_register }, {"49", &z::LD_register_register }, {"4A", &z::LD_register_register }, {"4B", &z::LD_register_register }, {"4C", &z::LD_register_register }, {"4D", &z::LD_register_register }, {"4E", &z::LD_register_register_indirect }, {"4F", &z::LD_register_register },
        {"50", &z::LD_register_register }, {"51", &z::LD_register_register }, {"52", &z::LD_register_register }, {"53", &z::LD_register_register }, {"54", &z::LD_register_register }, {"55", &z::LD_register_register }, {"56", &z::LD_register_register_indirect }, {"57", &z::LD_register_register }, {"58", &z::LD_register_register }, {"59", &z::LD_register_register }, {"5A", &z::LD_register_register }, {"5B", &z::LD_register_register }, {"5C", &z::LD_register_register }, {"5D", &z::LD_register_register }, {"5E", &z::LD_register_register_indirect }, {"5F", &z::LD_register_register },
        {"60", &z::LD_register_register }, {"61", &z::LD_register_register }, {"62", &z::LD_register_register }, {"63", &z::LD_register_register }, {"64", &z::LD_register_register }, {"65", &z::LD_register_register }, {"66", &z::LD_register_register_indirect }, {"67", &z::LD_register_register }, {"68", &z::LD_register_register }, {"69", &z::LD_register_register }, {"6A", &z::LD_register_register }, {"6B", &z::LD_register_register }, {"6C", &z::LD_register_register }, {"6D", &z::LD_register_register }, {"6E", &z::LD_register_register_indirect }, {"6F", &z::LD_register_register },
        {"70", &z::LD_register_indirect_register }, {"71", &z::LD_register_indirect_register }, {"72", &z::LD_register_indirect_register }, {"73", &z::LD_register_indirect_register }, {"74", &z::LD_register_indirect_register }, {"75", &z::LD_register_indirect_register }, {"76", nullptr }, {"77", &z::LD_register_indirect_register }, {"78", &z::LD_register_register }, {"79", &z::LD_register_register }, {"7A", &z::LD_register_register }, {"7B", &z::LD_register_register }, {"7C", &z::LD_register_register }, {"7D", &z::LD_register_register }, {"7E", &z::LD_register_register_indirect }, {"7F", &z::LD_register_register },
        {"80", &z::ADD_implied_register }, {"81", &z::ADD_implied_register }, {"82", &z::ADD_implied_register }, {"83", &z::ADD_implied_register }, {"84", &z::ADD_implied_register }, {"85", &z::ADD_implied_register }, {"86", &z::ADD_implied_register_indirect }, {"87", &z::ADD_implied_register }, {"88", &z::ADC_implied_register }, {"89", &z::ADC_implied_register }, {"8A", &z::ADC_implied_register }, {"8B", &z::ADC_implied_register }, {"8C", &z::ADC_implied_register }, {"8D", &z::ADC_implied_register }, {"8E", &z::ADC_implied_register_indirect }, {"8F", &z::ADC_implied_register },
        {"90", &z::SUB_implied_register }, {"91", &z::SUB_implied_register }, {"92", &z::SUB_implied_register }, {"93", &z::SUB_implied_register }, {"94", &z::SUB_implied_register }, {"95", &z::SUB_implied_register }, {"96", &z::SUB_implied_register_indirect }, {"97", &z::SUB_implied_register }, {"98", &z::SBC_implied_register }, {"99", &z::SBC_implied_register }, {"9A", &z::SBC_implied_register }, {"9B", &z::SBC_implied_register }, {"9C", &z::SBC_implied_register }, {"9D", &z::SBC_implied_register }, {"9E", &z::SBC_implied_register_indirect }, {"9F", &z::SBC_implied_register },
        {"A0", &z::AND_implied_register }, {"A1", &z::AND_implied_register }, {"A2", &z::AND_implied_register }, {"A3", &z::AND_implied_register }, {"A4", &z::AND_implied_register }, {"A5", &z::AND_implied_register }, {"A6", &z::AND_implied_register_indirect }, {"A7", &z::AND_implied_register }, {"A8", &z::XOR_implied_register }, {"A9", &z::XOR_implied_register }, {"AA", &z::XOR_implied_register }, {"AB", &z::XOR_implied_register }, {"AC", &z::XOR_implied_register }, {"AD", &z::XOR_implied_register }, {"AE", &z::XOR_implied_register_indirect }, {"AF", &z::XOR_implied_register },
        {"B0", &z::OR_implied_register }, {"B1", &z::OR_implied_register }, {"B2", &z::OR_implied_register }, {"B3", &z::OR_implied_register }, {"B4", &z::OR_implied_register }, {"B5", &z::OR_implied_register }, {"B6", &z::OR_implied_register_indirect }, {"B7", &z::OR_implied_register }, {"B8", &z::CP_implied_register }, {"B9", &z::CP_implied_register }, {"BA", &z::CP_implied_register }, {"BB", &z::CP_implied_register }, {"BC", &z::CP_implied_register }, {"BD", &z::CP_implied_register }, {"BE", &z::CP_implied_register_indirect }, {"BF", &z::CP_implied_register },
        {"C0", nullptr }, {"C1", &z::POP_register_indirect_register }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", &z::PUSH_register_indirect_register }, {"C6", &z::ADD_implied_immediate }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", &z::bit_instructions }, {"CC", nullptr }, {"CD", nullptr }, {"CE", &z::ADC_implied_immediate }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", &z::POP_register_indirect_register }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", &z::PUSH_register_indirect_register }, {"D6", &z::SUB_implied_immediate }, {"D7", nullptr }, {"D8", nullptr }, {"D9", &z::EXX_implied_implied }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", &z::ix_instructions }, {"DE", &z::SBC_implied_immediate }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", &z::POP_register_indirect_register }, {"E2", nullptr }, {"E3", &z::EX_register_indirect_implied_hl }, {"E4", nullptr }, {"E5", &z::PUSH_register_indirect_register }, {"E6", &z::AND_implied_immediate }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", &z::EX_implied_implied }, {"EC", nullptr }, {"ED", &z::misc_instructions }, {"EE", &z::XOR_implied_immediate }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", &z::POP_register_indirect_register }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", &z::PUSH_register_indirect_register }, {"F6", &z::OR_implied_immediate }, {"F7", nullptr }, {"F8", nullptr }, {"F9", &z::LD_register_register_hl }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", &z::iy_instructions }, {"FE", &z::CP_implied_immediate }, {"FF", nullptr }
    };

	misc_instruction_table = {
		{"00", nullptr },{ "01", nullptr },{ "02", nullptr },{ "03", nullptr },{ "04", nullptr },{ "05", nullptr },{ "06", nullptr },{ "07", nullptr },{ "08", nullptr },{ "09", nullptr },{ "0A", nullptr },{ "0B", nullptr },{ "0C", nullptr },{ "0D", nullptr },{ "0E", nullptr },{ "0F", nullptr },
		{"10", nullptr },{ "11", nullptr },{ "12", nullptr },{ "13", nullptr },{ "14", nullptr },{ "15", nullptr },{ "16", nullptr },{ "17", nullptr },{ "18", nullptr },{ "19", nullptr },{ "1A", nullptr },{ "1B", nullptr },{ "1C", nullptr },{ "1D", nullptr },{ "1E", nullptr },{ "1F", nullptr },
		{"20", nullptr },{ "21", nullptr },{ "22", nullptr },{ "23", nullptr },{ "24", nullptr },{ "25", nullptr },{ "26", nullptr },{ "27", nullptr },{ "28", nullptr },{ "29", nullptr },{ "2A", nullptr },{ "2B", nullptr },{ "2C", nullptr },{ "2D", nullptr },{ "2E", nullptr },{ "2F", nullptr },
		{"30", nullptr },{ "31", nullptr },{ "32", nullptr },{ "33", nullptr },{ "34", nullptr },{ "35", nullptr },{ "36", nullptr },{ "37", nullptr },{ "38", nullptr },{ "39", nullptr },{ "3A", nullptr },{ "3B", nullptr },{ "3C", nullptr },{ "3D", nullptr },{ "3E", nullptr },{ "3F", nullptr },
		{"40", nullptr },{ "41", nullptr },{ "42", &z::SBC_implied_register_extended },{ "43", &z::LD_extended_register_16_bit },{ "44", &z::NEG_implied },{ "45", nullptr },{ "46", nullptr },{ "47", &z::LD_implied_register },{ "48", nullptr },{ "49", nullptr },{ "4A", &z::ADC_implied_register_extended },{ "4B", &z::LD_register_extended_16_bit },{ "4C", nullptr },{ "4D", nullptr },{ "4E", nullptr },{ "4F", &z::LD_implied_register },
		{"50", nullptr },{ "51", nullptr },{ "52", &z::SBC_implied_register_extended },{ "53", &z::LD_extended_register_16_bit },{ "54", nullptr },{ "55", nullptr },{ "56", nullptr },{ "57", &z::LD_register_implied },{ "58", nullptr },{ "59", nullptr },{ "5A", &z::ADC_implied_register_extended },{ "5B", &z::LD_register_extended_16_bit },{ "5C", nullptr },{ "5D", nullptr },{ "5E", nullptr },{ "5F", &z::LD_register_implied },
		{"60", nullptr },{ "61", nullptr },{ "62", &z::SBC_implied_register_extended },{ "63", &z::LD_extended_register_16_bit },{ "64", nullptr },{ "65", nullptr },{ "66", nullptr },{ "67", &z::RRD_implied },{ "68", nullptr },{ "69", nullptr },{ "6A", &z::ADC_implied_register_extended },{ "6B", &z::LD_register_extended_16_bit },{ "6C", nullptr },{ "6D", nullptr },{ "6E", nullptr },{ "6F", &z::RLD_implied },
		{"70", nullptr },{ "71", nullptr },{ "72", &z::SBC_implied_register_extended },{ "73", &z::LD_extended_register_16_bit },{ "74", nullptr },{ "75", nullptr },{ "76", nullptr },{ "77", nullptr },{ "78", nullptr },{ "79", nullptr },{ "7A", &z::ADC_implied_register_extended },{ "7B", &z::LD_register_extended_16_bit },{ "7C", nullptr },{ "7D", nullptr },{ "7E", nullptr },{ "7F", nullptr },
		{"80", nullptr },{ "81", nullptr },{ "82", nullptr },{ "83", nullptr },{ "84", nullptr },{ "85", nullptr },{ "86", nullptr },{ "87", nullptr },{ "88", nullptr },{ "89", nullptr },{ "8A", nullptr },{ "8B", nullptr },{ "8C", nullptr },{ "8D", nullptr },{ "8E", nullptr },{ "8F", nullptr },
		{"90", nullptr },{ "91", nullptr },{ "92", nullptr },{ "93", nullptr },{ "94", nullptr },{ "95", nullptr },{ "96", nullptr },{ "97", nullptr },{ "98", nullptr },{ "99", nullptr },{ "9A", nullptr },{ "9B", nullptr },{ "9C", nullptr },{ "9D", nullptr },{ "9E", nullptr },{ "9F", nullptr },
		{"A0", &z::LDI_register_indirect_register_indirect },{ "A1", &z::CPI_register_indirect },{ "A2", nullptr },{ "A3", nullptr },{ "A4", nullptr },{ "A5", nullptr },{ "A6", nullptr },{ "A7", nullptr },{ "A8", &z::LDD_register_indirect_register_indirect },{ "A9", &z::CPD_register_indirect },{ "AA", nullptr },{ "AB", nullptr },{ "AC", nullptr },{ "AD", nullptr },{ "AE", nullptr },{ "AF", nullptr },
		{"B0", &z::LDIR_register_indirect_register_indirect },{ "B1", &z::CPIR_register_indirect },{ "B2", nullptr },{ "B3", nullptr },{ "B4", nullptr },{ "B5", nullptr },{ "B6", nullptr },{ "B7", nullptr },{ "B8", &z::LDDR_register_indirect_register_indirect },{ "B9", &z::CPDR_register_indirect },{ "BA", nullptr },{ "BB", nullptr },{ "BC", nullptr },{ "BD", nullptr },{ "BE", nullptr },{ "BF", nullptr },
        {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

	ix_instruction_table = {
        {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", nullptr }, {"07", nullptr }, {"08", nullptr }, {"09", &z::ADD_implied_register_extended_ix }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", nullptr }, {"0F", nullptr },
        {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", nullptr }, {"17", nullptr }, {"18", nullptr }, {"19", &z::ADD_implied_register_extended_ix }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", nullptr }, {"1F", nullptr },
        {"20", nullptr }, {"21", &z::LD_register_immediate_extended_ix }, {"22", &z::LD_extended_register_ix }, {"23", &z::INC_implied_register_extended_ix }, {"24", nullptr }, {"25", nullptr }, {"26", nullptr }, {"27", nullptr }, {"28", nullptr }, {"29", &z::ADD_implied_register_extended_ix }, {"2A", &z::LD_register_extended_ix }, {"2B", &z::DEC_implied_register_extended_ix }, {"2C", nullptr }, {"2D", nullptr }, {"2E", nullptr }, {"2F", nullptr },
        {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", &z::INC_implied_indexed_ix }, {"35", &z::DEC_implied_indexed_ix }, {"36", &z::LD_indexed_ix_immediate }, {"37", nullptr }, {"38", nullptr }, {"39", &z::ADD_implied_register_extended_ix }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", nullptr }, {"3F", nullptr },
        {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", &z::LD_register_indexed_ix }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", &z::LD_register_indexed_ix }, {"4F", nullptr },
        {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", &z::LD_register_indexed_ix }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", &z::LD_register_indexed_ix }, {"5F", nullptr },
        {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", &z::LD_register_indexed_ix }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", &z::LD_register_indexed_ix }, {"6F", nullptr },
        {"70", &z::LD_indexed_ix_register }, {"71", &z::LD_indexed_ix_register }, {"72", &z::LD_indexed_ix_register }, {"73", &z::LD_indexed_ix_register }, {"74", &z::LD_indexed_ix_register }, {"75", &z::LD_indexed_ix_register}, {"76", nullptr }, {"77", &z::LD_indexed_ix_register }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", &z::LD_register_indexed_ix }, {"7F", nullptr },
        {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", &z::ADD_implied_indexed_ix }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", &z::ADC_implied_indexed_ix }, {"8F", nullptr },
        {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", &z::SUB_implied_indexed_ix }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", &z::SBC_implied_indexed_ix }, {"9F", nullptr },
        {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", &z::AND_implied_indexed_ix }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", &z::XOR_implied_indexed_ix }, {"AF", nullptr },
        {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", &z::OR_implied_indexed_ix }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", &z::CP_implied_indexed_ix }, {"BF", nullptr },
        {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", &z::ix_bit_instructions }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", &z::POP_register_indirect_register_ix }, {"E2", nullptr }, {"E3", &z::EX_register_indirect_implied_ix }, {"E4", nullptr }, {"E5", &z::PUSH_register_indirect_register_ix }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", &z::LD_register_register_ix }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

	iy_instruction_table = {
        {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", nullptr }, {"07", nullptr }, {"08", nullptr }, {"09", &z::ADD_implied_register_extended_iy }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", nullptr }, {"0F", nullptr },
        {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", nullptr }, {"17", nullptr }, {"18", nullptr }, {"19", &z::ADD_implied_register_extended_iy }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", nullptr }, {"1F", nullptr },
        {"20", nullptr }, {"21", &z::LD_register_immediate_extended_iy }, {"22", &z::LD_extended_register_iy }, {"23", &z::INC_implied_register_extended_iy }, {"24", nullptr }, {"25", nullptr }, {"26", nullptr }, {"27", nullptr }, {"28", nullptr }, {"29", &z::ADD_implied_register_extended_iy }, {"2A", &z::LD_register_extended_iy }, {"2B", &z::DEC_implied_register_extended_iy }, {"2C", nullptr }, {"2D", nullptr }, {"2E", nullptr }, {"2F", nullptr },
        {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", &z::INC_implied_indexed_iy }, {"35", &z::DEC_implied_indexed_iy }, {"36", &z::LD_indexed_iy_immediate }, {"37", nullptr }, {"38", nullptr }, {"39", &z::ADD_implied_register_extended_iy }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", nullptr }, {"3F", nullptr },
        {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", &z::LD_register_indexed_iy }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", &z::LD_register_indexed_iy }, {"4F", nullptr },
        {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", &z::LD_register_indexed_iy }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", &z::LD_register_indexed_iy }, {"5F", nullptr },
        {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", &z::LD_register_indexed_iy }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", &z::LD_register_indexed_iy }, {"6F", nullptr },
        {"70", &z::LD_indexed_iy_register }, {"71", &z::LD_indexed_iy_register }, {"72", &z::LD_indexed_iy_register }, {"73", &z::LD_indexed_iy_register }, {"74", &z::LD_indexed_iy_register }, {"75", &z::LD_indexed_iy_register }, {"76", nullptr }, {"77", &z::LD_indexed_iy_register }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", &z::LD_register_indexed_iy }, {"7F", nullptr },
        {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", &z::ADD_implied_indexed_iy }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", &z::ADC_implied_indexed_iy }, {"8F", nullptr },
        {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", &z::SUB_implied_indexed_iy }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", &z::SBC_implied_indexed_iy }, {"9F", nullptr },
        {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", &z::AND_implied_indexed_iy }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", &z::XOR_implied_indexed_iy }, {"AF", nullptr },
        {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", &z::OR_implied_indexed_iy }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", &z::CP_implied_indexed_iy }, {"BF", nullptr },
        {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", &z::iy_bit_instructions }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
        {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
        {"E0", nullptr }, {"E1", &z::POP_register_indirect_register_iy }, {"E2", nullptr }, {"E3", &z::EX_register_indirect_implied_iy }, {"E4", nullptr }, {"E5", &z::PUSH_register_indirect_register_iy }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
        {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", &z::LD_register_register_iy }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

    bit_instruction_table = {
            {"00", &z::RLC_implied }, {"01", &z::RLC_implied }, {"02", &z::RLC_implied }, {"03", &z::RLC_implied }, {"04", &z::RLC_implied }, {"05", &z::RLC_implied }, {"06", &z::RLC_indirect }, {"07", &z::RLC_implied }, {"08", &z::RRC_implied }, {"09", &z::RRC_implied }, {"0A", &z::RRC_implied }, {"0B", &z::RRC_implied }, {"0C", &z::RRC_implied }, {"0D", &z::RRC_implied }, {"0E", &z::RRC_indirect }, {"0F", &z::RRC_implied },
            {"10", &z::RL_implied }, {"11", &z::RL_implied }, {"12", &z::RL_implied }, {"13", &z::RL_implied }, {"14", &z::RL_implied }, {"15", &z::RL_implied }, {"16", &z::RL_indirect }, {"17", &z::RL_implied }, {"18", &z::RR_implied }, {"19", &z::RR_implied  }, {"1A", &z::RR_implied  }, {"1B", &z::RR_implied  }, {"1C", &z::RR_implied  }, {"1D", &z::RR_implied  }, {"1E", &z::RR_indirect  }, {"1F", &z::RR_implied  },
            {"20", &z::SLA_implied }, {"21", &z::SLA_implied }, {"22", &z::SLA_implied }, {"23", &z::SLA_implied }, {"24", &z::SLA_implied }, {"25", &z::SLA_implied }, {"26", &z::SLA_indirect }, {"27", &z::SLA_implied }, {"28", &z::SRA_implied }, {"29", &z::SRA_implied }, {"2A", &z::SRA_implied }, {"2B", &z::SRA_implied }, {"2C", &z::SRA_implied }, {"2D", &z::SRA_implied }, {"2E", &z::SRA_indirect }, {"2F", &z::SRA_implied },
            {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", nullptr }, {"37", nullptr }, {"38", &z::SRL_implied }, {"39", &z::SRL_implied }, {"3A", &z::SRL_implied }, {"3B", &z::SRL_implied }, {"3C", &z::SRL_implied }, {"3D", &z::SRL_implied }, {"3E", &z::SRL_indirect }, {"3F", &z::SRL_implied },
            {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", nullptr }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", nullptr }, {"4F", nullptr },
            {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", nullptr }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", nullptr }, {"5F", nullptr },
            {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", nullptr }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", nullptr }, {"6F", nullptr },
            {"70", nullptr }, {"71", nullptr }, {"72", nullptr }, {"73", nullptr }, {"74", nullptr }, {"75", nullptr }, {"76", nullptr }, {"77", nullptr }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", nullptr }, {"7F", nullptr },
            {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", nullptr }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", nullptr }, {"8F", nullptr },
            {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", nullptr }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", nullptr }, {"9F", nullptr },
            {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", nullptr }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", nullptr }, {"AF", nullptr },
            {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", nullptr }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", nullptr }, {"BF", nullptr },
            {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
            {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
            {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
            {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

    ix_bit_instruction_table = {
            {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", &z::RLC_indexed_ix }, {"07", nullptr }, {"08", nullptr }, {"09", nullptr }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", &z::RRC_indexed_ix}, {"0F", nullptr },
            {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", &z::RL_indexed_ix }, {"17", nullptr }, {"18", nullptr }, {"19", nullptr }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", &z::RR_indexed_ix }, {"1F", nullptr },
            {"20", nullptr }, {"21", nullptr }, {"22", nullptr }, {"23", nullptr }, {"24", nullptr }, {"25", nullptr }, {"26", &z::SLA_indexed_ix }, {"27", nullptr }, {"28", nullptr }, {"29", nullptr }, {"2A", nullptr }, {"2B", nullptr }, {"2C", nullptr }, {"2D", nullptr }, {"2E", &z::SRA_indexed_ix }, {"2F", nullptr },
            {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", nullptr }, {"37", nullptr }, {"38", nullptr }, {"39", nullptr }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", &z::SRL_indexed_ix }, {"3F", nullptr },
            {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", nullptr }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", nullptr }, {"4F", nullptr },
            {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", nullptr }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", nullptr }, {"5F", nullptr },
            {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", nullptr }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", nullptr }, {"6F", nullptr },
            {"70", nullptr }, {"71", nullptr }, {"72", nullptr }, {"73", nullptr }, {"74", nullptr }, {"75", nullptr }, {"76", nullptr }, {"77", nullptr }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", nullptr }, {"7F", nullptr },
            {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", nullptr }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", nullptr }, {"8F", nullptr },
            {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", nullptr }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", nullptr }, {"9F", nullptr },
            {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", nullptr }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", nullptr }, {"AF", nullptr },
            {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", nullptr }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", nullptr }, {"BF", nullptr },
            {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
            {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
            {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
            {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
    };

    iy_bit_instruction_table = {
            {"00", nullptr }, {"01", nullptr }, {"02", nullptr }, {"03", nullptr }, {"04", nullptr }, {"05", nullptr }, {"06", &z::RLC_indexed_iy }, {"07", nullptr }, {"08", nullptr }, {"09", nullptr }, {"0A", nullptr }, {"0B", nullptr }, {"0C", nullptr }, {"0D", nullptr }, {"0E", &z::RRC_indexed_iy }, {"0F", nullptr },
            {"10", nullptr }, {"11", nullptr }, {"12", nullptr }, {"13", nullptr }, {"14", nullptr }, {"15", nullptr }, {"16", &z::RL_indexed_iy }, {"17", nullptr }, {"18", nullptr }, {"19", nullptr }, {"1A", nullptr }, {"1B", nullptr }, {"1C", nullptr }, {"1D", nullptr }, {"1E", &z::RR_indexed_iy }, {"1F", nullptr },
            {"20", nullptr }, {"21", nullptr }, {"22", nullptr }, {"23", nullptr }, {"24", nullptr }, {"25", nullptr }, {"26", &z::SLA_indexed_iy }, {"27", nullptr }, {"28", nullptr }, {"29", nullptr }, {"2A", nullptr }, {"2B", nullptr }, {"2C", nullptr }, {"2D", nullptr }, {"2E", &z::SRA_indexed_iy }, {"2F", nullptr },
            {"30", nullptr }, {"31", nullptr }, {"32", nullptr }, {"33", nullptr }, {"34", nullptr }, {"35", nullptr }, {"36", nullptr }, {"37", nullptr }, {"38", nullptr }, {"39", nullptr }, {"3A", nullptr }, {"3B", nullptr }, {"3C", nullptr }, {"3D", nullptr }, {"3E", &z::SRL_indexed_iy }, {"3F", nullptr },
            {"40", nullptr }, {"41", nullptr }, {"42", nullptr }, {"43", nullptr }, {"44", nullptr }, {"45", nullptr }, {"46", nullptr }, {"47", nullptr }, {"48", nullptr }, {"49", nullptr }, {"4A", nullptr }, {"4B", nullptr }, {"4C", nullptr }, {"4D", nullptr }, {"4E", nullptr }, {"4F", nullptr },
            {"50", nullptr }, {"51", nullptr }, {"52", nullptr }, {"53", nullptr }, {"54", nullptr }, {"55", nullptr }, {"56", nullptr }, {"57", nullptr }, {"58", nullptr }, {"59", nullptr }, {"5A", nullptr }, {"5B", nullptr }, {"5C", nullptr }, {"5D", nullptr }, {"5E", nullptr }, {"5F", nullptr },
            {"60", nullptr }, {"61", nullptr }, {"62", nullptr }, {"63", nullptr }, {"64", nullptr }, {"65", nullptr }, {"66", nullptr }, {"67", nullptr }, {"68", nullptr }, {"69", nullptr }, {"6A", nullptr }, {"6B", nullptr }, {"6C", nullptr }, {"6D", nullptr }, {"6E", nullptr }, {"6F", nullptr },
            {"70", nullptr }, {"71", nullptr }, {"72", nullptr }, {"73", nullptr }, {"74", nullptr }, {"75", nullptr }, {"76", nullptr }, {"77", nullptr }, {"78", nullptr }, {"79", nullptr }, {"7A", nullptr }, {"7B", nullptr }, {"7C", nullptr }, {"7D", nullptr }, {"7E", nullptr }, {"7F", nullptr },
            {"80", nullptr }, {"81", nullptr }, {"82", nullptr }, {"83", nullptr }, {"84", nullptr }, {"85", nullptr }, {"86", nullptr }, {"87", nullptr }, {"88", nullptr }, {"89", nullptr }, {"8A", nullptr }, {"8B", nullptr }, {"8C", nullptr }, {"8D", nullptr }, {"8E", nullptr }, {"8F", nullptr },
            {"90", nullptr }, {"91", nullptr }, {"92", nullptr }, {"93", nullptr }, {"94", nullptr }, {"95", nullptr }, {"96", nullptr }, {"97", nullptr }, {"98", nullptr }, {"99", nullptr }, {"9A", nullptr }, {"9B", nullptr }, {"9C", nullptr }, {"9D", nullptr }, {"9E", nullptr }, {"9F", nullptr },
            {"A0", nullptr }, {"A1", nullptr }, {"A2", nullptr }, {"A3", nullptr }, {"A4", nullptr }, {"A5", nullptr }, {"A6", nullptr }, {"A7", nullptr }, {"A8", nullptr }, {"A9", nullptr }, {"AA", nullptr }, {"AB", nullptr }, {"AC", nullptr }, {"AD", nullptr }, {"AE", nullptr }, {"AF", nullptr },
            {"B0", nullptr }, {"B1", nullptr }, {"B2", nullptr }, {"B3", nullptr }, {"B4", nullptr }, {"B5", nullptr }, {"B6", nullptr }, {"B7", nullptr }, {"B8", nullptr }, {"B9", nullptr }, {"BA", nullptr }, {"BB", nullptr }, {"BC", nullptr }, {"BD", nullptr }, {"BE", nullptr }, {"BF", nullptr },
            {"C0", nullptr }, {"C1", nullptr }, {"C2", nullptr }, {"C3", nullptr }, {"C4", nullptr }, {"C5", nullptr }, {"C6", nullptr }, {"C7", nullptr }, {"C8", nullptr }, {"C9", nullptr }, {"CA", nullptr }, {"CB", nullptr }, {"CC", nullptr }, {"CD", nullptr }, {"CE", nullptr }, {"CF", nullptr },
            {"D0", nullptr }, {"D1", nullptr }, {"D2", nullptr }, {"D3", nullptr }, {"D4", nullptr }, {"D5", nullptr }, {"D6", nullptr }, {"D7", nullptr }, {"D8", nullptr }, {"D9", nullptr }, {"DA", nullptr }, {"DB", nullptr }, {"DC", nullptr }, {"DD", nullptr }, {"DE", nullptr }, {"DF", nullptr },
            {"E0", nullptr }, {"E1", nullptr }, {"E2", nullptr }, {"E3", nullptr }, {"E4", nullptr }, {"E5", nullptr }, {"E6", nullptr }, {"E7", nullptr }, {"E8", nullptr }, {"E9", nullptr }, {"EA", nullptr }, {"EB", nullptr }, {"EC", nullptr }, {"ED", nullptr }, {"EE", nullptr }, {"EF", nullptr },
            {"F0", nullptr }, {"F1", nullptr }, {"F2", nullptr }, {"F3", nullptr }, {"F4", nullptr }, {"F5", nullptr }, {"F6", nullptr }, {"F7", nullptr }, {"F8", nullptr }, {"F9", nullptr }, {"FA", nullptr }, {"FB", nullptr }, {"FC", nullptr }, {"FD", nullptr }, {"FE", nullptr }, {"FF", nullptr }
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

//TODO: create another variable to store displacement, ex: DD CB d 06
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