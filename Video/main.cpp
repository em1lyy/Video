#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc == 2)
    {
        std::string path(argv[1]);
        MainWindow *w = new MainWindow(0, path);
        w->setWindowIcon(QIcon::fromTheme("video"));
        w->show();
    }
    else if (argc >= 2)
    {
        std::cout << "ARGUMENT LENGTH MUST BE 0 OR 1!\n EXITING!" << endl;
        return 1;
    }
    else
    {
        MainWindow *w = new MainWindow(0, "");
        w->setWindowIcon(QIcon::fromTheme("video"));
        w->show();
    }

    return a.exec();
}
