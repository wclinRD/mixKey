#include "LatinPassthroughLM.h"

namespace McBopomofo::MixedScript {

void LatinPassthroughLM::registerSoleEntry(const std::string& key, const std::string& value) {
  entries_.clear();
  entries_.emplace_back(value, 0);
}

void LatinPassthroughLM::registerAlternate(const std::string& key, const std::string& value, double score) {
  entries_.emplace_back(value, score);
}

bool LatinPassthroughLM::hasValue(const std::string& key, const std::string& value) const {
  for (const auto& p : entries_) {
    if (p.first == value) return true;
  }
  return false;
}

void LatinPassthroughLM::clear() { entries_.clear(); }
void LatinPassthroughLM::clearKey(const std::string& key) { entries_.clear(); }

std::vector<std::pair<std::string, double>> LatinPassthroughLM::getUnigrams(const std::string& key) {
  return entries_;
}

bool LatinPassthroughLM::hasUnigrams(const std::string& key) {
  return !entries_.empty();
}

}  // namespace McBopomofo::MixedScript
