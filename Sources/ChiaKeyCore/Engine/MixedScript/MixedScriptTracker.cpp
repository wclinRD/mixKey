// Copyright (c) 2026 and onwards The ChiaKey Authors.
// Based on bopomix MixedScript implementation (MIT License)

#include "MixedScriptTracker.h"

namespace McBopomofo::MixedScript {

Verdict MixedScriptTracker::feedKey(const void* layout, char key) {
  latinRun_.push_back(key);
  alreadyRemembered_ = false;

  if (latinLocked_) {
    return Verdict::kLatin;
  }

  // Note: shape tracking would need layout integration
  if (latinRun_.size() >= kMinAmbiguousWordLength && lexicon_ != nullptr) {
    return Verdict::kAmbiguous;
  }
  return Verdict::kChinese;
}

Verdict MixedScriptTracker::onBoundary(bool isSpaceOrEnd) const {
  if (latinLocked_) {
    return Verdict::kLatin;
  }
  return Verdict::kAmbiguous;
}

void MixedScriptTracker::popLastLatinChar() {
  if (latinRun_.empty()) return;
  if (latinLocked_) {
    latinRun_.pop_back();
    alreadyRemembered_ = false;
    if (latinRun_.empty()) reset();
    return;
  }
  reset();
}

void MixedScriptTracker::acceptCompletion(const std::string& word) {
  latinRun_ = word;
  latinLocked_ = true;
  alreadyRemembered_ = true;
}

void MixedScriptTracker::reset() {
  latinRun_.clear();
  latinLocked_ = false;
  alreadyRemembered_ = false;
}

bool IsAllAsciiLetters(const std::string& value) {
  if (value.empty()) return false;
  for (unsigned char c : value) {
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
      return false;
    }
  }
  return true;
}

}  // namespace McBopomofo::MixedScript
