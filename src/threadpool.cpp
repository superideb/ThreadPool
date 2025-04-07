#include "threadpool.hpp"

//注释为个人理解，待规范

ThreadPool::ThreadPool(int Threadnums):stop(false)
{   
    //?是否会阻滞
    for(int i=0;i<Threadnums;++i)
    {
        //直接在线程容器末尾插入新线程,Lamda表达式函数非成员，常传入this指针
        threads.emplace_back([this]{
            while(true)
            {
                //?持锁等待
                unique_lock<mutex> lock(mux);
                condition.wait(lock,[this]{
                    return (!tasks.empty()||stop);//?并上stop防止任务结束后线程仍进入等待。这样进入下个if就可以return，解决方案的逻辑非常巧妙
                    //?进入wait会释放锁
                });
                if(stop&&tasks.empty())//?并上后者，意思是当收到stop信号时，先解决残留任务，再stop
                {
                    return;
                }
                function<void()> task=tasks.front();
                tasks.pop();
                lock.unlock();  //手动解锁，任务的执行无需加锁
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        unique_lock<mutex> lock(mux);   //?防止正在等待的线程一直等待，加锁提高优先级
        stop=true; 
    }
    condition.notify_all(); //?至此，是否上述解释有问题呢，notifyall已经避免了线程一直等待，是否可以认为，stop并不是任意时刻可以执行的，而是当线程都不持锁的时刻，且无任务等待，因为等待要持锁，然后这时任务也结束了，析构函数抢到锁执行stop。但是如果这样，有任务等待那析构函数会拿不到锁，那进程是不是死机了呢？
    for(thread &t:threads)
    {
        t.join();   //?逐个停止，如果用detach()可能线程还没释放，进程就结束了
    }
}



