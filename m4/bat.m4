AC_DEFUN([AC_SEARCH_BAT],[
AC_MSG_CHECKING([for the BAT library])
AC_ARG_WITH(
        [BAT],
        [AS_HELP_STRING([--with-BAT=prefix],[compile with BAT support])],
        [
                use_BAT=yes
		AC_MSG_RESULT([found])
                AC_MSG_NOTICE([Adding BAT with path $with_BAT])
        ],
        [
		use_BAT=no
		AC_MSG_RESULT([not found])
		AC_MSG_NOTICE([])
		AC_MSG_ERROR([BAT is essential, cannot compile without it. Abort.])
	]
)
AC_CHECK_HEADERS([$with_BAT/include/BAT/BCDataSet.h],[],[AC_MSG_ERROR([Cannot find BAT headers]) ])

if test $use_BAT = yes ; then
   AM_CXXFLAGS="$AM_CXXFLAGS -I$with_BAT/include/BAT"
   AM_LDFLAGS="$AM_LDFLAGS -L$with_BAT/lib -lBAT"

   BAT_CFLAGS="-I$with_BAT/include"
   AC_SUBST(BAT_CFLAGS)

   BAT_LIBS="-L$with_BAT/lib -lBAT"
   AC_SUBST(BAT_LIBS)
fi
])