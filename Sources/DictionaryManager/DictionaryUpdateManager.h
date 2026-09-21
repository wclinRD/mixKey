#pragma once

#include <string>
#include <vector>

class DictionaryUpdateManager {
public:
    // Builtin word lists
    static std::string builtinWordsPath();
    static std::string techSeedPath();
    
    // User learned words
    static std::string userWordsPath();
    static void ensureUserWordsFolder();
    
    // Update functions
    static bool checkForDictionaryUpdates();
    static void loadBuiltinWords();
    static void loadTechSeedWords();
    static void loadUserWords();
    
private:
    static std::vector<std::string> s_builtinWords;
    static std::vector<std::string> s_techSeedWords;
};
