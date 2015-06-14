#include "src/mainwidget.h"

#include <QHostAddress>
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    graphicsView->hide();
    adjustSize();

    graphicsView->setScene(&scene);
    scene.setSceneRect(0, 0, 320, 316);

    QImage image;
    image.load(":/images/lamp.jpg");
    scene.addPixmap(QPixmap::fromImage(image));

    pen.setColor(Qt::black);
    pen.setWidth(1);

    brush.setColor(Qt::black);

    ellipse = scene.addEllipse(38, 65, 244, 244, pen, brush);

    connect(connectPushButton, SIGNAL(clicked()), this, SLOT(connectPushButton_clicked()));

    connect(&socket, SIGNAL(connected()), this, SLOT(connectionEstablished()));
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(buildCommand()));


    command.length = 0;
}

MainWidget::~MainWidget()
{
    closeConnection();
}

void MainWidget::connectPushButton_clicked()
{
    socket.connectToHost(QHostAddress(addressLineEdit->text()), portSpinBox->value());
}

void MainWidget::connectionEstablished()
{
    widget->hide();
    graphicsView->show();
    adjustSize();
}

void MainWidget::error()
{
    graphicsView->hide();
    widget->show();
    adjustSize();

    QMessageBox::warning(this,
                         tr("Connection error"),
                         socket.errorString(),
                         QMessageBox::Ok);

    closeConnection();
}

void MainWidget::closeConnection()
{
    socket.close();
}

void MainWidget::buildCommand()
{
    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_4_5);

    forever {
        if(command.length == 0) {
            if(socket.bytesAvailable() < 3)
                break;

            in >> command.type >> command.length;
        }

        if(socket.bytesAvailable() < command.length)
            break;

        if(command.length > 0)
            buildValue(in);

        manageCommand();

        command.length = 0;
    }
}

void MainWidget::buildValue(QDataStream &stream)
{
    switch (command.type) {
    case COLOR:
        stream >> color.r >> color.g >> color.b;
        break;
    default:
        QByteArray trash;
        trash.resize(command.length);
        stream >> trash;
        break;
    }
}

void MainWidget::manageCommand()
{
    switch (command.type) {
    case ON:
        onLamp();
        break;
    case OFF:
        offLamp();
        break;
    case COLOR:
        changeColor();
        break;
    default:
        break;
    }
}

void MainWidget::onLamp()
{
    brush.setStyle(Qt::Dense1Pattern);

    updateLamp();
}

void MainWidget::offLamp()
{
    brush.setStyle(Qt::NoBrush);

    updateLamp();
}

void MainWidget::changeColor()
{
    brush.setColor(QColor(color.r, color.g, color.b));

    updateLamp();
}

void MainWidget::updateLamp()
{
    ellipse->setPen(pen);
    ellipse->setBrush(brush);
    ellipse->update(38, 65, 244, 244);
}
