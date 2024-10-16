//==-- SYCLKernelParamOptInfo.h -- get kernel param optimization info ------==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// Analysis pass which collects parameter optimization info for SPIR kernels.
// Currently the info is whether i'th kernel parameter as emitted by the FE has
// been optimized away by the LLVM optimizer. The information is produced by
// DeadArgumentElimination transformation and stored into a specific metadata
// attached to kernel functions in a module.
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"

namespace llvm {

// the StringRef key refers to a function name
using SYCLKernelParamOptInfoBaseTy = DenseMap<StringRef, BitVector>;

class SYCLKernelParamOptInfo : public SYCLKernelParamOptInfoBaseTy {
public:
  void releaseMemory();
};

class SYCLKernelParamOptInfoAnalysis
    : public AnalysisInfoMixin<SYCLKernelParamOptInfoAnalysis> {
  friend AnalysisInfoMixin<SYCLKernelParamOptInfoAnalysis>;

  static AnalysisKey Key;

public:
  /// Provide the result type for this analysis pass.
  using Result = SYCLKernelParamOptInfo;

  /// Run the analysis pass over a function and produce BPI.
  SYCLKernelParamOptInfo run(Module &M, ModuleAnalysisManager &AM);
};

} // namespace llvm
