#include "gui.h"


gui::gui(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    canvas = new QPixmap(448, 448);
    canvas->fill();
    ui.canvasLabel->setPixmap(*canvas);
    connect(ui.clearButton, &QPushButton::pressed, this, &gui::clear);
    connect(ui.submitButton, &QPushButton::pressed, this, &gui::submit);
    setMouseTracking(true);
}

void gui::mouseMoveEvent(QMouseEvent* e)
{
    if (!isMouseActive)
    {
        isMouseActive = true;
        lastX = e->x();
        lastY = e->y();
        return;
    }


    QPainter painter = QPainter(canvas);
    painter.setPen(QPen(Qt::black, 28));
    painter.drawLine(lastX, lastY, e->x(), e->y());
    painter.end();

    ui.canvasLabel->setPixmap(*canvas);

    lastX = e->x();
    lastY = e->y();
}

void gui::mouseReleaseEvent(QMouseEvent* e)
{
    isMouseActive = false;
}


void gui::clear()
{
    canvas->fill();
    ui.canvasLabel->setPixmap(*canvas);
    ui.textLabel->setText(QString(""));
    update();
}

void gui::submit()
{
    QImage image = ui.canvasLabel->pixmap().toImage();
    
    double** arr = new double*[448];
    for (int i = 0; i < 448; i++)
    {
        arr[i] = new double[448];
    }
    
    for (int i = 0; i < 448; i++)
    {
        for (int j = 0; j < 448; j++)
        {
            arr[j][i] = static_cast<double>(qRed(image.pixel(j, i)));
        }
    }

    double** input = new double* [PictureMatrix::size];

    for (int i = 0; i < PictureMatrix::size; i++)
    {
        input[i] = new double[PictureMatrix::size];
    }

    for (int i = 0; i < PictureMatrix::size; i++)
    {
        for (int j = 0; j < PictureMatrix::size; j++)
        {
            double average = 0;
            auto test = 0;
            for (int y = 0; y < 16; y++)
            {
                for (int x = 0; x < 16; x++)
                {
                    test++;
                    average += arr[x + j * 16][y + i * 16] ;
                }
            }

            if (average / 256 < 180)
            {
                input[j][i] = 1;
            }
            else
            {
                input[j][i] = 0;
            }
        }
    }
    
    PictureMatrix p = PictureMatrix(input, 0);
    Network net(false);
    ui.textLabel->setText(QString::number(net.Calculate(p)));
    
    for (int i = 0; i < 448; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;
}

gui::~gui()
{
    delete canvas;
}
