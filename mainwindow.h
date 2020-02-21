#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
    void on_actionexit_triggered();

    void on_actionPlay_triggered();

    void on_actionOrbit_triggered();

    void groupActions();

    void on_actionTranslate_triggered();

    void on_actionZoom_triggered();

    void on_actionPerspective_triggered();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
