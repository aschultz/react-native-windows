// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

#include "I18nModule.h"

#include <winrt/Windows.ApplicationModel.Resources.Core.h>
#include <winrt/Windows.Globalization.h>
#include "Unicode.h"

namespace react {
namespace uwp {

/*static*/ I18nModule::I18nInfo I18nModule::GetI18nInfo() {
  std::string locale = "en-us";
  bool isRTL = false;

  auto langs = winrt::Windows::Globalization::ApplicationLanguages::Languages();
  if (langs.Size() > 0) {
    locale = Microsoft::Common::Unicode::Utf16ToUtf8(langs.GetAt(0));

    auto layoutDirection = winrt::Windows::ApplicationModel::Resources::Core::ResourceContext()
                               .GetForCurrentView()
                               .QualifierValues()
                               .Lookup(L"LayoutDirection");
    isRTL = layoutDirection != L"LTR";
  }

  return std::make_pair<std::string, bool>(std::move(locale), std::move(isRTL));
}

I18nModule::I18nModule(std::pair<std::string, bool> &&i18nInfo)
    : m_i18nInfo(std::move(i18nInfo)), m_isRTLForced(false), m_isRTLAllowed(true), m_swapLeftAndRightInRTL(false) {}

std::string I18nModule::getLocaleIdentifier() {
  return m_i18nInfo.first;
}

bool I18nModule::getIsRTL() {
  if (m_isRTLForced) {
    return true;
  }

  const bool isRTLPreferred = m_i18nInfo.second;
  if (m_isRTLAllowed && isRTLPreferred) {
    return true;
  }

  return false;
}

bool I18nModule::getIsRTLAllowed() {
  return m_isRTLAllowed;
}

bool I18nModule::getIsRTLForced() {
  return m_isRTLForced;
}

bool I18nModule::getIsLeftAndRightSwappedInRTL() {
  return m_swapLeftAndRightInRTL;
}

void I18nModule::allowRTL(bool allowRTL) {
  m_isRTLAllowed = allowRTL;
}
void I18nModule::forceRTL(bool forceRTL) {
  m_isRTLForced = forceRTL;
}
void I18nModule::swapLeftAndRightInRTL(bool flipStyles) {
  m_swapLeftAndRightInRTL = flipStyles;
}

} // namespace uwp
} // namespace react
