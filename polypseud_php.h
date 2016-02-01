#ifndef POLYPSEUD_PHP_H
#define POLYPSEUD_PHP_H 1

#define POLYPSEUD_PHP_VERSION "1.0"
#define POLYPSEUD_PHP_EXTNAME "polypseud_php"

PHP_FUNCTION(polypseud_decrypt);
PHP_FUNCTION(polypseud_generate_pp);

extern zend_module_entry polypseud_php_module_entry;
#define phpext_polypseud_php_ptr &polypseud_php_module_entry

#endif
