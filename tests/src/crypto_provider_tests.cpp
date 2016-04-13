//#include "utils.h"
//
//TEST(crypto_provider_case, installer_crypto_providers_test)
//{
//	auto providers = libcrypto::installed_crypto_providers();
//	EXPECT_TRUE(providers.size() > 0);
//
//	for (auto& provider : providers)
//	{
//		ASSERT_TRUE(provider != nullptr);
//
//		if (provider->type == libcrypto::CryptoProviderType::CRYPTO_API)
//		{
//			std::cout << *static_cast<libcrypto::CryptoApiProviderInfo*>(provider.get()) << std::endl;
//		}
//		else
//		{
//			std::cout << "Type: " << "Pkcs11Provider" << std::endl;
//			std::cout << *static_cast<libcrypto::Pkcs11ProviderInfo*>(provider.get()) << std::endl;
//		}
//	}
//}