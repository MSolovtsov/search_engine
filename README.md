**Поисковый Движок**
=====================
[![Build Status](https://travis-ci.org/MSolovtsov/search_engine.svg?branch=main)](https://travis-ci.org/MSolovtsov/search_engine)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Version](https://img.shields.io/badge/Version-1.0.0-green.svg)](https://semver.org/)

**Описание**
---------------

Поисковый движок - консольное приложение, осуществляющее поиск и имеющее возможность настройки через файлы формата JSON. Движок предназначен для поиска среди набора документов и может быть использован на любом сервере или компьютере.

**Принципы Работы**
-------------------

1. **Конфигурационный файл**: перед запуском приложения задаются названия файлов, по которым движок будет осуществлять поиск.
2. **Индексирование**: поисковый движок самостоятельно обходит все файлы и индексирует их для последующего поиска.
3. **Запрос**: пользователь задаёт запрос через JSON-файл requests.json.
4. **Трансформация запроса**: запрос трансформируется в список слов.
5. **Поиск**: в индексе ищутся те документы, на которых встречаются все слова из запроса.
6. **Ранжирование и сортировка**: результаты поиска ранжируются и сортируются.
7. **Ответ**: максимальное количество возможных документов в ответе задаётся в конфигурационном файле.

**Файлы**
---------

* **config.json**: конфигурационный файл, в котором задаются названия файлов для поиска и другие настройки.
* **requests.json**: файл, содержащий запросы для поиска.
* **answers.json**: файл, содержащий результаты поиска.

**Установка и Запуск**
----------------------

1. Скачайте репозиторий.
2. Установите необходимые зависимости.
3. Создайте конфигурационный файл config.json с содержимым:
```json
{
  "config": {
    "name": "SearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "../resources/file001.txt",
    "../resources/file002.txt",
    "../resources/file003.txt",
    "../resources/file004.txt",
    "../resources/file005.txt",
    "../resources/file006.txt",
    "../resources/file007.txt",
    "../resources/file008.txt",
    "../resources/file009.txt",
    "../resources/file010.txt"
  ]
}
```
4. Запустите приложение.

**Пример Использования**
------------------------

1. Создайте файл requests.json с содержимым:
```json
{
  "requests": [
    "some words..",
    "some words..",
    "some words..",
    "some words.."
  ]
}
```
2. Запустите приложение.
3. Результаты поиска будут записаны в файл answers.json.

**Лицензия**
------------

Этот проект является открытым исходным кодом и доступен под лицензией Apache 2.0.

**Авторы**
------------

* Михаил Соловцов (mikhail.solovtsov@gmail.com)

**Контакты**
------------

* Email: mikhail.solovtsov@gmail.com

**Статистика**
-------------

[![GitHub stars](https://img.shields.io/github/stars/MSolovtsov/search_engine.svg)](https://github.com/MSolovtsov/search_engine/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/MSolovtsov/search_engine.svg)](https://github.com/MSolovtsov/search_engine/network/members)
[![GitHub issues](https://img.shields.io/github/issues/MSolovtsov/search_engine.svg)](https://github.com/MSolovtsov/search_engine/issues)

**Open Source**
--------------

Этот проект является частью сообщества open source и доступен для всех. Мы приветствуем любые вклады и предложения по улучшению проекта.