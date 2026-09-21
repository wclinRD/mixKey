#ifndef YKAFMixedScriptPhraseAwarePackage_h
#define YKAFMixedScriptPhraseAwarePackage_h

#if defined(__APPLE__)
#include <OpenVanilla/OpenVanilla.h>
#else
#include "OpenVanilla.h"
#endif

#include "YKAFMixedScriptPhraseAware.h"

namespace OpenVanilla {

class YKAFMixedScriptPhraseAwarePackage : public OVModulePackage {
 public:
  YKAFMixedScriptPhraseAwarePackage() {
    m_moduleVector.push_back(new OVModuleClassWrapper<YKAFMixedScriptPhraseAware>);
  }

  virtual bool initialize(OVPathInfo*, OVLoaderService* loaderService) {
    loaderService->logger("YKAFMixedScriptPhraseAwarePackage") << "Initialized" << endl;
    return true;
  }
};

}  // namespace OpenVanilla

#endif
