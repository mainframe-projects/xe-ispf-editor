##*CID: #+vbh0R~:                                   update#=  164; #~vbh0R~
##vbh0:180123 (Linux Bug)configure dis not chk ncursesw/ncurses.h #~vbh0I~
##vb99:170328 ubuntu undefined ref to libiconb #~vb99I~
##vb32:160424 try to del AM_PROG_LIBTOOL #~vb32R~
##            add AC_PROG_RANLIB #~vb32R~
##var9:140212 pkg-config may not be installed;chk by AC_CHECK_FILE #~var9I~
##var8 20140126 use gtk3 if no gtk2 installed #~var8I~
##              warning missing template for PACKAGE_DATA_DIR when AC_DIFINE is missing #~var8I~
##              no tinfo but required for suse12.3 #~var8I~
##              consider adding AC_CONFIG_MACRO_DIR #~var8I~
##vaq2:131228 (gtk3)option to skip gxe #~vaq2I~
##vap1:131220 (LNX)configure aupports NOPRINT for RedHat5.8 #~vap1I~
##vam0:130911*for distro removed gnome-print,use GTKprint #~vaiEI~
##vaiE:130706 use lutimes to set timestamp to slink #~vaiER~
##v770:100701-(LNX)LP64 support #~v770R~
##v7az:090501-(LNX)autgen pkg chk "term.h" installed
##v5mh:080308 regex support(confirm regex.h installed)
##v767:070606-autoconf:add header chk(ncurses.h,cups/cups.h)
##                     add lib chk(gnome-vfs) and use PACKAGE_LIB set by PKG_CHECKE_MODULES(set -L)
dnl Process this file with autoconf to produce a configure script.

dnl AC_PREREQ(2.59)
#AC_INIT(configure.in) #~var8R~
AC_INIT(gxe,1.29) #~var9R~ #~vb99R~
#AM_INIT_AUTOMAKE(gxe, 1.27) #~v770R~ #~var8R~
AM_INIT_AUTOMAKE #~var8I~
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4]) #~vaiEI~
AM_MAINTAINER_MODE
AC_ISC_POSIX
dnl ## avoid -g -O2 as default (dquote required)
#CFLAGS="-Wimplicit -Wformat=0 -Wreturn-type -Wunused -funsigned-char -O0 -D_FILE_OFFSET_BITS=64 -DLNX -DUNX -DLNXLC2 -DLNXLC2TL6 -DNOTRACE -DDUMMYPRINTF" #~v770R~
CFLAG_TRACE="-DNOTRACE -DDUMMYPRINTF" #~v770R~
GTK_VERSION_REQ=2.8.20 #~vap1R~
gtk_req="gtk+-2.0 >= $GTK_VERSION_REQ" #~vaiEI~
gtk_pkgs="${gtk_req}" #~vaiEI~
deps_pkgs="$gtk_pkgs" #~vaiEI~
GTK_VERSION_REQ2=2.10.0 #~var8R~
gtk_req2="gtk+-2.0 >= $GTK_VERSION_REQ2" #~vap1I~
gtk_pkgs2="${gtk_req2}" #~vap1I~
deps_pkgs2="$gtk_pkgs2" #~vap1I~
VFS_VERSION_REQ=2.14.2 # from fc5 ~vaq2I~ #~vaq2R~
#vfs_req="gnome-vfs-module-2.0 >= $VFS_VERSION_REQ" #~vaq2R~ #~var9R~
#vfs_pkgs="${vfs_req}" #~vaq2I~ #~var9R~
deps_pkgs3="$vfs_pkgs" #~vaq2I~
deps_pkgs0=$gtk_pkgs2 #~vap1I~
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
dnl AC_PROG_RANLIB #~vaiER~
AC_PROG_RANLIB #~vb32R~

AM_PROG_CC_STDC
AM_PROG_CC_C_O

