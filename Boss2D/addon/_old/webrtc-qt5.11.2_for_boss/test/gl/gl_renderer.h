/*
 *  Copyright (c) 2013 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef TEST_GL_GL_RENDERER_H_
#define TEST_GL_GL_RENDERER_H_

#ifdef WEBRTC_MAC
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "test/video_renderer.h"
#include BOSS_WEBRTC_U_typedefs_h //original-code:"typedefs.h"  // NOLINT(build/include)


namespace webrtc {
namespace test {

class GlRenderer : public VideoRenderer {
 public:
  void OnFrame(const webrtc::VideoFrame& frame) override;

 protected:
  GlRenderer();

  void Init();
  void Destroy();

  void ResizeViewport(size_t width, size_t height);

 private:
  bool is_init_;
  uint8_t* buffer_;
  GLuint texture_;
  size_t width_, height_, buffer_size_;

  void ResizeVideo(size_t width, size_t height);
};
}  // test
}  // webrtc

#endif  // TEST_GL_GL_RENDERER_H_
