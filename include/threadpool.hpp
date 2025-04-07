#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

using namespace std;

// 线程池单例对象
//?单例体现在哪里
class ThreadPool
{
public:
    ThreadPool(int Threadnums);
    ~ThreadPool();

    template<class F,class ...Args>  //?函数模板，2参表示列表?
    void enqueue(F &&f,Args &&...args)  //变量名前加&&
    {
        function<void()> task = bind(forward<F>(f), forward<Args>(args)...);
        //?锁被占用是否会往下执行，还是会阻塞?
        {
            unique_lock<mutex> lock(mux); // 装填任务加锁
            tasks.emplace(move(task));    // move：左值->右值，queue插入不用back,自动尾部插入
        }
        condition.notify_one(); // 等待和唤醒均由条件变量控制
    }

private:
    // 停止信号
    bool stop;
    // 线程容器
    vector<thread> threads;
    // 全局锁
    mutex mux;
    // 全局条件变量
    condition_variable condition;
    // 任务队列
    queue<function<void()>> tasks;
};

