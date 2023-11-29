#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include "Kalkulator.h"
#include <QFileDialog>

bool MainWindow::checker = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
   // ui->setupUi(this);
    this->setWindowTitle("Calculator");
    this->setFixedSize(240,405);

    //// make ui
    make_status_bar();
    make_menu_bar();
    make_fullstaff();
    make_expansion();

    for (size_t i = 0; i < digits.size(); i++)
    {
        for (size_t j = 0; j < digits[i].size(); j++)
        {
            connect(digits[i][j],SIGNAL(clicked()),this,SLOT(digits_numbers()));
        }
    }
    connect(l_edit, SIGNAL(returnPressed()),this,SLOT(on_equal_clicked()));
    connect(file_op, SIGNAL(triggered(bool)),this, SLOT(open_()));
    connect(div,SIGNAL(clicked(bool)),this,SLOT(math_operations()));
    connect(mult,SIGNAL(clicked(bool)),this,SLOT(math_operations()));
    connect(plus,SIGNAL(clicked(bool)),this,SLOT(math_operations()));
    connect(minus,SIGNAL(clicked(bool)),this,SLOT(math_operations()));
    connect(ac,SIGNAL(clicked(bool)),this,SLOT(on_ac_clicked()));
    connect(bc,SIGNAL(clicked(bool)),this,SLOT(Backspace()));
    connect(eq,SIGNAL(clicked(bool)),this,SLOT(on_equal_clicked()));
    connect(abc,SIGNAL(clicked(bool)),this,SLOT(on_abc_clicked()));

    for (size_t i = 0; i < trygonometry_func.size(); i++)
    {
        connect(trygonometry_func[i],SIGNAL(clicked()),this,SLOT(digits_numbers()));
    }
    connect(open_br,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(close_br,SIGNAL(clicked()),this,SLOT(digits_numbers()));
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::check_checkers_state()
{
    if(checker)
    {
        l_edit->clear();
        checker = false;
    }
}

void MainWindow::make_menu_bar()
{
    mbar  = this->menuBar();
    file = new QMenu("&File");
    file_op = new QAction("&Open");
    file_op->setShortcut(QKeySequence::Open);
    file->addAction(file_op);
    mbar->addMenu(file);
}

void MainWindow::make_status_bar()
{
    stbar = this->statusBar();
}

void MainWindow::make_fullstaff()
{
    w = new QWidget(this);
    l_edit = new QLineEdit(w);
    l_edit->resize(240,60);
    l_edit->setStyleSheet("QLineEdit {"
        "qproperty-alignment: 'AlignVCenter | AlignRight' ;"
    "}"
    "QLineEdit:hover {"
        "background-color: rgb(239, 243, 255);"
                      "}");
    l_edit->setToolTip("Enter expression");
    l_edit->setFont(QFont("Segoe UI",14));
    l_edit->setText("0");

    ac = new QPushButton("AC",w);
    ac->setFixedSize(60,60);
    ac->move(0,60);
    ac->setStyleSheet("QPushButton {"
                      "float: right;"
                      "margin-right: 3%;"
                      "margin-top: 5px;"
                      "border-radius: 5px;"
                      "padding: 5px 9px;"
                      "font-size: 1.2em;"
                      "background-color: rgba(236, 101, 80, 1);"
                      "border-bottom: 4px solid rgba(217, 91, 72, 1);"
                      "color: white;"
                      "font-family: 'Roboto Slab', serif;"

                      "}"
                      "QPushButton:pressed {"
                      "float: right;"
                      "margin-right: 3%;"
                      "margin-top: 5px;"
                      "border-radius: 5px;"
                      "padding: 5px 9px;"
                      "font-size: 1.2em;"
                      "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0#FF7832, stop: 1 #FF9739);"
                      "}");

    bc = new QPushButton("BC",w);
    bc->setFixedSize(60,60);
    bc->setStyleSheet(css1);
    bc->move(60,60);
    abc = new QPushButton("abc",w);
    abc->setFixedSize(60,60);
    abc->move(120,60);
    abc->setStyleSheet(css1);
    abc->setCheckable(true);

    digits.resize(4);
    int x = 0;
    int y = 120;
    int numb = 6;

    for (size_t i = 0; i < digits.size(); i++)
    {
        if(i == digits.size() - 1)
        {
            digits[i].resize(2);
            for (size_t j = 0; j < digits[i].size(); j++)
            {
                QString d;
                if(j == 0)
                {
                    d = to_string(j).c_str();
                    digits[i][j] = new QPushButton(d, w);
                    digits[i][j]->setFixedSize(120,60);
                    digits[i][j]->move(j * 60, y + (60 * i));
                }
                else
                {
                    d = ".";
                    digits[i][j] = new QPushButton(d, w);
                    digits[i][j]->setFixedSize(60,60);
                    digits[i][j]->move((j+1) * 60, y + (60 * i));
                }
                digits[i][j]->setStyleSheet(css2);
            }
        }
        else
        {
            digits[i].resize(3);
            for (size_t j = 0; j < digits[i].size(); j++)
            {
                QString d(to_string(numb+1).c_str());
                digits[i][j] = new QPushButton(d, w);
                digits[i][j]->setFixedSize(60,60);
                digits[i][j]->move(j * 60, y + (60 * i));
                digits[i][j]->setStyleSheet(css2);
                numb++;
            }
            numb-=6;
        }
    }

    div = new QPushButton("÷",w);
    div->setFixedSize(60,60);
    div->move(180,60);
    div->setStyleSheet(css3);

    mult = new QPushButton("×",w);
    mult->setFixedSize(60,60);
    mult->move(180,120);
    mult->setStyleSheet(css3);

    minus = new QPushButton("-",w);
    minus->setFixedSize(60,60);
    minus->move(180,180);
    minus->setStyleSheet(css3);

    plus = new QPushButton("+",w);
    plus->setFixedSize(60,60);
    plus->move(180, 240);
    plus->setStyleSheet(css3);

    eq = new QPushButton("=",w);
    eq->setFixedSize(60,60);
    eq->move(180, 300);
    eq->setStyleSheet(css3);

    this->setCentralWidget(w);
}

void MainWindow::make_expansion()
{
    open_br = new QPushButton("(",w);
    open_br->setFixedSize(60,120);
    open_br->setStyleSheet(css2);
    open_br->move(300,60);
    close_br = new QPushButton(")",w);
    close_br->setFixedSize(60,120);
    close_br->setStyleSheet(css2);
    close_br->move(300,180);

    int x = 240;
    int y = 60;
    trygonometry_func.resize(6);
    for(size_t i = 0; i < trygonometry_func.size(); ++i)
    {
        trygonometry_func[i] = new QPushButton(tryg_f[i], w);
        trygonometry_func[i]->setFixedSize(60, 60);
        if(i == (trygonometry_func.size() - 1))
        {
            trygonometry_func[i]->move(300, (60 * i));
        }
        else
            trygonometry_func[i]->move(x, y + (60 * i));

        trygonometry_func[i]->setStyleSheet(css2);
    }
}

void MainWindow::digits_numbers()
{
    check_checkers_state();
    QPushButton *button = (QPushButton *) sender();

    if(l_edit->text() == "0")
        l_edit->clear();

    QString string;
    string = l_edit->text() + button->text();
    l_edit->setText(string);
}


void MainWindow::Backspace()
{
     QString string = l_edit->text();
     string.chop(1);

    if(string.isEmpty())
        string = "0";

    l_edit->setText(string);
}

void MainWindow::math_operations()
{
    if(checker)
    {
        checker = false;
    }

    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "÷")
    {
        l_edit->setText(l_edit->text() + "/");
    }
    else if (button->text() == "×")
    {
        l_edit->setText(l_edit->text() + "*");
    }
    else
    {
        QString string = l_edit->text() + button->text();
        l_edit->setText(string);
    }

}

void MainWindow::on_ac_clicked()
{
    l_edit->setText("0");
}


void MainWindow::on_equal_clicked()
{
    Kalkulator<float> K;
    Reader file;
    checker = true;

    std::string expression = l_edit->text().toStdString();

    try
    {
        K.Parsing(expression);
        QString result = QString::fromStdString(expression);

        l_edit->setText(result);
    }
    catch (std::exception& ex)
    {
        QString exept(ex.what());
        l_edit->setText(exept);
    }
    catch (...)
    {
        l_edit->setText("exeption");
    }

}

void MainWindow::on_abc_clicked()
{
    QPushButton *button = (QPushButton *)sender();

    if(button->isChecked())
    {
        button->setText("123");
        l_edit->resize(360, 60);
        this->setFixedSize(360,405);
    }
    else
    {
        l_edit->resize(240,60);
        button->setText("abc");
        this->setFixedSize(240,405);
    }
}


void MainWindow::open_()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a file");

    std::string file_path = filename.toStdString();
    Reader file;
    file.set_tbar(this->stbar);
    try
    {
        file.ReadfromFile(file_path);
    }
    catch (...)
    {

    }
}


