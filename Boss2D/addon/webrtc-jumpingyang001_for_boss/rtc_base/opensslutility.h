/*
 *  Copyright 2018 The WebRTC Project Authors. All rights reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef RTC_BASE_OPENSSLUTILITY_H_
#define RTC_BASE_OPENSSLUTILITY_H_

#include BOSS_OPENSSL_V_openssl__ossl_typ_h //original-code:<openssl/ossl_typ.h>
#include <string>
#include BOSS_WEBRTC_U_rtc_base__sslcertificate_h //original-code:"rtc_base/sslcertificate.h"

namespace rtc {
// The openssl namespace holds static helper methods. All methods related
// to OpenSSL that are commonly used and don't require global state should be
// placed here.
namespace openssl {
// Verifies that the hostname provided matches that in the peer certificate
// attached to this SSL state.
bool VerifyPeerCertMatchesHost(SSL* ssl, const std::string& host);

// Logs all the errors in the OpenSSL errror queue from the current thread. A
// prefix can be provided for context.
void LogSSLErrors(const std::string& prefix);

#ifdef WEBRTC_BUILT_IN_SSL_ROOT_CERTIFICATES
// Attempt to add the certificates from the loader into the SSL_CTX. False is
// returned only if there are no certificates returned from the loader or none
// of them can be added to the TrustStore for the provided context.
bool LoadBuiltinSSLRootCertificates(SSL_CTX* ssl_ctx);
#endif  // WEBRTC_BUILT_IN_SSL_ROOT_CERTIFICATES

}  // namespace openssl
}  // namespace rtc

#endif  // RTC_BASE_OPENSSLUTILITY_H_
