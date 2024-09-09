#include <iostream>
//
#include "ConverterJSON.h"
#include "InvertedIndex.h"

int main() {

    InvertedIndex index;
   /* std::vector<std::string> text = ConverterJSON::GetTextDocuments();
            //ConverterJSON::GetRequests();

    if (!text.empty()) {
        *//*for (int i = 0; i < text.size(); i++) {
            std::cout << i + 1 << ".\t" << text[i] << "\n\n\n\n" << std::endl;
        }*//*

        index.UpdateDocumentBase(text);
    } else
        std::cout << "It's empty" << std::endl;

    //std::cout << ConverterJSON::GetResponsesLimit();


    std::cout << "\n\n\n\n" << std::endl;
    std::vector<Entry> en_vec = index.GetWordCount("biba");

    for (auto & i : en_vec){
        std::cout << "{" << i.doc_id << ", " << i.count << "}" << std::endl;
    }*/


    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
    const std::vector<std::vector<Entry>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            }, {
                    {0, 2}, {1, 2}, {2, 5}
            }, {
                    {3, 1}
            }
    };
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    for (int i = 0; i < result.size(); i++){
        for (int j = 0; j < result[i].size(); j++){
            std::cout << "{" << result[i][j].doc_id << ", " << result[i][j].count << "} ";
        }
        std::cout  << std::endl;
    }
    return 0;
}
