#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QMutex>

class Logger : public QObject {
    Q_OBJECT
    
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };
    
    static Logger& instance();
    
    void setLogLevel(LogLevel level);
    void setLogFile(const QString& filePath);
    
    static void debug(const QString& message);
    static void info(const QString& message);
    static void warning(const QString& message);
    static void error(const QString& message);
    static void critical(const QString& message);
    
private:
    explicit Logger(QObject* parent = nullptr);
    ~Logger();
    
    void log(LogLevel level, const QString& message);
    QString levelToString(LogLevel level) const;
    QString getCurrentTimestamp() const;
    
    LogLevel m_logLevel;
    QFile* m_logFile;
    QTextStream* m_logStream;
    QMutex m_mutex;
    
    static Logger* s_instance;
};

#endif // LOGGER_H
