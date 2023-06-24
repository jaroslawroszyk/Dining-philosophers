#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <memory>
#include <condition_variable>

using namespace std;

constexpr int NUM_PHILOSOPHERS = 5;

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
    Chopstick(int id) : id_(id) {}
    Chopstick() : id_(0) {}

    void pick_up()
    {
        mutex_.lock();
        id_++;
    }

    void put_down()
    {
        mutex_.unlock();
    }

    int getId() const { return id_; }

private:
    int id_;
    std::mutex mutex_;
};

class Philosopher
{
public:
    Philosopher(int id, Chopstick* left_chopstick, Chopstick* right_chopstick, Semaphore* waiter, int eatingCount = 0)
        : id_(id), left_chopstick_(left_chopstick), right_chopstick_(right_chopstick), waiter_(waiter), status_("Thinking"), eatingCount(eatingCount)
    {
    }

    void dine()
    {
        while (true)
        {
            cout << "Philosopher " << id_ << " is " << status_ << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));

            if (status_ == "Thinking")
            {
                waiter_->wait();
                left_chopstick_->pick_up();
                right_chopstick_->pick_up();
                eatingCount++;
                status_ = "Eating";
            }
            else if (status_ == "Eating")
            {
                left_chopstick_->put_down();
                right_chopstick_->put_down();
                waiter_->notify();
                status_ = "Waiting";
            }
            else if (status_ == "Waiting")
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                status_ = "Thinking";
            }
        }
    }
    int getEatingCount() const { return eatingCount; }

    int getId() const { return id_; }
    const std::string& getStatus() const { return status_; }
    Chopstick* getLeftChopstick() const { return left_chopstick_; }
    Chopstick* getRightChopstick() const { return right_chopstick_; }

private:
    int id_;
    Chopstick* left_chopstick_;
    Chopstick* right_chopstick_;
    Semaphore* waiter_;
    std::string status_;
    int eatingCount;
};

#include <iomanip>

void printTable(const vector<Philosopher>& philosophers)
{
    cout << "--------------------------------------------------------------" << endl;
    cout << "| Id Ph| Status     | Left  Fork | Right Fork |  Count |" << endl;
    cout << "--------------------------------------------------------------" << endl;

    for (const auto& philosopher : philosophers)
    {
        cout << "| " << setw(5) << philosopher.getId() << " | ";
        cout << setw(10) << philosopher.getStatus() << " |";
        cout << setw(11) << philosopher.getLeftChopstick()->getId() << " |";
        cout << setw(12) << philosopher.getRightChopstick()->getId() << " |";
        cout << setw(7) << philosopher.getEatingCount() << " |";

        cout << endl;
    }

    cout << "--------------------------------------------------------------" << endl;
}

int main()
{
    vector<Philosopher> philosophers;
    Semaphore waiter(NUM_PHILOSOPHERS - 1);

    vector<Chopstick> chopsticks(NUM_PHILOSOPHERS);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        philosophers.emplace_back(i, &chopsticks[i], &chopsticks[(i + 1) % NUM_PHILOSOPHERS], &waiter);
    }

    vector<thread> threads;
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        threads.emplace_back(&Philosopher::dine, &philosophers[i]);
    }

    while (true)
    {
        system("clear");
        printTable(philosophers);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}
