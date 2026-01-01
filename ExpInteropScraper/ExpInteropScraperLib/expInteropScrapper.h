#pragma once

#include <memory>
#include <string>

#include "expInteropScrapper_api.h"


namespace expInterop {
	class impl_expInteropScrapper;
	class expInteropScrapper;
	using expInteropScrapper_ptr = std::shared_ptr<expInteropScrapper>;
	class expInteropScrapper {
	private:

#pragma region Private Property
		std::unique_ptr< impl_expInteropScrapper> impl;
#pragma endregion

		
#pragma region Constructor
		ExpInteropAPI expInteropScrapper();
#pragma endregion

	public:

#pragma region Destructor
		ExpInteropAPI ~expInteropScrapper();
#pragma endregion


#pragma region Public Functions
		ExpInteropAPI std::string getHtml(std::string address);
#pragma endregion

#pragma region Static Functions
		ExpInteropAPI static expInteropScrapper_ptr create();
#pragma endregion

	};
}