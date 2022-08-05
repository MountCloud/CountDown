#ifndef TEXTSHOWFORM_H
#define TEXTSHOWFORM_H

#include <QWidget>
#include <QFont>

namespace Ui {
class TextShowForm;
}

class TextShowForm : public QWidget
{
    Q_OBJECT

public:
    explicit TextShowForm(QWidget *parent = nullptr);
    ~TextShowForm();

    void setTextFont(QFont font);
    void setTextSize(int size);
    void setTextColor(QString color);
    void setText(QString text);

    void setTextAlignment(Qt::Alignment alignment);

    QFont getTextFont();
    QString getText();

    void setTop();

    QSize getWinodwSize();
private:
    Ui::TextShowForm *ui;

private:
    void init();
};

#endif // TEXTSHOWFORM_H
