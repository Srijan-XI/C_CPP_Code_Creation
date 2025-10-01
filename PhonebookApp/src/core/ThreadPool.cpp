#include "ThreadPool.h"
#include <QThread>

ThreadPool* ThreadPool::s_instance = nullptr;

ThreadPool::ThreadPool(QObject* parent) : QObject(parent) {
    m_threadPool = new QThreadPool(this);
    
    // Set reasonable defaults
    int idealThreadCount = QThread::idealThreadCount();
    m_threadPool->setMaxThreadCount(idealThreadCount > 0 ? idealThreadCount : 4);
}

ThreadPool& ThreadPool::instance() {
    if (!s_instance) {
        s_instance = new ThreadPool();
    }
    return *s_instance;
}

void ThreadPool::setMaxThreadCount(int count) {
    m_threadPool->setMaxThreadCount(count);
}

int ThreadPool::maxThreadCount() const {
    return m_threadPool->maxThreadCount();
}

int ThreadPool::activeThreadCount() const {
    return m_threadPool->activeThreadCount();
}

void ThreadPool::waitForDone() {
    m_threadPool->waitForDone();
}

void ThreadPool::clear() {
    m_threadPool->clear();
}
