#ifndef __SYSMGR_JSON_DEF_H_
#define __SYSMGR_JSON_DEF_H_
/*****************************************************************************/
#define SYSMGR_JSON_PORT_NUMBER 42600

//rpc-1
#define SYSMGR_RPC_FMW_VER_GET         "get_fmw_ver"
#define SYSMGR_RPC_FMW_VER_SET         "set_fmw_ver"
#define SYSMGR_RPC_FMW_VER_ARGVER      "version"
typedef struct SYSMGR_FMW_VER_PACKET_T
{
	char fmw_ver[512];
}SYSMGR_FMW_VER_PACKET;

//rpc-2
#define SYSMGR_RPC_IP_ADDR_GET         "get_ip_addr"
#define SYSMGR_RPC_IP_ADDR_SET         "set_ip_addr"
#define SYSMGR_RPC_IP_ADDR_ARGVER      "iface"
typedef struct SYSMGR_IP_ADDR_PACKET_T
{
	char ip_addr[512];
}SYSMGR_IP_ADDR_PACKET;

#endif

