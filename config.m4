dnl $Id$
dnl config.m4 for extension immortal

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(immortal, for immortal support,
dnl Make sure that the comment is aligned:
dnl [  --with-immortal             Include immortal support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(immortal, whether to enable immortal support,
[  --enable-immortal           Enable immortal support])

if test "$PHP_IMMORTAL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-immortal -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/immortal.h"  # you most likely want to change this
  dnl if test -r $PHP_IMMORTAL/$SEARCH_FOR; then # path given as parameter
  dnl   IMMORTAL_DIR=$PHP_IMMORTAL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for immortal files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       IMMORTAL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$IMMORTAL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the immortal distribution])
  dnl fi

  dnl # --with-immortal -> add include path
  dnl PHP_ADD_INCLUDE($IMMORTAL_DIR/include)

  dnl # --with-immortal -> check for lib and symbol presence
  dnl LIBNAME=immortal # you may want to change this
  dnl LIBSYMBOL=immortal # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $IMMORTAL_DIR/lib, IMMORTAL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_IMMORTALLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong immortal lib version or lib not found])
  dnl ],[
  dnl   -L$IMMORTAL_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(IMMORTAL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(immortal, immortal.c, $ext_shared,,,,yes)
fi
