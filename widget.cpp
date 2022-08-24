#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->StartProperites();
}


void Widget::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    size_t index = 0;
    for (size_t i = 0; i < MATRIX_SIZE; ++i)
    {
        for (size_t j = 0; j < MATRIX_SIZE; ++j)
        {
            if (m[j* MATRIX_SIZE + i][0] >= 255)
                m[j* MATRIX_SIZE + i][0] = 255;

            qp.setPen(QColor::fromRgb(m[index][0],m[index][0], m[index][0]));
            qp.setBrush(QColor::fromRgb(m[index][0],m[index][0], m[index][0]));
            qp.drawRect(DOT_WH * j,DOT_WH * i, DOT_WH, DOT_WH);
            ++index;

            if (isWrite)
            {
                qp.setBrush(Qt::black);
                for(size_t i = 0; i < 10; ++i)
                    qp.drawRect(MATRIX_SIZE * DOT_WH + 70, 18 + 56 * i, answers[i][0] * 100, 20);
            }
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    size_t forX = (QCursor().pos().x() - this->pos().x()) / 20;
    size_t forY = (QCursor().pos().y() - this->pos().y() - 37) / 20;

    if (forX < 28 && forY < 28)
    {
        qDebug() <<"x: " <<forX<<"  y: "<<forY;
        qDebug() <<"matrix index: "<< forX* MATRIX_SIZE + forY;

        switch (event->buttons()) {
        case Qt::LeftButton:
            this->EditRect(forX, forY, Rect::Add);
            answers = w.Solve(m);
            isWrite = true;
            break;
        case Qt::RightButton:
             this->EditRect(forX, forY, Rect::Delete);
            isWrite = false;
            ui->solveLabel->setVisible(false);
            break;
        }
    }
    this->update();

    //this->label->setText(tr("x = %1, y = %2").arg(QCursor().pos().x() - this->pos().x()).arg(QCursor().pos().y() - this->pos().y() - 37));
}

void Widget::StartProperites()
{
    this->resize(DOT_WH * MATRIX_SIZE + 300, DOT_WH * MATRIX_SIZE + 50);
    this->setMaximumSize(DOT_WH * MATRIX_SIZE + 300, DOT_WH * MATRIX_SIZE + 50);
    this->setMinimumSize(DOT_WH * MATRIX_SIZE + 300, DOT_WH * MATRIX_SIZE + 50);
    this->setWindowTitle("Mini neural network");
    this->setMouseTracking(true);
    this->m.Resize(MATRIX_SIZE * MATRIX_SIZE, 1);
    this->w.ParseDataFromFile("BestGeneration");
    this->answers.Resize(10,1);

    ui->pushButton->setGeometry(20, DOT_WH * MATRIX_SIZE + 10, 100, 30);
    ui->pushButton->setText("Import data.");

    ui->solveLabel->setGeometry(130, DOT_WH * MATRIX_SIZE + 10, 100, 30);
    ui->solveLabel->setText("start");

    for(size_t i = 0; i < 10; ++i)
    {
        QLabel* L = new QLabel(this);
        L->setGeometry(MATRIX_SIZE * DOT_WH + 50, 18 + 56 * i, 20, 20);
        L->setText(QString::number(i) + ":");
    }
    this->test("DataSet");
}

void Widget::EditRect(const size_t& y, const size_t& x, const Rect& r) // change
{
    if (x - 1 > 0 && x + 1 < 28 && y - 1 > 0 && y + 1 < 28)
    {
        switch (r) {
        case Rect::Add:
                m[x*MATRIX_SIZE + (y - 1)][0] += WHITE/4;
                m[(x - 1) * MATRIX_SIZE + y][0] += WHITE/4;
                m[x*MATRIX_SIZE + y][0] += WHITE;
                m[(x + 1)*MATRIX_SIZE + y][0] += WHITE/4;
                m[x*MATRIX_SIZE + (y + 1)][0] += WHITE/4;

                m[(x-1)*MATRIX_SIZE + (y - 1)][0] += WHITE/10;
                m[(x + 1) * MATRIX_SIZE + (y - 1)][0] += WHITE/10;
                m[(x - 1)*MATRIX_SIZE + y + 1][0] += WHITE/10;
                m[(x + 1)*MATRIX_SIZE + (y + 1)][0] += WHITE/10;
            break;
        case Rect::Delete:
                m[x*MATRIX_SIZE + (y - 1)][0] = 0;
                m[(x - 1) * MATRIX_SIZE + y][0] = 0;
                m[x*MATRIX_SIZE + y][0] = 0;
                m[(x + 1)*MATRIX_SIZE + y][0] = 0;
                m[x*MATRIX_SIZE + (y + 1)][0] = 0;

                m[(x-1)*MATRIX_SIZE + (y - 1)][0] = 0;
                m[(x + 1) * MATRIX_SIZE + (y - 1)][0] = 0;
                m[(x - 1)*MATRIX_SIZE + y + 1][0] = 0;
                m[(x + 1)*MATRIX_SIZE + (y + 1)][0] = 0;
            break;
        }
    }
}


Widget::~Widget()
{
    delete ui;
}


void Widget::test(const std::string &fileName)
{
    file.open(fileName + ".txt", std::ios::in);

    if (file.is_open())
        qDebug() <<"file open.";
    else
        qDebug() <<"can't open file.";
}


void Widget::on_pushButton_clicked()
{
    isWrite = true;
    ui->solveLabel->setVisible(true);
    std::string temp;
    file>>temp;
    QString rightAnswer = QString::fromStdString(temp);
    int i = 0;
    while (i < 784)
    {
        file >> temp;
        m[i][0] = std::stof(temp);
        ++i;
    }
    this->update();
    answers = w.Solve(m);
    ui->solveLabel->setText(QString("Expected: ") + rightAnswer);
}
