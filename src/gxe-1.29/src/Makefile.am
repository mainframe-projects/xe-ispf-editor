## Process this file with automake to produce Makefile.in
##vam0:130911*for distro removed gnome-print,use GTKprint 
##v767:070606-autoconf:add header chk(ncurses.h,cups/cups.h)
##                     use PACKAGE_LIBS for -lgnomevfs-2 set by PKG_CHECKE_MODULES(set -L)

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration
SUBDIRS = ulib xe xsub xp
EXTRA_DIST = TurnkeyMVS

INCLUDES2 = \
	$(PACKAGE_CFLAGS)\
	 -I./ulib -I./xe

#XXCFLAGS = -DXXE -DGTK -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD
XXCFLAGS = -DXXE -DGTK -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD $(CFLAGS_PRINT) $(INCLUDES2)

bin_PROGRAMS = $(CFLAGS_MAKE_GXE)
EXTRA_PROGRAMS  = gxe
#noinst_PROGRAMS = gxeDebug

gxe_SOURCES = \
	support.h\
	support.c\
	main.c\
	interface.h\
	interface.c\
	callbacks.h\
	callbacks.c\
	gxeview.c\
	gxeview.h\
	gxedlg.c\
	gxedlg.h\
	gxe.h\
	gxe.c\
	xxemain.c\
	xxemain.h\
	gxemfrm.c\
	gxemfrm.h\
	xxecsub.h\
	xxecsub.c\
	xxedef.h\
	xxexei.h\
	xxexei.c\
	xxekbd.c\
	xxeres.h\
	xxescr.c\
	xxexei3.c\
	xxexei3.h\
	xxemouse.c\
	xxexei2.c\
	xxecsub2.c\
	xxefile.c\
	xxefile.h\
	gxepage.c\
	gxepage.h\
	xxeprt.c
#gxeDebug_SOURCES = $(gxe_SOURCES)

DEPS=  ulib/libuserxxe.a xe/libxxe.a
DEPSD= ulib/libuserxxeD.a xe/libxxeD.a
gxe_DEPENDENCIES= $(DEPS)
#gxeDebug_DEPENDENCIES= $(DEPSD)

gxe_LDFLAGS  = \
	 -Xlinker -Map  -Xlinker gxe.map
#gxeDebug_LDFLAGS = \
-Xlinker -Map  -Xlinker gxeDebug.map

#   -lncursesw $(LD_NCURSES) -lcups -lX11 -ldl 
LDADD =  \
	$(PACKAGE_LIBS) \
	-lncursesw $(LD_NCURSES) -lcups -lX11 -ldl \
	-ldl -lncursesw $(LD_NCURSES) -lcups -lX11 \
	 -L./ulib -L./xe
#gxe_LDADD  = $(LDADD) -lxxe  -luserxxe
gxe_LDADD  = -lxxe -luserxxe $(LDADD)
#gxeDebug_LDADD = $(LDADD) -lxxeD -luserxxeD
gxe_CFLAGS  =  $(XXCFLAGS)
#gxeDebug_CFLAGS =  $(gxe_CFLAGS) -g

