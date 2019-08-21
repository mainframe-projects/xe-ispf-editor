## Process this file with automake to produce Makefile.in
##v767:070606-autoconf:add header chk(ncurses.h,cups/cups.h)
##                     use PACKAGE_LIBS for -lgnomevfs-2 set by PKG_CHECKE_MODULES(set -L)

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES2 = \
	$(PACKAGE_CFLAGS)\
	 -I/usr/include/ncursesw\
	 -I../ulib -I../

XXCFLAGS=-DHAVE_CONFIG_H $(INCLUDES2)

bin_PROGRAMS     = xe xe3270 xekbchk
noinst_PROGRAMS  = xeacb
#noinst_PROGRAMS  = xeDebug xe3270Debug
#noinst_LIBRARIES = libxxe.a libxxeD.a
noinst_LIBRARIES = libxxe.a

DEPS = ../ulib/libuserxe.a
DEPSD= ../ulib/libuserxeD.a
xe_DEPENDENCIES           = $(DEPS)
xe3270_DEPENDENCIES       = $(DEPS)
xekbchk_DEPENDENCIES      = $(DEPS)
xeacb_DEPENDENCIES        = $(DEPS)
#xeDebug_DEPENDENCIES      = $(DEPSD)
#xe3270Debug_DEPENDENCIES  = $(DEPSD)

xe3270_SOURCES = \
     xe3270.c        \
     xe3270.h        \
     xe3270e.c       \
     xe3270f.c       \
     xe3270f2.c      \
     xe3270s.c       \
     xe3270s.h       \
     xe3270s2.c

xeacb_SOURCES = \
     xeacb.c         \
     xeacbdmy.h         \
     xeacb.h        \
     xesub2.c

xekbchk_SOURCES = \
     xekbchk.c  \
     xecsr.c    \
     xeebc.c    \
     xeerr.c    \
     xefunc.c   \
     xefunct.c  \
     xefunct2.c \
     xegbl.c    \
     xekbd.c    \
     xescr.c    \
     xescr2.c   \
     xesub.c    \
     xesub2.c   \
     xeutf2.c  \
     xeutf.c

xe_SOURCES = \
     xe.c            \
     xe.h            \
     xe3270.h        \
     xe3270s.h       \
     xeacb.h         \
     xearm.h         \
     xecalc.c        \
     xecalc.h        \
     xecalc2.c       \
     xecalc2.h       \
     xecalc21.c      \
     xecalc21.h      \
     xecalc22.c      \
     xecalc3.c       \
     xecalc3.h       \
     xecap.c         \
     xecap.h         \
     xecap2.c        \
     xecap2.h        \
     xechar.c        \
     xechar.h        \
     xechar12.c      \
     xechar12.h      \
     xechar13.c      \
     xechar2.c       \
     xechar2.h       \
     xecsr.c         \
     xecsr.h         \
     xedcmd.c        \
     xedcmd.h        \
     xedcmd2.c       \
     xedcmd2.h       \
     xedcmd3.c       \
     xedcmd3.h       \
     xedcmd4.c       \
     xedcmd4.h       \
     xedir.c         \
     xedir.h         \
     xedir2.c        \
     xedir2.h        \
     xedir3.c        \
     xedir3.h        \
     xedir4.c        \
     xedir4.h        \
     xedlcmd.c       \
     xedlcmd.h       \
     xedlcmd2.c      \
     xedlcmd2.h      \
     xedlcmd3.c      \
     xedlcmd3.h      \
     xedlcmd4.c      \
     xedlcmd4.h      \
     xedlcmd5.c      \
     xedlcmd5.h      \
     xedlcmd6.c      \
     xedlcmd6.h      \
     xeebc.c         \
     xeebc.h         \
     xeerr.c         \
     xeerr.h         \
     xefcmd.c        \
     xefcmd.h        \
     xefcmd2.c       \
     xefcmd2.h       \
     xefcmd22.c      \
     xefcmd22.h      \
     xefcmd23.c      \
     xefcmd23.h      \
     xefcmd24.c      \
     xefcmd24.h      \
     xefcmd25.c      \
     xefcmd26.c      \
     xefcmd27.c      \
     xefcmd27.h      \
     xefcmd3.c       \
     xefcmd3.h       \
     xefcmd4.c       \
     xefcmd4.h       \
     xefcmd42.c      \
     xefcmd43.c      \
     xefcmd43.h      \
     xefcmd5.c       \
     xefcmd5.h       \
     xefcmd6.c       \
     xefcmd6.h       \
     xefcmd7.c       \
     xefcmd7.h       \
     xefile.c        \
     xefile.h        \
     xefile12.c      \
     xefile12.h      \
     xefile13.c      \
     xefile13.h      \
     xefile14.c      \
     xefile14.h      \
     xefile15.c      \
     xefile2.c       \
     xefile2.h       \
     xefile22.c      \
     xefile22.h      \
     xefile23.c      \
     xefile3.c       \
     xefile3.h       \
     xefile4.c       \
     xefile4.h       \
     xefile42.c      \
     xefile42.h      \
     xefile43.c      \
     xefile43.h      \
     xefile5.c       \
     xefile5.h       \
     xefile6.c       \
     xefile6.h       \
     xefile7.c       \
     xefile7.h       \
     xefsub.c        \
     xefsub.h        \
     xefsubw.h       \
     xeftp.c         \
     xeftp.h         \
     xefunc.c        \
     xefunc.h        \
     xefunc2.c       \
     xefunc2.h       \
     xefunct.c       \
     xefunct.h       \
     xefunct2.c      \
     xegbl.c         \
     xegbl.h         \
     xeini.c         \
     xeini.h         \
     xeini2.c        \
     xeini2.h        \
     xeini3.c        \
     xeini3.h        \
     xekbchkl.h      \
     xekbd.c         \
     xekbd.h         \
     xelcmd.c        \
     xelcmd.h        \
     xelcmd2.c       \
     xelcmd2.h       \
     xelcmd3.c       \
     xelcmd3.h       \
     xelcmd4.c       \
     xelcmd4.h       \
     xelcmd5.c       \
     xelcmd5.h       \
     xemainl.c       \
     xemousel.c      \
     xemousel.h      \
     xeopt.c         \
     xeopt.h         \
     xeopt2.c        \
     xepan.c         \
     xepan.h         \
     xepan2.c        \
     xepan2.h        \
     xepan22.c       \
     xepan22.h       \
     xepan23.c       \
     xepan24.c       \
     xepan3.c        \
     xepan3.h        \
     xescr.c         \
     xescr.h         \
     xescr2.c        \
     xescr2.h        \
     xesub.c         \
     xesub.h         \
     xesub2.c         \
     xesub2.h         \
     xesyn.c         \
     xesyn.h         \
     xesyn2.c        \
     xesyn2.h        \
     xesyscmd.h      \
     xetso.c         \
     xetso.h         \
     xetso2.c        \
     xeundo.c        \
     xeundo.h        \
     xeutf.c         \
     xeutf.h         \
     xeutf2.c         \
     xeutf2.h 

