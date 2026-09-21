# AGENTS.md - Project Handover File

## Project Overview

**Project Name**: KeyMan - ChiaKey Mixed Script Extension  
**Purpose**: Integrate bopomix's mixed-script (中英混打) features into the ChiaKey input method.  
**Repository**: `https://github.com/wclinRD/mixKey`

---

## Changes Made

### 1. Core C++ Engine Implementation

#### MixedScriptTracker (`Sources/ChiaKeyCore/Engine/MixedScript/MixedScriptTracker.{h,cpp}`)
- Implements the mixed-script state machine with three rules:
  - **Rule A**: Structural dead Bopomofo shape → English pass-through
  - **Rule B**: Dictionary word with Bopomofo shape → Offer English as second-row candidate
  - **Rule C**: User's own lexicon + space/Enter → Promote to English automatically
- State tracking for pending Latin runs, locked Latin state, and completion acceptance.

#### LatinPassthroughLM (`Sources/ChiaKeyCore/Engine/MixedScript/LatinPassthroughLM.{h,cpp}`)
- English prediction and candidate word management.
- Handles tooltip generation, Tab completion, and Shift+Tab multiple completions.
- Score-based ranking for user-learned words vs. dictionary words.

### 2. Language Model Integration

#### LanguageModelManager (`Sources/ChiaKeyCore/LanguageModel/LanguageModelManager.{h,cpp}`)
- Manages user lexicon file paths: `~/Library/Application Support/ChiaKey/latin-user.txt`.
- Provides folder creation and word list persistence logic.

### 3. OpenVanilla Module Packages

#### MixedScriptIME (`Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/`)
- `MixedScriptIME.{h,m}` — OpenVanilla `OVInputMethod` implementation.
- `MixedScriptIMEPackage.h` / `PackageMain.cpp` — Module package registration via `OVModulePackageMain()`.
- `MixedScriptIME-Info.plist` — macOS InputMethodKit bundle configuration.

#### YKAFMixedScriptPhraseAware (`Sources/YKAFPhraseAware/`)
- `YKAFMixedScriptPhraseAware.{h,cpp}` — Phrase awareness module tracking English runs during Chinese composition.
- `YKAFMixedScriptPhraseAwarePackage.h` / `PackageMain.cpp` — Module package wrapper.

### 4. UI and KeyHandler Extension

#### LatinCompletionView (`Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/LatinCompletionView.swift`)
- SwiftUI candidate window for English predictions.
- Displays up to `Preferences.candidateKeys.length` completions.

#### KeyHandler+MixedScript (`Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/KeyHandler+MixedScript.{h,mm}`)
- Extension for the main KeyHandler to handle mixed-script key events.
- Integrates with OpenVanilla's `OVInputMethod` context.

### 5. Preferences System (`Sources/Preferences/Preferences.{h,cpp}`)

Supports the following `defaults write` commands:

| Feature | Command |
|---|---|
| Disable mixed typing (all) | `defaults write com.chiakey.ChiaKey MixedScriptEnabled -bool false` |
| Disable Latin prediction & Tab completion | `defaults write com.chiakey.ChiaKey LatinCompletionEnabled -bool false` |
| Disable learning from typed English | `defaults write com.chiakey.ChiaKey LatinLearnTypedWords -bool false` |
| Disable auto-English on space for user words | `defaults write com.chiakey.ChiaKey MixedScriptLatinOnSpaceForUserWords -bool false` |

### 6. Dictionary Update Mechanism (`Sources/DictionaryManager/DictionaryUpdateManager.{h,cpp}`)

- Handles builtin word lists (`latin-words.txt`, ~204k+ common English words).
- Handles tech seed words (`latin-tech-seed.txt`, high-priority tech terms).
- Handles user learned words (`latin-user.txt`, one per line).
- Provides update check interface for GitHub releases integration.

### 7. Xcode Project Configuration (`KeyMan.xcodeproj/project.pbxproj`)

- C++17, Swift 5.0 support.
- Debug/Release build configurations.
- Static library target `KeyManCore`.

### 8. Integration Scripts

- `merge_into_chiakey.sh` — Script to copy KeyMan files into the ChiaKey source tree.
- `test_mixed_script.sh` — Test script for mixed-script functionality.
- `INTEGRATION_GUIDE.md` — Detailed integration guide.

---

## Next Steps (Manual Confirmation/Execution Required)

### 1. Update ChiaKey Xcode Project

**Task**: Add new module files to `Takao.xcodeproj/project.pbxproj` build phases.

