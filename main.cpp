#include "mainwindow.h"
#include <QApplication>
#include <VTF/Pointers>
#include <QFile>
#include <iostream>

#include "Paths/parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        qsrand(0);
        QFile f("Paths/t1.k16");
        f.open(QFile::ReadOnly);
        CNCCommandList list = CNCParser::parse(f);
        MainWindow w;
        w.show();

        return a.exec();
    } catch (const VTF::Exception& e)
    {
        std::cerr << e.message();
    }
}
