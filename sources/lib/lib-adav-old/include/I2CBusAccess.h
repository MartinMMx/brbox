#ifndef __I2C_BUS_ACCESS_H_
#define __I2C_BUS_ACCESS_H_
#include <iostream>
#include "ADCommon.hpp"
#include <stdint.h>
using namespace std;
//#include "ADCmdlineHelper.hpp"
//#include "ADCmnStringProcessor.hpp"
class I2CBusAccess
{
	int fd;
	RPC_SRV_RESULT DevOpened;
	std::string node;
public:
	I2CBusAccess(std::string DevNode);
	~I2CBusAccess();
	RPC_SRV_RESULT SetSlaveAddr(uint8_t addr);
	RPC_SRV_RESULT read_byte(uint32_t addr, uint8_t *data);
	RPC_SRV_RESULT write_byte(uint32_t addr, uint8_t data);
	RPC_SRV_RESULT read_word(uint32_t addr, uint16_t *data);
	RPC_SRV_RESULT write_word(uint32_t addr, uint16_t data);
	RPC_SRV_RESULT read_dword(uint32_t addr, uint32_t *data);
	RPC_SRV_RESULT write_dword(uint32_t addr, uint32_t data);
	RPC_SRV_RESULT write_array(uint32_t addr, uint8_t *data,uint32_t len);
};
#endif