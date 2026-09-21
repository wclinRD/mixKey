#pragma once

#include <string>
#include <vector>

namespace McBopomofo::MixedScript {

class LatinPassthroughLM {
public:
    static double ScoreJustBelow(double topScore) { return topScore - 0.001; }
    
    void registerSoleEntry(const std::string& key, const std::string& value);
    void registerAlternate(const std::string& key, const std::string& value, double score);
    bool hasValue(const std::string& key, const std::string& value) const;
    void clear();
    void clearKey(const std::string& key);
    std::vector<std::pair<std::string, double>> getUnigrams(const std::string& key);
    bool hasUnigrams(const std::string& key);

private:
    std::vector<std::pair<std::string, double>> entries_;
};

}  // namespace McBopomofo::MixedScript
