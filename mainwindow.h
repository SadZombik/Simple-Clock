#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QPixmap>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    void closeEvent(QCloseEvent *event);

private:
    QSystemTrayIcon *trayIcon;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
