#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <memory>
/*

Problem ucztujących filozofów jest klasycznym problemem synchronizacji w systemach operacyjnych, którego celem jest uniknięcie zakleszczenia (ang. deadlock) w sytuacji, gdy wiele procesów (filozofów) próbuje uzyskać jednocześnie zasoby (pałeczki), które są potrzebne do dalszej pracy.

Problem składa się z grupy filozofów siedzących przy okrągłym stole, a między każdymi dwoma filozofami leży jedna pałeczka. Filozof może albo jeść albo myśleć. Aby zacząć posiłek, musi posiadać dwie pałeczki - jedną po lewej i drugą po prawej stronie. Kiedy skończy jedzenie, odkłada pałeczki i znowu zaczyna myśleć.

Problem polega na tym, że każdy filozof będzie czekał na swoją kolej, aż jego pałeczki będą wolne. W przypadku, gdy każdy filozof podniesie pałeczki po swojej lewej stronie, ale nie ma wolnej pałeczki po prawej stronie, to wszyscy filozofowie zaczną czekać na siebie nawzajem, co prowadzi do zakleszczenia.

Rozwiązaniem problemu jest wprowadzenie mechanizmu koordynacji, który zapewni, że każdy filozof będzie miał dostęp do dwóch pałeczek tylko wtedy, gdy będą one wolne. Najczęściej stosowane rozwiązania to algorytmy oparte na semaforach, mutexach lub monitorach.

Aby spełnić wszystkie założenia problemu ucztujących filozofów, można wprowadzić dodatkowe ograniczenia, takie jak:

Filozofowie nie mogą trzymać pałeczek przez zbyt długi czas, aby zapobiec zagłodzeniu innych filozofów.
Filozofowie powinni być aktywowani w przypadkowej kolejności, aby uniknąć zakleszczenia spowodowanego kolejnością ich aktywacji.
W przypadku, gdy filozofowie otrzymują jedzenie z zewnętrznego źródła, problem zostaje rozwiązany poprzez zapewnienie, że jest wystarczająca ilość jedzenia dla każdego filozofa.

*/
using namespace std;

const int NUM_PHILOSOPHERS = 5;

class Semaphore
{
public:
    Semaphore(int count = 1) : count_(count) {}

    void notify()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        count_++;
        cv_.notify_one();
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0)
        {
            cv_.wait(lock);
        }
        count_--;
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
};

class Chopstick
{
public:
    Chopstick() {}

    void pick_up()
    {
        mutex_.lock();
    }

    void put_down()
    {
        mutex_.unlock();
    }

private:
    std::mutex mutex_;
};

class Philosopher
{
public:
    Philosopher(int id, Chopstick *left_chopstick, Chopstick *right_chopstick, Semaphore *waiter)
        : id_(id), left_chopstick_(left_chopstick), right_chopstick_(right_chopstick), waiter_(waiter) {}

    void dine()
    {
        while (true)
        {
            cout << "Philosopher " << id_ << " is thinking" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            waiter_->wait();
            left_chopstick_->pick_up();
            right_chopstick_->pick_up();

            cout << "Philosopher " << id_ << " is eating" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            left_chopstick_->put_down();
            right_chopstick_->put_down();
            waiter_->notify();
        }
    }

private:
    int id_;
    Chopstick *left_chopstick_;
    Chopstick *right_chopstick_;
    Semaphore *waiter_;
};

int main()
{
    vector<Chopstick> chopsticks(NUM_PHILOSOPHERS);
    vector<Philosopher> philosophers;
    Semaphore waiter(NUM_PHILOSOPHERS - 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosophers.emplace_back(i, &chopsticks[i], &chopsticks[(i + 1) % NUM_PHILOSOPHERS], &waiter);
    }

    vector<thread> threads;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        threads.emplace_back(&Philosopher::dine, &philosophers[i]);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}

