//#include "utils.h"
//#include <tuple>
//
//#ifdef _WIN32
//
//class CryptoApiProvidersTest : public ::testing::TestWithParam<std::tuple<DWORD, std::string>>
//{
//protected:
//	virtual void SetUp()
//	{
//		auto& param = GetParam();
//		auto name = std::get<1>(param);
//		provider_ = std::make_unique<libcrypto::CryptoApiCryptoProvider>(std::get<0>(param), std::move(name));
//	}
//
//	std::unique_ptr<libcrypto::CryptoApiCryptoProvider> provider_;
//};
//
//TEST_P(CryptoApiProvidersTest, created)
//{
//	ASSERT_TRUE(provider_ != nullptr);
//}
//
//TEST_P(CryptoApiProvidersTest, supported_algorithms_test)
//{
//	auto algorithms = provider_->supported_algorithms();
//	EXPECT_TRUE(algorithms.size() > 0);
//
//	for (const auto& algorithm : algorithms)
//	{
//		std::cout << algorithm << std::endl;
//	}
//}
//
//INSTANTIATE_TEST_CASE_P(CryptoProvider, CryptoApiProvidersTest, ::testing::Values(
//	std::make_tuple<DWORD, std::string>(75, "Crypto-Pro GOST R 34.10-2001 Cryptographic Service Provider")));
//
//TEST(crypto_api_provider_case, installed_crypto_providers)
//{
//	auto providers = libcrypto::CryptoApiCryptoProvider::installed_crypto_providers();
//	EXPECT_TRUE(providers.size() > 0);
//
//	for (const auto& provider : providers)
//	{
//		std::cout << *provider << std::endl;
//	}
//}
//
//
//#endif