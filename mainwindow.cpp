#include "mainwindow.h"
#include "ui_mainwindow.h"
#define pi 3.1416

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QWidget::setWindowFlags( Qt::CustomizeWindowHint );
    ui->setupUi(this);
    this->setWindowTitle("Clock");

    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    QPixmap pix(":/icon.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(pix);
    trayIcon->setToolTip("Clock");

    QMenu *menu = new QMenu(this);

    QAction *viewWindow = new QAction(("Развернуть"), this);
    QAction *hideWindow = new QAction(("Свернуть"), this);
    QAction *quitAction = new QAction(("Выход"), this);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(hideWindow, SIGNAL(triggered()), this, SLOT(hide()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    menu->addAction(viewWindow);
    menu->addAction(hideWindow);
    menu->addAction(quitAction);

    trayIcon->setContextMenu(menu);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QApplication::exit();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter qp(this);
    drawLines(&qp);
}

void MainWindow::drawLines(QPainter *qp)
{
    int w = MainWindow::width();    //window size
    float w2 = w/2;
    float x, y; //coordinates for divisions
    QTime current_time = QTime::currentTime();

    QPen clock3(Qt::white, 3, Qt::SolidLine);
    QPen clock2(Qt::white, 2, Qt::SolidLine);
    QPen clock1(Qt::white, 1, Qt::SolidLine);

    //drawing divisions
    qp->save();
    qp->translate(w2, w2);

    qp->setPen(clock3);

    for (int i = 0; i < 12; i++)
    {
        x = cos(i * pi/6) * w2;
        y = sin(i * pi/6) * w2;

        qp->drawLine(x * 0.8, y * 0.8, x, y);
    }

    qp->setPen(clock2);

    for (int i = 0; i < 60; i++)
    {
        x = cos(i * pi/30) * w2 * 0.8;
        y = sin(i * pi/30) * w2 * 0.8;
        qp->drawLine(x, y, x * 1.15, y * 1.15);
    }

    //drawing second hand
    qp->setPen(clock1);
    x = cos((current_time.second() - 15) * pi/30) * w2;
    y = sin((current_time.second() - 15) * pi/30) * w2;
    qp->drawLine(0, 0, x * 0.75, y * 0.75);

    //drawing minute hand
    qp->setPen(clock2);
    x = cos((current_time.minute() - 15) * pi/30) * w2;
    y = sin((current_time.minute() - 15) * pi/30) * w2;
    qp->drawLine(0, 0, x * 0.7, y * 0.7);

    //drawinf hour hand
    qp->setPen(clock3);
    x = cos((current_time.hour() - 15) * pi/30) * w2;
    y = sin((current_time.hour() - 15) * pi/30) * w2;
    qp->drawLine(0, 0, x * 0.65, y * 0.65);

    qp->restore();
}
