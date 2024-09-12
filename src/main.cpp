#include <iostream>
//
#include "ConverterJSON.h"
#include "SearchServer.h"

int main() {

    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> request = {"milk water", "sugar"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.8},
                    {1, 0.2}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request, ConverterJSON::GetResponsesLimit());

    std::vector<std::vector<std::pair<int, float>>> buf;

    for (int i = 0; i < result.size(); i++){
        std::vector<std::pair<int, float>> buf1;
        for (int j = 0; j < result[i].size(); j++){
            int id = result[i][j].doc_id;
            float rank = result[i][j].rank;
            buf1.push_back(std::make_pair(id, rank));
        }
        buf.push_back(buf1);
    }
    ConverterJSON::putAnswers(buf);



    return 0;
}
