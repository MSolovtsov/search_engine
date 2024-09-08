#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"

using namespace std;

int main() {

    InvertedIndex index;
    vector<std::string> text = ConverterJSON::GetTextDocuments();
            //ConverterJSON::GetRequests();

    if (!text.empty()) {
        /*for (int i = 0; i < text.size(); i++) {
            std::cout << i + 1 << ".\t" << text[i] << "\n\n\n\n" << std::endl;
        }*/

        index.UpdateDocumentBase(text);
    } else
        std::cout << "It's empty" << std::endl;

    //std::cout << ConverterJSON::GetResponsesLimit();


    std::cout << "\n\n\n\n" << std::endl;
    std::vector<Entry> en_vec = index.GetWordCount("biba");

    for (int i = 0; i < en_vec.size(); i++){
        std::cout << "{" << en_vec[i].doc_id << ", " << en_vec[i].count << "}" << std::endl;
    }

    return 0;
}
