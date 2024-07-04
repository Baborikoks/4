#include "employeemanager.h"

#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QHBoxLayout>
#include <QIcon>
//Баборико Карина 6 группа
//Задание 4

// Конструктор класса EmployeeManager
EmployeeManager::EmployeeManager(QWidget* parent) : QWidget(parent) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    QMenuBar* menuBar = new QMenuBar(this);
    layout->setMenuBar(menuBar);

    // Создадим меню "Файл"
    QMenu* fileMenu = menuBar->addMenu(QIcon(":/res/img/menu.png"),"Файл");

    // Добавим действия в меню "Файл"
    QAction* openAction = fileMenu->addAction(QIcon(":/res/img/otc.png"),"Открыть");
    QAction* saveAction = fileMenu->addAction(QIcon(":/res/img/sav.png"),"Сохранить");
    QAction* exitAction = fileMenu->addAction(QIcon(":/res/img/vxd.png"),"Выход");

    // Создание таблицы
    table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Имя", "Фамилия", "Должность", "Зарплата"});

    // Создание кнопок
    QPushButton* addButton = new QPushButton("Добавить");
    QPushButton* editButton = new QPushButton("Редактировать");
    QPushButton* deleteButton = new QPushButton("Удалить");

    // Компоновка элементов
    layout->addWidget(table);
    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);

    // Подключение сигналов
    connect(addButton, &QPushButton::clicked, this, &EmployeeManager::showAddDialog);
    connect(editButton, &QPushButton::clicked, this, &EmployeeManager::showEditDialog);
    connect(deleteButton, &QPushButton::clicked, this, &EmployeeManager::deleteEmployee);
    connect(openAction, &QAction::triggered, this, &EmployeeManager::loadDataFromFile);
    connect(saveAction, &QAction::triggered, this, &EmployeeManager::saveDataToFile);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
}

// Метод загрузки данных из файла
void EmployeeManager::loadDataFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Text Files (employee.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            table->setRowCount(0); // Очистка текущих данных
            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(",");
                if (fields.size() == 4) {
                    int rowCount = table->rowCount();
                    table->insertRow(rowCount);
                    table->setItem(rowCount, 0, new QTableWidgetItem(fields[0].trimmed()));
                    table->setItem(rowCount, 1, new QTableWidgetItem(fields[1].trimmed()));
                    table->setItem(rowCount, 2, new QTableWidgetItem(fields[2].trimmed()));
                    table->setItem(rowCount, 3, new QTableWidgetItem(fields[3].trimmed()));
                }
            }
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        }
    }
}

void EmployeeManager::showAddDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Добавить сотрудника");

    QLineEdit* nameEdit = new QLineEdit(&dialog);
    QLineEdit* surnameEdit = new QLineEdit(&dialog);
    QLineEdit* positionEdit = new QLineEdit(&dialog);
    QLineEdit* salaryEdit = new QLineEdit(&dialog);

    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Отмена", &dialog);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(new QLabel("Имя:"));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Фамилия:"));
    layout->addWidget(surnameEdit);
    layout->addWidget(new QLabel("Должность:"));
    layout->addWidget(positionEdit);
    layout->addWidget(new QLabel("Зарплата:"));
    layout->addWidget(salaryEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // Добавление новой строки в таблицу
        int rowCount = table->rowCount();
        table->insertRow(rowCount);
        table->setItem(rowCount, 0, new QTableWidgetItem(nameEdit->text()));
        table->setItem(rowCount, 1, new QTableWidgetItem(surnameEdit->text()));
        table->setItem(rowCount, 2, new QTableWidgetItem(positionEdit->text()));
        table->setItem(rowCount, 3, new QTableWidgetItem(salaryEdit->text()));
    }
}

void EmployeeManager::showEditDialog() {
    // Реализация диалогового окна для редактирования сотрудника
    // Получение выбранной строки
    int currentRow = table->currentRow();
    if (currentRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите сотрудника для редактирования.");
        return;
    }

    // Диалоговое окно для редактирования сотрудника
    QDialog dialog(this);
    dialog.setWindowTitle("Редактировать сотрудника");

    QLineEdit* nameEdit = new QLineEdit(&dialog);
    QLineEdit* surnameEdit = new QLineEdit(&dialog);
    QLineEdit* positionEdit = new QLineEdit(&dialog);
    QLineEdit* salaryEdit = new QLineEdit(&dialog);

    // Заполнение полей текущими данными
    nameEdit->setText(table->item(currentRow, 0)->text());
    surnameEdit->setText(table->item(currentRow, 1)->text());
    positionEdit->setText(table->item(currentRow, 2)->text());
    salaryEdit->setText(table->item(currentRow, 3)->text());

    QPushButton* okButton = new QPushButton("OK", &dialog);
    QPushButton* cancelButton = new QPushButton("Отмена", &dialog);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    layout->addWidget(new QLabel("Имя:"));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Фамилия:"));
    layout->addWidget(surnameEdit);
    layout->addWidget(new QLabel("Должность:"));
    layout->addWidget(positionEdit);
    layout->addWidget(new QLabel("Зарплата:"));
    layout->addWidget(salaryEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);


    if (dialog.exec() == QDialog::Accepted) {
        // Обновление данных в таблице
        table->setItem(currentRow, 0, new QTableWidgetItem(nameEdit->text()));
        table->setItem(currentRow, 1, new QTableWidgetItem(surnameEdit->text()));
        table->setItem(currentRow, 2, new QTableWidgetItem(positionEdit->text()));
        table->setItem(currentRow, 3, new QTableWidgetItem(salaryEdit->text()));
    }
}

void EmployeeManager::deleteEmployee() {
    // Реализация удаления сотрудника
    // Получение выбранной строки
    int currentRow = table->currentRow();
    if (currentRow == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите сотрудника для удаления.");
        return;
    }

    // Удаление выбранной строки
    table->removeRow(currentRow);
}

void EmployeeManager::saveDataToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Text Files (employee.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int i = 0; i < table->rowCount(); i++) {
                QString name = table->item(i, 0)->text();
                QString surname = table->item(i, 1)->text();
                QString position = table->item(i, 2)->text();
                QString salary = table->item(i, 3)->text();
                out << name << "," << surname << "," << position << "," << salary << "\n";
            }
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        }
    }
}