AC_HEADER_STDC
#AC_CHECK_HEADERS([fcntl.h stddef.h stdlib.h string.h sys/timeb.h sys/vfs.h unistd.h]) #v767
AC_CHECK_HEADERS([fcntl.h stddef.h stdlib.h string.h sys/timeb.h sys/vfs.h unistd.h]) #v767
#AC_CHECK_HEADERS([ncurses.h cups/cups.h regex.h libgnomevfs/gnome-vfs-init.h libgnomevfs/gnome-vfs-mime.h gnome.h libgnomeprint/gnome-print.h]) #v767
#AC_CHECK_HEADERS([ncursesw/ncurses.h cups/cups.h regex.h libgnomevfs/gnome-vfs-init.h libgnomevfs/gnome-vfs-mime.h gnome.h libgnomeprint/gnome-print.h]) #v767
#AC_CHECK_HEADERS([term.h ncursesw/ncurses.h cups/cups.h regex.h libgnomevfs/gnome-vfs-init.h libgnomevfs/gnome-vfs-mime.h gnome.h libgnomeprint/gnome-print.h]) #~v770R~
#AC_CHECK_HEADERS([term.h ncursesw/ncurses.h cups/cups.h regex.h]) #~v770R~ #~vaiER~
#AC_CHECK_HEADERS([term.h ncursesw/ncurses.h cups/cups.h regex.h]) #~vaiER~ #~vb99R~
AC_CHECK_HEADERS([term.h ncursesw/ncurses.h cups/cups.h regex.h iconv.h]) #~vb99R
if test "$ac_cv_header_term_h" = "no"; then
  AC_MSG_ERROR("FATAL:term.h not found. Install ncurses-devel and also ncursesw.");
fi
#if test "$ac_cv_header_ncurses_h" = "no"; then #~vbh0R~
if test "$ac_cv_header_ncursesw_ncurses_h" = "no"; then #~vbh0I~
# AC_MSG_ERROR("FATAL:ncurses.h not found. Install ncursesw-devel."); #~vbh0R~
  AC_MSG_ERROR("FATAL:ncursesw/ncurses.h not found. Install ncursesw-devel."); #~vbh0I~
fi
if test "$ac_cv_header_cups_cups_h" = "no"; then
  AC_MSG_ERROR("FATAL:cups/cups.h not found. Install cups-devel.");
fi
# Checks for libraries.
# FIXME: Replace `main' with a function in `-lcups':
AC_CHECK_LIB([cups], [cupsGetDests])
AC_CHECK_LIB([ncursesw], [initscr])
#AC_CHECK_LIB([iconv], [iconv_open])            # #~vb99R~
# FIXME: Replace `main' with a function in `-luserxe':
#AC_CHECK_LIB([userxe], [main]) #~vb99R~
# FIXME: Replace `main' with a function in `-luserxxe':
#AC_CHECK_LIB([userxxe], [main]) #~vb99R~
# FIXME: Replace `main' with a function in `-luserxxeD':
#AC_CHECK_LIB([userxxeD], [main]) #~vb99R~
# FIXME: Replace `main' with a function in `-lxxe':
#AC_CHECK_LIB([xxe], [main]) #~vb99R~
# FIXME: Replace `main' with a function in `-lxxeD':
#AC_CHECK_LIB([xxeD], [main]) #~vb99R~

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
#AC_CHECK_FUNCS([ftime getpagesize memset putenv strchr strspn strstr strtol]) #~vaiER~
AC_CHECK_FUNCS([lutimes ftime getpagesize memset putenv strchr strspn strstr strtol]) #~vaiER~

GETTEXT_PACKAGE=gxe
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Package name for gettext])

#2010/07/29 for suse64  start   @@@@ #~v770R~
am_isrc=
AC_SUBST(am_isrc)

AC_CACHE_VAL(ac_cv_cache_val_print_unix,[ac_cv_cache_print_unix=gtk+-unix-print-2.0]) #~vap1R~
AC_CACHE_VAL(ac_cv_cache_val_libgnome,[ac_cv_cache_libgnome=libgnomeui-2.0]) #~var9R~
AC_CACHE_VAL(ac_cv_cache_val_gtkversion,[ac_cv_cache_gtkversion=gtk+-2.0]) #~vaq2I~
AC_CACHE_VAL(ac_cv_cache_val_gtkprinter,[ac_cv_cache_gtkprinter=gtk/gtkprinter.h]) #~vaq2I~
#PRINTINC=-I/usr/include/gtk+-unix-print-2.0 #~vap1R~
CFLAGS_PRINT="-DGTKPRINT" #~vap1I~
CFLAGS_PRINT_GXP=gxp #~vap1I~
CFLAGS_MAKE_GXE=gxe #~vaq2I~

