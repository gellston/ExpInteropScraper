
//C++
#include "expInteropScrapper.h"
//C++/CLI
#include <msclr/marshal_cppstd.h>
//C#
using namespace SharpScrapperLib;


#pragma region Impl
namespace expInterop {
	class impl_expInteropScrapper {
	public:

#pragma region Private Property

		msclr::gcroot<SimpleScraper^> instance;
#pragma endregion
#pragma region Constructor
		impl_expInteropScrapper() : instance(gcnew SimpleScraper()) {
		}
#pragma endregion

#pragma region Destructor
		~impl_expInteropScrapper() {
			SimpleScraper^ scrapper = this->instance;
			if (scrapper != nullptr) {
				delete scrapper;
				this->instance = nullptr;
			}
		}
#pragma endregion
	};
}
#pragma endregion


#pragma region Constructor
expInterop::expInteropScrapper::expInteropScrapper() : impl(new impl_expInteropScrapper()){

}
#pragma endregion

#pragma region Destructor
expInterop::expInteropScrapper::~expInteropScrapper() {

}
#pragma endregion


#pragma region Public Functions
std::string expInterop::expInteropScrapper::getHtml(std::string address) {
	try {
		auto managedAddress = msclr::interop::marshal_as<System::String^>(address);
		auto managedHTML = this->impl->instance->GetHtml(managedAddress);

		return msclr::interop::marshal_as<std::string>(managedHTML);
	}
	catch (System::Exception^ ex) {
		throw std::exception(msclr::interop::marshal_as<std::string>(ex->Message).c_str());
	}
}
#pragma endregion


#pragma region Static Functions
expInterop::expInteropScrapper_ptr expInterop::expInteropScrapper::create() {
	try {
		return std::shared_ptr<expInterop::expInteropScrapper>(new expInterop::expInteropScrapper());
	}
	catch (System::Exception^ ex) {
		throw std::exception(msclr::interop::marshal_as<std::string>(ex->Message).c_str());
	}
}
#pragma endregion
