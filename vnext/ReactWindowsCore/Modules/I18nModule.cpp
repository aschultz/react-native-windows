// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "I18nModule.h"

namespace react {
namespace windows {

I18nModule::I18nModule(std::unique_ptr<II18nModule> module) : m_module(std::move(module)) {}

std::string I18nModule::getName() {
  return "I18nManager";
}

std::map<std::string, folly::dynamic> I18nModule::getConstants() {
  return {{"localeIdentifier", folly::dynamic{m_module->getLocaleIdentifier()}},
          {"isRTL", folly::dynamic{m_module->getIsRTL()}}};
}

std::vector<facebook::xplat::module::CxxModule::Method> I18nModule::getMethods() {
  return {Method(
              "allowRTL",
              [this](folly::dynamic args) {
                if (args.size() > 0 && args[0].isBool()) {
                  m_module->allowRTL(args[0].asBool());
                }
              }),
          Method(
              "forceRTL",
              [this](folly::dynamic args) {
                if (args.size() > 0 && args[0].isBool()) {
                  m_module->forceRTL(args[0].asBool());
                }
              }),
          Method("swapLeftAndRightInRTL", [this](folly::dynamic args) {
            if (args.size() > 0 && args[0].isBool()) {
              m_module->swapLeftAndRightInRTL(args[0].asBool());
            }
          })};
}

std::unique_ptr<facebook::xplat::module::CxxModule> createI18nModule(std::unique_ptr<II18nModule> module) {
  return std::make_unique<I18nModule>(std::move(module));
}

} // namespace windows
} // namespace react
