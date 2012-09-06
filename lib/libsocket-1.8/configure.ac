AC_PREREQ(2.52)
AC_INIT([libsocket], [1.8])
# +1 : ? : +1  == new interface that does not break old one
# +1 : ? : 0   == new interface that breaks old one
#  ? : ? : 0   == no new interfaces, but breaks apps
#  ? :+1 : ?   == just some internal changes, nothing breaks but might work
#                 better
# Current : Revision : Age
LIBSOCKET_SO_VERSION=1:8:1

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_FILES(config/Makefile)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)

AC_LANG_CPLUSPLUS
AC_PROG_CXX

AC_PROG_CC

AM_PROG_LEX
AC_PROG_YACC

#AC_PROG_RANLIB
AC_PROG_LIBTOOL

AC_SEARCH_LIBS(gethostbyname,nsl)
AC_SEARCH_LIBS(connect,socket)

AM_CONFIG_HEADER(config.h)

CXXFLAGS="$CXXFLAGS -Wall -ansi -pedantic"

AC_ARG_ENABLE(gcc-warnings,
[  --enable-gcc-warnings   Turn on lots of GCC warnings (not recommended)],
[case "${enableval}" in
   yes|no) ;;
   *) AC_MSG_ERROR([bad value ${enableval} for gcc-warnings option]) ;;
 esac],
              [enableval=no])
if test "${enableval}" = yes; then
  CXXFLAGS="$CXXFLAGS -Wall -W -Wbad-function-cast -Wcast-align -Wcast-qual -Wformat -Wmissing-declarations -Wmissing-prototypes -Wnested-externs -Wshadow -Wstrict-prototypes -Wwrite-strings"
fi

AC_ARG_WITH(tls, dnl
[  --with-tls              Enable GNUTLS support [[default=no]]],
	    tls=$withval, tls=no)
AC_ARG_WITH(ipv6, dnl
[  --with-ipv6             Enable ipv6 support [[default=no]]],
	    ipv6=$withval, ipv6=no)

if test "$with_libdbglib" = "yes"; then 
  with_libdbglib="."
  for ac_dir in /usr/local /usr; do
    if test -f "$ac_dir/lib/happycoders/libdbg.so"; then
      with_libdbglib=$ac_dir/lib/happycoders
      break;
    fi
  done
fi

if test "$with_libdbginclude" = "yes"; then 
  with_libdbginclude="."  
  for ac_dir in /usr/local /usr; do
    if test -f "$ac_dir/include/happycoders/dbg/dbg.h"; then
      with_libdbginclude=$ac_dir/include/happycoders/dbg
      break;
    fi
  done
fi

DBGLIB=$with_libdbglib
DBGINCLUDE=$with_libdbginclude
DBG=""

if test "$ipv6" = yes; then
  CXXFLAGS="$CXXFLAGS -DIPV6"
fi

if test "$tls" = yes; then
  CXXFLAGS="$CXXFLAGS -DTLS"
  EXTRALIB="-lgnutls"
else
  EXTRALIB=""
fi

os=`uname`
case $os in
  SunOS)
  EXTRALIB="$EXTRALIB -lnsl /usr/lib/libsocket.a"
  ;;
esac

AC_SUBST(EXTRALIB)
AC_SUBST(LIBSOCKET_SO_VERSION)

AC_STDC_HEADERS

AC_CONFIG_FILES(Makefile src/Makefile src/tests/Makefile)

AC_OUTPUT
