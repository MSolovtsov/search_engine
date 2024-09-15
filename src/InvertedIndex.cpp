//
// Created by mikha on 08.09.2024.
//

#include "InvertedIndex.h"

/* Обновить или заполнить базу документов, по которой будем совершать поиск
* @param input_docs содержимое документов */
void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    docs.clear();

    for (const auto & input_doc : input_docs){
        docs.push_back(input_doc);
    }

}

/* Метод определяет количество вхождений слова word в загруженной базе документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов*/
std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    std::vector<Entry> entry_vec;
    const auto count = word.size();

    // Проверяем каждый текст
    for (int i = 0; i < this->docs.size(); i++){
        Entry entry{};
        entry.count = 0;
        std::string buf;
        buf.clear();

        // Проверяем внутри текста
        for (int j = 0; j <= this->docs[i].size(); j++){
            // Вариант 1
            /* Тз: При этом каждый документ содержит не более
            * 1000 слов с максимальной длиной каждого в 100 символов. Слова
            * состоят из строчных латинских букв и разделены одним или несколькими
            * пробелами */
            if (this->docs[i][j] > 96 && this->docs[i][j] < 123){
                buf += docs[i][j];
            } else {
                if (buf.size() == count)
                    if (buf == word)
                        entry.count++;
                buf.clear();
            }
        }

        if (entry.count != 0) {
            entry.doc_id = i;
            entry_vec.push_back(entry);
        }
    }

    return entry_vec;
}
