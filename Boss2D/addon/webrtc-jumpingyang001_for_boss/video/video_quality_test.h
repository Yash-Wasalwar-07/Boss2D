/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef VIDEO_VIDEO_QUALITY_TEST_H_
#define VIDEO_VIDEO_QUALITY_TEST_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include BOSS_WEBRTC_U_api__fec_controller_h //original-code:"api/fec_controller.h"
#include BOSS_WEBRTC_U_api__test__video_quality_test_fixture_h //original-code:"api/test/video_quality_test_fixture.h"
#include BOSS_WEBRTC_U_call__fake_network_pipe_h //original-code:"call/fake_network_pipe.h"
#include BOSS_WEBRTC_U_media__engine__internalencoderfactory_h //original-code:"media/engine/internalencoderfactory.h"
#include "test/call_test.h"
#include "test/frame_generator.h"
#include "test/layer_filtering_transport.h"

namespace webrtc {

class VideoQualityTest :
    public test::CallTest, public VideoQualityTestFixtureInterface {
 public:
  explicit VideoQualityTest(
      std::unique_ptr<FecControllerFactoryInterface> fec_controller_factory);

  void RunWithAnalyzer(const Params& params) override;
  void RunWithRenderers(const Params& params) override;

  const std::map<uint8_t, webrtc::MediaType>& payload_type_map() override {
    return payload_type_map_;
  }

  static void FillScalabilitySettings(
      Params* params,
      size_t video_idx,
      const std::vector<std::string>& stream_descriptors,
      int num_streams,
      size_t selected_stream,
      int num_spatial_layers,
      int selected_sl,
      InterLayerPredMode inter_layer_pred,
      const std::vector<std::string>& sl_descriptors);

  // Helper static methods.
  static VideoStream DefaultVideoStream(const Params& params, size_t video_idx);
  static VideoStream DefaultThumbnailStream();
  static std::vector<int> ParseCSV(const std::string& str);

 protected:
  std::map<uint8_t, webrtc::MediaType> payload_type_map_;

  // No-op implementation to be able to instantiate this class from non-TEST_F
  // locations.
  void TestBody() override;

  // Helper methods accessing only params_.
  std::string GenerateGraphTitle() const;
  void CheckParams();

  // Helper methods for setting up the call.
  void CreateCapturers();
  std::unique_ptr<test::FrameGenerator> CreateFrameGenerator(size_t video_idx);
  void SetupThumbnailCapturers(size_t num_thumbnail_streams);
  std::unique_ptr<VideoEncoder> CreateVideoEncoder(
      const SdpVideoFormat& format);
  void SetupVideo(Transport* send_transport, Transport* recv_transport);
  void SetupThumbnails(Transport* send_transport, Transport* recv_transport);
  void StartAudioStreams();
  void StartThumbnailCapture();
  void StopThumbnailCapture();
  void StartThumbnails();
  void StopThumbnails();
  void DestroyThumbnailStreams();
  void InitializeAudioDevice(Call::Config* send_call_config,
                             Call::Config* recv_call_config);
  void SetupAudio(Transport* transport);

  void StartEncodedFrameLogs(VideoSendStream* stream);
  void StartEncodedFrameLogs(VideoReceiveStream* stream);

  virtual std::unique_ptr<test::LayerFilteringTransport> CreateSendTransport();
  virtual std::unique_ptr<test::DirectTransport> CreateReceiveTransport();

  std::vector<std::unique_ptr<test::VideoCapturer>> thumbnail_capturers_;
  Clock* const clock_;

  test::FunctionVideoEncoderFactory video_encoder_factory_;
  InternalEncoderFactory internal_encoder_factory_;
  std::vector<VideoSendStream::Config> thumbnail_send_configs_;
  std::vector<VideoEncoderConfig> thumbnail_encoder_configs_;
  std::vector<VideoSendStream*> thumbnail_send_streams_;
  std::vector<VideoReceiveStream::Config> thumbnail_receive_configs_;
  std::vector<VideoReceiveStream*> thumbnail_receive_streams_;

  int receive_logs_;
  int send_logs_;

  Params params_;

  // Note: not same as similarly named member in CallTest. This is the number of
  // separate send streams, the one in CallTest is the number of substreams for
  // a single send stream.
  size_t num_video_streams_;
};

}  // namespace webrtc

#endif  // VIDEO_VIDEO_QUALITY_TEST_H_
