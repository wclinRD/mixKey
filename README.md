# KeyMan - ChiaKey Mixed Script Extension

This project integrates bopomix's mixed-script (中英混打) features into the ChiaKey input method.

## Features

### 1. Mixed Script Typing (中英混打)
- Type English in the middle of Chinese without switching input methods
- When letters cannot form Zhuyin (e.g., `th`, `acer`), the input method treats them as English
- Tab completion for English words: type 4 letters to see predictions, press Tab to complete

### 2. User Latin Lexicon
- Learned English words are stored in `~/Library/Application Support/ChiaKey/latin-user.txt`
- One word per line, editable manually
- Words are learned only after being submitted (not while typing)

### 3. Preferences
All features are enabled by default. To disable in Terminal:

| Feature | Command |
|---|---|
| Disable mixed typing (all) | `defaults write com.chiakey.ChiaKey MixedScriptEnabled -bool false` |
| Disable Latin prediction & Tab completion | `defaults write com.chiakey.ChiaKey LatinCompletionEnabled -bool false` |
| Disable learning from typed English | `defaults write com.chiakey.ChiaKey LatinLearnTypedWords -bool false` |
| Disable auto-English on space for user words | `defaults write com.chiakey.ChiaKey MixedScriptLatinOnSpaceForUserWords -bool false` |

## File Structure

```
KeyMan/
├── Sources/
│   ├── ChiaKeyCore/
│   │   └── Engine/MixedScript/
│   │       ├── MixedScriptTracker.{h,cpp}
│   │       └── LatinPassthroughLM.{h,cpp}
│   ├── ChiaKeyInputMethod/
│   │   └── ModulePackages/MixedScriptIME/
│   │       ├── MixedScriptIME.h/m
│   │       └── LatinCompletionView.swift
│   └── Data/LatinWords/
│       ├── latin-words.txt (builtin dictionary)
│       └── latin-tech-seed.txt (tech seed words)
└── Tests/MixedScriptTests/
```

## License

The mixed script implementation is based on [bopomix](https://github.com/lmanchu/bopomix) which is licensed under the MIT License.