#xe3270Debug_SOURCES = $(xe3270_SOURCES)
#xeDebug_SOURCES = $(xe_SOURCES)
libxxe_a_SOURCES = $(xe_SOURCES)
#libxxeD_a_SOURCES = $(xe_SOURCES)

libxxe_a_CFLAGS         =  $(XXCFLAGS) -DXXE -DGTK -pthread  -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD
libxxeD_a_CFLAGS        =  $(libxxe_a_CFLAGS) -g
xe_CFLAGS        =  $(XXCFLAGS) -DCURSESW -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD
xeDebug_CFLAGS   =  $(xe_CFLAGS) -g

xe3270_CFLAGS      =  $(XXCFLAGS) -pthread -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD
xe3270Debug_CFLAGS =  $(xe3270_CFLAGS) -g
xekbchk_CFLAGS     =  $(XXCFLAGS) -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD
xeacb_CFLAGS       =  $(XXCFLAGS) -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD

xeacb_LDFLAGS = \
	 -L../ulib\
	 -Xlinker -Map\
	 -Xlinker xeacb.map
xe3270_LDFLAGS = \
	 -L../ulib\
	 -Xlinker -Map\
	 -Xlinker xe3270.map
#xe3270Debug_LDFLAGS = \
	 -L../ulib\
	 -Xlinker -Map\
	 -Xlinker xe3270D.map
xe_LDFLAGS = \
	 -L../ulib\
	 -Xlinker -Map\
	 -Xlinker xe.map
#xeDebug_LDFLAGS = \
	 -L../ulib \
	 -Xlinker -Map\
	 -Xlinker xeDebug.map
xekbchk_LDFLAGS = \
	 -L../ulib\
	 -Xlinker -Map\
	 -Xlinker xekbchk.map

#	-lncursesw  -ldl     #v767
LDADD= \
	$(PACKAGE_LIBS)    \
	-ldl -lncursesw   #v767
xe_LDADD = \
	-luserxe $(LDADD)    #v767
#xeDebug_LDADD = \
	 -luserxeD $(LDADD)  #v767
xe3270_LDADD = $(xe_LDADD)
#xe3270Debug_LDADD = $(xeDebug_LDADD)
xekbchk_LDADD = $(xe_LDADD)
xeacb_LDADD = $(xe_LDADD)
