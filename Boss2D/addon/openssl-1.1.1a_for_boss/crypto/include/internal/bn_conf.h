// author BOSS

// removed by BOSS: {- join("\n",map { "/* $_ */" } @autowarntext) -}
/*
 * Copyright 2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_BN_CONF_H
# define HEADER_BN_CONF_H

/*
 * The contents of this file are not used in the UEFI build, as
 * both 32-bit and 64-bit builds are supported from a single run
 * of the Configure script.
 */

/* Should we define BN_DIV2W here? */

/* Only one for the following should be defined */
// removed by BOSS: {- $config{b64l} ? "#define" : "#undef" -} SIXTY_FOUR_BIT_LONG
// removed by BOSS: {- $config{b64}  ? "#define" : "#undef" -} SIXTY_FOUR_BIT
// removed by BOSS: {- $config{b32}  ? "#define" : "#undef" -} THIRTY_TWO_BIT

#endif
