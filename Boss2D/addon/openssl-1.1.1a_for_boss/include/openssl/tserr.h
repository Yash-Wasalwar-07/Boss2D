/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_TSERR_H
# define HEADER_TSERR_H

# include BOSS_OPENSSL_V_openssl__opensslconf_h //original-code:<openssl/opensslconf.h>

# ifndef OPENSSL_NO_TS

#  ifdef  __cplusplus
extern "C"
#  endif
int ERR_load_TS_strings(void);

/*
 * TS function codes.
 */
#  define TS_F_DEF_SERIAL_CB                               110
#  define TS_F_DEF_TIME_CB                                 111
#  define TS_F_ESS_ADD_SIGNING_CERT                        112
#  define TS_F_ESS_ADD_SIGNING_CERT_V2                     147
#  define TS_F_ESS_CERT_ID_NEW_INIT                        113
#  define TS_F_ESS_CERT_ID_V2_NEW_INIT                     156
#  define TS_F_ESS_SIGNING_CERT_NEW_INIT                   114
#  define TS_F_ESS_SIGNING_CERT_V2_NEW_INIT                157
#  define TS_F_INT_TS_RESP_VERIFY_TOKEN                    149
#  define TS_F_PKCS7_TO_TS_TST_INFO                        148
#  define TS_F_TS_ACCURACY_SET_MICROS                      115
#  define TS_F_TS_ACCURACY_SET_MILLIS                      116
#  define TS_F_TS_ACCURACY_SET_SECONDS                     117
#  define TS_F_TS_CHECK_IMPRINTS                           100
#  define TS_F_TS_CHECK_NONCES                             101
#  define TS_F_TS_CHECK_POLICY                             102
#  define TS_F_TS_CHECK_SIGNING_CERTS                      103
#  define TS_F_TS_CHECK_STATUS_INFO                        104
#  define TS_F_TS_COMPUTE_IMPRINT                          145
#  define TS_F_TS_CONF_INVALID                             151
#  define TS_F_TS_CONF_LOAD_CERT                           153
#  define TS_F_TS_CONF_LOAD_CERTS                          154
#  define TS_F_TS_CONF_LOAD_KEY                            155
#  define TS_F_TS_CONF_LOOKUP_FAIL                         152
#  define TS_F_TS_CONF_SET_DEFAULT_ENGINE                  146
#  define TS_F_TS_GET_STATUS_TEXT                          105
#  define TS_F_TS_MSG_IMPRINT_SET_ALGO                     118
#  define TS_F_TS_REQ_SET_MSG_IMPRINT                      119
#  define TS_F_TS_REQ_SET_NONCE                            120
#  define TS_F_TS_REQ_SET_POLICY_ID                        121
#  define TS_F_TS_RESP_CREATE_RESPONSE                     122
#  define TS_F_TS_RESP_CREATE_TST_INFO                     123
#  define TS_F_TS_RESP_CTX_ADD_FAILURE_INFO                124
#  define TS_F_TS_RESP_CTX_ADD_MD                          125
#  define TS_F_TS_RESP_CTX_ADD_POLICY                      126
#  define TS_F_TS_RESP_CTX_NEW                             127
#  define TS_F_TS_RESP_CTX_SET_ACCURACY                    128
#  define TS_F_TS_RESP_CTX_SET_CERTS                       129
#  define TS_F_TS_RESP_CTX_SET_DEF_POLICY                  130
#  define TS_F_TS_RESP_CTX_SET_SIGNER_CERT                 131
#  define TS_F_TS_RESP_CTX_SET_STATUS_INFO                 132
#  define TS_F_TS_RESP_GET_POLICY                          133
#  define TS_F_TS_RESP_SET_GENTIME_WITH_PRECISION          134
#  define TS_F_TS_RESP_SET_STATUS_INFO                     135
#  define TS_F_TS_RESP_SET_TST_INFO                        150
#  define TS_F_TS_RESP_SIGN                                136
#  define TS_F_TS_RESP_VERIFY_SIGNATURE                    106
#  define TS_F_TS_TST_INFO_SET_ACCURACY                    137
#  define TS_F_TS_TST_INFO_SET_MSG_IMPRINT                 138
#  define TS_F_TS_TST_INFO_SET_NONCE                       139
#  define TS_F_TS_TST_INFO_SET_POLICY_ID                   140
#  define TS_F_TS_TST_INFO_SET_SERIAL                      141
#  define TS_F_TS_TST_INFO_SET_TIME                        142
#  define TS_F_TS_TST_INFO_SET_TSA                         143
#  define TS_F_TS_VERIFY                                   108
#  define TS_F_TS_VERIFY_CERT                              109
#  define TS_F_TS_VERIFY_CTX_NEW                           144

/*
 * TS reason codes.
 */
#  define TS_R_BAD_PKCS7_TYPE                              132
#  define TS_R_BAD_TYPE                                    133
#  define TS_R_CANNOT_LOAD_CERT                            137
#  define TS_R_CANNOT_LOAD_KEY                             138
#  define TS_R_CERTIFICATE_VERIFY_ERROR                    100
#  define TS_R_COULD_NOT_SET_ENGINE                        127
#  define TS_R_COULD_NOT_SET_TIME                          115
#  define TS_R_DETACHED_CONTENT                            134
#  define TS_R_ESS_ADD_SIGNING_CERT_ERROR                  116
#  define TS_R_ESS_ADD_SIGNING_CERT_V2_ERROR               139
#  define TS_R_ESS_SIGNING_CERTIFICATE_ERROR               101
#  define TS_R_INVALID_NULL_POINTER                        102
#  define TS_R_INVALID_SIGNER_CERTIFICATE_PURPOSE          117
#  define TS_R_MESSAGE_IMPRINT_MISMATCH                    103
#  define TS_R_NONCE_MISMATCH                              104
#  define TS_R_NONCE_NOT_RETURNED                          105
#  define TS_R_NO_CONTENT                                  106
#  define TS_R_NO_TIME_STAMP_TOKEN                         107
#  define TS_R_PKCS7_ADD_SIGNATURE_ERROR                   118
#  define TS_R_PKCS7_ADD_SIGNED_ATTR_ERROR                 119
#  define TS_R_PKCS7_TO_TS_TST_INFO_FAILED                 129
#  define TS_R_POLICY_MISMATCH                             108
#  define TS_R_PRIVATE_KEY_DOES_NOT_MATCH_CERTIFICATE      120
#  define TS_R_RESPONSE_SETUP_ERROR                        121
#  define TS_R_SIGNATURE_FAILURE                           109
#  define TS_R_THERE_MUST_BE_ONE_SIGNER                    110
#  define TS_R_TIME_SYSCALL_ERROR                          122
#  define TS_R_TOKEN_NOT_PRESENT                           130
#  define TS_R_TOKEN_PRESENT                               131
#  define TS_R_TSA_NAME_MISMATCH                           111
#  define TS_R_TSA_UNTRUSTED                               112
#  define TS_R_TST_INFO_SETUP_ERROR                        123
#  define TS_R_TS_DATASIGN                                 124
#  define TS_R_UNACCEPTABLE_POLICY                         125
#  define TS_R_UNSUPPORTED_MD_ALGORITHM                    126
#  define TS_R_UNSUPPORTED_VERSION                         113
#  define TS_R_VAR_BAD_VALUE                               135
#  define TS_R_VAR_LOOKUP_FAILURE                          136
#  define TS_R_WRONG_CONTENT_TYPE                          114

# endif
#endif
