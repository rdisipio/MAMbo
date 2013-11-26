# Convert argument to an absolute path
AC_DEFUN([AC_CUSTOM_ABSPATH], [
  inpath=${$1}
  abspath=""
  if test -d "$inpath"; then
    abspath=`cd $inpath && pwd`
  elif test -f "$inpath"; then
    dirpart=`dirname $inpath`
    localpart=`basename $inpath`
    abspath="`cd $dirpart && pwd`/$localpart"
  fi
  if test -z "$abspath"; then
    AC_MSG_ERROR(Could not make absolute path $1 from ${$1})
  fi
  $1=$abspath
])


# A version of AC_SUBST which ensures that paths are absolute
AC_DEFUN([AC_CUSTOM_PATH_SUBST], [
  AC_CUSTOM_ABSPATH($1)
  AC_SUBST($1)
])


#AC_CUSTOM_HEADERS(PrettyName, ReleaseNumber, action-if-true, action-if-false)
AC_DEFUN([AC_CUSTOM_HEADERS], [
  ## Define a bunch of case permutations
  m4_define([custom_PkgName], [$1])dnl
  m4_define([custom_PKGNAME], [translit([translit([$1], [a-z], [A-Z])], [.])])dnl
  m4_define([custom_pkgname], [translit([translit([$1], [A-Z], [a-z])], [.])])dnl
  m4_define([custom_SAFEPKGNAME], [translit(custom_PKGNAME, [-], [_])])dnl
  m4_define([custom_safepkgname], [translit(custom_pkgname, [-], [_])])dnl
  m4_define([custom_IncName], [custom_PkgName])dnl
  m4_define([custom_INCNAME], [custom_PKGNAME])dnl
  m4_define([custom_incname], [custom_pkgname])dnl
  m4_define([custom_IncName1], [translit(custom_PkgName, [-], [_])])dnl
  m4_define([custom_INCNAME1], [translit(custom_PKGNAME, [-], [_])])dnl
  m4_define([custom_incname1], [translit(custom_pkgname, [-], [_])])dnl
  m4_define([custom_IncName2], [translit(custom_PkgName, [-], [])])dnl
  m4_define([custom_INCNAME2], [translit(custom_PKGNAME, [-], [])])dnl
  m4_define([custom_incname2], [translit(custom_pkgname, [-], [])])dnl
  m4_define([custom_pkgversion], [$2])dnl

  ## We have a set of user-set variables:
  pkgpath=""; pkgincpath=""
  ## Also need some status variables:
  pkginc=no

  ## Don't know why this isn't working by default:
  test x${prefix} = xNONE && prefix=${ac_default_prefix}

  ## Environment variables for specifying paths
  AC_ARG_VAR(@&t@custom_SAFEPKGNAME@&t@PATH,
    path to custom_PkgName @<:@$prefix and various standard locations@:>@)
  AC_ARG_VAR(@&t@custom_SAFEPKGNAME@&t@INCPATH,
    path to the directory containing the custom_PkgName header files @<:@custom_SAFEPKGNAME@&t@PATH/include@:>@)

  ## "configure" option switches for specifying paths
  pkgpath=${custom_SAFEPKGNAME@&t@PATH}
  AC_ARG_WITH(custom_safepkgname,
              AC_HELP_STRING(--with-@&t@custom_safepkgname@&t@, 
                path to custom_PkgName @<:@$prefix and various standard locations@:>@),
              [pkgpath=$with_@&t@custom_safepkgname], [])
  dnl echo "DEBUG: withval=$withval, with_@&t@custom_safepkgname=$with_@&t@custom_safepkgname -> pkgpath=$pkgpath"
  if test "$pkgpath"; then custom_SAFEPKGNAME@&t@PATH="$pkgpath"; fi

  pkgincpath=${custom_SAFEPKGNAME@&t@INCPATH}
  AC_ARG_WITH(custom_safepkgname@&t@-incpath,
              AC_HELP_STRING(--with-@&t@custom_safepkgname@&t@-incpath, 
                path to directory containing custom_PkgName headers @<:@custom_SAFEPKGNAME@&t@PATH/include@:>@),
              [pkgincpath=$with_@&t@custom_safepkgname@&t@_incpath], [])

  ## Has this header been disabled?
  if test x$pkgpath = xno; then 
    AC_MSG_NOTICE(Not building against custom_PkgName)
    $4
  else
    ## Base paths
    pkgbases="$prefix $ac_default_prefix /usr /"
    if test "$pkgpath"; then pkgbases="$pkgpath"; fi

    ## Look for include files: first build the search list...
    incpaths=""
    if test "$pkgincpath"; then 
      incpath=`echo $pkgincpath | sed -e 's://*:/:g' -e 's:/$::'`
      incpaths="$incpath"
    else
      for base in $pkgbases; do
        incpath=`echo "$base/include" | sed -e 's://*:/:g' -e 's:/$::'`
        incpaths="$incpaths $incpath"
      done
    fi
    
    if test "x$CUSTOM_M4_DEBUG" != "x"; then
      echo "DEBUG: inc paths = $incpaths"
    fi


    ## Build package names
    incnames="custom_IncName custom_INCNAME custom_incname"
    if test "custom_IncName" != "custom_IncName1"; then
      incnames="$incnames custom_IncName1 custom_INCNAME1 custom_incname1"
    fi
    if test "custom_IncName" != "custom_IncName2"; then
      incnames="$incnames custom_IncName2 custom_INCNAME2 custom_incname2"
    fi

    ## .. and then do the search:
    for incpath in $incpaths; do
      for incname in $incnames; do
        fullincpath="$incpath/$incname"
        if test "x$CUSTOM_M4_DEBUG" != "x"; then
          echo "Testing custom_PkgName inc path: $fullincpath"
        fi
        if test -d $fullincpath; then
          pkginc=yes
          break
        else 
          pkginc=no;
        fi
        if test x$pkginc != xno; then break; fi
      done
      if test x$pkginc != xno; then break; fi
    done

    if test x$pkginc != xno; then
      custom_SAFEPKGNAME@&t@INCPATH="$incpath"
      AC_CUSTOM_ABSPATH(custom_SAFEPKGNAME@&t@INCPATH)
      custom_SAFEPKGNAME@&t@INCNAME="$incname"
      custom_SAFEPKGNAME@&t@CPPFLAGS="-I$custom_SAFEPKGNAME@&t@INCPATH"
      #echo custom_SAFEPKGNAME@&t@INCPATH : $custom_SAFEPKGNAME@&t@INCPATH
      AC_MSG_NOTICE([Found custom_PkgName header directory at $incpath])
    else
      ## Last resort --- only tried if $pkgpath was specified
      if test x$pkgpath != x; then
        incpath="$pkgpath/include"
        if test -d "$incpath"; then
          custom_SAFEPKGNAME@&t@INCPATH=`echo $incpath | sed -e s:'/$':'':`
          AC_CUSTOM_ABSPATH(custom_SAFEPKGNAME@&t@INCPATH)
          custom_SAFEPKGNAME@&t@INCNAME=""
          custom_SAFEPKGNAME@&t@CPPFLAGS="-I$custom_SAFEPKGNAME@&t@INCPATH"
          pkginc=yes
          #AC_MSG_NOTICE([Found custom_PkgName header directory at $incpath])
        fi
      else
        AC_MSG_WARN(custom_PkgName header directory was not found)
      fi
    fi

    ## Execute pass/fail shell code
    if test "x$pkginc" = "xyes"; then
      true
      $3
    else 
      true
      $4
    fi
  fi

  ## Export variables to automake
  AC_SUBST(custom_SAFEPKGNAME@&t@INCPATH)
  AC_SUBST(custom_SAFEPKGNAME@&t@INCNAME)
  AC_SUBST(custom_SAFEPKGNAME@&t@CPPFLAGS)
  AM_CONDITIONAL(WITH_@&t@custom_SAFEPKGNAME@&t@INC, [test x$pkgginc != xno])
  AM_CONDITIONAL(WITHOUT_@&t@custom_SAFEPKGNAME@&t@INC, [test x$pkgginc = xno])
])