AC_ARG_ENABLE(print,
[  --enable-print  !!! print support under gtk-2:no|gtk [[default=gtk]]], #~vap1R~ #~var8R~
[ if test "x$enableval" == "xno" ; then #~vap1I~
	echo "!!!! NOPRINT !!!!" #~var8I~
    CFLAGS_PRINT="-DNOPRINT" #~vap1I~
    CFLAGS_PRINT_GXP= #~vap1I~
#	PRINTINC= #~vap1I~
#	PRINTUNIX= #~vap1R~
	AC_CACHE_VAL(ac_cv_cache_val_print_unix,[ac_cv_cache_print_unix=])
#   AC_CACHE_VAL(ac_cv_cache_val_gtkprinter,[ac_cv_cache_gtkprinter=gnome.h]) #~vaq2R~ #~var9R~
    AC_CACHE_VAL(ac_cv_cache_val_gtkprinter,[ac_cv_cache_gtkprinter=]) #~var9I~
	deps_pkgs0=$gtk_pkgs #~vap1I~
  fi #~vap1I~
  if test "x$enableval" == "xgtk" ; then
	CFLAGS_PRINT="-DGTKPRINT"
  fi #~vap1I~
]) #~v@@1I~ #~vap1I~

No_gxe=N #~var8I~
AC_ARG_ENABLE(gxe,
[  --enable-gxe    !!! makes gxe :no|yes [[default=yes. if no, makes xe only.]]], #~vaq2I~ #~var8R~
[ if test "x$enableval" == "xno" ; then #~vaq2I~
	echo "!!!! NOGXE !!!!" #~var8R~
    No_gxe=Y #~var8I~
    CFLAGS_PRINT="-DNOPRINT -DNOGXE" #~vaq2I~
    CFLAGS_PRINT_GXP= #~vaq2I~
    CFLAGS_MAKE_GXE= #~vaq2I~
	AC_CACHE_VAL(ac_cv_cache_val_print_unix,[ac_cv_cache_print_unix=]) #~vaq2I~
	AC_CACHE_VAL(ac_cv_cache_val_gtkversion,[ac_cv_cache_gtkversion=]) #~vaq2I~
	AC_CACHE_VAL(ac_cv_cache_val_libgnome,[ac_cv_cache_libgnome=]) #~vaq2I~
#   AC_CACHE_VAL(ac_cv_cache_val_gtkprinter,[ac_cv_cache_gtkprinter=gnome.h]) #~vaq2I~ #~var9R~
    AC_CACHE_VAL(ac_cv_cache_val_gtkprinter,[ac_cv_cache_gtkprinter=]) #~var9I~
	deps_pkgs0=$deps_pkgs3 #~vaq2R~
  fi #~vaq2I~
]) #~vaq2I~

#***************************** #~var8M~
#*gtk3 #~var8M~
#***************************** #~var8M~
#if test "x$No_gxe" != "xY";then #gxe=no #~var9R~
#    AC_CHECK_HEADERS([gtk/gtk.h]) #!!! requires glib.h etc #~var9R~
#    if test "$ac_cv_header_gtk_gtk_h" = "no"; then #~var9R~
#        AC_MSG_ERROR("FATAL:gtk/gtk.h not found. Install gtk2-devel or gtk3-devel."); #~var9R~
#    fi #~var9R~
#fi #~var9R~
#GTK_VERSION_REQ3=3.6.4 #suse12.3:3.6.4 fc19:3.8.0 debian jessie:3.8.6 #~var9R~
#GTK_VERSION_REQ3=3.0.0 #suse12.3:3.6.4 fc19:3.8.0 debian jessie:3.8.6,Kubuntu12.4 3.6.4 #~var9R~
GTK_VERSION_REQ3=3.4.0 #suse12.3:3.6.4 fc19:3.8.0 debian jessie:3.8.6,Kubuntu12.4 3.6.4 s390x 3.2.1 #~var9R~
gtk_req3="gtk+-3.0 >= $GTK_VERSION_REQ3" #~var8M~
PKG_CHECK_MODULES(CHK_INSTALL_GTK3,[gtk+-3.0],gtk3_use=yes,gtk3_use=no) #~var8M~
if test "x$PKG_CONFIG" = x; then #$PKG_CONFIG is set after first PKG_CHECK_MODULES #~var9M~
    AC_MSG_ERROR([!!! pkg-config was not found, install it or set PATH environment to it !!!]) #~var9M~
