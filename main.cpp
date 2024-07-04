#include "employeemanager.h"

#include <QApplication>

// Баборико Карина 6 группа 
// Задание 3-4 по учебной практике  

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmployeeManager w;
    w.show();
    return a.exec();
}
