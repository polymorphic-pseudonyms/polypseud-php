#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "polypseud_php.h"

#include <polypseud.h>

static zend_function_entry polypseud_php_functions[] = {
    PHP_FE(polypseud_decrypt, NULL)
    PHP_FE(polypseud_generate_pp, NULL)
    PHP_FE(polypseud_specialize, NULL)
    PHP_FE(polypseud_randomize, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry polypseud_php_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    POLYPSEUD_PHP_EXTNAME,
    polypseud_php_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    POLYPSEUD_PHP_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_POLYPSEUD_PHP
ZEND_GET_MODULE(polypseud_php)
#endif

PHP_FUNCTION(polypseud_decrypt) {
    char *ep, *privkey, *closingkey;
    int ep_len, privkey_len, closingkey_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &ep, &ep_len, &privkey, &privkey_len, &closingkey, &closingkey_len) == FAILURE) {
        RETURN_NULL();
    }

    char *fp = polypseud_decrypt_ep(ep, privkey, closingkey);

    RETURN_STRING(fp, 1);
}

PHP_FUNCTION(polypseud_generate_pp) {
   char *yK, *uid;
   int yK_len, uid_len;

   if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &yK, &yK_len, &uid, &uid_len) == FAILURE) {
       RETURN_NULL();
   }

   char *pp = polypseud_generate_pp(yK, uid);

   RETURN_STRING(pp, 1);
}

PHP_FUNCTION(polypseud_specialize) {
    char *pp, *spid, *dp, *dk;
    int pp_len, spid_len, dp_len, dk_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssss", &pp, &pp_len, &spid, &spid_len, &dp, &dp_len, &dk, &dk_len) == FAILURE) {
        RETURN_NULL();
    }

    char *ep = polypseud_specialize_pp(pp, spid, dp, dk);

    RETURN_STRING(ep, 1);
}

PHP_FUNCTION(polypseud_randomize) {
   char *pseud;
   int pseud_len;

   if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pseud, &pseud_len) == FAILURE) {
       RETURN_NULL();
   }

   char *randomized = polypseud_randomize_enc(pseud);

   RETURN_STRING(randomized, 1);
}

