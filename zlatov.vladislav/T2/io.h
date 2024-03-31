#ifndef IO_H
#define IO_H

#include <vector>
#include <string>

namespace zlatov {

  // Типы данных для key1 и key2
  typedef double Key1Type;
  typedef unsigned long long Key2Type;

  // Структура DataStruct
  struct DataStruct {
    Key1Type key1;
    Key2Type key2;
    std::string key3;
  };

  // Функция для разбора строки и заполнения структуры DataStruct
  // Возвращает true, если строка была успешно обработана, иначе false
  bool parseDataStruct(const std::string& input, DataStruct& data);

  // Функция для вывода структуры DataStruct
  void printDataStruct(const DataStruct& data);

  // Компаратор для сортировки
  bool compareDataStruct(const DataStruct& a, const DataStruct& b);

  // Главная функция
  void processData();

} // namespace zlatov

#endif // IO_H
