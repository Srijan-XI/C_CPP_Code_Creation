#include "Logger.h"
#include <QDateTime>
#include <QDebug>
#include <QMutexLocker>
#include <QStandardPaths>
#include <QDir>

Logger* Logger::s_instance = nullptr;

Logger::Logger(QObject* parent)
    : QObject(parent)
    , m_logLevel(Info)
    , m_logFile(nullptr)
    , m_logStream(nullptr) {
}

Logger::~Logger() {
    if (m_logStream) {
        delete m_logStream;
    }
    if (m_logFile) {
        m_logFile->close();
        delete m_logFile;
    }
}

Logger& Logger::instance() {
    if (!s_instance) {
        s_instance = new Logger();
        
        // Set default log file
        QString logDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        QDir().mkpath(logDir);
        QString logFilePath = logDir + "/phonebook.log";
        s_instance->setLogFile(logFilePath);
    }
    return *s_instance;
}

void Logger::setLogLevel(LogLevel level) {
    m_logLevel = level;
}

void Logger::setLogFile(const QString& filePath) {
    QMutexLocker locker(&m_mutex);
    
    if (m_logStream) {
        delete m_logStream;
        m_logStream = nullptr;
    }
    
    if (m_logFile) {
        m_logFile->close();
        delete m_logFile;
        m_logFile = nullptr;
    }
    
    m_logFile = new QFile(filePath);
    if (m_logFile->open(QIODevice::WriteOnly | QIODevice::Append)) {
        m_logStream = new QTextStream(m_logFile);
    } else {
        qWarning() << "Failed to open log file:" << filePath;
        delete m_logFile;
        m_logFile = nullptr;
    }
}

void Logger::debug(const QString& message) {
    instance().log(Debug, message);
}

void Logger::info(const QString& message) {
    instance().log(Info, message);
}

void Logger::warning(const QString& message) {
    instance().log(Warning, message);
}

void Logger::error(const QString& message) {
    instance().log(Error, message);
}

void Logger::critical(const QString& message) {
    instance().log(Critical, message);
}

void Logger::log(LogLevel level, const QString& message) {
    if (level < m_logLevel) {
        return;
    }
    
    QMutexLocker locker(&m_mutex);
    
    QString logMessage = QString("[%1] %2: %3")
                        .arg(getCurrentTimestamp())
                        .arg(levelToString(level))
                        .arg(message);
    
    // Output to console
    qDebug() << logMessage;
    
    // Output to file if available
    if (m_logStream) {
        *m_logStream << logMessage << Qt::endl;
        m_logStream->flush();
    }
}

QString Logger::levelToString(LogLevel level) const {
    switch (level) {
        case Debug: return "DEBUG";
        case Info: return "INFO";
        case Warning: return "WARNING";
        case Error: return "ERROR";
        case Critical: return "CRITICAL";
        default: return "UNKNOWN";
    }
}

QString Logger::getCurrentTimestamp() const {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}
