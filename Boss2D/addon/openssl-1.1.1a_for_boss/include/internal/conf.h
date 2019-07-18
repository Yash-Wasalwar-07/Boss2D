/*
 * Copyright 2016-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_INTERNAL_CONF_H
# define HEADER_INTERNAL_CONF_H

#include BOSS_OPENSSL_V_openssl__conf_h //original-code:<openssl/conf.h>

struct ossl_init_settings_st {
    char *appname;
};

void openssl_config_int(const char *appname);
void openssl_no_config_int(void);
void conf_modules_free_int(void);

#endif
