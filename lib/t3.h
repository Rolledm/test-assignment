#ifndef T3_H
#define T3_H

#include <cstdio>
#include <string>

namespace Utilities {

// структуру ListNode модифицировать нельзя
struct ListNode {
    ListNode * prev;
    ListNode * next;
    ListNode * rand; // указатель на произвольный элемент данного списка, либо NULL
    std::string data;
};

class List {
public:
    void Serialize (FILE * file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize (FILE * file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))
    
    std::string GetDBGData();
//private:
    ListNode * head;
    ListNode * tail;
    int count;
};


}

#endif