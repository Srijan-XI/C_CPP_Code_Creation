#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace Config {
    // Application information
    const QString APP_NAME = "Modern Phonebook";
    const QString APP_VERSION = "1.0.0";
    const QString ORGANIZATION = "ModernPhonebook";
    
    // File extensions
    const QString EXPORT_FILE_EXTENSION = "json";
    const QString BACKUP_FILE_EXTENSION = "bak";
    
    // Default settings
    const int DEFAULT_WINDOW_WIDTH = 1000;
    const int DEFAULT_WINDOW_HEIGHT = 700;
    const int MIN_WINDOW_WIDTH = 800;
    const int MIN_WINDOW_HEIGHT = 600;
    
    // Contact validation
    const int MAX_NAME_LENGTH = 100;
    const int MAX_PHONE_LENGTH = 20;
    const int MAX_EMAIL_LENGTH = 100;
    
    // Threading
    const int MAX_THREAD_POOL_SIZE = 4;
    
    // UI settings
    const int STATUS_MESSAGE_TIMEOUT = 3000; // milliseconds
    const int SEARCH_DELAY = 300; // milliseconds
}

#endif // CONFIG_H
