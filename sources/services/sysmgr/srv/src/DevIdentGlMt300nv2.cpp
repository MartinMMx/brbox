#include "DevIdentGlMt300nv2.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;
/* ------------------------------------------------------------------------- */
DevIdentGlMt300nv2::DevIdentGlMt300nv2()
{
}
/* ------------------------------------------------------------------------- */
DevIdentGlMt300nv2::~DevIdentGlMt300nv2()
{
}
/* ------------------------------------------------------------------------- */
RPC_SRV_RESULT DevIdentGlMt300nv2::device_identify()
{
	char command[255];
	//blink blue led on nexx3020f pocket router
	for(int i=0;i<10;i++)
	{
// /sys/class/leds/gl-mt300n-v2\:green\:power/brightness

		sprintf(command,"echo 1 > /sys/class/leds/gl-mt300n-v2\\:green\\:power/brightness");
		system(command);
		usleep(250000);
		sprintf(command,"echo 0 > /sys/class/leds/gl-mt300n-v2\\:green\\:power/brightness");
		system(command);
		usleep(250000);
	}

	//switch the blue led to ON
	sprintf(command,"echo 0 > /sys/class/leds/gl-mt300n-v2\\:green\\:power/brightness");
	if(system(command)!=0)
	{
		//pPanelReq->result=RPC_SRV_RESULT_FILE_OPEN_ERR;
		//return 0;
		;
	}
	return RPC_SRV_RESULT_SUCCESS;
}
/* ------------------------------------------------------------------------- */

