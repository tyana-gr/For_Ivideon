#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QGraphicsItem>

#include "_ui_temp/ui_mainWidget.h"
#include "src/lampface.h"

using namespace protocol;

class MainWidget : public QWidget, public Ui::MainWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void connectPushButton_clicked();

    void connectionEstablished();
    void error();

    void buildCommand();

private:
    QTcpSocket socket;

    Command command;

    Color color;

    QGraphicsScene scene;
    QPen pen;
    QBrush brush;
    QGraphicsEllipseItem *ellipse;

    void closeConnection();

    void buildValue(QDataStream &stream);

    void manageCommand();

    void onLamp();
    void offLamp();
    void changeColor();

    void updateLamp();
};

#endif // MAINWIDGET_H
