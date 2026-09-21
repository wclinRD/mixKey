/*
Copyright (c) 2026 and onwards The ChiaKey Authors.
Based on bopomix (MIT License).
*/

#include "MixedScriptIMEPackage.h"

using namespace OpenVanilla;

extern "C" OVEXPORT OVModulePackage* OVModulePackageMain() {
  return new MixedScriptIMEPackage;
}

extern "C" OVEXPORT unsigned int OVModulePackageFrameworkVersion() {
  return OVFrameworkInfo::Version();
}
