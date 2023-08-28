#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoStack>
#include <QUndoView>
#include <QAction>
#include <QUndoCommand>
#include <QImage>
#include <QKeyEvent>

class ImageBaseWidget;
class Command : public QUndoCommand
{
public:

    Command(const QImage& imgL, const QImage& imgC, void* ptr, QUndoCommand *parent = 0);
	~Command();

	void undo() override;
	void redo() override;

private:
	QImage m_imgLast{ QImage() };
	QImage m_imgCurr{ QImage() };
    void* m_ptr{ Q_NULLPTR };
};



class CommandStack : public QObject
{
	Q_OBJECT
public:
	static CommandStack& instance()
	{
		static CommandStack instance;
		return instance;
	}
	void create(){}
    void push(const QImage& imgL, const QImage& imgC, void* ptr);

	void keyEvent(QKeyEvent* event);

private:
	CommandStack();
	~CommandStack();

private:
	QUndoStack* m_undoStack{ Q_NULLPTR };
	QAction* m_undoAction{ Q_NULLPTR };
	QAction* m_redoAction{ Q_NULLPTR };

	QUndoView *m_undoView{ Q_NULLPTR };
};

#endif // !COMMANDS_H
