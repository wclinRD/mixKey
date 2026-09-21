# KeyMan to ChiaKey Integration Guide

This document describes how to integrate the KeyMan mixed-script features into the actual ChiaKey repository.

## Step 1: Copy Module Files

Run the merge script from the ChiaKey repository root:

```bash
./merge_into_chiakey.sh /path/to/ChiaKey-source
```

This copies all KeyMan files into the appropriate OpenVanilla module package directories.

## Step 2: Register Modules in ChiaKey Loader

In ChiaKey's module loader configuration (typically in `ChiaKey-Source/Loaders/` or the main input method bundle), add the new modules:

1. `MixedScriptIME` — Main mixed-script input method module
2. `YKAFMixedScriptPhraseAware` — Phrase awareness for English runs

Example module registration (pseudo-code for OpenVanilla):

```cpp
// In the main module package initializer:
m_moduleVector.push_back(new OVModuleClassWrapper<MixedScriptIME>);
m_moduleVector.push_back(new OVModuleClassWrapper<YKAFMixedScriptPhraseAware>);
```

## Step 3: Merge KeyHandler Logic

The `KeyHandler+MixedScript.mm` file contains the mixed-script key handling logic. To integrate:

1. Open `ChiaKey-Source/.../KeyHandler.mm` (the main key handler for ChiaKey).
2. Add the mixed-script state tracker instance:
   ```cpp
   McBopomofo::MixedScript::MixedScriptTracker* _mixedScriptTracker;
   ```
3. In the key handling method, add the mixed-script decision logic:
   - Check if the key is a lowercase ASCII letter.
   - Feed the key to `_mixedScriptTracker->feedKey()`.
   - If `Verdict::kLatin`, treat the key as English pass-through.
   - If `Verdict::kAmbiguous`, offer the English word as a candidate.
4. Handle Tab and Shift+Tab for completion acceptance.

## Step 4: Update Preferences

Add the following defaults to ChiaKey's preferences system:

```objc
// In Preferences.m or equivalent:
[[NSUserDefaults standardUserDefaults] registerDefaults:@{
    @"MixedScriptEnabled": @YES,
    @"LatinCompletionEnabled": @YES,
    @"LatinLearnTypedWords": @YES,
    @"MixedScriptLatinOnSpaceForUserWords": @YES
}];
```

## Step 5: Update Xcode Project

Add the new source files to the Xcode project:

1. `ModulePackages/MixedScriptIME/` — All mixed-script module files
2. `ModulePackages/YKAFMixedScriptPhraseAware/` — Phrase awareness module
3. `Utilities/Preferences/` — Preferences system
4. `Utilities/DictionaryManager/` — Dictionary update manager
5. `Data/LatinWords/` — Latin word lists

## Step 6: Build and Test

Build requirements:
- macOS 13+
- Apple Silicon (M1/M2/M3)
- Modern Xcode (15+)

Test cases:
1. Type Chinese, then switch to English letters mid-sentence (e.g., "我在 slack 上看到").
2. Type 4+ English letters to see prediction tooltip.
3. Press Tab to accept completion.
4. Press Shift+Tab to see multiple completions.
5. Verify `latin-user.txt` is created and updated with learned words.
6. Test preference toggles via `defaults write`.

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

## License Considerations

- bopomix mixed-script code: MIT License
- ChiaKey: BSD 3-Clause "New" or "Revised" License
- Ensure proper attribution in the integrated code headers.
