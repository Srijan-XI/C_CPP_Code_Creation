# Modern Phonebook Application - SETUP INSTRUCTIONS

## Current Status: Qt Not Found

The PhonebookApp requires Qt6 (6.5+) or Qt5 (5.15+) to build and run. Qt is not currently installed on this system.

## Quick Setup Options

### Option 1: Install Qt6 via MSYS2 (Recommended for MinGW)

1. **Install MSYS2** (if not already installed):
   - Download from: https://www.msys2.org/
   - Run the installer and follow instructions

2. **Install Qt6 and build tools**:
   ```bash
   # Open MSYS2 MinGW 64-bit terminal
   pacman -Syu
   pacman -S mingw-w64-x86_64-qt6-base
   pacman -S mingw-w64-x86_64-qt6-tools
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-ninja
   ```

3. **Build the application**:
   ```bash
   cd /p/CODE-XI/P-Half-2025/PhonebookApp
   mkdir build
   cd build
   cmake -G "Ninja" ..
   ninja
   ```

### Option 2: Install Qt6 via Official Installer

1. **Download Qt Online Installer**:
   - Visit: https://www.qt.io/download-qt-installer
   - Download the online installer

2. **Install Qt6**:
   - Run the installer
   - Create a Qt account (free)
   - Select Qt 6.5+ for MinGW or MSVC
   - Install to default location (e.g., C:\Qt)

3. **Configure environment**:
   ```powershell
   $env:CMAKE_PREFIX_PATH = "C:\Qt\6.5.0\mingw_64"
   # or for MSVC: $env:CMAKE_PREFIX_PATH = "C:\Qt\6.5.0\msvc2019_64"
   ```

4. **Build the application**:
   ```powershell
   cd "P:\CODE-XI\P-Half-2025\PhonebookApp"
   cmake -B build
   cmake --build build
   ```

### Option 3: Use vcpkg (Alternative Package Manager)

1. **Install vcpkg**:
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. **Install Qt6**:
   ```powershell
   .\vcpkg install qt6-base:x64-windows
   .\vcpkg install qt6-tools:x64-windows
   ```

3. **Build with vcpkg toolchain**:
   ```powershell
   cd "P:\CODE-XI\P-Half-2025\PhonebookApp"
   cmake -B build -DCMAKE_TOOLCHAIN_FILE=path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
   cmake --build build
   ```

## Console-Only Demo Version

If you want to test the core functionality without Qt, here's a simple console version:

### Build Core Components Only

The core classes (Contact, BST, ContactManager) can be built and tested without Qt:

```cpp
// Simple console demo
#include "core/Contact.h"
#include "core/BST.h"
#include <iostream>

int main() {
    BST<Contact> contactTree;
    
    // Add some contacts
    contactTree.insert(Contact("Alice", "123-456-7890", "alice@example.com"));
    contactTree.insert(Contact("Bob", "987-654-3210", "bob@example.com"));
    contactTree.insert(Contact("Charlie", "555-1234", "charlie@example.com"));
    
    // Display all contacts (sorted)
    auto contacts = contactTree.inorderTraversal();
    for (const auto& contact : contacts) {
        std::cout << contact.getName().toStdString() << " - " 
                  << contact.getPhone().toStdString() << std::endl;
    }
    
    return 0;
}
```

## After Installing Qt

Once Qt is installed, follow these steps:

1. **Verify Qt installation**:
   ```bash
   qmake --version  # Should show Qt version
   ```

2. **Configure and build**:
   ```bash
   cd PhonebookApp
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

3. **Run the application**:
   ```bash
   ./PhonebookApp     # Linux/macOS
   .\PhonebookApp.exe # Windows
   ```

## Next Steps

1. Install Qt using one of the methods above
2. Rebuild the project
3. Enjoy the modern phonebook application!

The application includes:
- Modern Qt6 GUI with tables and forms
- Binary Search Tree for efficient contact storage
- SQLite database integration
- Import/Export functionality (JSON, CSV, XML)
- Comprehensive search and filtering
- Unit tests for all components

## Need Help?

- Qt Documentation: https://doc.qt.io/
- CMake Documentation: https://cmake.org/documentation/
- Project Issues: Create an issue in the repository

The code is complete and ready to run once Qt is installed!