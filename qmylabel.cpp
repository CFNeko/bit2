#include "qmylabel.h"

QMylabel::QMylabel(QWidget *parent) : QLabel(parent)
{
    this->setPixmap(QPixmap(":/myresource/info_bg.jpg"));
    this->setScaledContents(true);
    this->setFixedSize(480,200);
    this->move(235,5);
    this->show();

    label_text = new QLabel(parent);
    label_text->move(250,45);
    label_text->setFixedWidth(370);
    label_text->setFixedHeight(100);
    label_text->setWordWrap(true);  //自动换行
    label_text->setStyleSheet("font: 12pt \"Ubuntu Mono\";");
}
