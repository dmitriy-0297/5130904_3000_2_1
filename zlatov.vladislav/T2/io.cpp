#include "io.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace zlatov {

  bool parseDataStruct(const std::string& input, DataStruct& data) {
    // Переменные для хранения данных
    Key1Type key1;
    Key2Type key2;
    std::string key3;

    // Индекс начала и конца скобок
    size_t start = input.find('(');
    size_t end = input.find(')');

    // Проверка наличия скобок
    if (start == std::string::npos || end == std::string::npos) {
      return false;
    }

    // Обрезаем строку до содержимого внутри скобок
    std::string content = input.substr(start + 1, end - start - 1);

    // Итератор для обхода содержимого
    auto it = content.begin();

    // Пока не достигнут конец строки
    while (it != content.end()) {
      // Ищем разделитель
      auto colonPos = std::find(it, content.end(), ':');

      // Если разделитель не найден, выходим из цикла
      if (colonPos == content.end()) {
        break;
      }

      // Получаем имя поля
      std::string fieldName(it, colonPos);
      it = colonPos + 1;

      // Пропускаем пробельные символы
      while (it != content.end() && std::isspace(*it)) {
        ++it;
      }

      // Если достигнут конец строки, выходим из цикла
      if (it == content.end()) {
        break;
      }

      // Получаем значение поля
      std::string fieldValue;
      if (*it == '\'' || *it == '"') { // если строка
        auto closingQuote = std::find(it + 1, content.end(), *it);
        if (closingQuote == content.end()) {
          return false; // Если не найдена закрывающая кавычка, игнорируем строку
        }
        fieldValue = std::string(it + 1, closingQuote);
        it = closingQuote + 1;
      }
      else { // если число
        auto fieldEnd = std::find_if(it, content.end(), [](char c) { return std::isspace(c) || c == ':'; });
        fieldValue = std::string(it, fieldEnd);
        it = fieldEnd;
      }

      // Пропускаем пробельные символы
      while (it != content.end() && std::isspace(*it)) {
        ++it;
      }

      // Заполняем соответствующее поле структуры
      if (fieldName == "key1") {
        std::istringstream iss(fieldValue);
        char suffix;
        iss >> key1 >> suffix;
        if (suffix != 'd' && suffix != 'D') {
          return false; // Если суффикс не соответствует формату [DBL LIT], игнорируем строку
        }
      }
      else if (fieldName == "key2") {
        try {
          size_t pos;
          key2 = std::stoull(fieldValue, &pos, 16);
          if (pos != fieldValue.size()) {
            return false; // Если после числа есть лишние символы, игнорируем строку
          }
        }
        catch (...) {
          return false; // Если не удалось преобразовать значение, игнорируем строку
        }
      }
      else if (fieldName == "key3") {
        key3 = fieldValue;
      }
      else {
        return false; // Если неизвестное поле, игнорируем строку
      }
    }

    // Записываем данные в структуру DataStruct
    data.key1 = key1;
    data.key2 = key2;
    data.key3 = key3;

    return true; // Успешно обработана строка
  }

  void printDataStruct(const DataStruct& data) {
    std::cout << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d"
      << ":key2 " << std::hex << data.key2 << ":key3 " << data.key3 << ":)" << std::endl;
  }

  bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) {
      return a.key1 < b.key1;
    }
    else if (a.key2 != b.key2) {
      return a.key2 < b.key2;
    }
    else {
      return a.key3.size() < b.key3.size();
    }
  }

  void processData() {
    // Вектор для хранения структур DataStruct
    std::vector<DataStruct> dataVector;

    // Считываем данные и заполняем вектор
    std::string input;
    while (std::getline(std::cin, input)) {
      DataStruct data;
      if (parseDataStruct(input, data)) {
        dataVector.push_back(data);
      }
    }

    // Если не найдено ни одной поддерживаемой записи, выводим сообщение и завершаем выполнение
    if (dataVector.empty()) {
      std::cerr << "Looks like there is no supported record. Cannot determine input. Test skipped" << std::endl;
      return;
    }

    // Сортируем данные
    std::sort(dataVector.begin(), dataVector.end(), compareDataStruct);

    // Выводим отсортированные данные
    std::for_each(dataVector.begin(), dataVector.end(), printDataStruct);
  }

} // namespace zlatov
