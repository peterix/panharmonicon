#include "PanharmoniconWindow.h"

#include <QApplication>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

#include "DeckEditorWidget.h"

class PanharmoniconWindowUi
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainWindowLayout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *window)
    {
        if (window->objectName().isEmpty())
            window->setObjectName(QString::fromUtf8("PanharmoniconWindow"));
        window->resize(1146, 779);
        centralwidget = new DeckEditorWidget(window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        mainWindowLayout = new QVBoxLayout(centralwidget);

        window->setCentralWidget(centralwidget);

        statusbar = new QStatusBar(window);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        window->setStatusBar(statusbar);

        retranslateUi(window);

        QMetaObject::connectSlotsByName(window);
    } // setupUi

    void retranslateUi(QMainWindow *window)
    {
        window->setWindowTitle(QApplication::translate("PanharmoniconWindow", "Panharmonicon", nullptr));
    } // retranslateUi

};

PanharmoniconWindow::PanharmoniconWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new PanharmoniconWindowUi)
{
    m_ui->setupUi(this);
}

PanharmoniconWindow::~PanharmoniconWindow()
{
}
