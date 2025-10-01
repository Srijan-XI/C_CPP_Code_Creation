# Modern Phonebook Application

A feature-rich phonebook application built with Qt6/Qt5 and C++20, featuring a modern GUI and efficient data structures.

## Features

- **Modern GUI**: Clean, intuitive interface with Qt6 Widgets
- **Efficient Data Structures**: Binary Search Tree for fast contact management
- **Search & Sort**: Advanced search with fuzzy matching and multiple sorting options
- **Import/Export**: Support for JSON, CSV, and XML formats
- **Database Integration**: SQLite database with automatic migrations
- **Thread Safety**: Multi-threaded operations with thread pool management
- **Comprehensive Testing**: Unit tests for all major components
- **Cross-Platform**: Runs on Windows, macOS, and Linux

## Technology Stack

- **Framework**: Qt6 (with Qt5 fallback support)
- **Language**: C++20
- **Database**: SQLite
- **Build System**: CMake
- **Testing**: Google Test
- **Data Structures**: Custom Binary Search Tree implementation

## Project Structure

```
PhonebookApp/
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # Project documentation
├── resources/                  # Application resources
│   ├── resources.qrc           # Qt resource file
│   └── icons/                  # SVG icons for UI
│       ├── phonebook.svg
│       ├── add.svg
│       ├── edit.svg
│       ├── delete.svg
│       ├── import.svg
│       ├── export.svg
│       ├── lock.svg
│       └── search.svg
│
├── src/                        # Source code
│   ├── main.cpp                # Application entry point
│   │
│   ├── gui/                    # User Interface components
│   │   ├── MainWindow.cpp      # Main application window
│   │   └── MainWindow.h
│   │
│   ├── core/                   # Core business logic
│   │   ├── Contact.cpp         # Contact data model
│   │   ├── Contact.h
│   │   ├── ContactManager.cpp  # Contact management logic
│   │   ├── ContactManager.h
│   │   ├── BST.cpp             # Binary Search Tree implementation
│   │   ├── BST.h
│   │   ├── SearchSort.cpp      # Search and sorting algorithms
│   │   ├── SearchSort.h
│   │   ├── ThreadPool.cpp      # Thread pool for async operations
│   │   ├── ThreadPool.h
│   │   ├── FileHandler.cpp     # Import/Export functionality
│   │   └── FileHandler.h
│   │
│   ├── db/                     # Database layer
│   │   ├── Database.cpp        # SQLite database wrapper
│   │   ├── Database.h
│   │   └── migrations.sql      # Database schema and migrations
│   │
│   └── utils/                  # Utility classes
│       ├── Logger.cpp          # Logging system
│       ├── Logger.h
│       └── Config.h            # Application configuration
│
├── include/                    # Public headers (reserved for future use)
├── build/                      # Build output directory
└── tests/                      # Unit tests
    ├── test_contacts.cpp       # Contact class tests
    ├── test_bst.cpp           # BST implementation tests
    ├── test_database.cpp      # Database functionality tests
    └── test_filehandler.cpp   # File I/O tests
```

## Prerequisites

### Required Dependencies
- **Qt6 (6.5+)** or **Qt5 (5.15+)**
  - Core, Gui, Widgets, Sql, Concurrent modules
- **CMake 3.22+**
- **C++20 compatible compiler**
  - GCC 10+, Clang 10+, or MSVC 2019+

### Optional Dependencies
- **Google Test** (for running unit tests)
- **SQLite3** (usually bundled with Qt)

## Building the Application

### Using CMake (Recommended)

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd PhonebookApp
   ```

2. **Configure the build**
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Build the application**
   ```bash
   cmake --build .
   ```

4. **Run the application**
   ```bash
   ./PhonebookApp
   ```

### Platform-Specific Instructions

#### Windows (MinGW/MSYS2)
```bash
# Install Qt6 via MSYS2
pacman -S mingw-w64-x86_64-qt6

# Configure with specific Qt path if needed
cmake -DQt6_DIR="C:/msys64/mingw64/lib/cmake/Qt6" ..
```

#### Windows (Visual Studio)
```bash
# Use Qt Online Installer or vcpkg
cmake -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64" ..
```

#### macOS
```bash
# Install Qt via Homebrew
brew install qt6

