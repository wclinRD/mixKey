#!/bin/bash
# test_mixed_script.sh
# Test cases for the mixed-script integration.

echo "=== Mixed Script Integration Tests ==="

# Test 1: Basic ASCII letter handling
echo "Test 1: ASCII letter keys should be tracked by MixedScriptTracker..."
# This would require a C++ test binary or Objective-C test target.

# Test 2: Prediction tooltip at 4 letters
echo "Test 2: Type 'iss' + 1 more letter -> tooltip should appear..."

# Test 3: Tab completion
echo "Test 3: Press Tab -> accept top completion..."

# Test 4: User lexicon persistence
echo "Test 4: Completed words should be written to latin-user.txt..."
USER_WORDS="~/Library/Application Support/ChiaKey/latin-user.txt"
if [ -f "$USER_WORDS" ]; then
    echo "  User words file exists: $USER_WORDS"
    cat "$USER_WORDS"
else
    echo "  User words file not found (expected until first completion)."
fi

# Test 5: Preference toggles
echo "Test 5: Verify defaults..."
defaults read com.chiakey.ChiaKey MixedScriptEnabled 2>/dev/null || echo "  MixedScriptEnabled not set (using default YES)."
defaults read com.chiakey.ChiaKey LatinCompletionEnabled 2>/dev/null || echo "  LatinCompletionEnabled not set (using default YES)."

echo "=== Manual UI tests required ==="
echo "1. Open any text field, switch to ChiaKey input method."
echo "2. Type Chinese characters, then English letters without switching."
echo "3. Verify the candidate window shows English predictions."
echo "4. Press Tab to accept, Shift+Tab for multiple options."
