#pragma once
#include <QScopedPointer>
#include <QWidget>

namespace Ui
{
class DeckEditorWidget;
}

struct DeckComparisonState;

class DeckEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeckEditorWidget(QWidget *parent = nullptr);
    virtual ~DeckEditorWidget();

public slots:
    void deck_a_changed();
    void deck_b_changed();

private:
    QScopedPointer<Ui::DeckEditorWidget> m_ui;
    QScopedPointer<DeckComparisonState> m_state;
};

