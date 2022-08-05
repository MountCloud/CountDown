#ifndef LASTCLOSEUPFORM_H
#define LASTCLOSEUPFORM_H

#include <QWidget>
namespace Ui {
class LastCloseUpForm;
}

class LastCloseUpForm : public QWidget
{
    Q_OBJECT

public:
    explicit LastCloseUpForm(QWidget *parent = nullptr);
    ~LastCloseUpForm();

    void setTop();

    void setColor(QString color);

    void set(int num);

    int getSize();

    void setSize(int size);

    QSize getWinodwSize();
private:
    Ui::LastCloseUpForm *ui;

private:
    void init();
};

#endif // LASTCLOSEUPFORM_H
