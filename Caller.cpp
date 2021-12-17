#include "Caller.h"

#include <utility>
#include <thread>

/*
 * Класс, описывающий абонента из условия задачи
 */
void Caller::call(Caller* caller) {
    phone_lock_.lock();
    // Дозвонились, теперь общаемся 1 секунду.
    printf("%d called %d\n", caller->getID(), getID());
    std::chrono::seconds time_to_talk(1);
    std::this_thread::sleep_for(time_to_talk);

    phone_lock_.unlock();
}

/*
 * Обзваниваем всех из списка контактов
 */
void Caller::run() {
    for (auto contact : call_list_) {
        call(contact);
    }
}

/*
 * Обновляем список контактов.
 */
void Caller::addCallList(std::vector<Caller *> call_list) {
    call_list_ = std::move(call_list);
}