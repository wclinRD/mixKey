#pragma once

#include <string>

namespace McBopomofo::MixedScript {
class LatinLexicon;
}

class LanguageModelManager {
public:
    static void ensureLatinUserWordListFolder();
    static std::string latinUserWordListPath();
    static void reloadLatinUserWordList();
};
