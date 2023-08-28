#ifndef MATRIXWIDGET_H
#define MATRIXWIDGET_H

#include <QWidget>
#include <QVector4D>

namespace Ui {
class MatrixWidget;
}

class QDoubleSpinBox;

class MatrixWidget : public QWidget
{
    Q_OBJECT
public:
    enum MatrixType     /**表示该矩阵是否可编辑，默认是可编辑状态**/
    {
        EDIT_ENABLE = 1,
        EDIT_DISABLE
    };

public:
    explicit MatrixWidget(QWidget *parent = 0);
    ~MatrixWidget();

    void initMatrix(int nRows, int nColumns);

    void setMatrixType(MatrixType nType);

    /**
    * @brief 获取矩阵某一行的数据，要求矩阵满足m*4
    * @param[in]    nIndex          需要获取的行号
    * @param[out]   matrix          返回数据
    */
    void getValue(int nIndex, QVector4D& matrix);

    template<typename T> void getValue(T **result);
    template<typename T> void setValue(T **result);
    template<typename T> void setValue(int nRow, int nColumn, T pValue);

private:
    Ui::MatrixWidget *ui;
    QList<QList<QDoubleSpinBox*>> m_listMatrix;
};

template<typename T> void MatrixWidget::getValue(T **result)
{
    for(int nIndex = 0; nIndex < m_listMatrix.size(); nIndex++)
    {
        QList<QDoubleSpinBox*> list = m_listMatrix.at(nIndex);
        for(int nRet = 0; nRet < list.size(); nRet++)
        {
            /**目的是为了区分返回值的数据**/
            if(std::is_same<T, int>::value)
            {
                result[nIndex][nRet] = list.at(nRet)->text().toInt();
                continue;
            }
            result[nIndex][nRet] = list.at(nRet)->text().toDouble();
        }
    }
}

template<typename T> void MatrixWidget::setValue(T **result)
{
    for(int nIndex = 0; nIndex < m_listMatrix.size(); nIndex++)
    {
        QList<QDoubleSpinBox*> list = m_listMatrix.at(nIndex);
        for(int nRet = 0; nRet < list.size(); nRet++)
        {
            list.at(nRet)->setValue(result[nIndex][nRet]);
        }
    }
}

template<typename T> void MatrixWidget::setValue(int nRow, int nColumn, T value)
{
    if(nRow >= m_listMatrix.size())
    {
        return;
    }
    if(nColumn >= m_listMatrix.at(nRow).size())
    {
        return;
    }
    m_listMatrix.at(nRow).at(nColumn)->setValue(value);
}

#endif // MATRIXWIDGET_H
