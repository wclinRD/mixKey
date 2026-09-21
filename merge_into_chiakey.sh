#!/bin/bash
# merge_into_chiakey.sh
# Script to integrate KeyMan mixed-script features into the ChiaKey repository.
# Run this from the root of the ChiaKey source tree.

set -e

CHIAKEY_ROOT="${1:-/tmp/ChiaKey-src}"
KEYMAN_ROOT="/Users/wclin/hermes/dev/KeyMan"

echo "=== KeyMan to ChiaKey Integration Script ==="
echo "ChiaKey root: $CHIAKEY_ROOT"
echo "KeyMan source: $KEYMAN_ROOT"

# 1. Create the MixedScriptIME module package directory in ChiaKey
MODULE_PKG="$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/MixedScriptIME"
mkdir -p "$MODULE_PKG"

# Copy Core C++ engine files
cp "$KEYMAN_ROOT/Sources/ChiaKeyCore/Engine/MixedScript/MixedScriptTracker.h" "$MODULE_PKG/MixedScriptTracker.h"
cp "$KEYMAN_ROOT/Sources/ChiaKeyCore/Engine/MixedScript/MixedScriptTracker.cpp" "$MODULE_PKG/MixedScriptTracker.cpp"
cp "$KEYMAN_ROOT/Sources/ChiaKeyCore/Engine/MixedScript/LatinPassthroughLM.h" "$MODULE_PKG/LatinPassthroughLM.h"
cp "$KEYMAN_ROOT/Sources/ChiaKeyCore/Engine/MixedScript/LatinPassthroughLM.cpp" "$MODULE_PKG/LatinPassthroughLM.cpp"

# Copy LanguageModel files
mkdir -p "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/LanguageModel"
cp "$KEYMAN_ROOT/Sources/ChiaKeyCore/LanguageModel/LanguageModelManager.h" "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/LanguageModel/LanguageModelManager.h"
cp "$KEYMAN_ROOT/Sources/ChiaKeyCore/LanguageModel/LanguageModelManager.cpp" "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/LanguageModel/LanguageModelManager.cpp"

# Copy YKAFPhraseAware extension
mkdir -p "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/YKAFMixedScriptPhraseAware"
cp "$KEYMAN_ROOT/Sources/YKAFPhraseAware/YKAFMixedScriptPhraseAware.h" "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/YKAFMixedScriptPhraseAware/YKAFMixedScriptPhraseAware.h"
cp "$KEYMAN_ROOT/Sources/YKAFPhraseAware/YKAFMixedScriptPhraseAware.cpp" "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/YKAFMixedScriptPhraseAware/YKAFMixedScriptPhraseAware.cpp"
cp "$KEYMAN_ROOT/Sources/YKAFPhraseAware/YKAFMixedScriptPhraseAwarePackage.h" "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/YKAFMixedScriptPhraseAware/YKAFMixedScriptPhraseAwarePackage.h"
cp "$KEYMAN_ROOT/Sources/YKAFPhraseAware/PackageMain.cpp" "$CHIAKEY_ROOT/ChiaKey-Source/ModulePackages/YKAFMixedScriptPhraseAware/PackageMain.cpp"

# Copy module package files
cp "$KEYMAN_ROOT/Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/MixedScriptIMEPackage.h" "$MODULE_PKG/MixedScriptIMEPackage.h"
cp "$KEYMAN_ROOT/Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/PackageMain.cpp" "$MODULE_PKG/PackageMain.cpp"
cp "$KEYMAN_ROOT/Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/MixedScriptIME-Info.plist" "$MODULE_PKG/MixedScriptIME-Info.plist"

# Copy UI and KeyHandler files
cp "$KEYMAN_ROOT/Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/LatinCompletionView.swift" "$MODULE_PKG/LatinCompletionView.swift"
cp "$KEYMAN_ROOT/Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/KeyHandler+MixedScript.h" "$MODULE_PKG/KeyHandler+MixedScript.h"
cp "$KEYMAN_ROOT/Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/KeyHandler+MixedScript.mm" "$MODULE_PKG/KeyHandler+MixedScript.mm"

# Copy preferences and dictionary manager
mkdir -p "$CHIAKEY_ROOT/ChiaKey-Source/Utilities/Preferences"
cp "$KEYMAN_ROOT/Sources/Preferences/Preferences.h" "$CHIAKEY_ROOT/ChiaKey-Source/Utilities/Preferences/Preferences.h"
cp "$KEYMAN_ROOT/Sources/Preferences/Preferences.cpp" "$CHIAKEY_ROOT/ChiaKey-Source/Utilities/Preferences/Preferences.cpp"

mkdir -p "$CHIAKEY_ROOT/ChiaKey-Source/Utilities/DictionaryManager"
cp "$KEYMAN_ROOT/Sources/DictionaryManager/DictionaryUpdateManager.h" "$CHIAKEY_ROOT/ChiaKey-Source/Utilities/DictionaryManager/DictionaryUpdateManager.h"
cp "$KEYMAN_ROOT/Sources/DictionaryManager/DictionaryUpdateManager.cpp" "$CHIAKEY_ROOT/ChiaKey-Source/Utilities/DictionaryManager/DictionaryUpdateManager.cpp"

# Copy Latin word lists
mkdir -p "$CHIAKEY_ROOT/ChiaKey-Source/Data/LatinWords"
cp "$KEYMAN_ROOT/Sources/Data/LatinWords/latin-words.txt" "$CHIAKEY_ROOT/ChiaKey-Source/Data/LatinWords/latin-words.txt"
cp "$KEYMAN_ROOT/Sources/Data/LatinWords/latin-tech-seed.txt" "$CHIAKEY_ROOT/ChiaKey-Source/Data/LatinWords/latin-tech-seed.txt"

echo "=== Integration complete ==="
echo "Files copied to: $MODULE_PKG and adjacent module directories"
echo "Next steps:"
echo "1. Add new modules to ChiaKey's module loader configuration"
echo "2. Merge KeyHandler+MixedScript.mm logic into the main KeyHandler"
echo "3. Update Xcode project to include new source files and modules"
echo "4. Build and test the integrated input method on macOS 13+ Apple Silicon"
