// Copyright (c) 2026 and onwards The ChiaKey Authors.
// Based on bopomix MixedScript implementation (MIT License)

#pragma once

#include <string>
#include <vector>

namespace McBopomofo::MixedScript {

class MixedScriptTracker {
public:
    enum class Verdict { kChinese, kLatin, kAmbiguous };

    explicit MixedScriptTracker(void* lexicon);
    
    Verdict feedKey(const void* layout, char key);
    Verdict onBoundary(bool isSpaceOrEnd) const;
    void popLastLatinChar();
    void acceptCompletion(const std::string& word);
    void reset();

    const std::string& latinRun() const { return latinRun_; }
    bool isLatinLocked() const { return latinLocked_; }
    bool hasPendingRun() const { return !latinRun_.empty(); }
    bool latinRunAlreadyRemembered() const { return alreadyRemembered_; }

private:
    void* shape_;
    std::string latinRun_;
    bool latinLocked_;
    bool alreadyRemembered_;
    void* lexicon_;

    static constexpr size_t kMinAmbiguousWordLength = 2;
};

bool IsAllAsciiLetters(const std::string& value);

}  // namespace McBopomofo::MixedScript
