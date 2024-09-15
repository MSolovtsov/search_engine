#include <iostream>
//
#include "ConverterJSON.h"
#include "SearchServer.h"
//
#include <chrono>

// Основная программа
int main() {

    auto t_start = std::chrono::high_resolution_clock::now();

    // Заполняет vector текстом из файла
    InvertedIndex idx;
    idx.UpdateDocumentBase(ConverterJSON::GetTextDocuments());
    // Поиск
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(
            ConverterJSON::GetRequests(),
            ConverterJSON::GetResponsesLimit()
            );

    // Преобразуем результат в понятный answers.json формат
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
    // Заполняем answers.json
    ConverterJSON::putAnswers(buf);
    buf.clear();
    result.clear();

    auto t_end = std::chrono::high_resolution_clock::now();

    // Отображаем время работы программы
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout << "Run time: " << elapsed_time_ms << " ms" << std::endl;

    return 0;
}
