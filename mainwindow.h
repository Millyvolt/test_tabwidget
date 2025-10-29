#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ThemeManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ThemeManager *themeManager, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ThemeManager *m_themeManager;
};
#endif // MAINWINDOW_H
