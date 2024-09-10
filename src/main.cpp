#include <iostream>
//
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {

    /*InvertedIndex index;
    std::vector<std::string> text = ConverterJSON::GetTextDocuments();
            //ConverterJSON::GetRequests();

    if (!text.empty()) {
        for (int i = 0; i < text.size(); i++) {
            std::cout << i + 1 << ".\t" << text[i] << "\n\n\n\n" << std::endl;
        }

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
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.666666687},
                    {1, 0.666666687},
                    {2, 0.666666687}
            }
    };

    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);
    srv.search(request);



    return 0;
}
