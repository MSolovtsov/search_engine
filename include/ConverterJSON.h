//
// Created by mikha on 07.08.2024.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
//
#pragma once
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <exception>
#include <filesystem>
//
#include <nlohmann/json.hpp>

/* Класс для работы с JSON-файлами */
class ConverterJSON {
private:

    /* Функция проверяет корректность config.json файла */
    static bool CheckConfig(const nlohmann::json& configJson);

    /* Функция проверяет корректность requests.json файла */
    static bool CheckRequests(const nlohmann::json& requestsJson);

    /* Метод считывает json из файла
     * @return Возвращает объект json */
    static nlohmann::json CorrectOpenJson(bool is_config);

public:
    ConverterJSON() = default;

    /* Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json */
    static std::vector<std::string> GetTextDocuments();

    /* Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return */
    static int GetResponsesLimit();

    /* Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json */
    static std::vector<std::string> GetRequests();

    /* Положить в файл answers.json результаты поисковых запросов */
    static void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

};


#endif //SEARCH_ENGINE_CONVERTERJSON_H
