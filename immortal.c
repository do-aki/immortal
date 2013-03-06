/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_extensions.h"
#include "php_immortal.h"

#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

ZEND_DECLARE_MODULE_GLOBALS(immortal)

#ifdef ZTS
#define IMMORTAL_G(v) TSRMG(immortal_globals_id, zend_immortal_globals *, v)
#else
#define IMMORTAL_G(v) (immortal_globals.v)
#endif


/* True global resources - no need for thread safety here */
static int le_immortal;

/* {{{ immortal_functions[]
 *
 * Every user visible function must have an entry in immortal_functions[].
 */
const zend_function_entry immortal_functions[] = {
	PHP_FE_END	/* Must be the last line in immortal_functions[] */
};
/* }}} */

/* {{{ immortal_module_entry
 */
zend_module_entry immortal_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"immortal",
	immortal_functions,
	PHP_MINIT(immortal),
	PHP_MSHUTDOWN(immortal),
	PHP_RINIT(immortal),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(immortal),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(immortal),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_IMMORTAL
ZEND_GET_MODULE(immortal)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("immortal.throw_exception_at_exit", "0", PHP_INI_ALL, OnUpdateLong, throw_exception_at_exit, zend_immortal_globals, immortal_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_immortal_init_globals
 */
static void php_immortal_init_globals(zend_immortal_globals *immortal_globals)
{
	immortal_globals->throw_exception_at_exit = 0;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(immortal)
{
	REGISTER_INI_ENTRIES();

	zend_set_user_opcode_handler(ZEND_EXIT, immortal_exit_handler);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(immortal)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(immortal)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(immortal)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(immortal)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "immortal support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ immortal_exit_handler */
int immortal_exit_handler(ZEND_OPCODE_HANDLER_ARGS) 
{
	if (IMMORTAL_G(throw_exception_at_exit)) {
		zend_throw_exception(spl_ce_RuntimeException, "die", 0 TSRMLS_CC);
		return ZEND_USER_OPCODE_RETURN;
	}

	return ZEND_USER_OPCODE_DISPATCH;
}
/* }}} */

/* {{{ immortal_zend_startup */
ZEND_DLEXPORT int immortal_zend_startup(zend_extension *extension)
{
    return zend_startup_module(&immortal_module_entry);
}
/* }}} */

/* {{{ immortal_zend_shutdown */
ZEND_DLEXPORT void immortal_zend_shutdown(zend_extension *extension)
{
        /* Do nothing. */
}
/* }}} */

#ifndef ZEND_EXT_API
#define ZEND_EXT_API    ZEND_DLEXPORT
#endif
ZEND_EXTENSION();

/* {{{ zend_extension_entry */
ZEND_DLEXPORT zend_extension zend_extension_entry = {
  "immortal",
  "0.1",
  "do_aki",
  "http://do-aki.net/",
  "copyright (c) by do_ki",
  immortal_zend_startup,
  immortal_zend_shutdown,
  NULL,
  NULL,
  NULL,   // message_handler_func_t
  NULL,   // op_array_handler_func_t
  NULL,   // statement_handler_func_t
  NULL,   // fcall_begin_handler_func_t
  NULL,   // fcall_end_handler_func_t
  NULL,   // op_array_ctor_func_t
  NULL,   // op_array_dtor_func_t
  STANDARD_ZEND_EXTENSION_PROPERTIES
};
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
