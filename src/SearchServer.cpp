//
// Created by mikha on 09.09.2024.
//

#include "SearchServer.h"

/* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла requests.json
* @return возвращает отсортированный список релевантных ответов для заданных запросов */
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {

    /// Разложить запрос по словестно

    for (const auto & i : queries_input){
        /// Потоки -->

        std::vector<Entry> buf;
        buf = this->_index.GetWordCount(i);
        this->freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(i, buf));

        buf.clear();
    }
    /// <--

    std::vector<Entry> bufCount = numberOfMatches(this->freq_dictionary);

    for (auto & i : bufCount){
        std::cout << "{" << i.doc_id << ", " << i.count << "}" << std::endl;
    }

    int max_count = 0;
    for (auto & i : bufCount){
        int count = i.count;
        if (count > max_count)
            max_count = count;
    }

    std::cout << max_count << std::endl;

    std::vector<std::vector<RelativeIndex>> result;
    std::vector<RelativeIndex> rel_idx;
    for (auto & i : bufCount){
        RelativeIndex idx{};
        idx.doc_id = i.doc_id;
        idx.rank = i.count / max_count;

        rel_idx.push_back(idx);
    }

    /// Отсортировать 1->0

    result.push_back(rel_idx);

    for (auto & i : rel_idx){
        std::cout << "{" << i.doc_id << ", " << i.rank << "}" << std::endl;
    }

    return result;
}

/* Метод обработки количества совпадений
* @param map_input пробигается по каждому значению-вектору, сравнивает,
* есть ли doc_id в векторе bufCount, если есть суммирует count, если нет, добавляет в вектор
* @return возвращает отсортированный список количества совпадений */
std::vector<Entry> SearchServer::numberOfMatches(std::map<std::string, std::vector<Entry>>& map_input) {
    std::vector<Entry> result;
    // пробегает по ключу freq_dictionary
    for (auto & it : map_input){

        if (!result.empty()){
            // Пробигает по вектору-значению
            for (auto & j : it.second){
                /// Потоки -->
                bool thereIs = false;

                for (auto & k : result){
                    if (k.doc_id == j.doc_id){
                        k.count += j.count;
                        thereIs = true;
                    }
                }
                if (!thereIs){
                    result.push_back(j);

                }
                /// <--
            }
        } else
            result = it.second;

    }
    return result;
}
