#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <QObject>
#include <QThreadPool>
#include <QRunnable>
#include <QFuture>
#include <QtConcurrent>
#include <functional>

class ThreadPool : public QObject {
    Q_OBJECT
    
public:
    explicit ThreadPool(QObject* parent = nullptr);
    ~ThreadPool() = default;
    
    // Static instance for global access
    static ThreadPool& instance();
    
    // Thread pool management
    void setMaxThreadCount(int count);
    int maxThreadCount() const;
    int activeThreadCount() const;
    
    // Task execution
    template<typename Func>
    QFuture<void> execute(Func&& function);
    
    template<typename Func, typename Result = std::invoke_result_t<Func>>
    QFuture<Result> executeWithResult(Func&& function);
    
    // Utility methods
    void waitForDone();
    void clear();
    
private:
    QThreadPool* m_threadPool;
    static ThreadPool* s_instance;
};

// Template implementations
template<typename Func>
QFuture<void> ThreadPool::execute(Func&& function) {
    return QtConcurrent::run(m_threadPool, std::forward<Func>(function));
}

template<typename Func, typename Result>
QFuture<Result> ThreadPool::executeWithResult(Func&& function) {
    return QtConcurrent::run(m_threadPool, std::forward<Func>(function));
}

#endif // THREADPOOL_H
