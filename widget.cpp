#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QTransform>

int couner = 0;
bool on_off = true;

int counter_2 = 0;
bool on_off_2 = false;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/new/prefix1/car"));

    ui->label_2->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_3_clicked()
{
    on_off = false;
    QApplication::exit();
}

void Widget::on_pushButton_clicked()
{
    on_off = true;
    while(on_off == true){

    QApplication::processEvents();

    QPixmap ship(":/new/prefix1/car");
    QPixmap rotate(ship.size());

    QPainter p(&rotate);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.translate(rotate.size().width() / 2, rotate.size().height() / 2);
    p.rotate(couner);
    p.translate(-rotate.size().width() / 2, -rotate.size().height() / 2);

    p.drawPixmap(0, 0, ship);
    p.end();

//    ui->label->setPixmap(rotate);

    couner++;

    if(on_off_2 == true){

        QApplication::processEvents();
        QPixmap slope(rotate.size());
        slope.fill(Qt::XAxis);

        QPainter painter;
        painter.begin(&slope);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);

        QTransform transform;
        transform.translate(rect().width() / 2, 0);
        transform.rotate(counter_2, Qt::XAxis);
        transform.translate(-rect().width() / 2, 0);

        painter.setTransform(transform);
        painter.drawPixmap(0, 0, rotate);

        painter.end();

        if(counter_2 < 25){
            counter_2++;
        }
        ui->label->setPixmap(slope);
    }else{
        if(counter_2 > 0)
        {
            QApplication::processEvents();
            QPixmap slope(rotate.size());
            slope.fill(Qt::XAxis);

            QPainter painter;
            painter.begin(&slope);
            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::HighQualityAntialiasing);

            QTransform transform;
            transform.translate(rect().width() / 2, 0);
            transform.rotate(counter_2, Qt::XAxis);
            transform.translate(-rect().width() / 2, 0);

            painter.setTransform(transform);
            painter.drawPixmap(0, 0, rotate);

            painter.end();

            counter_2--;

            ui->label->setPixmap(slope);
        }else{
            ui->label->setPixmap(rotate);
        }
    }
    }
    return;
}

void Widget::on_pushButton_2_clicked()
{
    on_off = false;
}

bool Widget::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->label_2){
        if(e->type() == QEvent::Enter){
            on_off_2 = true;
            return true;
        }
        if(e->type() == QEvent::Leave){
            on_off_2 = false;
        }
    }

    return QWidget::eventFilter(o, e);
}
