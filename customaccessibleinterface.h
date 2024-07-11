#ifndef CUSTOMACCESSIBLEINTERFACE_H
#define CUSTOMACCESSIBLEINTERFACE_H
#include <QApplication>
#include <QPushButton>
#include <QAccessible>
#include <QAccessibleWidget>

class CustomAccessibleInterface : public QAccessibleWidget
{
public:
    CustomAccessibleInterface(QWidget *w, const QString &automationId, const QString &name)
        : QAccessibleWidget(w), m_automationId(automationId), m_name(name) {}

    QString text(QAccessible::Text t) const override {
        if (t == QAccessible::Name) {
            return m_name;
        } else if (t == QAccessible::Description) {
            return m_automationId;
        }
        return QAccessibleWidget::text(t);
    }

private:
    QString m_automationId;
    QString m_name;
};

#endif // CUSTOMACCESSIBLEINTERFACE_H
