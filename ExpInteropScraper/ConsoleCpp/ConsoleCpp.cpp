#include <iostream>
#include <expInteropScrapper.h>

void main()
{
    try {
        auto scrapper = expInterop::expInteropScrapper::create();
        auto html_content = scrapper->getHtml("https://www.naver.com");
        std::cout << html_content << std::endl;

    }
    catch (std::exception ex) {

    }
    

}
