#include <QApplication>
#include <QIcon>
#include "gui/MainWindow.h"
#include "utils/Config.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("PhonebookApp");
    QApplication::setOrganizationName("ModernPhonebook");

    QIcon appIcon(":/icons/phonebook.svg");
    QApplication::setWindowIcon(appIcon);

    MainWindow w;
    w.show();
    return app.exec();
}