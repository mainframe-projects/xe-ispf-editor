## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration
EXTRA_DIST = icuLinux icuLinux/include icuLinux/include/unicode

INCLUDES2 = \
	$(PACKAGE_CFLAGS)\
	 -I/usr/include/ncursesw\
	 -I./icuLinux/include\
	 -I../
#	  -I/usr/include/libgnomeprint-2.2

XXCFLAGS = $(INCLUDES2)

#noinst_LIBRARIES = libuserxe.a libuserxeD.a libuserxxe.a libuserxxeD.a
noinst_LIBRARIES = libuserxe.a libuserxxe.a

ulib_SOURCES = \
    os2.h       \
    u3270.c     \
    u3270.h     \
    u32702.c    \
    u32702.h    \
    u32703.c    \
    uabend.c    \
    uabend.h    \
    ualloc.h    \
    uallocl.c   \
    ucalc.c     \
    ucalc.h     \
    ucalc2.c    \
    ucalc2.h    \
    ucurses.h   \
    ucvebc.c    \
    ucvebc.h    \
    ucvebc2.c   \
    ucvebc2.h   \
    ucvebc3.c   \
    ucvebc32.c  \
    ucvebc4.c   \
    ucvebc4.h   \
    ucvebct.c   \
    ucvext.c    \
    ucvext12.c  \
    ucvext12.h  \
    ucvext.h    \
    ucvext2.c   \
    ucvext2.h   \
    ucvucs.c    \
    ucvucs.h    \
    ucvucst.c   \
    ucvucst.h   \
    udbcschk.c  \
    udbcschk.h  \
    udbcsck2.c  \
    udos.h      \
    udos2.c     \
    udos2.h     \
    udosl.c     \
    uedit.c     \
    uedit.h     \
    uedit2.c    \
    uedit2.h    \
    ueh.h       \
    uehl.c      \
    uehl.h      \
    uerr.c      \
    uerr.h      \
    ufemsg.c    \
    ufemsg.h    \
    ufile.c     \
    ufile.h     \
    ufile12.c   \
    ufile1f.c   \
    ufile1f.h   \
    ufile1l.c   \
    ufile1l.h   \
    ufile1l2.c  \
    ufile1l2.h  \
    ufile2.c    \
    ufile2.h    \
    ufile2f.c   \
    ufile2l.c   \
    ufile2l.h   \
    ufile2l2.c  \
    ufile2l2.h  \
    ufile3.c    \
    ufile3.h    \
    ufile3f.c   \
    ufile4.c    \
    ufile4.h    \
    ufile5.c    \
    ufile5.h    \
    ufilew.h    \
    uftp.c      \
    uftp.h      \
    uftp2.c     \
    uftp3.c     \
    uftp3.h     \
    ugcclib.c   \
    ugcclib.h   \
    uicu.h      \
    ukbd.h      \
    ukbdl.c     \
    ukbdl.h     \
    ukbdl2.h    \
    ukbdlnxc.c  \
    ukbdlnxc.h  \
    ukbdlnxm.c  \
    ukbdlnxm.h  \
    ukbdsym.h   \
    ukbdw.h     \
    ulib.h      \
    ulibarm.h   \
    ulibarm.c   \
    ulibdef.h   \
    ulibdefc.h  \
    ulibdefu.h  \
    ulibdefw.h  \
    ulibos2.h   \
    ulibunx.h   \
    umiscf.c    \
    umiscf.h    \
    uparse.c    \
    uparse.h    \
    upopup.h    \
    uproc.c     \
    uproc.h     \
    uproc2.c    \
    uproc2.h    \
    uproc22.c   \
    uproc3.c    \
    uproc4.c    \
    uproc4.h    \
    uque.c      \
    uque.h      \
    uregex.h    \
    ustrcpy.c   \
    ustrcpy.h   \
    ustring.c   \
    ustring.h   \
    utf.c       \
    utf.h       \
    utf2.c      \
    utf2.h      \
    utf22.c      \
    utf22.h      \
    utf3.c      \
    utf4.c      \
    utrace.c    \
    utrace.h    \
    utraceno.c  \
    uunxsub.c   \
    uunxsub.h   \
    uvio.h      \
    uvio2.h     \
    uviol.h     \
    uviom.c     \
    uviom.h     \
    uviow.h     \
    uwinsub.h
libuserxe_a_SOURCES      = $(ulib_SOURCES) uviol.c
libuserxxe_a_SOURCES     = $(ulib_SOURCES) uviolx.c
#libuserxeD_a_SOURCES     = $(libuserxe_a_SOURCES)
#libuserxxeD_a_SOURCES    = $(libuserxxe_a_SOURCES)

#user_LDFLAGS = \
#	 -L./ulib -L./ulib

#gxe_LDADD =  \                                           #
#	$(PACKAGE_LIBS)\                                      #
#	 -lcurses -lxxe -luserxxe -lgnomeprint-2-2 -lcups     #
libuserxe_a_CFLAGS      =  $(XXCFLAGS) -DUTF8SUPPH -DCURSESW -DUTF8UCS2 -DUTF8EBCD
libuserxeD_a_CFLAGS     =  $(libuserxe_a_CFLAGS) -g
libuserxxe_a_CFLAGS     =  $(XXCFLAGS) -DXXE -DGTK -pthread -DUTF8SUPPH -DUTF8UCS2 -DUTF8EBCD
libuserxxeD_a_CFLAGS    =  $(libuserxxe_a_CFLAGS) -g

