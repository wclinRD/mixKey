/*
Copyright (c) 2026 and onwards The ChiaKey Authors.
Based on bopomix (MIT License).

Phrase awareness module that tracks English words typed in the middle of Chinese.
*/

#ifndef YKAFMixedScriptPhraseAware_h
#define YKAFMixedScriptPhraseAware_h

#if defined(__APPLE__)
#include <OpenVanilla/OpenVanilla.h>
#else
#include "OpenVanilla.h"
#endif

namespace OpenVanilla {

class YKAFMixedScriptPhraseAware : public OVAroundFilter {
 public:
  virtual const string localizedName(const string& locale) {
    return "Mixed Script Phrase Awareness";
  }

  virtual OVEventHandlingContext* createContext() {
    return new YKAFMixedScriptPhraseAwareContext(this);
  }

  virtual bool initialize(OVPathInfo* pathInfo, OVLoaderService* loaderService) {
    return true;
  }

  virtual const string identifier() const { return "YKAFMixedScriptPhraseAware"; }

  virtual int suggestedOrder() const { return -15000; }

  // Collect English words typed during Chinese composition
  virtual void collectEnglishRun(const std::string& englishWord) {
    m_recentEnglish.push_back(englishWord);
    if (m_recentEnglish.size() > 5) {
      m_recentEnglish.erase(m_recentEnglish.begin(),
                            m_recentEnglish.begin() + (m_recentEnglish.size() - 5));
    }
  }

 protected:
  std::vector<std::string> m_recentEnglish;
};

class YKAFMixedScriptPhraseAwareContext : public OVEventHandlingContext {
 public:
  YKAFMixedScriptPhraseAwareContext(YKAFMixedScriptPhraseAware* module) : m_module(module) {}

  virtual bool handleDirectText(const std::vector<std::string>& segments,
                                OVTextBuffer* readingText,
                                OVTextBuffer* composingText,
                                OVCandidateService* candidateService,
                                OVLoaderService* loaderService) {
    return false;
  }

  virtual bool handleKey(OVKey* key, OVTextBuffer* readingText,
                         OVTextBuffer* composingText,
                         OVCandidateService* candidateService,
                         OVLoaderService* loaderService) {
    return false;
  }

 protected:
  YKAFMixedScriptPhraseAware* m_module;
};

}  // namespace OpenVanilla

#endif
