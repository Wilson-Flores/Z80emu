#ifndef  Bus_hpp
#define Bus_hpp

#include <cstdint>
#include "z80.hpp"
#include <array>


constexpr size_t MEMORY_SIZE = 1024 * 64;

class Bus {
public:
	Bus();

	z80cpu cpu;

	std::array<uint8_t, MEMORY_SIZE> ram{};
    std::array<uint8_t, MEMORY_SIZE> rom{};

	void ram_write(uint16_t address, uint8_t data);
	uint8_t ram_read(uint16_t address);


    void rom_write(uint16_t address, uint8_t data);
    uint8_t rom_read(uint16_t address);
	void rom_reset();

};


#endif // ! Bus_hpp
