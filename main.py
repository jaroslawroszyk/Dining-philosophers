import threading
import time

class Chopstick:
    def __init__(self, id):
        self.id = id
        self.mutex = threading.Lock()

    def pick_up(self, p_id):
        self.mutex.acquire()
        self.p_id = p_id

    def put_down(self):
        self.p_id = -1
        self.mutex.release()

    def get_id(self):
        return self.id

class Semaphore:
    def __init__(self, initial):
        self.mutex = threading.Lock()
        self.counter = initial
        self.condition = threading.Condition()

    def wait(self):
        with self.condition:
            self.counter -= 1
            if self.counter < 0:
                self.condition.wait()

    def notify(self):
        with self.condition:
            self.counter += 1
            if self.counter <= 0:
                self.condition.notify()


class Philosopher:
    def __init__(self, id, left_chopstick, right_chopstick, waiter, eating_count=0):
        self.id = id
        self.left_chopstick = left_chopstick
        self.right_chopstick = right_chopstick
        self.waiter = waiter
        self.status = "Thinking"
        self.eating_count = eating_count

    def dine(self):
        while True:
            print(f"Philosopher {self.id} is {self.status}")
            time.sleep(1)

            if self.status == "Thinking":
                self.waiter.wait()
                self.left_chopstick.pick_up(self.id)
                self.right_chopstick.pick_up(self.id)
                self.eating_count += 1
                self.status = "Eating"
            elif self.status == "Eating":
                self.left_chopstick.put_down()
                self.right_chopstick.put_down()
                self.waiter.notify()
                self.status = "Waiting"
            elif self.status == "Waiting":
                time.sleep(1)
                self.status = "Thinking"

    def get_id(self):
        return self.id

    def get_status(self):
        return self.status

    def get_eating_count(self):
        return self.eating_count

    def get_left_chopstick(self):
        return self.left_chopstick

    def get_right_chopstick(self):
        return self.right_chopstick


class Utils:
    @staticmethod
    def clear_screen():
        import os

        os.system("cls" if os.name == "nt" else "clear")

    @staticmethod
    def print_table(philosophers):
        print("--------------------------------------------------------------")
        print("| Id Ph| Status     | Left  Fork | Right Fork |  Count |")
        print("--------------------------------------------------------------")

        for philosopher in philosophers:
            print(
                f"| {philosopher.get_id():^5d}| "
                f"{philosopher.get_status():^10s} |"
                f"{philosopher.get_left_chopstick().get_id():^11d}|"
                f"{philosopher.get_right_chopstick().get_id():^12d}|"
                f"{philosopher.get_eating_count():^7d} |"
            )

        print("--------------------------------------------------------------")


NUM_OF_PHILOSOPHERS = 5

if __name__ == "__main__":
    philosophers = []
    waiter = Semaphore(NUM_OF_PHILOSOPHERS - 1)

    chopsticks = [Chopstick(i) for i in range(NUM_OF_PHILOSOPHERS)]
    for i in range(NUM_OF_PHILOSOPHERS):
        philosophers.append(
            Philosopher(
                i,
                chopsticks[i],
                chopsticks[(i + 1) % NUM_OF_PHILOSOPHERS],
                waiter
            )
        )

    threads = []
    for i in range(NUM_OF_PHILOSOPHERS):
        threads.append(threading.Thread(target=philosophers[i].dine))

    for thread in threads:
        thread.start()

    while True:
        Utils.clear_screen()
        Utils.print_table(philosophers)
        time.sleep(1)

