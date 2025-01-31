/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/resources/behavioral/multi_armed_bandits/epsilon_greedy_bandit_resource.h"

#include <memory>

#include "base/strings/strcat.h"
#include "brave/components/brave_ads/common/pref_names.h"
#include "brave/components/brave_ads/core/internal/ads/ad_unittest_util.h"
#include "brave/components/brave_ads/core/internal/catalog/catalog.h"
#include "brave/components/brave_ads/core/internal/catalog/catalog_url_request_builder_util.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "brave/components/brave_ads/core/internal/common/unittest/unittest_mock_util.h"
#include "net/http/http_status_code.h"

// npm run test -- brave_unit_tests --filter=BraveAds*

namespace brave_ads {

class BraveAdsEpsilonGreedyBanditResourceTest : public UnitTestBase {
 protected:
  void SetUp() override {
    UnitTestBase::SetUp();

    catalog_ = std::make_unique<Catalog>();
    resource_ = std::make_unique<EpsilonGreedyBanditResource>(*catalog_);
  }

  void LoadResource(const std::string& catalog) {
    const URLResponseMap url_responses = {
        {BuildCatalogUrlPath(),
         {{net::HTTP_OK,
           /*response_body*/ base::StrCat({"/", catalog})}}}};
    MockUrlResponses(ads_client_mock_, url_responses);

    NotifyDidInitializeAds();
  }

  std::unique_ptr<Catalog> catalog_;
  std::unique_ptr<EpsilonGreedyBanditResource> resource_;
};

TEST_F(BraveAdsEpsilonGreedyBanditResourceTest, IsNotInitialized) {
  // Arrange

  // Act

  // Assert
  EXPECT_FALSE(resource_->IsInitialized());
}

TEST_F(BraveAdsEpsilonGreedyBanditResourceTest,
       LoadResourceIfBravePrivateAdsAndBraveNewsAdsAreEnabled) {
  // Arrange

  // Act
  LoadResource("catalog.json");

  // Assert
  EXPECT_TRUE(resource_->IsInitialized());
}

TEST_F(BraveAdsEpsilonGreedyBanditResourceTest,
       LoadResourceIfBravePrivateAdsAreDisabledAndBraveNewsAdsAreEnabled) {
  // Arrange
  DisableBravePrivateAds();

  // Act
  LoadResource("catalog.json");

  // Assert
  EXPECT_TRUE(resource_->IsInitialized());
}

TEST_F(BraveAdsEpsilonGreedyBanditResourceTest,
       LoadResourceIfBravePrivateAdsAreEnabledAndBraveNewsAdsAreDisabled) {
  // Arrange
  DisableBraveNewsAds();

  // Act
  LoadResource("catalog.json");

  // Assert
  EXPECT_TRUE(resource_->IsInitialized());
}

TEST_F(BraveAdsEpsilonGreedyBanditResourceTest, LoadResourceIfEmptyCatalog) {
  // Arrange

  // Act
  LoadResource("empty_catalog.json");

  // Assert
  EXPECT_TRUE(resource_->IsInitialized());
}

TEST_F(BraveAdsEpsilonGreedyBanditResourceTest,
       DoNotLoadResourceIfBravePrivateAdsAndBraveNewsAdsAreDisabled) {
  // Arrange
  DisableBravePrivateAds();
  DisableBraveNewsAds();

  // Act
  LoadResource("catalog.json");

  // Assert
  EXPECT_FALSE(resource_->IsInitialized());
}

TEST_F(
    BraveAdsEpsilonGreedyBanditResourceTest,
    ResetResourceWhenEnabledPrefDidChangeIfBravePrivateAdsAndBraveNewsAdsAreDisabled) {
  // Arrange
  LoadResource("catalog.json");

  DisableBravePrivateAds();
  DisableBraveNewsAds();

  // Act
  NotifyPrefDidChange(prefs::kEnabled);

  // Assert
  EXPECT_FALSE(resource_->IsInitialized());
}

TEST_F(
    BraveAdsEpsilonGreedyBanditResourceTest,
    DoNotResetResourceWhenEnabledPrefDidChangeIfBravePrivateAdsOrBraveNewsAdsAreEnabled) {
  // Arrange
  LoadResource("catalog.json");

  // Act
  NotifyPrefDidChange(prefs::kEnabled);

  // Assert
  EXPECT_TRUE(resource_->IsInitialized());
}

}  // namespace brave_ads
