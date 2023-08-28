
#ifndef DRWA_TOOL_DEFINES_H
#define DRWA_TOOL_DEFINES_H

#include <QString>
#include <QVariant>
#include <QSize>
#include <QImage>

#define BRUSH_WIDTH_MAX 40

namespace DrawTool
{

const int DRAW_TOOL_DRAWMOVE = 1;
const int DRAW_TOOL_POLYGON = 2;
const int DRAW_TOOL_BRUSH = 3;

class DrawToolDefine
{
public:
    static DrawToolDefine& instance()
    {
        static DrawToolDefine instance ;
        return instance;
    }

    QVariantMap m_MenuMap;
private:

    DrawToolDefine()
    {
        m_MenuMap.insert("DragMove", DRAW_TOOL_DRAWMOVE);
        m_MenuMap.insert("Polygon",	 DRAW_TOOL_POLYGON);
        m_MenuMap.insert("Brush",    DRAW_TOOL_BRUSH);
    }
};
//    static QVariantMap tool_property()
//    {
//        static QVariantMap operate
//        {
//            {"DragMove", DRAW_TOOL_DRAWMOVE},
//            {"Polygon",	 DRAW_TOOL_POLYGON},
//            {"Brush",    DRAW_TOOL_BRUSH},
//        };

//        return operate;
//    };

    struct ImageShow
    {
        QImage img{ QImage() };
        QSize size{ QSize() };

        ImageShow() {}

        operator QVariant() const
        {
            return QVariant::fromValue(*this);
        }

        ImageShow(const QVariant& variant)
        {
            *this = variant.value<ImageShow>();
        }
    };
    Q_DECLARE_METATYPE(ImageShow)

	enum BrushStroke
	{
		VALID = 0,
		RECT = 1,
		CIRCLE
	};

    struct DrawToolData
	{
		int diaphaneity{ 255 };
        int width{ 10 };
        int operate{ DRAW_TOOL_DRAWMOVE };
		bool all{ true };

		BrushStroke stroke{ RECT };
        QColor pre_label_color{ QColor() };
        QColor back_label_color{ QColor() };

        DrawToolData() {}

		operator QVariant() const
		{
			return QVariant::fromValue(*this);
		}

        DrawToolData(const QVariant& variant)
		{
            *this = variant.value<DrawToolData>();
		}
	};
    Q_DECLARE_METATYPE(DrawToolData)

    struct Polygon
	{
		int width{ 4 };
		bool filled{ false };
		bool paintend{ false };
        QVector<QPointF> pts;

        Polygon() {}

		operator QVariant() const
		{
			return QVariant::fromValue(*this);
		}

        Polygon(const QVariant& variant)
		{
            *this = variant.value<Polygon>();
		}

		void clear()
		{
            pts.clear();
			filled = false;
			paintend = false;
		}
	};
    Q_DECLARE_METATYPE(Polygon)
}


#endif // DRWA_TOOL_DEFINES_H
