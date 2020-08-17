#include <iostream>
// tensorflow includes
#include "pc_utils.hpp"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/array_ops.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/io_ops.h"
#include "tensorflow/cc/ops/math_ops.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/public/session.h"

void checkStatus(const tensorflow::Status &status) {
  if (!status.ok()) {
    std::cout << status.ToString() << std::endl;
    exit(1);
  }
}

int main() {
  // set tensorflow alias
  namespace tf = tensorflow;

  std::string image =
      "/home/loukil/Documents/Projects/LaserNet/example/airplane.png";

  std::int32_t input_width = 299;
  std::int32_t input_height = 299;
  float input_mean = 0;
  float input_std = 255;
  std::vector<tf::Tensor> resized_tensors;

  // create root scope
  auto root = tf::Scope::NewRootScope();

  // create some placeholders
  auto filename = tf::ops::Placeholder(root.WithOpName("input"), tf::DT_STRING);
  auto file_reader = tf::ops::ReadFile(root.WithOpName("file_readr"), filename);
  const int wanted_channels = 3;
  auto image_reader =
      tf::ops::DecodeJpeg(root.WithOpName("jpeg_reader"), file_reader,
                          tf::ops::DecodeJpeg::Channels(wanted_channels));
  auto float_caster = tf::ops::Cast(root.WithOpName("float_caster"),
                                    image_reader, tf::DT_FLOAT);
  auto dims_expander =
      tf::ops::ExpandDims(root.WithOpName("dim"), float_caster, 0);
  auto resized = tf::ops::ResizeBilinear(
      root.WithOpName("size"), dims_expander,
      tf::ops::GuaranteeConst(root, {input_width, input_height}));
  auto d = tf::ops::Div(root.WithOpName("normalized"),
                        tf::ops::Sub(root, resized, {input_mean}), {input_std});
  // create session
  tf::ClientSession session(root);
  std::cout << "running session" << std::endl;
  TF_CHECK_OK(session.Run({{filename, image}}, {d}, &resized_tensors));



  return 0;
}