# Configure build
cmake -DCMAKE_PREFIX_PATH="$(brew --prefix qt6)" ..
```

#### Linux (Ubuntu/Debian)
```bash
# Install Qt6 development packages
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential

# Build normally
cmake ..
make
```

## Usage

### Basic Operations

1. **Adding Contacts**: Click "Add Contact" button or use Ctrl+A
2. **Editing Contacts**: Double-click a contact or select and click "Edit"
3. **Deleting Contacts**: Select a contact and click "Delete" or press Delete key
4. **Searching**: Use the search bar to find contacts by name, phone, or email

### Advanced Features

- **Fuzzy Search**: The search supports approximate matching
- **Sorting**: Contacts are automatically sorted alphabetically by name
- **Import/Export**: Use File menu to import/export contacts in JSON, CSV, or XML format

### Keyboard Shortcuts

- `Ctrl+A`: Add new contact
- `Ctrl+F`: Focus search bar
- `Delete`: Delete selected contact
- `Ctrl+Q`: Quit application

## Architecture

### Data Structure
The application uses a custom Binary Search Tree (BST) implementation for efficient contact storage and retrieval:
- **O(log n)** average insertion, deletion, and search operations
- **O(n)** in-order traversal for sorted contact listing
- Thread-safe operations with mutex protection

### Design Patterns
- **MVC Pattern**: Separation of data (Contact), logic (ContactManager), and presentation (MainWindow)
- **Observer Pattern**: Qt's signal-slot mechanism for event handling
- **Singleton Pattern**: Logger and ThreadPool instances
- **Template Pattern**: Generic BST implementation

### Database Integration
- SQLite database for persistent storage
- Automatic schema migrations
- Connection pooling and error handling
- SQL injection prevention with prepared statements

## Testing

Run the unit tests to verify functionality:

```bash
# Build tests (if Google Test is available)
cmake -DBUILD_TESTING=ON ..
cmake --build .

# Run tests
ctest
```

### Test Coverage
- Contact validation and comparison
- BST operations and invariants
- Database CRUD operations
- File import/export functionality

## Configuration

The application stores configuration in platform-appropriate locations:
- **Windows**: `%APPDATA%/ModernPhonebook/`
- **macOS**: `~/Library/Application Support/ModernPhonebook/`
- **Linux**: `~/.local/share/ModernPhonebook/`

### Logging
Logs are written to `phonebook.log` in the application data directory.
Log levels: DEBUG, INFO, WARNING, ERROR, CRITICAL

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-feature`)
3. Make your changes and add tests
4. Ensure all tests pass
5. Commit your changes (`git commit -am 'Add new feature'`)
6. Push to the branch (`git push origin feature/new-feature`)
7. Create a Pull Request

### Code Style
- Follow C++ Core Guidelines
- Use meaningful variable and function names
- Add documentation for public APIs
- Maintain const-correctness
- Use RAII for resource management

## Troubleshooting

### Common Issues

1. **Qt6 not found**
   - Install Qt6 development packages
   - Set `CMAKE_PREFIX_PATH` to Qt installation directory
   - Check that required Qt modules are installed

2. **Build errors with C++20**
   - Ensure compiler supports C++20
   - Update to a recent compiler version
   - Check CMake is version 3.22 or higher

3. **Database errors**
   - Check write permissions in application data directory
   - Verify SQLite support in Qt installation
   - Check database file is not corrupted

4. **Missing icons or resources**
   - Ensure resource files are properly embedded
   - Check QRC file syntax
   - Verify icon files exist in resources/icons/

### Performance Tips
- For large contact lists (>10,000), consider database-only mode
- Use search to filter large datasets
- Regularly backup your contacts using export functionality

## License

This project is open source. See LICENSE file for details.

## Version History

- **v1.0.0**: Initial release with core functionality
  - Basic contact management
  - BST data structure implementation
  - SQLite database integration
  - Import/Export capabilities
  - Modern Qt6 GUI

## Future Enhancements

- [ ] Contact photos and attachments
- [ ] Advanced search filters
- [ ] Contact categories and groups
- [ ] Cloud synchronization
- [ ] Mobile responsive design
- [ ] Plugin system for extensions
- [ ] Multi-language support
- [ ] Dark theme support

## Support

For questions, bug reports, or feature requests, please create an issue in the project repository.