/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef MODULES_REMOTE_BITRATE_ESTIMATOR_INCLUDE_BWE_DEFINES_H_
#define MODULES_REMOTE_BITRATE_ESTIMATOR_INCLUDE_BWE_DEFINES_H_

#include BOSS_ABSEILCPP_U_absl__types__optional_h //original-code:"absl/types/optional.h"

#define BWE_MAX(a, b) ((a) > (b) ? (a) : (b))
#define BWE_MIN(a, b) ((a) < (b) ? (a) : (b))

namespace webrtc {

namespace congestion_controller {
int GetMinBitrateBps();
}  // namespace congestion_controller

static const int64_t kBitrateWindowMs = 1000;

extern const char kBweTypeHistogram[];

enum BweNames {
  kReceiverNoExtension = 0,
  kReceiverTOffset = 1,
  kReceiverAbsSendTime = 2,
  kSendSideTransportSeqNum = 3,
  kBweNamesMax = 4
};

enum class BandwidthUsage {
  kBwNormal = 0,
  kBwUnderusing = 1,
  kBwOverusing = 2,
  kLast
};

enum RateControlState { kRcHold, kRcIncrease, kRcDecrease };

enum RateControlRegion { kRcNearMax, kRcAboveMax, kRcMaxUnknown };

struct RateControlInput {
  RateControlInput(BandwidthUsage bw_state,
                   const absl::optional<uint32_t>& estimated_throughput_bps);
  ~RateControlInput();

  BandwidthUsage bw_state;
  absl::optional<uint32_t> estimated_throughput_bps;
};
}  // namespace webrtc

#endif  // MODULES_REMOTE_BITRATE_ESTIMATOR_INCLUDE_BWE_DEFINES_H_
