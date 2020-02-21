#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->groupActions();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionexit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionPlay_triggered()
{

}

void MainWindow::on_actionOrbit_triggered()
{
    this->ui->openGLWidget->setViewMode(1);
}

void MainWindow::groupActions(){

    QActionGroup *actions = new QActionGroup(this);
    actions->addAction(this->ui->actionZoom);
    actions->addAction(this->ui->actionOrbit);
    actions->addAction(this->ui->actionPerspective);
    actions->addAction(this->ui->actionTranslate);

}

void MainWindow::on_actionTranslate_triggered()
{
    this->ui->openGLWidget->setViewMode(2);
}

void MainWindow::on_actionZoom_triggered()
{
    this->ui->openGLWidget->setViewMode(3);
}

void MainWindow::on_actionPerspective_triggered()
{
    this->ui->openGLWidget->setViewMode(4);
}
