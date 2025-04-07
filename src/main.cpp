#include "threadpool.hpp"
#include <iostream>
#include <stdio.h>
#include <chrono>   //?提供不同单位的时间间隔
void func()
{
    cout<<this_thread::get_id()<<"---"<<"#####"<<endl;
}
int main()
{
    ThreadPool threadpool(4);
    for(int i=0;i<10;++i)
    {
        threadpool.enqueue([i]{
            // cout<<this_thread::get_id()<<"---"<<i<<endl;
            this_thread::sleep_for(chrono::seconds(1));    //?线程静态函数sleep
        });
    }
    for(int i=0;i<10;++i)
    {
        threadpool.enqueue(func);
    }
    return 0;
    //主线程也可调用this_thread::sleep_for
}   
