#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QBuffer>
#include <QPen>
#include <QRGB>
#include <fstream>
#include "ui_gui.h"

#include "Network.h"
#include "PictureMatrix.h"

class gui : public QMainWindow
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    ~gui();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Ui::guiClass ui;
    QPixmap* canvas;

    int lastX, lastY;
    bool isMouseActive = false;
    Network net = Network(false);

    void clear();
    void submit();
};
