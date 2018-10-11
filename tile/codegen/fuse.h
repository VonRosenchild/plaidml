// Copyright 2018, Intel Corp.

#pragma once

#include <map>
#include <string>

#include <boost/optional.hpp>

#include "tile/codegen/alias.h"

namespace vertexai {
namespace tile {
namespace codegen {

struct FusionPlan {
  std::map<std::string, std::string> remap_a;
  std::map<std::string, std::string> remap_b;
};

// Given a shared buffer between two blocks, compute a possible fusion
boost::optional<FusionPlan> ComputeFusionPlan(const stripe::Block& a, const stripe::Block& b,
                                              const std::string& buf_name);

// Prepare each block for fusion by renaming / moving indexes
std::shared_ptr<stripe::Block> FusionRefactor(const stripe::Block& block,
                                              const std::map<std::string, std::string>& mapping);

// Attempt to fuse b into a.  Return true on success, in which case blocks have been
// destructively modified.  Otherwise returns false and leave blocks unaltered.
bool FuseBlocks(const AliasMap& scope, stripe::Block* a, stripe::Block* b);

}  // namespace codegen
}  // namespace tile
}  // namespace vertexai
