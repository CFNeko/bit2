#include "commands.h"
#include "image_widget.h"

#define TEST_WITH_STACK_VIEW 0

Command::Command(const QImage& imgL, const QImage& imgC, void* ptr, QUndoCommand *parent /* = 0 */)
    : m_imgLast(imgL), m_imgCurr(imgC), m_ptr(ptr)
{

#if TEST_WITH_STACK_VIEW
	
	setText("1");
	m_imgLast.save("./test/img_last.png");
	m_imgCurr.save("./test/img_curr.png");

#endif
}

Command::~Command()
{
	m_ptr = Q_NULLPTR;
}

void Command::undo()
{
    static_cast<ImageWidget*>(m_ptr)->updateImage(m_imgLast);
}

void Command::redo()
{
     static_cast<ImageWidget*>(m_ptr)->updateImage( m_imgCurr);
}

CommandStack::CommandStack()
{
	m_undoStack = new QUndoStack(this);
	m_undoAction = m_undoStack->createUndoAction(this, tr(""));
	m_undoAction->setShortcuts(QKeySequence::Undo);

	m_redoAction = m_undoStack->createRedoAction(this, tr(""));
	m_redoAction->setShortcuts(QKeySequence::Redo);

#if TEST_WITH_STACK_VIEW

	m_undoView = new QUndoView(m_undoStack);
	m_undoView->setWindowTitle(tr("Command List"));
	m_undoView->show();
	m_undoView->setAttribute(Qt::WA_QuitOnClose, false);

#endif
}

CommandStack::~CommandStack()
{
	m_undoStack->deleteLater();
	m_undoAction->deleteLater();
	m_redoAction->deleteLater();

#if TEST_WITH_STACK_VIEW
	m_undoView->deleteLater();
#endif

}

void CommandStack::push(const QImage& imgL, const QImage& imgC, void* ptr)
{
    m_undoStack->push(new Command(imgL, imgC, ptr));
}

void CommandStack::keyEvent(QKeyEvent* event)
{
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Z)
	{
		m_undoAction->trigger();
	}
	if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Y)
	{
		m_redoAction->trigger();
	}
}
