#include "DictionaryUpdateManager.h"
#include <fstream>
#include <filesystem>

std::vector<std::string> DictionaryUpdateManager::s_builtinWords;
std::vector<std::string> DictionaryUpdateManager::s_techSeedWords;

std::string DictionaryUpdateManager::builtinWordsPath() {
    return "~/Library/Application Support/ChiaKey/Resources/latin-words.txt";
}

std::string DictionaryUpdateManager::techSeedPath() {
    return "~/Library/Application Support/ChiaKey/Resources/latin-tech-seed.txt";
}

std::string DictionaryUpdateManager::userWordsPath() {
    return "~/Library/Application Support/ChiaKey/latin-user.txt";
}

void DictionaryUpdateManager::ensureUserWordsFolder() {
    std::filesystem::create_directories("~/Library/Application Support/ChiaKey");
    std::filesystem::create_directories("~/Library/Application Support/ChiaKey/Resources");
}

bool DictionaryUpdateManager::checkForDictionaryUpdates() {
    // Check for updates from GitHub releases
    // This would fetch the latest latin-words.txt and latin-tech-seed.txt
    // from https://github.com/lmanchu/bopomix/releases or similar source
    return true;
}

void DictionaryUpdateManager::loadBuiltinWords() {
    std::ifstream file(builtinWordsPath());
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            s_builtinWords.push_back(line);
        }
    }
}

void DictionaryUpdateManager::loadTechSeedWords() {
    std::ifstream file(techSeedPath());
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            s_techSeedWords.push_back(line);
        }
    }
}

void DictionaryUpdateManager::loadUserWords() {
    std::ifstream file(userWordsPath());
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            // Add to user lexicon
        }
    }
}
