#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "draw_tool_defines.h"
#include <QFileDialog>
#include <QStyledItemDelegate>
#include <QDebug>
#include <QFile>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPage();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_button->deleteLater();
}

void MainWindow::initPage()
{
    ui->cmbBackLabel->setItemDelegate(new QStyledItemDelegate(this));
    ui->cmbCurrentLabel->setItemDelegate(new QStyledItemDelegate(this));

    ui->buttonGroup->setId(ui->btnRect, DrawTool::BrushStroke::RECT);
    ui->buttonGroup->setId(ui->btnCircle, DrawTool::BrushStroke::CIRCLE);

    m_button = new QButtonGroup(this);

    QPoint pos(0, 0);
    //for (auto& t : DrawTool::tool_property())
    for (auto& t : DrawTool::DrawToolDefine::instance().m_MenuMap)
    {
        //auto btn = new QPushButton(DrawTool::tool_property().key(t), this);
        auto btn = new QPushButton(DrawTool::DrawToolDefine::instance().m_MenuMap.key(t), this);
        m_button->addButton(btn, t.toInt());
        ui->gridTool->addWidget(btn, pos.x(), pos.y());
        pos.setY(pos.y() + 1);

        if (pos.y() % 4 == 0)
        {
            pos.setX(pos.x() + 1);
            pos.setY(0);
        }
    }

    connect(m_button, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, [this](int id)
    {
        DrawTool::DrawToolData op = ui->widget->operate();
        op.operate = id;

        ui->widget->setOperate(op);
    });

    auto slot_operate = [this](const QString &)
    {
        DrawTool::DrawToolData op = ui->widget->operate();
        op.pre_label_color = ui->cmbCurrentLabel->currentData().value<QColor>();
        op.back_label_color = ui->cmbBackLabel->currentData().value<QColor>();
        op.all = !ui->cmbBackLabel->currentData().value<QColor>().isValid();
        ui->widget->setOperate(op);
    };

    auto slot_update = [this](int val)
    {
        DrawTool::DrawToolData op = ui->widget->operate();
        op.width = ui->sliderSize->value();
        double t = ui->sliderDiaphaneity->value();
        op.diaphaneity = 255 * (1 - t / 100);
        op.diaphaneity = std::max(0, op.diaphaneity);
        op.diaphaneity = std::min(255, op.diaphaneity);

        ui->widget->setOperate(op);
    };

    connect(ui->cmbBackLabel, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), this, slot_operate);
    connect(ui->cmbCurrentLabel, static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged), this, slot_operate);

    connect(ui->sliderSize, &QSlider::valueChanged, this, slot_update);
    connect(ui->sliderDiaphaneity, &QSlider::valueChanged, this, slot_update);

    connect(ui->buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, [this](int val)
    {
        DrawTool::DrawToolData op = ui->widget->operate();
        op.stroke = (DrawTool::BrushStroke)val;

        ui->widget->setOperate(op);
    });

    connect(ui->btnOpen, &QPushButton::clicked, this, [this]()
    {
        QString path = QFileDialog::getOpenFileName(this, "open file dialog", QDir::currentPath(), "image files(*.bmp;*.png;*.jpg)");

        DrawTool::ImageShow img;
        img.img.load(path);
        img.size = img.img.size();

        ui->widget->setImg(img);

    });

    auto addItem = [this](const QString& name, QColor color, QComboBox* cmb)
    {
        QPixmap pixmap(14, 14);

        pixmap.fill(color);
        cmb->addItem(QIcon(pixmap), name, color);
    };

    addItem("All Labels", QColor(), ui->cmbBackLabel);

    addItem("Label 1", Qt::red, ui->cmbBackLabel);
    addItem("Label 2", Qt::green, ui->cmbBackLabel);
    addItem("Label 3", Qt::blue, ui->cmbBackLabel);
    addItem("Label 4", Qt::darkYellow, ui->cmbBackLabel);
    addItem("Label 5", Qt::darkGreen, ui->cmbBackLabel);
    addItem("Label 6", Qt::darkRed, ui->cmbBackLabel);

    addItem("Label 1", Qt::red, ui->cmbCurrentLabel);
    addItem("Label 2", Qt::green, ui->cmbCurrentLabel);
    addItem("Label 3", Qt::blue, ui->cmbCurrentLabel);
    addItem("Label 4", Qt::darkYellow, ui->cmbCurrentLabel);
    addItem("Label 5", Qt::darkGreen, ui->cmbCurrentLabel);
    addItem("Label 6", Qt::darkRed, ui->cmbCurrentLabel);

    DrawTool::ImageShow img;
    img.img.load("./img_curr.png");
    img.size = img.img.size();

    ui->widget->setImg(img);
}
