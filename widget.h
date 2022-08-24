#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <Miniweb.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

static const int DOT_WH = 20, MATRIX_SIZE = 28;
static const int WHITE = 120;

enum class Rect
{
    Delete, Add
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void StartProperites();
    void EditRect(const size_t& y, const size_t& x,const Rect& r);
    void setWidthAns();

    MiniWeb w;
    Matrix answers;
    Matrix m;
    Ui::Widget *ui;
    bool isWrite = false;

    std::fstream file;
    void test(const std::string& fileName);
    //QLabel* label = new QLabel(this);
    //void mousePressEvent(QMouseEvent* event);
};
#endif // WIDGET_H
