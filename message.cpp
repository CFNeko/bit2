#include "message.h"
#include "ui_message.h"

#include <QDebug>
#include <QtMath>
#include <QTimer>


message::message(QString str,QString time,QString author,QByteArray img,QString currentAuthor,QWidget *parent) :
    QLabel(parent),
    ui(new Ui::message)
{
    ui->setupUi(this);
    if(author == "doctor"){
        ui->headImg->setPixmap(QPixmap(":/doctor_pic.jpg").scaled(QSize(60,60)));
    }else if(author == "patient"){
        ui->headImg->setPixmap(QPixmap(":/resource111/patient_avatar.jpg").scaled(QSize(60,60)));
    }

    ui->time->setText(time.mid(0,16));

    QFontMetrics fontMetrics(ui->info->font());
    double fontSize = fontMetrics.height();
    int lineMax = 20;

    if(!img.isEmpty()){
        ui->info->show();
        ui->sendImg->show();

        QImage image;
        image.loadFromData(img);
        int width = image.width();
        int height = image.height();

        int fixedHeight = 300;
        double newWidth = double(width)/height*fixedHeight;


        QPixmap pixmap;
        pixmap.loadFromData(img);
        ui->sendImg->setPixmap(pixmap.scaled(QSize(newWidth-20,fixedHeight-20)));
        ui->info->setPlainText("");

        ui->info->setFixedHeight(fixedHeight);
        ui->info->setFixedWidth(newWidth);

        ui->sendImg->setFixedHeight(fixedHeight-20);
        ui->sendImg->setFixedWidth(newWidth-20);

        this->setFixedHeight(fixedHeight+50);



    }else{
        ui->info->show();
        ui->sendImg->hide();

        ui->info->setPlainText(str);


        int lineCount = qCeil(double(str.length())/lineMax);

        if(lineCount>2){
            ui->info->setFixedHeight(fontSize * lineCount * 1.3 + 5);
            ui->info->setFixedWidth(fontSize * lineMax * 0.87 +10);
            this->setFixedHeight(fontSize * lineCount *1.3 + 40);
        }else if(lineCount == 2){
            ui->info->setFixedHeight(fontSize * lineCount * 1.4 + 5);
            ui->info->setFixedWidth(fontSize * lineMax * 0.87 + 10);
            this->setFixedHeight(fontSize * lineCount *1.3 +50);
        }else{
            ui->info->setFixedHeight(fontSize * 1.6 + 5);
            ui->info->setFixedWidth(fontSize * str.length() *0.87 + 10);
            this->setFixedHeight(fontSize *1.3 +60);
        }




    }

    this->setMinimumWidth(fontSize * lineMax * 0.87 +200);

    ui->sendImg->move(ui->info->x()+10,ui->info->y()+10);

    Ismine = (author == currentAuthor);
    if(Ismine){
        ui->info->setStyleSheet("background-color: lightgreen;");
        ui->info->move(this->width() - ui->info->x() - ui->info->width(),ui->info->y());
        ui->headImg->move(this->width() - ui->headImg->x() - ui->headImg->width(),ui->headImg->y());
        ui->time->move(this->width() - ui->time->x() - ui->time->width(),ui->time->y());
        ui->sendImg->move(this->width() - ui->sendImg->x() - ui->sendImg->width(),ui->sendImg->y());

        ui->time->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    }else{
        ui->info->setStyleSheet("background-color: lightblue;");
    }

}

message::~message()
{
    delete ui;
}

