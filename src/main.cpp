#include <iostream>
#include "ConverterJSON.h"

using namespace std;

int main() {

    vector<std::string> text = ConverterJSON::GetTextDocuments();
    if (!text.empty()) {
        for (int i = 0; i < 10; i++) {
            std::cout << i + 1 << ".\t" << text[i] << "\n\n\n\n" << std::endl;
        }
    }


    return 0;
}
