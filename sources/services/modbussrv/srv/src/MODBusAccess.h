#ifndef __MOD_BUS_ACCESS_H_
#define __MOD_BUS_ACCESS_H_
#include <iostream>
#include "ADCommon.hpp"
#include "ModBusSrvJsonDef.h"
#include <stdint.h>
#include <modbus.h>
using namespace std;
/* ------------------------------------------------------------------------- */
typedef enum MODBUS_BAUD_T
{
	MODBUS_BAUD_1200,
	MODBUS_BAUD_2400,
	MODBUS_BAUD_4800,
	MODBUS_BAUD_9600,
	MODBUS_BAUD_END,
	MODBUS_BAUD_NONE
}MODBUS_BAUD;
/* ------------------------------------------------------------------------- */
typedef enum MODBUS_PARITY_T
{
	MODBUS_PARITY_ODD,
	MODBUS_PARITY_EVEN,
	MODBUS_PARITY_NO, //no parity
	MODBUS_PARITY_END,
	MODBUS_PARITY_NONE
}MODBUS_PARITY;
/* ------------------------------------------------------------------------- */
class MODBusAccess
{
	int fd;
	std::string node;
	RPC_SRV_RESULT DevOpened;
	RPC_SRV_RESULT getMeasureFloat(modbus_t *ctx, int address, int retries, int nb,float &result);
public:
	modbus_t *ctx;
	bool LogFlag;
	MODBusAccess(std::string DevNode,bool debuglog=false,int baud=9600,char parity='N',int stopbits=1);
	~MODBusAccess();
	RPC_SRV_RESULT InitModbus(const char* devnode,int baud,char parity,int stop_bits,bool debug=false);
	RPC_SRV_RESULT getEnergyParam(EJSON_ENRGYPARM,std::string &result);
	RPC_SRV_RESULT write_register(modbus_t *ctx, uint16_t slave, uint16_t address, uint16_t value);
	RPC_SRV_RESULT read_register(modbus_t *ctx, uint16_t slave, uint16_t address, uint16_t *value);
};
#endif
