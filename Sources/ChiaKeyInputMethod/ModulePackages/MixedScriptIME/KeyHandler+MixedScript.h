#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class KeyHandler;

@interface KeyHandler (MixedScript)

@property (nonatomic, readonly, getter=isMixedScriptEnabled) BOOL mixedScriptEnabled;
@property (nonatomic, readonly, getter=isLatinCompletionEnabled) BOOL latinCompletionEnabled;

- (BOOL)handleMixedScriptKey:(UniChar)charCode stateCallback:(void (^)(InputState *))stateCallback;
- (nullable InputStateChoosingCandidate *)buildLatinCompletionCandidateState;
- (void)acceptLatinCompletionWithValue:(NSString *)value;

@end

NS_ASSUME_NONNULL_END
