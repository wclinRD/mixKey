#pragma once

#include <string>

namespace ChiaKeyPreferences {
    // Mixed script features
    extern bool mixedScriptEnabled;
    extern bool latinCompletionEnabled;
    extern bool latinLearnTypedWords;
    extern bool mixedScriptLatinOnSpaceForUserWords;
    
    // Load preferences from NSUserDefaults
    void loadPreferences();
    
    // Commands for defaults write:
    // defaults write com.chiakey.ChiaKey MixedScriptEnabled -bool false
    // defaults write com.chiakey.ChiaKey LatinCompletionEnabled -bool false
    // defaults write com.chiakey.ChiaKey LatinLearnTypedWords -bool false
    // defaults write com.chiakey.ChiaKey MixedScriptLatinOnSpaceForUserWords -bool false
}