**Details**:
- Locate the ChiaKey Xcode project: `ChiaKey-Source/Takao.xcodeproj/project.pbxproj`.
- Add the following files to the appropriate build phases:
  - `ModulePackages/MixedScriptIME/MixedScriptTracker.{h,cpp}`
  - `ModulePackages/MixedScriptIME/LatinPassthroughLM.{h,cpp}`
  - `ModulePackages/MixedScriptIME/MixedScriptIMEPackage.h`
  - `ModulePackages/MixedScriptIME/PackageMain.cpp`
  - `ModulePackages/YKAFMixedScriptPhraseAware/YKAFMixedScriptPhraseAware.{h,cpp}`
  - `ModulePackages/YKAFMixedScriptPhraseAware/YKAFMixedScriptPhraseAwarePackage.h`
  - `ModulePackages/YKAFMixedScriptPhraseAware/PackageMain.cpp`
  - `Utilities/Preferences/Preferences.{h,cpp}`
  - `Utilities/DictionaryManager/DictionaryUpdateManager.{h,cpp}`
  - `Data/LatinWords/latin-words.txt`, `latin-tech-seed.txt`

**Verification**: Ensure the Xcode project compiles without missing file errors.

### 2. Merge KeyHandler Logic

**Task**: Merge `KeyHandler+MixedScript.mm` processing logic into ChiaKey's main KeyHandler.

**Details**:
- Locate ChiaKey's main KeyHandler (typically in the input method module or framework).
- Add the mixed-script state tracker instance:
  ```cpp
  McBopomofo::MixedScript::MixedScriptTracker* _mixedScriptTracker;
  ```
- In the key handling method, add mixed-script decision logic:
  - Check if the key is a lowercase ASCII letter.
  - Feed the key to `_mixedScriptTracker->feedKey()`.
  - If `Verdict::kLatin`, treat the key as English pass-through.
  - If `Verdict::kAmbiguous`, offer the English word as a candidate.
- Handle Tab and Shift+Tab for completion acceptance.

**Verification**: Test that English letters typed during Chinese composition are correctly recognized and completed.

### 3. Preferences Integration

**Task**: Add `Preferences.{h,cpp}` to ChiaKey's preference system.

**Details**:
- Integrate the four preference keys into ChiaKey's `NSUserDefaults` setup:
  - `MixedScriptEnabled` (default: YES)
  - `LatinCompletionEnabled` (default: YES)
  - `LatinLearnTypedWords` (default: YES)
  - `MixedScriptLatinOnSpaceForUserWords` (default: YES)
- Ensure the preferences are readable/writable via `defaults write` commands.

**Verification**: Toggle each preference and verify the mixed-script behavior changes accordingly.

### 4. Build and Test on macOS 13+ Apple Silicon

**Task**: Build the integrated input method and test mixed-script functionality.

**Requirements**:
- macOS 13+
- Apple Silicon (M1/M2/M3)
- Modern Xcode (15+)

**Test Cases**:
1. Type Chinese, then switch to English letters mid-sentence (e.g., "我在 slack 上看到").
2. Type 4+ English letters to see prediction tooltip.
3. Press Tab to accept the top completion.
4. Press Shift+Tab to see multiple completions.
5. Verify `latin-user.txt` is created and updated with learned words.
6. Test preference toggles via `defaults write`.

**Expected Behavior**:
- English letters should be tracked by `MixedScriptTracker`.
- Prediction tooltip should appear at 4+ letters.
- Tab completion should accept the top word and write it to `latin-user.txt`.
- User words should persist across input method switches.

---

## File Mapping Summary

| KeyMan File | ChiaKey Target |
|---|---|
| `Sources/ChiaKeyCore/Engine/MixedScript/*` | `ModulePackages/MixedScriptIME/MixedScriptTracker.*`, `LatinPassthroughLM.*` |
| `Sources/ChiaKeyCore/LanguageModel/*` | `ModulePackages/LanguageModel/LanguageModelManager.*` |
| `Sources/YKAFPhraseAware/*` | `ModulePackages/YKAFMixedScriptPhraseAware/*` |
| `Sources/ChiaKeyInputMethod/ModulePackages/MixedScriptIME/*` | `ModulePackages/MixedScriptIME/*` |
| `Sources/Preferences/*` | `Utilities/Preferences/*` |
| `Sources/DictionaryManager/*` | `Utilities/DictionaryManager/*` |
| `Sources/Data/LatinWords/*` | `Data/LatinWords/*` |

---

## License Considerations

- bopomix mixed-script code: **MIT License**
- ChiaKey: **BSD 3-Clause "New" or "Revised" License**
- Ensure proper attribution in the integrated code headers.

---

## Contact / Notes

This handover file documents the current state of the KeyMan project and the required next steps for full integration into the ChiaKey repository. Any questions or clarifications regarding the implementation should refer to this document or the source code in the `mixKey` repository.
