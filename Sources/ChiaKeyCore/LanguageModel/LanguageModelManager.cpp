#include "LanguageModelManager.h"
#include <filesystem>

std::string LanguageModelManager::latinUserWordListPath() {
    return std::string("~/Library/Application Support/ChiaKey/latin-user.txt");
}

void LanguageModelManager::ensureLatinUserWordListFolder() {
    std::filesystem::create_directories("~/Library/Application Support/ChiaKey");
}

void LanguageModelManager::reloadLatinUserWordList() {
    // Reload logic would go here
}