fi #~var9M~
PKG_CHECK_MODULES(CHK_INSTALL_GTK2,[gtk+-2.0],gtk2_installed=yes,gtk2_installed=no) #~var8M~ #~var9R~
if test "x$No_gxe" != "xY";then #gxe=no #+vbh0I~
if test "x$gtk2_installed" == "xno" ; then #~vbh0R~
	if test "x$gtk3_use" == "xno" ; then #~vbh0R~
    	AC_MSG_ERROR([install GTK2(>=$GTK_VERSION_REQ2) or GTK3(>=$GTK_VERSION_REQ3) if enable-gxe=no.]) #+vbh0R~
	fi #~vbh0I~
fi #~vbh0I~
fi #+vbh0I~
AC_CHECK_LIB([tinfo],[curses_version],tinfo_installed=yes,tinfo_installed=no) #~var8M~
AC_ARG_ENABLE(gtk3, 
[  --enable-gtk3   !!! makes on gtk3 :yes|no [[default=yes if gtk3 is installed]]], #~var8R~
[ #~var8M~
#	echo "!!!! $gtk3_use,$gtk2_installed !!!" #~var8M~
  	if test "x$enableval" == "xyes" ; then #~var8M~
	  	if test "x$gtk3_use" == "xno" ; then #~var8M~
        	AC_MSG_ERROR([--enable-gtk3 specified 'yes', but gtk+-3.0 is not installed.]) #~var8M~
        fi #~var8M~
    else #~var8M~
  		if test "x$enableval" == "xno" ; then #~var8M~
	  		if test "x$gtk2_installed" == "xno" ; then #~var8M~
        		AC_MSG_ERROR([--enable-gtk3 specified 'no', but gtk+-2.0 is not installed.]) #~var8M~
        	fi #~var8M~
        else #~var8M~
        	AC_MSG_ERROR([--enable-gtk3 was invalid("$enableval"), specify yes or no.]) #~var8M~
  		fi #~var8M~
        gtk3_use=no #~var8M~
    fi #~var8M~
]) #~var8M~
if test "x$tinfo_installed" == "xyes"; then #~var8M~
	echo "!!!! TINFO installed !!!!" #~var8M~
	LD_NCURSES=-ltinfo #~var8M~
else #~var8M~
	echo "???? no TINFO installed ????"
	LD_NCURSES= #~var8M~
fi #~var8M~
if test "x$gtk3_use" == "xyes"; then #~var8M~
	if test "x$No_gxe" != "xY";then	#gxe=no #~var8I~
		echo "!!!! GTK-3 !!!!($gtk_req3)" #~var8R~
		AC_CACHE_VAL(ac_cv_cache_val_print_unix,[ac_cv_cache_print_unix=gtk+-unix-print-3.0]) #~var9I~
		AC_CACHE_VAL(ac_cv_cache_val_gtkprinter,[ac_cv_cache_gtkprinter=]) #~var9R~
	    PKG_CHECK_MODULES(CHK_EXIST_GTK3_LIBGNOME2, [libgnome-2.0],,[AC_MSG_ERROR([!!! libgnome-2.0 installation required])]) #~var9I~
	    PKG_CHECK_MODULES(CHK_EXIST_GTK3_GNOMEVFS2E, [gnome-vfs-2.0],,[AC_MSG_ERROR([!!! gnome-vfs-2.0 installation required])]) #~var9I~
		PKG_CHECK_MODULES(CHK_VERSION_GTK3,$gtk_req3,,[AC_MSG_ERROR([!!! gtk+-3.0 version requirement unmatch(>=$GTK_VERSION_REQ3. use option of "--enable-gtk3=no")])]) #~var9R~
 		PKG_CHECK_MODULES(PACKAGE,[gtk+-3.0 ${ac_cv_cache_print_unix} libgnome-2.0 gnome-vfs-2.0]) #~var8R~ #~var9R~
    	CFLAGS_PRINT="$CFLAGS_PRINT -DOPTGTK3" #~var8R~
    else #~var8I~
		PKG_CHECK_MODULES(PACKAGE,[libgnome-2.0 gnome-vfs-2.0]) #~var8I~
    fi #~var8I~
