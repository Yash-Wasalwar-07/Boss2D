/*
 *  Copyright 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef PC_AUDIOTRACK_H_
#define PC_AUDIOTRACK_H_

#include <string>

#include BOSS_WEBRTC_U_api__mediastreaminterface_h //original-code:"api/mediastreaminterface.h"
#include BOSS_WEBRTC_U_api__notifier_h //original-code:"api/notifier.h"
#include BOSS_WEBRTC_U_pc__mediastreamtrack_h //original-code:"pc/mediastreamtrack.h"
#include BOSS_WEBRTC_U_rtc_base__constructormagic_h //original-code:"rtc_base/constructormagic.h"
#include BOSS_WEBRTC_U_rtc_base__scoped_ref_ptr_h //original-code:"rtc_base/scoped_ref_ptr.h"
#include BOSS_WEBRTC_U_rtc_base__thread_checker_h //original-code:"rtc_base/thread_checker.h"

namespace webrtc {

class AudioTrack : public MediaStreamTrack<AudioTrackInterface>,
                   public ObserverInterface {
 protected:
  // Protected ctor to force use of factory method.
  AudioTrack(const std::string& label,
             const rtc::scoped_refptr<AudioSourceInterface>& source);
  ~AudioTrack() override;

 public:
  static rtc::scoped_refptr<AudioTrack> Create(
      const std::string& id,
      const rtc::scoped_refptr<AudioSourceInterface>& source);

 private:
  // MediaStreamTrack implementation.
  std::string kind() const override;

  // AudioTrackInterface implementation.
  AudioSourceInterface* GetSource() const override;

  void AddSink(AudioTrackSinkInterface* sink) override;
  void RemoveSink(AudioTrackSinkInterface* sink) override;

  // ObserverInterface implementation.
  void OnChanged() override;

 private:
  const rtc::scoped_refptr<AudioSourceInterface> audio_source_;
  rtc::ThreadChecker thread_checker_;
  RTC_DISALLOW_IMPLICIT_CONSTRUCTORS(AudioTrack);
};

}  // namespace webrtc

#endif  // PC_AUDIOTRACK_H_
