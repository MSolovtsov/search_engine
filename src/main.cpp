#include <iostream>
//
#include "ConverterJSON.h"
#include "SearchServer.h"

int main() {

    InvertedIndex idx;
    idx.UpdateDocumentBase(ConverterJSON::GetTextDocuments());
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(
            ConverterJSON::GetRequests(),
            ConverterJSON::GetResponsesLimit()
            );

    std::vector<std::vector<std::pair<int, float>>> buf;
    for (auto & i : result){
        std::vector<std::pair<int, float>> buf1;
        for (auto & j : i){
            int id = j.doc_id;
            float rank = j.rank;
            buf1.emplace_back(id, rank);
        }
        buf.push_back(buf1);
        buf1.clear();
    }
    ConverterJSON::putAnswers(buf);
    buf.clear();
    result.clear();

    return 0;
}
