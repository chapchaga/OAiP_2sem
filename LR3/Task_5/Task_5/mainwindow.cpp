#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);

    openButton = new QPushButton("Выбрать папку");
    resultLabel = new QLabel("Файлы: 0\nПапки: 0");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(openButton);
    layout->addWidget(resultLabel);

    central->setLayout(layout);
    setCentralWidget(central);

    connect(openButton, &QPushButton::clicked,
            this, &MainWindow::openFolder);

    setWindowTitle("Рекурсивный подсчет файлов и папок");
    resize(400,200);
}

void MainWindow::openFolder()
{
    QString path = QFileDialog::getExistingDirectory(this, "Выберите папку");

    if(path.isEmpty())
        return;

    int files = 0;
    int folders = 0;

    recursiveCount(path, files, folders);

    resultLabel->setText(
        "Файлы: " + QString::number(files) +
        "\nПапки: " + QString::number(folders)
        );
}

void MainWindow::recursiveCount(QString path, int &files, int &folders)
{
    QDir dir(path);

    QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot |
                                           QDir::AllDirs |
                                           QDir::Files);

    for(int i = 0; i < list.size(); i++)
    {
        QFileInfo info = list[i];

        if(info.isDir())
        {
            folders++;
            recursiveCount(info.absoluteFilePath(), files, folders);
        }
        else
        {
            files++;
        }
    }
}
