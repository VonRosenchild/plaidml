// Copyright 2019 Intel Corporation.

#pragma once

#include <memory>
#include <string>

#include "plaidml2/core/ffi.h"
#include "pmlc/dialect/tile/builder.h"
#include "tile/base/platform.h"
#include "tile/base/shape.h"
#include "tile/lang/ast/ast.h"

extern "C" {

struct plaidml_string {
  std::string str;
};

struct plaidml_shape {
  vertexai::tile::TensorShape shape;
};

struct plaidml_expr {
  vertexai::tile::lang::ast::ExprPtr expr;
  mlir::Value* value = nullptr;
};

struct plaidml_program {
  vertexai::tile::lang::ast::ProgramEvaluation eval;
  std::shared_ptr<pmlc::dialect::tile::TileProgram> program;
};

struct plaidml_buffer {
  std::shared_ptr<vertexai::tile::Buffer> buffer;
};

struct plaidml_view {
  std::shared_ptr<vertexai::tile::View> view;
};

}  // extern "C"

namespace plaidml {
namespace core {

vertexai::tile::Platform* GetPlatform();

template <typename T, typename F>
T ffi_wrap(plaidml_error* err, T val, F fn) {
  try {
    err->code = 0;
    err->msg = nullptr;
    return fn();
  } catch (const std::exception& ex) {
    err->code = 1;
    err->msg = new plaidml_string{ex.what()};
    return val;
  } catch (...) {
    err->code = 1;
    err->msg = new plaidml_string{"C++ exception"};
    return val;
  }
}

template <typename F>
void ffi_wrap_void(plaidml_error* err, F fn) {
  try {
    err->code = 0;
    err->msg = nullptr;
    fn();
  } catch (const std::exception& ex) {
    err->code = 1;
    err->msg = new plaidml_string{ex.what()};
  } catch (...) {
    err->code = 1;
    err->msg = new plaidml_string{"C++ exception"};
  }
}

}  // namespace core
}  // namespace plaidml
