#include "YKAFMixedScriptPhraseAwarePackage.h"

using namespace OpenVanilla;

extern "C" OVEXPORT OVModulePackage* OVModulePackageMain() {
  return new YKAFMixedScriptPhraseAwarePackage;
}

extern "C" OVEXPORT unsigned int OVModulePackageFrameworkVersion() {
  return OVFrameworkInfo::Version();
}
