
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
#include <QIcon>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QAction>
#include <QMenu>
#include <QStatusBar>
#include <QLineEdit>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QPushButton* ac,*bc,*abc;
    QPushButton *div, *mult, *plus, *minus, *eq;
    std::vector<std::vector<QPushButton*>> digits;
    QPushButton* op;
    QLineEdit* l_edit;

    QStatusBar *stbar;

    //file
    QMenuBar* mbar;
    QMenu* file;
    QAction* file_op;

    QWidget *w;

    //for mainwindow extansion
    QPushButton *open_br, *close_br;
    std::vector<QString> tryg_f{"sin","cos","tan","cot","sqrt","abs"};
    std::vector<QPushButton*> trygonometry_func;

    QString css1 = "QPushButton {"
                 "float: right;"
                 "margin-right: 3%;"
                 "margin-top: 5px;"
                 "border-radius: 5px;"
                 "padding: 5px 9px;"
                 "font-size: 1.2em;"
                 "background-color: rgb(215, 215, 215);"
                 "border: 1px solid gray;"

                 "}"
                 "QPushButton:pressed {"
                 "float: right;"
                 "margin-right: 3%;"
                 "margin-top: 5px;"
                 "border-radius: 5px;"
                 "padding: 5px 9px;"
                 "font-size: 1.2em;"
                 "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0#BEBEBE, stop: 1 #D7D7D7);"
                "}";

    QString css2 = "QPushButton {"
                   "float: right;"
                   "margin-right: 3%;"
                   "margin-top: 5px;"
                   "border-radius: 5px;"
                   "padding: 5px 9px;"
                   "font-size: 1.2em;"
                   "border: 1px solid gray;"
                   "}"

                   "QPushButton:pressed {"
                   "float: right;"
                   "margin-right: 3%;"
                   "margin-top: 5px;"
                   "border-radius: 5px;"
                   "padding: 5px 9px;"
                   "font-size: 1.2em;"
                   "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0#BEBEBE, stop: 1 #D7D7D7);"
                   "}";
    QString css3 = "QPushButton {"
                   "float: right;"
                   "margin-right: 3%;"
                   "margin-top: 5px;"
                   "border-radius: 5px;"
                   "padding: 5px 9px;"
                   "font-size: 1.2em;"
                   "background-color: rgb(215,151,57);"
                   "color: white;"
                   "border: 1px solid gray;"
                   "}"

                   "QPushButton:pressed {"
                   "float: right;"
                   "margin-right: 3%;"
                   "margin-top: 5px;"
                   "border-radius: 5px;"
                   "padding: 5px 9px;"
                   "font-size: 1.2em;"
                   "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0#FF7832, stop: 1 #FF9739);"
                   "}";

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static void SetChecker(bool state)
    {
        checker = state;
    }

    static bool GetChecker()
    {
        return checker;
    }

private:
    SecondWindow *window;
    static bool checker;

    // methods
    void check_checkers_state();
    void make_menu_bar();
    void make_status_bar();
    void make_fullstaff();
    void make_expansion();

private slots:
    void digits_numbers();
    void Backspace();
    void on_ac_clicked();
    void on_equal_clicked();
    void math_operations();
    void on_abc_clicked();
    void open_();
};

#endif // MAINWINDOW_H
