#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SmarteyeJsonDef.h"
#include "SmarteyeRpc.h"
#include "ADJsonRpcMgr.hpp"
#include "MyCmdline.h"
#include "SrcControlVersion.h"
#include "ADTimer.hpp"
/* ------------------------------------------------------------------------- */
using namespace std;
int main(int argc, const char* argv[])
{
	//cmdline parsing
	char ver[255];snprintf(ver,254,"%05d",SRC_CONTROL_VERSION);
	MyCmdline CmdLine(CMDLINE_HELPER_MODE_SERVER,SMARTEYE_JSON_PORT_NUMBER,ver);//40000 is the portnumber
	CmdLine.parse_cmdline_arguments(argc,(char**)argv);
	if(CmdLine.is_help_printed())
		return -1;//user just requested to print the help info

	//read the board-type info from cmdline argument
	ADCMN_DEV_INFO DevInfo;
	CmdLine.get_dev_info(&DevInfo);

	bool dbglog = CmdLine.get_debug_log();
	bool emulat = CmdLine.get_emulation_mode();

	//start 100ms timer
	ADTimer AppTimer(100,CmdLine.get_port_number());//only one instance per application(or process) must exist
	//create a common data Cache of the service
	SMARTEYE_CMN_DATA_CACHE DataCache;
	DataCache.pDevInfo=(void*)&DevInfo;//rpc's needs to know board or device type

	//attach rpc classes to ADJsonRpcMgr
	ADJsonRpcMgr RpcMgr(SRC_CONTROL_VERSION,dbglog,&DevInfo); //main rpc handler

	SmarteyeRpc PatternGet (SMARTEYE_RPC_ID_PATTERN_CHECK      ,EJSON_SMARTEYE_RPC_CHECK_ID_PATTERN ,emulat,dbglog,&DataCache);
	SmarteyeRpc DbgFileGet (SMARTEYE_RPC_DEBUG_OUTFILE_GET     ,EJSON_SMARTEYE_RPC_DEBUG_OUTFILE_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc DbgFileSet (SMARTEYE_RPC_DEBUG_OUTFILE_SET     ,EJSON_SMARTEYE_RPC_DEBUG_OUTFILE_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc CaptureFile(SMARTEYE_RPC_CAPTURE_JPG_IMG       ,EJSON_SMARTEYE_RPC_CAPTURE_JPG_IMG  ,emulat,dbglog,&DataCache);
	SmarteyeRpc SetCaptrRes(SMARTEYE_RPC_CAPTURE_RESOLUTION_SET,EJSON_SMARTEYE_RPC_CAPTURE_RESOLUTION_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc ChkWallFileGet(SMARTEYE_RPC_CHECKWALL_FILE_GET ,EJSON_SMARTEYE_RPC_CHECKWALL_FILE_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc ChkWallFileSet(SMARTEYE_RPC_CHECKWALL_FILE_SET ,EJSON_SMARTEYE_RPC_CHECKWALL_FILE_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc ChkWallBaseFileGet(SMARTEYE_RPC_CHECKWALL_BASE_FILE_GET ,EJSON_SMARTEYE_RPC_CHECKWALL_BASE_FILE_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc ChkWallBaseFileSet(SMARTEYE_RPC_CHECKWALL_BASE_FILE_SET ,EJSON_SMARTEYE_RPC_CHECKWALL_BASE_FILE_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc QrStringScan(SMARTEYE_RPC_SCAN_QRSTRING ,EJSON_SMARTEYE_RPC_SCAN_QRSTRING,emulat,dbglog,&DataCache);
	SmarteyeRpc CompareImages(SMARTEYE_RPC_COMPARE_IMG ,EJSON_SMARTEYE_RPC_COMPARE_IMG,emulat,dbglog,&DataCache);

	SmarteyeRpc AutoExposureGet(SMARTEYE_RPC_AUTO_EXPOSURE_GET ,EJSON_SMARTEYE_RPC_AUTO_EXPOSURE_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc AutoExposureSet(SMARTEYE_RPC_AUTO_EXPOSURE_SET ,EJSON_SMARTEYE_RPC_AUTO_EXPOSURE_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc ExposureGet    (SMARTEYE_RPC_EXPOSURE_GET ,EJSON_SMARTEYE_RPC_EXPOSURE_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc ExposureSet    (SMARTEYE_RPC_EXPOSURE_SET ,EJSON_SMARTEYE_RPC_EXPOSURE_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc AutoFocusGet(SMARTEYE_RPC_AUTO_FOCUS_GET ,EJSON_SMARTEYE_RPC_AUTO_FOCUS_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc AutoFocusSet(SMARTEYE_RPC_AUTO_FOCUS_SET ,EJSON_SMARTEYE_RPC_AUTO_FOCUS_SET,emulat,dbglog,&DataCache);
	SmarteyeRpc FocusGet    (SMARTEYE_RPC_FOCUS_GET ,EJSON_SMARTEYE_RPC_FOCUS_GET,emulat,dbglog,&DataCache);
	SmarteyeRpc FocusSet    (SMARTEYE_RPC_FOCUS_SET ,EJSON_SMARTEYE_RPC_FOCUS_SET,emulat,dbglog,&DataCache);

	RpcMgr.AttachRpc(&PatternGet);
	RpcMgr.AttachRpc(&DbgFileGet);
	RpcMgr.AttachRpc(&DbgFileSet);
	RpcMgr.AttachRpc(&CaptureFile);
	RpcMgr.AttachRpc(&SetCaptrRes);
	RpcMgr.AttachRpc(&ChkWallFileGet);
	RpcMgr.AttachRpc(&ChkWallFileSet);
	RpcMgr.AttachRpc(&ChkWallBaseFileGet);
	RpcMgr.AttachRpc(&ChkWallBaseFileSet);
	RpcMgr.AttachRpc(&QrStringScan);
	RpcMgr.AttachRpc(&CompareImages);

	RpcMgr.AttachRpc(&AutoExposureGet);
	RpcMgr.AttachRpc(&AutoExposureSet);
	RpcMgr.AttachRpc(&ExposureGet);
	RpcMgr.AttachRpc(&ExposureSet);
	RpcMgr.AttachRpc(&AutoFocusGet);
	RpcMgr.AttachRpc(&AutoFocusSet);
	RpcMgr.AttachRpc(&FocusGet);
	RpcMgr.AttachRpc(&FocusSet);


	//start listening for rpc-commands
	RpcMgr.AttachHeartBeat(&AppTimer);//attach 100ms heartbeat to ADJsonRpcMgr
	//RpcMgr.SupportShutdownRpc(false);//this is a system-manager, needs to be alive all the time, hence dont support shutdown via rpc
	RpcMgr.Start(CmdLine.get_port_number(),CmdLine.get_socket_log(),CmdLine.get_emulation_mode());
	//server is ready to serve rpc's
	RpcMgr.SetServiceReadyFlag(EJSON_RPCGMGR_READY_STATE_READY);


	//wait for sigkill or sigterm signal
	AppTimer.wait_for_exit_signal();//loop till KILL or TERM signal is received
	AppTimer.stop_timer();//stop sending heart-beats to other objects
	return 0;
}
