/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_PRIVACY_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_UNITTEST_UTIL_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_PRIVACY_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_UNITTEST_UTIL_H_

#include <vector>

namespace ads::privacy::cbr {

class SignedToken;

SignedToken GetSignedToken();
std::vector<SignedToken> GetSignedTokens();

SignedToken GetInvalidSignedToken();
std::vector<SignedToken> GetInvalidSignedTokens();

}  // namespace ads::privacy::cbr

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_PRIVACY_CHALLENGE_BYPASS_RISTRETTO_SIGNED_TOKEN_UNITTEST_UTIL_H_
