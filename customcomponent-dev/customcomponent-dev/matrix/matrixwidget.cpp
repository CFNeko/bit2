#include "matrixwidget.h"
#include "ui_matrixwidget.h"
#include <QDoubleSpinBox>

MatrixWidget::MatrixWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixWidget)
{
    ui->setupUi(this);

    //我们的控件自适应其父控件的大小，这样做的好处就是在进行布局的时候只需要注意父类的布局就可以了
    this->setFixedSize(parent->size());
}

MatrixWidget::~MatrixWidget()
{
    delete ui;
}

void MatrixWidget::initMatrix(int nRows, int nColumns)
{
    for(int nIndex = 0; nIndex < nRows; nIndex++)
    {
        QList<QDoubleSpinBox*> listLineEdit;
        for(int nRet = 0; nRet < nColumns; nRet++)
        {
            auto pUI = new QDoubleSpinBox();

            pUI->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
            pUI->setButtonSymbols(QAbstractSpinBox::NoButtons);
            pUI->setMinimum(-DBL_MAX);
            pUI->setMaximum(DBL_MAX);

            //通过下面的方法我们可以设置QDoubleSpinBox的显示精度，这样我们就能实现在一个m*n的矩阵中，其中单元的显示
            pUI->setDecimals(3);
            pUI->setEnabled(true);

            ui->gridLayout->addWidget(pUI, nIndex, nRet);
            listLineEdit.append(pUI);
        }
        m_listMatrix.append(listLineEdit);
    }
}

void MatrixWidget::setMatrixType(MatrixType nType)
{
    //通过控制主界面的状态间接的控制其中的QDoubleSpinBox的编辑状态
    ui->widgetMain->setEnabled(nType == EDIT_ENABLE);
}

void MatrixWidget::getValue(int nIndex, QVector4D& matrix)
{
    if (nIndex >= m_listMatrix.size())
    {
        return;
    }
    QList<QDoubleSpinBox*> list = m_listMatrix.at(nIndex);
    matrix.setW(list.at(0)->value());
    matrix.setX(list.at(1)->value());
    matrix.setY(list.at(2)->value());
    matrix.setZ(list.at(3)->value());
}
