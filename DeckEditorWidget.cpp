#include "DeckEditorWidget.h"
#include "ui_DeckEditorWidget.h"

#include <QMap>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>

struct DeckList
{
    void clear()
    {
        cards.clear();
        errors.clear();
    }
    QMap<QString, int> cards;
    QList<QString> errors;
};

struct DeckComparisonState
{
    DeckList deckA;
    DeckList deckB;
};

void parseDeck(const QString & input, DeckList & out)
{
    out.clear();
    QRegularExpression re("^((?<number>\\d+)[xX]?\\s+)?(?<name>.+)$");
    auto lines = input.split('\n');
    int lineNr = 0;
    for (auto & line: lines)
    {
        lineNr++;
        auto trimmedLine = line.trimmed();
        if(trimmedLine.isEmpty())
        {
            continue;
        }
        QRegularExpressionMatch match = re.match(trimmedLine);
        if(!match.hasMatch())
        {
            out.errors.push_back(QString("Error on line %1: %2").arg(lineNr).arg(trimmedLine));
            continue;
        }
        int number = 1;
        if(match.captured("number").size())
        {
            number = match.captured("number").toInt();
        }
        QString card = match.captured("name");
        card.replace(QChar(u'’'), '\'');
        auto iter = out.cards.find(card);
        if(iter != out.cards.end())
        {
            iter.value() += number;
        }
        else
        {
            out.cards.insert(card, number);
        }
    }
    if(out.errors.length())
    {
        qDebug() << out.errors;
    }
}

void compareDecks(const DeckList& original, const DeckList& changed, DeckList& addedCards, DeckList& removedCards)
{
    // removals and normal number changes
    {
        auto iter = original.cards.begin();
        while (iter != original.cards.end())
        {
            const QString &card = iter.key();
            int currentValue = iter.value();
            auto iterRight = changed.cards.find(card);
            if(iterRight != changed.cards.end())
            {
                int newValue = iterRight.value();
                if(newValue > currentValue)
                {
                    addedCards.cards.insert(card, newValue - currentValue);
                }
                else if(currentValue > newValue)
                {
                    removedCards.cards.insert(card, currentValue - newValue);
                }
            }
            else
            {
                removedCards.cards.insert(card, currentValue);
            }
            iter++;
        }
    }
    // new additions
    {
        auto iter = changed.cards.begin();
        while (iter != changed.cards.end())
        {
            const QString &card = iter.key();
            int newValue = iter.value();
            auto iterLeft = original.cards.find(card);
            if(iterLeft != original.cards.end())
            {
                iter++;
                continue;
            }
            addedCards.cards.insert(card, newValue);
            iter++;
        }
    }
}

QString printDeck(const DeckList& deck)
{
    QString output;
    QTextStream stream(&output);
    if(deck.cards.count())
    {
        auto iter = deck.cards.begin();
        while (iter != deck.cards.end())
        {
            stream << iter.value() << " " << iter.key() << "\n";
            iter++;
        }
        stream << "\n";
    }
    return output;
}

DeckEditorWidget::DeckEditorWidget(QWidget* parent):
    QWidget(parent),
    m_ui(new Ui::DeckEditorWidget),
    m_state(new DeckComparisonState)
{
    m_ui->setupUi(this);
    connect(m_ui->deckA, &QPlainTextEdit::textChanged, this, &DeckEditorWidget::deck_a_changed);
    connect(m_ui->deckB, &QPlainTextEdit::textChanged, this, &DeckEditorWidget::deck_b_changed);
}

DeckEditorWidget::~DeckEditorWidget()
{
}


void DeckEditorWidget::deck_a_changed()
{
    parseDeck(m_ui->deckA->toPlainText(), m_state->deckA);
    DeckList added;
    DeckList removed;
    compareDecks(m_state->deckA, m_state->deckB, added, removed);
    m_ui->removedFromA->setText(printDeck(removed));
    m_ui->addedInB->setText(printDeck(added));
}

void DeckEditorWidget::deck_b_changed()
{
    parseDeck(m_ui->deckB->toPlainText(), m_state->deckB);
    DeckList added;
    DeckList removed;
    compareDecks(m_state->deckA, m_state->deckB, added, removed);
    m_ui->removedFromA->setText(printDeck(removed));
    m_ui->addedInB->setText(printDeck(added));
}
