/*
Copyright (c) 2026 and onwards The ChiaKey Authors.
Based on bopomix (MIT License).

OpenVanilla module package for mixed-script (中英混打) input method extension.
*/

#ifndef MixedScriptIMEPackage_h
#define MixedScriptIMEPackage_h

#if defined(__APPLE__)
#include <OpenVanilla/OpenVanilla.h>
#else
#include "OpenVanilla.h"
#endif

#include "MixedScriptIME.h"

namespace OpenVanilla {

class MixedScriptIMEPackage : public OVModulePackage {
 public:
  MixedScriptIMEPackage() {
    m_moduleVector.push_back(new OVModuleClassWrapper<MixedScriptIME>);
  }

  virtual bool initialize(OVPathInfo*, OVLoaderService* loaderService) {
    loaderService->logger("MixedScriptIMEPackage") << "Initialized" << endl;
    return true;
  }
};

};  // namespace OpenVanilla

#endif
