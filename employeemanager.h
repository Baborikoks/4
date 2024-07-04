#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <QWidget>
#include <QTableWidget>

class EmployeeManager : public QWidget {
    Q_OBJECT

public:
    explicit EmployeeManager(QWidget* parent = nullptr);

private slots:
    void loadDataFromFile();
    void saveDataToFile();
    void showAddDialog();
    void showEditDialog();
    void deleteEmployee();

private:
    QTableWidget* table;
};

#endif // EMPLOYEEMANAGER_H
