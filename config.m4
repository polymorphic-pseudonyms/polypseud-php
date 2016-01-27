PHP_ARG_WITH(libpolypseud, location of the polypseud library,
[ --with-libpolypseud=DIR  Location of the polypseud library])

if test "$PHP_LIBPOLYPSEUD" == "no"; then
    PHP_LIBPOLYPSEUD="/usr"
fi
if test "$PHP_LIBPOLYPSEUD" == "yes"; then
    AC_MSG_ERROR([You must specify a path when using --with-libpolypseud])
fi

PHP_CHECK_LIBRARY(polypseud, decrypt_ep,
[
    PHP_ADD_INCLUDE($PHP_LIBPOLYPSEUD/include)
    PHP_ADD_LIBRARY_WITH_PATH(polypseud, $PHP_LIBPOLYPSEUD/lib, POLYPSEUD_PHP_SHARED_LIBADD)
],[
    AC_MSG_ERROR([polypseud library not found. Check config.log for more information.])
],[polypseud]
)

PHP_CHECK_LIBRARY(crypto, EC_POINT_new,
[
    PHP_ADD_LIBRARY(crypto,1,POLYPSEUD_PHP_SHARED_LIBADD)
    dnl AC_DEFINE(HAVE_CRYPTO, 1, [Whether you have libcrypto])
],[
    AC_MSG_ERROR([OpenSSL crypto library not found. Check config.log for more information.])
],[crypto]
)

AC_DEFINE(HAVE_POLYPSEUD_PHP, 1, [Whether you have polymorphic pseudonyms])
PHP_NEW_EXTENSION(polypseud_php, polypseud_php.c, $ext_shared)
PHP_SUBST(POLYPSEUD_PHP_SHARED_LIBADD)