else #~var8M~
	if test "x$No_gxe" != "xY";then	#gxe=no #~var8I~
		echo "!!!! GTK-2 !!!!($deps_pkgs0)" #~var8M~
    fi #~var8M~
#   PKG_CHECK_MODULES(CHK_VERSION_GTK2,$gtk_req2,,[AC_MSG_ERROR([!!! gtk+-2.0 version requirement unmatch(>=$GTK_VERSION_REQ2)])]) #~var8M~
	PKG_CHECK_MODULES(CHK_VERSION_GTK2, [$deps_pkgs0],,
   [$as_echo "!!! gtk version check failed. ??? 
    Check gtk2-devel or gtk3-devel is installed. 
    Try \"./configure --enable-print=no\" if gtk version is old.
    OR --enable-gxe=no if you do not want to install gxe and use xe(no Gtk dependency) only."]) 
	if test "x${ac_cv_cache_print_unix}" != "x";then #~var8M~
		PKG_CHECK_MODULES(CHK_VERSION_UNIX_PRINT,${ac_cv_cache_print_unix},,[AC_MSG_ERROR([!!! print function requires gtk+-2.0>=2.10.  Try --enable-print=no)])]) #~var8M~
    fi #~var8M~
    PKG_CHECK_MODULES(CHK_EXIST_GTK2_PRINT, [${ac_cv_cache_gtkversion} ${ac_cv_cache_print_unix}]) #~var8I~
    PKG_CHECK_MODULES(CHK_EXIST_GTK2_LIBGNOME, [${ac_cv_cache_libgnome}]) #~var8I~
    PKG_CHECK_MODULES(CHK_EXIST_GTK2_GNOMEVFSMOD2, [gnome-vfs-module-2.0]) #~var8I~ #~var9R~
    PKG_CHECK_MODULES(CHK_EXIST_GTK2_GNOMEVFS2, [gnome-vfs-2.0]) #~var9I~
    PKG_CHECK_MODULES(PACKAGE, [${ac_cv_cache_libgnome} gnome-vfs-2.0 gnome-vfs-module-2.0 ${ac_cv_cache_gtkversion} ${ac_cv_cache_print_unix}]) #~var9R~
fi #~var8M~
AC_SUBST(LD_NCURSES) #~var8M~
#***end of gtk3 ************************** #~var8M~
AC_ARG_ENABLE(debug,
[  --enable-debug          build debug version for gdb [[default=no]]],
[ if test "x$enableval" == "xyes" ; then
    CFLAG_DEBUG="-g"
    LDFLAGS=" -g $LDFLAGS"
  fi
])
AC_ARG_ENABLE(trace,
[  --enable-trace          build allowing trace function [[default=no]]],
[ if test "x$enableval" == "xyes" ; then
    CFLAG_TRACE="-DTRACE -DNODUMMYPRINTF"
  fi
])
AC_ARG_ENABLE(unused-but-set,
[  --enable-unused-but-set   build with -Wunused-but-set-variable option(new from gcc4.6) [[default=no]]],
[ if test "x$enableval" == "xyes" ; then
    CFLAG_UNUSEDBUT="-Wunused-but-set-variable"
  fi
])
AC_ARG_ENABLE(pointer-sign,
[  --enable-pointer-sign   build with -Wpointer-sign option(new from gcc4.X) [[default=no]]],
[ if test "x$enableval" == "xyes" ; then
    CFLAG_POINTERSIGN="-Wpointer-sign"
  fi
])
if test $CC = gcc; then #~v770I~
	ac_gcc_version=`echo __GNUC__ | $CC -E - | grep -v ^\#` #~v770I~
    echo "GCC_VERSION=$ac_gcc_version" #~v770I~
	if test "$ac_gcc_version" -ge 4; then #~v770I~
		ac_gcc_minor_version=`echo __GNUC_MINOR__ | $CC -E - | grep -v ^\#` #~v770I~
	    echo "GCC_MINVERSION=$ac_gcc_minor version" #~v770I~
		if test "$ac_gcc_minor_version" -ge 6; then #~v770I~
        	if test "x$CFLAG_UNUSEDBUT" == "x" ; then #~v770I~
		    	CFLAG_UNUSEDBUT="-Wno-unused-but-set-variable" #~v770I~
        	fi #~v770I~
        fi #~v770I~
    fi #~v770I~
fi #~v770I~
if test $CC = gcc; then #~v770I~
	ac_gcc_version=`echo __GNUC__ | $CC -E - | grep -v ^\#` #~v770I~
    echo "GCC_VERSION=$ac_gcc_version" #~v770I~
	if test "$ac_gcc_version" -ge 4; then #~v770I~
        	if test "x$CFLAG_POINTERSIGN" == "x" ; then #~v770I~
		    	CFLAG_POINTERSIGN="-Wno-pointer-sign" #~v770I~
        	fi #~v770I~
    fi #~v770I~
fi #~v770I~
#2010/07/29 for suse64  end     @@@@ #~v770R~
#CFLAGS="$CFLAG_TRACE $CFLAG_UNUSEDBUT $CFLAG_POINTERSIGN $CFLAG_DEBUG -Wimplicit -Wformat=0 -Wreturn-type -Wunused -funsigned-char -Wuninitialized -O0 -D_FILE_OFFSET_BITS=64 -DLNX -DUNX -DLNXLC2 -DLNXLC2TL6" #~v770R~
CFLAGS="$CFLAG_TRACE $CFLAG_UNUSEDBUT $CFLAG_POINTERSIGN $CFLAG_DEBUG -Wimplicit -Wformat=0 -Wreturn-type -Wunused -funsigned-char -O0 -D_FILE_OFFSET_BITS=64 -DLNX -DUNX -DLNXLC2 -DLNXLC2TL6" #~v770I~

dnl Languages which your application supports
ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

#AC_PROG_LIBTOOL #~var9R~ #~vb32R~

#AC_SUBST(PRINTINC) #~vap1I~
#AC_SUBST(PRINTUNIX) #~vap1R~
AC_SUBST(CFLAGS_PRINT) #~vap1I~
AC_SUBST(CFLAGS_PRINT_GXP) #~vap1I~
AC_SUBST(CFLAGS_MAKE_GXE) #~vaq2I~

#PKG_CHECK_MODULES(DEPS, [$deps_pkgs0],,[$as_echo "!!! Try \"./configure --enable-print=no\" if gtk version check failed. ???"]) #~vap1R~ #~vaq2R~
#PKG_CHECK_MODULES(DEPS, [$deps_pkgs0],,[$as_echo "!!! Try \"./configure --enable-print=no\" if gtk version check failed. ??? #~var8R~
#OR --enable-gxe=no if you do not want install gxe and use xe(no Gtk dependency) only."]) #~vaq2R~ #~var8R~

#PKG_CHECK_MODULES(PACKAGE, [libgnomeui-2.0 gtk+-2.0 libgnomeprint-2.2 gnome-vfs-module-2.0])
#PKG_CHECK_MODULES(PACKAGE, [libgnomeui-2.0 gnome-vfs-module-2.0 libgnomeprint-2.2 ncurses-5.5-19 cups-1.1-30.2])
#PKG_CHECK_MODULES(PACKAGE, [libgnomeui-2.0 gnome-vfs-module-2.0 libgnomeprint-2.2])
#PKG_CHECK_MODULES(PACKAGE, [libgnomeui-2.0 gnome-vfs-module-2.0 libgnomeprint-2.2 libgnomeprintui-2.2]) #~vaiER~
#PKG_CHECK_MODULES(PACKAGE, [libgnomeui-2.0 gnome-vfs-module-2.0 gtk+-2.0 gtk+-unix-print-2.0]) #~vaiEI~ #~vap1R~
#PKG_CHECK_MODULES(PACKAGE, [libgnomeui-2.0 gnome-vfs-module-2.0 gtk+-2.0 ${ac_cv_cache_print_unix}]) #~vap1R~ #~vaq2R~
#PKG_CHECK_MODULES(PACKAGE, [${ac_cv_cache_libgnome} gnome-vfs-module-2.0 ${ac_cv_cache_gtkversion} ${ac_cv_cache_print_unix}]) #~vaq2R~ #~var8R~
AC_SUBST(PACKAGE_CFLAGS)
AC_SUBST(PACKAGE_LIBS)


###  @@@@ #~v770R~
CPPFLAGS_SV=$CPPFLAGS
CPPFLAGS="$PACKAGE_CFLAGS"
AC_CHECK_HEADERS([libgnomevfs/gnome-vfs-init.h])
AC_CHECK_HEADERS(libgnomevfs/gnome-vfs-mime.h)
#if test "x$gtk3_use" != "xyes"; then #~var9R~
#	AC_CHECK_HEADERS(gnome.h) #~var9R~
#AC_CHECK_HEADERS(libgnomeprint/gnome-print.h) #~vaiER~
#AC_CHECK_HEADERS(gtk/gtkprinter.h) #~vaiER~ #~vaq2R~
#else #~var9R~
if test "x$gtk3_use" == "xyes"; then #~var9I~
	AC_CHECK_HEADERS(gtk/gtk.h) #~var9I~
fi #~var9I~
AC_CHECK_HEADERS(${ac_cv_cache_val_gtkprinter}) #~vaq2I~
CPPFLAGS=$CPPFLAGS_SV
### #~v770R~
#if test $ac_cv_header_libgnomevfs_gnome-vfs-init_h = no; then #~v770R~
#  AC_MSG_ERROR("FATAL:libgnomevfs/libgnome-vfs-init.h not found. Install gnome-vfs-2.0-devel."); #~v770R~
#fi #~v770R~
#if test $ac_cv_header_libgnomevfs_gnome-vfs-mime_h = no; then #~v770R~
#  AC_MSG_ERROR("FATAL:libgnomevfs/libgnome-vfs-mime.h not found. Install gnome-vfs-module-2.0-devel."); #~v770R~
#fi #~v770R~
#if test $ac_cv_header_gnome_h = no; then    #path contains version /libgnomeui-2.0/gnome.h #~v770R~
#  AC_MSG_ERROR("FATAL:gnome.h not found. Install libgnomeui."); #~v770R~
#fi #~v770R~
#if test $ac_cv_header_libgnomeprint_gnome-print_h = no; then #~v770R~
#  AC_MSG_ERROR("FATAL:libgnomeprint/gnome-print.h not found. Install libgnomeprint-devel."); #~v770R~
#fi #~v770R~
#  if test "X${ac_cv_cache_print_unix+set}" != Xset; then #~vap1I~ #~var9R~
#if test "$ac_cv_header_gtk_gtkprinter_h" = "no"; then #~vaiEM~ #~var9R~
#  AC_MSG_ERROR(FATAL:gtk/gtkprinter.h not found.\nInstall gtk2-devel(fedora(chk by \"rpm -qf\"))/libgtk2.0(debian(chk by \"apt-file find\")).); #~vaiER~ #~var9R~
#fi #~vaiEM~ #~var9R~
#  fi #~vap1I~ #~var9R~
##  @@@@ #~v770R~

#dnl Checks for header files.
#/g/src/ulib/ulib.h


dnl Set PACKAGE_LOCALE_DIR in config.h.
if test "x${prefix}" = "xNONE"; then
  AC_DEFINE_UNQUOTED(PACKAGE_LOCALE_DIR, "${ac_default_prefix}/${DATADIRNAME}/locale", [Package local directory])
else
  AC_DEFINE_UNQUOTED(PACKAGE_LOCALE_DIR, "${prefix}/${DATADIRNAME}/locale", [Package local directory])
fi

dnl Set PACKAGE SOURCE DIR in config.h.
packagesrcdir=`cd $srcdir && pwd`

dnl Set PACKAGE PREFIX
if test "x${prefix}" = "xNONE"; then
  packageprefix=${ac_default_prefix}
else
  packageprefix=${prefix}
fi

dnl Set PACKAGE DATA & DOC DIR
packagedatadir=share
packagedocdir=doc/${PACKAGE}

dnl Set PACKAGE DIRs in config.h.
packagepixmapsdir=share/pixmaps/${PACKAGE}
packagehelpdir=share/gnome/help/${PACKAGE}
packagemenudir=share/gnome/apps

dnl Subst PACKAGE_DATA_DIR.
NO_PREFIX_PACKAGE_DATA_DIR="${packagedatadir}"
AC_SUBST(NO_PREFIX_PACKAGE_DATA_DIR)
PACKAGE_DATA_DIR="${packageprefix}/${packagedatadir}"
AC_SUBST(PACKAGE_DATA_DIR)

dnl Subst PACKAGE_DOC_DIR.
NO_PREFIX_PACKAGE_DOC_DIR="${packagedocdir}"
AC_SUBST(NO_PREFIX_PACKAGE_DOC_DIR)
PACKAGE_DOC_DIR="${packageprefix}/${packagedocdir}"
AC_SUBST(PACKAGE_DOC_DIR)

dnl Subst PACKAGE_PIXMAPS_DIR.
NO_PREFIX_PACKAGE_PIXMAPS_DIR="${packagepixmapsdir}"
AC_SUBST(NO_PREFIX_PACKAGE_PIXMAPS_DIR)
PACKAGE_PIXMAPS_DIR="${packageprefix}/${packagepixmapsdir}"
AC_SUBST(PACKAGE_PIXMAPS_DIR)

dnl Subst PACKAGE_HELP_DIR.
NO_PREFIX_PACKAGE_HELP_DIR="${packagehelpdir}"
AC_SUBST(NO_PREFIX_PACKAGE_HELP_DIR)
PACKAGE_HELP_DIR="${packageprefix}/${packagehelpdir}"
AC_SUBST(PACKAGE_HELP_DIR)

dnl Subst PACKAGE_MENU_DIR.
NO_PREFIX_PACKAGE_MENU_DIR="${packagemenudir}"
AC_SUBST(NO_PREFIX_PACKAGE_MENU_DIR)
PACKAGE_MENU_DIR="${packageprefix}/${packagemenudir}"
AC_SUBST(PACKAGE_MENU_DIR)

AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${packageprefix}/${packagedatadir}")
#for autoheader 2.57 err "missing template"
AH_TEMPLATE([PACKAGE_DATA_DIR],["${packageprefix}/${packagedatadir}"])

AC_DEFINE_UNQUOTED(PACKAGE_DOC_DIR, "${packageprefix}/${packagedocdir}")
AH_TEMPLATE([PACKAGE_DOC_DIR],["${packageprefix}/${packagedocdir}"])

AC_DEFINE_UNQUOTED(PACKAGE_PIXMAPS_DIR, "${packageprefix}/${packagepixmapsdir}")
AH_TEMPLATE([PACKAGE_PIXMAPS_DIR],[ "${packageprefix}/${packagepixmapsdir}"])

AC_DEFINE_UNQUOTED(PACKAGE_HELP_DIR, "${packageprefix}/${packagehelpdir}")
AH_TEMPLATE([PACKAGE_HELP_DIR],[ "${packageprefix}/${packagehelpdir}"])

AC_DEFINE_UNQUOTED(PACKAGE_MENU_DIR, "${packageprefix}/${packagemenudir}")
AH_TEMPLATE([PACKAGE_MENU_DIR],["${packageprefix}/${packagemenudir}"])

AC_DEFINE_UNQUOTED(PACKAGE_SOURCE_DIR, "${packagesrcdir}")
AH_TEMPLATE([PACKAGE_SOURCE_DIR],[ "${packagesrcdir}"])

AC_OUTPUT([
Makefile
po/Makefile.in
doc/Makefile
src/Makefile
src/xe/Makefile
src/ulib/Makefile
src/xsub/Makefile
src/xp/Makefile
gxe.desktop
])

