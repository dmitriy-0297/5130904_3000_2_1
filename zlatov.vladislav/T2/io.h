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
  DataStruct parseDataStruct(const std::string& input);

  // Функция для вывода структуры DataStruct
  void printDataStruct(const DataStruct& data);

  // Компаратор для сортировки
  bool compareDataStruct(const DataStruct& a, const DataStruct& b);

  // Главная функция
  void processData();

} // namespace zlatov

// Перегрузка оператора вывода для структуры DataStruct
std::ostream& operator<<(std::ostream& os, const zlatov::DataStruct& data);

// Перегрузка оператора ввода для структуры DataStruct
std::istream& operator>>(std::istream& is, zlatov::DataStruct& data);

#endif // IO_H
