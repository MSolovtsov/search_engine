//
// Created by mikha on 08.09.2024.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H
//
#pragma once
//
#include <iostream>
#include <vector>

struct Entry {
    size_t doc_id, count;

    // Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    /* Обновить или заполнить базу документов, по которой будем совершать поиск
    * @param input_docs содержимое документов */
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);

    /* Метод определяет количество вхождений слова word в загруженной базе документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов*/
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs; // список содержимого документов
    //std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
};



#endif //SEARCH_ENGINE_INVERTEDINDEX_H
