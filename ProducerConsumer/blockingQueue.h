/*
 * blockingQueue.h
 * Copyright (C) 2016 lopespt <lopespt@arch>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <mutex>

using namespace std;

template <class T> class blockingQueue {
private:
  mutex _m;
  condition_variable _cv;
  deque<T> _data;
  deque<int> _data2;

public:
  void push(const T &data) {
    {
      unique_lock<mutex> guard(_m);
      _data.push_back(data);
    }
    _cv.notify_one();
  }

  T pop() {
    unique_lock<mutex> guard(_m);
    _cv.wait(guard, [&]() { return !(this->_data.empty()); });
    T r(_data.front());
    _data.pop_front();
    return r;
  }
};

#endif /* !BLOCKINGQUEUE_H */
