//
// Created by mikha on 09.09.2024.
//

#include "SearchServer.h"

std::vector<std::string> cutRequest(const std::string& request){
    std::vector<std::string> words;
    std::string buf;
    for (char i : request){
        // 20 = [SPACE] по ASCII
        if (i == ' '){
            words.push_back(buf);
            buf.clear();
        } else
            buf.push_back(i);
    }

    return words;
}



/* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла requests.json
* @return возвращает отсортированный список релевантных ответов для заданных запросов */
std::vector<std::vector<RelativeIndex>> SearchServer::search(
        const std::vector<std::string> &queries_input,
        int limit_of_answers
        ) {

    std::vector<std::vector<RelativeIndex>> result;

    // Проходим по каждому запросу
    for (const auto & i : queries_input){
        std::vector<std::string> req = cutRequest(i);
        std::vector<std::thread> threads;
        std::mutex threads_access;
        std::mutex word_access;

        // Проходим по каждому слову в запросе
        for (const auto & j : req) {
            // Потоки -->
            threads.emplace_back([&j, this, &word_access, &threads_access]() {
                word_access.lock();
                std::string keyword = j;
                word_access.unlock();
                std::vector<Entry> buf;
                buf = this->_index.GetWordCount(keyword/*j*/);
                threads_access.lock();
                this->freq_dictionary.insert(std::pair<std::string, std::vector<Entry>>(keyword/*j*/, buf));
                threads_access.unlock();
                buf.clear();
            });
        }

        // <--
        for (auto & thread : threads){
            if(thread.joinable()) thread.join();
        }

        std::vector<RelativeIndex> rel_idx;
        std::vector<Entry> bufCount = GetNumberOfMatches(this->freq_dictionary);

        if (!bufCount.empty()) {
            // Максимальное число повторений
            int max_count = 0;
            for (auto &i: bufCount) {
                int count = i.count;
                if (count > max_count)
                    max_count = count;
            }

            // Запись в vector с релевантным индексом
            for (auto &i: bufCount) {
                RelativeIndex idx{};
                idx.doc_id = i.doc_id;
                idx.rank = (float )i.count / (float)max_count;

                rel_idx.push_back(idx);
            }

            // Сортировка по рангу и id
            for (int j = rel_idx.size()-1; j >= 0; j--){
                int max_j = 0;
                for (int k = 0; k <= j; k++) {

                    if (rel_idx[k].rank < rel_idx[max_j].rank) {
                        max_j = k;
                    } else if (rel_idx[k].rank == rel_idx[max_j].rank){
                        if (rel_idx[k].doc_id > rel_idx[max_j].doc_id)
                            max_j = k;
                    }
                }

                RelativeIndex buf = rel_idx[j];
                rel_idx[j] = rel_idx[max_j];
                rel_idx[max_j] = buf;
            }

            this->freq_dictionary.clear();
        }
        if (rel_idx.size() > limit_of_answers){
            rel_idx.resize(limit_of_answers);
        }
        result.push_back(rel_idx);
        rel_idx.clear();

    }

    return result;
}

/* Метод обработки количества совпадений
* @param map_input пробигается по каждому значению-вектору, сравнивает,
* есть ли doc_id в векторе bufCount, если есть суммирует count, если нет, добавляет в вектор
* @return возвращает отсортированный список количества совпадений */
std::vector<Entry> SearchServer::GetNumberOfMatches(std::map<std::string, std::vector<Entry>>& map_input) {
    std::vector<Entry> result;
    // пробегает по ключу freq_dictionary
    for (auto & it : map_input){

        if (!result.empty()){
            // Пробигает по вектору-значению
            for (auto & j : it.second){
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
            }
        } else
            result = it.second;
    }
    return result;
}
