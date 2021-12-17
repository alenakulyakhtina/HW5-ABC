#include <iostream>
#include "Caller.h"
#include <thread>
#include <ctime>

 /*
  *  Точка входа
  */
int main(int argc, char *argv[]) {
    unsigned int start_time =  clock();
    int number_of_callers;
    // Проверка параметров и инициализация переменной number_of_callers (количество болтунов)
    if (argc == 2){
        if (std::atoi(argv[1]) > 1) {
            number_of_callers = std::atoi(argv[1]);
        } else if (std::atoi(argv[1]) < 2){
            std::cout << "Incorrect parameters! Expected number of callers or nothing (if you using generation). Parameter cannot be < 2!\n";
            return 0;
        }
        else {
            std::cout << "Incorrect parameters! Expected number of callers or nothing (if you using generation).\n";
            return 0;
        }
    }
    else if (argc == 1){
        number_of_callers = 2 + rand();
    }
    else {
        std::cout << "Incorrect parameters! Expected number of callers or nothing (if you using generation).\n";
        return 0;
    }

     // Начало работы с "телефонным справочником"
     auto** appending_list = new Caller*[number_of_callers];

    for (int i = 0; i < number_of_callers; ++i) {
        appending_list[i] = new Caller(i);
    }

    for (int i = 0; i < number_of_callers; ++i) {
        Caller* current_caller = appending_list[i];

        std::vector<Caller*> callList;

        for (int j = 0; j < number_of_callers; ++j) {
            if (j != i) {
                callList.push_back(appending_list[j]);
            }
        }

        current_caller->addCallList(callList);
    }

    printf("Created call lists\n");

    printf("Creating threads\n");
    std::vector<std::thread> threads;
    threads.reserve(number_of_callers);

    for (int i = 0; i < number_of_callers; ++i) {
        threads.emplace_back(&Caller::run, appending_list[i]);
    }
    printf("Created threads\n");

    printf("Waiting for threads\n");
    for (int i = 0; i < number_of_callers; ++i) {
        threads.at(i).join();
    }

    printf("Waited for threads\n");

    for (int i = 0; i < number_of_callers; ++i) {
        delete appending_list[i];
    }

    delete[] appending_list;
    unsigned int end_time = clock();
    unsigned int result_time = end_time - start_time;
    // Время работы
    std::cout << "Time: " << result_time/1000.0;
    return 0;
}