#pragma once

#include <utility>
#include <vector>
#include <mutex>

/*
 * Класс, описывающий абонента из условия задачи
 */
class Caller {

public:

    explicit Caller(int id) : id_(id) { }

    void addCallList(std::vector<Caller*> call_list);

    void call(Caller* caller);
    void run();

    int getID() const {return id_; }

private:

private:
    int id_;
    std::vector<Caller*> call_list_;
    std::mutex phone_lock_;
};