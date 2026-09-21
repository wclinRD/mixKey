#include "Preferences.h"
#include <NSUserDefaults.h>

namespace ChiaKeyPreferences {
    bool mixedScriptEnabled = true;
    bool latinCompletionEnabled = true;
    bool latinLearnTypedWords = true;
    bool mixedScriptLatinOnSpaceForUserWords = true;

    void loadPreferences() {
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        mixedScriptEnabled = [defaults boolForKey:@"MixedScriptEnabled"];
        latinCompletionEnabled = [defaults boolForKey:@"LatinCompletionEnabled"];
        latinLearnTypedWords = [defaults boolForKey:@"LatinLearnTypedWords"];
        mixedScriptLatinOnSpaceForUserWords = [defaults boolForKey:@"MixedScriptLatinOnSpaceForUserWords"];
    }
}
