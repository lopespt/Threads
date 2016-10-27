/*
 * main.cpp
 * Copyright (C) 2016 lopespt <lopespt@arch>
 *
 * Distributed under terms of the MIT license.
 */

#include "blockingQueue.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

atomic<int> i(0);
mutex mut;
void produtor(blockingQueue<int> &q) {
  while (true) {
    i++;
    q.push(i);
    std::this_thread::sleep_for(chrono::seconds(1));
  }
}

int fib(int p) {
  if (p <= 1)
    return p;
  return fib(p - 1) + fib(p - 2);
}

int fat(int p) {
  int r = 1;
  while (p > 0) {
    r *= p;
    p--;
  }
  return r;
}

void consumidor(int threadId, blockingQueue<int> &q) {
  while (true) {
    int p = q.pop();
    // cout << "Peguei: " << p << "(thread: " << threadId << ")" << endl;
    int resp = fib(p);
    cout << " (thread: " << threadId << ") fib(" << p << ") = " << resp << endl;
  }
}

int main(int argc, const char *argv[]) {

  blockingQueue<int> t;
  vector<thread> threads;

  for (int i = 0; i < 1; i++)
    threads.push_back(thread(produtor, ref(t)));

  for (int i = 0; i < 5; i++)
    threads.push_back(thread(consumidor, i, ref(t)));

  for (thread &th : threads)
    th.join();
  return 0;
}
