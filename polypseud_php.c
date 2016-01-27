#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "polypseud_php.h"

#include <polypseud.h>

static zend_function_entry polypseud_php_functions[] = {
    PHP_FE(polypseud_decrypt, NULL)
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

PHP_FUNCTION(polypseud_decrypt)
{
    const char *ep, *privkey, *closingkey;
    int ep_len, privkey_len, closingkey_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &ep, &ep_len, &privkey, &privkey_len, &closingkey, &closingkey_len) == FAILURE) {
        RETURN_NULL();
    }

    char* pp = decrypt_ep(ep, privkey, closingkey);

    RETURN_STRING(pp, 1);
}
