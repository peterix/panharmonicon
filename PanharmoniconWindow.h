#include <QScopedPointer>
#include <QMainWindow>

class PanharmoniconWindowUi;

struct DeckComparisonState;

class PanharmoniconWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PanharmoniconWindow(QWidget *parent = nullptr);
    virtual ~PanharmoniconWindow();

private:
    QScopedPointer<PanharmoniconWindowUi> m_ui;
};
