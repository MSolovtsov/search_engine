//
// Created by mikha on 07.08.2024.
//

#include "ConverterJSON.h"

/* Функция проверяет корректность config.json файла */
bool ConverterJSON::CheckConfig(const nlohmann::json& configJson){
    /* Существует ли поле "config" */
    if (configJson["config"] == nullptr) {
        //TODO Сделать ошибкой
        std::cout << "config file is empty" << std::endl;
        return false;
    }

    /* Проверка версииm */
    if (configJson["config"]["version"] != "0.1"){
        //TODO Сделать ошибкой
        std::cout << "config.json has incorrect file version" << std::endl;
        return false;
    }
    return true;
}

/* Функция проверяет корректность requests.json файла */
bool ConverterJSON::CheckRequests(const nlohmann::json& requestsJson){

    /// CODE

    return true;
}

/* Функция проверяет корректность answers.json файла */
bool ConverterJSON::CheckAnswers(const nlohmann::json& answersJson){

    /// CODE

    return true;
}

/* Метод считывает json из файла
 * @return Возвращает объект json */
nlohmann::json ConverterJSON::CorrectOpenJson(bool is_config, bool is_requests){
    std::ifstream file;
    nlohmann::json fileJson;
    std::string nameFile = (is_config) ?
                           ("config.json") : ((is_requests) ?
                                              ("requests.json") : ("answers.json"));

    //TODO Исправить костыль!!
    std::string path = R"(..\..\json\)" + nameFile;

    file.open(path);
    if (file.is_open()) {
        file >> fileJson;
        file.close();
    } else {
        //TODO Сделать ошибкой (есть ли файл вообще)
        std::cout << nameFile + " file is missing." << std::endl;
        fileJson = nullptr;
    }

    auto isCorrect = (is_config) ?
                     (CheckConfig(fileJson)) : ((is_requests) ?
                                                CheckRequests(fileJson) : CheckAnswers(fileJson));
    if (!isCorrect) fileJson = nullptr;

    return fileJson;
}

/* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных в config.json */
std::vector<std::string> ConverterJSON::GetTextDocuments() {

    nlohmann::json configFileJson = CorrectOpenJson(true, false);
    std::vector<std::string> textDocs;

    if (configFileJson != nullptr) {
        for (auto &i: configFileJson["files"]) {
            std::ifstream textFile;
            //TODO Исправить костыль!!
            textFile.open(i);
            if (textFile.is_open()) {
                std::string text;
                std::getline(textFile, text);
                //TODO Посчитать слова и буквы в словах
                textDocs.push_back(text);
                textFile.close();
            } else {
                //TODO Исправить костыль!!
                std::cout << "PUPUPU" << std::endl;
                textDocs.emplace_back();
            }
        }
    } else textDocs.clear();

    return textDocs;
}

/* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return */
int ConverterJSON::GetResponsesLimit() {
    nlohmann::json configFileJson = CorrectOpenJson(true, false);
    if (configFileJson != nullptr){
        int count = configFileJson["config"]["max_responses"];
        return count;
    } else
        return 0;
}

/* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json */
std::vector<std::string> ConverterJSON::GetRequests() {
    nlohmann::json requestsFileJson = CorrectOpenJson(false, true);
    std::vector<std::string> keywords;

    if (requestsFileJson != nullptr){
        for (auto & i : requestsFileJson["requests"]){
            keywords.push_back(i);
        }
    } else {
        //TODO Исправить костыль!!
        std::cout << "PUPUPU" << std::endl;
        keywords.clear();
    }

    return keywords;
}

/* Положить в файл answers.json результаты поисковых запросов */
void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {

    /// CODE

    /*Тз: При этом каждый документ содержит не более
            1000 слов с максимальной длиной каждого в 100 символов. Слова
            состоят из строчных латинских букв и разделены одним или несколькими
            пробелами*/
}

