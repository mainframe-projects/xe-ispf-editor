## Process this file with automake to produce Makefile.in
##vam0:130911*for distro removed gnome-print,use GTKprint 
##v767:070606-autoconf:add header chk(ncurses.h,cups/cups.h)
##                     use PACKAGE_LIBS for -lgnomevfs-2 set by PKG_CHECKE_MODULES(set -L)

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

bin_PROGRAMS  = xprint $(CFLAGS_PRINT_GXP)
EXTRA_PROGRAMS  = gxp

INCLUDES2 = \
	$(PACKAGE_CFLAGS)\
	 -I../ulib -I../

xprint_CFLAGS=-DUTF8SUPP -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD $(INCLUDES2)
#gxeADDINC=-I/usr/include/libgnomeui-2.0 -I/usr/include/libgnomeprint-2.2 -I/usr/include/libgnome-2.0 -I/usr/include/gtk-2.0 -I/usr/include/libgnomecanvas-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/pango-1.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/libbonobo-2.0 -I/usr/include/libart-2.0 -I/usr/include/libbonoboui-2.0 -I/usr/include/gnome-vfs-2.0 -I/usr/include/cairo
#gxp_CFLAGS=-DUTF8SUPP -DGXP -DUTF8UCS2 -DUTF8EBCD
gxp_CFLAGS=-DUTF8SUPP -DUTF8SUPPH -DGXP -DUTF8UCS2 -DUTF8EBCD $(CFLAGS_PRINT) $(INCLUDES2)

xprint_SOURCES  = \
	xprint.c  \
	xp.h      \
	xp2p.c    \
	xp2p.h    \
	xpdesp.c  \
	xpdesp.h  \
	xpebc.c   \
	xpebc.h   \
	xpesc.c   \
	xpesc.h   \
	xphex.c   \
	xphex.h   \
	xphlp.c   \
	xpinp.c   \
	xpinp.h   \
	xpjob.h   \
	xpmult.c  \
	xppf.c    \
	xppf.h    \
	xpsub1.c  \
	xpsub1.h  \
	xputf.c   \
	xputf.h

gxp_SOURCES  = \
	$(xprint_SOURCES)  \
	xplnxp.c   \
	xplnxp.h

DEPS= ../ulib/libuserxe.a
xprint_DEPENDENCIES= $(DEPS)
gxp_DEPENDENCIES= $(DEPS)

xprint_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker xprint.map
gxp_LDFLAGS  = -L../ulib -Xlinker -Map -Xlinker gxp.map

#gxeADDLIB=-lgnomeprint-2-2 -lgnomeprintui-2-2 -lgnomeui-2
LDADD= \
	$(PACKAGE_LIBS) -ldl
xprint_LDADD = -luserxe $(LDADD)    #v767
gxp_LDADD = -luserxe $(LDADD) $(gxeADDLIB)
