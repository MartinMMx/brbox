#############################################################
#
# mkimage for host
#
#############################################################
BRBOX_MKIMAGE_SITE_METHOD = local
BRBOX_MKIMAGE_SITE = $(TOPDIR)/../sources/utils/brbox-mkimage
BRBOX_MKIMAGE_INSTALL_STAGING = NO
BRBOX_MKIMAGE_INSTALL_TARGET = YES
#BRBOX_MKIMAGE_CONF_OPTS = "/usr/"
$(eval $(host-cmake-package))
#BARCO_SD_CLIENT_SDCC_CONF_OPT=-DCMAKE_INSTALL_PREFIX="/opt/fmw"

