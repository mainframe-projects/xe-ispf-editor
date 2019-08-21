## Process this file with automake to produce Makefile.in
##v767:070606-autoconf:add header chk(ncurses.h,cups/cups.h)
##                     use PACKAGE_LIBS for -lgnomevfs-2 set by PKG_CHECKE_MODULES(set -L)
##
## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES2 = \
	$(PACKAGE_CFLAGS)\
	 -I../ulib -I../

#AM_CFLAGS=-DUTF8SUPP
AM_CFLAGS=-DUTF8SUPP $(INCLUDES2)

bin_PROGRAMS  = \
                xbc \
                xci \
                xcv \
                xfc \
                xff  \
                xfg  \
                xdc \
                xdd  \
                xpe  \
                xts 
noinst_PROGRAMS  = \
                xcvsjisc \
                xdig \
                xds  \
                xfmt \
                xfs  \
                xlow \
                xmj  \
                xutf8

xbc_SOURCES  = xbc.c
xci_SOURCES  = xci.c
xcv_SOURCES  = xcv.c
xcvsjisc_SOURCES  = xcvsjisc.c
xdc_SOURCES  = xdc.c
xdd_SOURCES  = xdd.c
xdig_SOURCES  = xdig.c
xds_SOURCES  = xds.c
xfc_SOURCES  = xfc.c
xff_SOURCES  = xff.c
xfg_SOURCES  = xfg.c
xfmt_SOURCES  = xfmt.c
xfs_SOURCES  = xfs.c
xlow_SOURCES  = xlow.c
xmj_SOURCES  = xmj.c
xpe_SOURCES  = xpe.c
xutf8_SOURCES  = xutf8.c
xts_SOURCES  = xts.c

DEPS= ../ulib/libuserxe.a
xbc_DEPENDENCIES       = $(DEPS)
xci_DEPENDENCIES       = $(DEPS)
xcv_DEPENDENCIES       = $(DEPS)
xcvsjisc_DEPENDENCIES  = $(DEPS)
xdc_DEPENDENCIES       = $(DEPS)
xdd_DEPENDENCIES       = $(DEPS)
xdig_DEPENDENCIES      = $(DEPS)
xds_DEPENDENCIES       = $(DEPS)
xfc_DEPENDENCIES       = $(DEPS)
xff_DEPENDENCIES       = $(DEPS)
xfg_DEPENDENCIES       = $(DEPS)
xfmt_DEPENDENCIES      = $(DEPS)
xfs_DEPENDENCIES       = $(DEPS)
xlow_DEPENDENCIES      = $(DEPS)
xmj_DEPENDENCIES       = $(DEPS)
xpe_DEPENDENCIES       = $(DEPS)
xts_DEPENDENCIES       = $(DEPS)
xutf8_DEPENDENCIES     = $(DEPS)

xcv_CFLAGS =  -DUTF8SUPPH -DUTF8EBCD -DUTF8UCS2 $(INCLUDES2)

xbc_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xbc.map
xci_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xci.map
xcv_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xcv.map
xcvsjisc_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xcvsjisc.map
xdc_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xdc.map
xdd_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xdd.map
xdig_LDFLAGS = -L../ulib -Xlinker -Map -Xlinker xdig.map
xds_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xds.map
xfc_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xfc.map
xff_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xff.map
xfg_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xfg.map
xfmt_LDFLAGS = -L../ulib -Xlinker -Map -Xlinker xfmt.map
xfs_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xfs.map
xlow_LDFLAGS = -L../ulib -Xlinker -Map -Xlinker xlow.map
xmj_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xmj.map
xpe_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xpe.map
xts_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xts.map
xutf8_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xutf8.map

XSUBLDADD  = -luserxe $(PACKAGE_LIBS)  -ldl    #v767
xbc_LDADD  = $(XSUBLDADD)
xci_LDADD  = $(XSUBLDADD)
xcv_LDADD  =      $(XSUBLDADD)
xcvsjisc_LDADD  = $(XSUBLDADD)
xdc_LDADD  =      $(XSUBLDADD)
xdd_LDADD  =      $(XSUBLDADD)
xdig_LDADD =      $(XSUBLDADD)
xds_LDADD  =      $(XSUBLDADD)
xfc_LDADD  =      $(XSUBLDADD)
xff_LDADD  =      $(XSUBLDADD)
xfg_LDADD  =      $(XSUBLDADD)
xfmt_LDADD =      $(XSUBLDADD)
xfs_LDADD  =      $(XSUBLDADD)
xlow_LDADD =      $(XSUBLDADD)
xmj_LDADD  =      $(XSUBLDADD)
xpe_LDADD  =      $(XSUBLDADD)
xts_LDADD  =      $(XSUBLDADD)
xutf8_LDADD  =    $(XSUBLDADD)
