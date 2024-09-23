//
// Created by mikha on 07.08.2024.
//

#include "ConverterJSON.h"

/* Функция проверяет удовлетворение условий текста в файле */
bool isCorrectFile(std::string textFile){
    int chars = 0;
    int words = 0;
    for (int j = 0; j <= textFile.size(); j++){
        /* Тз: При этом каждый документ содержит не более
        * 1000 слов с максимальной длиной каждого в 100 символов. Слова
        * состоят из строчных латинских букв и разделены одним или несколькими
        * пробелами */
        if (textFile[j] > 96 && textFile[j] < 123)
            chars++;
        else {
            if (chars > 100) return false;
            chars = 0;
            words++;
        }

        if (words > 1000) return false;
    }
    return true;
}

/* Функция проверяет корректность config.json файла */
bool ConverterJSON::CheckConfig(const nlohmann::json& configJson){
    /* Существует ли поле "config" */
    if (configJson["config"] == nullptr) {
        std::cerr << "config file is empty" << std::endl;
        return false;
    }

    /* Проверка версии */
    if (configJson["config"]["version"] != "0.1"){
        std::cerr << "config.json has incorrect file version" << std::endl;
        return false;
    }
    return true;
}

/* Функция проверяет корректность requests.json файла */
bool ConverterJSON::CheckRequests(const nlohmann::json& requestsJson){

    std::vector<std::string> req = requestsJson["requests"];
    int requests = req.size();

    if(requests > 1000) {
        std::cerr << "there are too many requests\n"
                     "there should be no more than 1000 requests" << std::endl;
        return false;
    }

    for (int j = 0; j < requests; j++){
        int words = 0;
        for (int i = 0; i <= req[j].size(); i++) {
            if (req[j][i] <= 96 || req[j][i] >= 123)
                words++;

            if (words > 10) {
                std::cerr << "there are too many words in request\n"
                             "there should be no more than 10 words" << std::endl;
                return false;
            }
        }
    }

    return true;
}

/* Метод считывает json из файла
 * @return Возвращает объект json */
nlohmann::json ConverterJSON::CorrectOpenJson(bool is_config){
    std::ifstream file;
    nlohmann::json fileJson;
    std::string nameFile = (is_config) ?
                           ("config.json") :  ("requests.json");

    file.open("../json/" + nameFile);
    if (file.is_open()) {
        file >> fileJson;
        file.close();
    } else {
        std::cerr << nameFile + " file is missing." << std::endl;
        fileJson = nullptr;
    }

    auto isCorrect = (is_config) ?
                     (CheckConfig(fileJson)) : CheckRequests(fileJson);
    if (!isCorrect) fileJson = nullptr;

    return fileJson;
}

/* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных в config.json */
std::vector<std::string> ConverterJSON::GetTextDocuments() {

    nlohmann::json configFileJson = CorrectOpenJson(true);
    std::vector<std::string> textDocs;

    if (configFileJson != nullptr) {
        for (auto &i: configFileJson["files"]) {
            std::ifstream textFile;

            textFile.open(i);
            if (textFile.is_open()) {
                std::string text;
                std::getline(textFile, text);
                if (isCorrectFile(i)) {
                    textDocs.push_back(text);
                } else {
                    std::cerr << i << " is not correct" << std::endl;
                    std::cerr << "there are more than 100 characters in a word"
                                 " or more than 1000 words in a text" << std::endl;
                }
                textFile.close();
            } else {
                std::cerr << "file " << i << " is not found." << std::endl;
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
    nlohmann::json configFileJson = CorrectOpenJson(true);
    if (configFileJson != nullptr){
        int count = configFileJson["config"]["max_responses"];
        if (count > 5)
            count = 5;
        return count;
    } else
        return 0;
}

/* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json */
std::vector<std::string> ConverterJSON::GetRequests() {
    nlohmann::json requestsFileJson = CorrectOpenJson(false);
    std::vector<std::string> keywords;

    if (requestsFileJson != nullptr){
        for (auto & i : requestsFileJson["requests"]){
            if (isCorrectFile(i)) {
                keywords.push_back(i);
            } else {
                std::cerr << i << " is not correct" << std::endl;
                std::cerr << "there are more than 100 characters in a word"
                             " or more than 1000 words in a text" << std::endl;
            }
        }
    } else {
        std::cerr << "there are problems with requests.json file" << std::endl;
        keywords.clear();
    }

    return keywords;
}

/* Положить в файл answers.json результаты поисковых запросов */
void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {

    nlohmann::json answer_json;

    for (auto i = 0; i < answers.size(); i++){
        std::string request_name = "request00" + std::to_string(i+1);
        answer_json["answers"][request_name]["result"] = (!answers[i].empty());

        for (const auto & j : answers[i]){

            answer_json["answers"][request_name]["relevance"] += {

                    {"docid", j.first},
                    {"rank", j.second}
            };

        }
    }

    std::ofstream file("../json/answers.json");
    if(file.is_open()) {
        file << answer_json;
        file.close();
    } else
        std::cerr << "answers.json file is missing." << std::endl;

}

