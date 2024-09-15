//
// Created by mikha on 09.09.2024.
//

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H
//
#pragma once
//
#include <map>
#include <thread>
#include <mutex>
//
#include "InvertedIndex.h"


struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:

    /* @param idx в конструктор класса передаётся ссылка на класс
    InvertedIndex, чтобы SearchServer мог узнать частоту слов встречаемых в запросе */
    explicit SearchServer(InvertedIndex& idx) : _index(idx){ };

    /* Метод обработки поисковых запросов
    * @param queries_input поисковые запросы взятые из файла requests.json
    * @return возвращает отсортированный список релевантных ответов для заданных запросов */
    std::vector<std::vector<RelativeIndex>> search(
            const std::vector<std::string>& queries_input,
            int limit_of_answers
            );

private:
    InvertedIndex _index;
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь

    /* Метод обработки количества совпадений
     * @param main_map пробигается по каждому значению-вектору, сравнивает, есть ли doc_id в векторе bufCount,
     * если есть суммирует count, если нет, добавляет в вектор
     * @return возвращает отсортированный список количества совпадений*/
    static std::vector<Entry> GetNumberOfMatches(std::map<std::string, std::vector<Entry>>& map_input);
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
