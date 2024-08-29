#include <iostream>
#include "ConverterJSON.h"

using namespace std;

int main() {

    vector<std::string> text = ConverterJSON::GetRequests();
            //ConverterJSON::GetTextDocuments();

    if (!text.empty()) {
        for (int i = 0; i < text.size(); i++) {
            std::cout << i + 1 << ".\t" << text[i] /*<< "\n\n\n\n"*/ << std::endl;
        }
    } else
        std::cout << "It's empty" << std::endl;

    std::cout << ConverterJSON::GetResponsesLimit();


    return 0;
}
