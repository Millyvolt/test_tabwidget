#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "ThemeManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "test_tabwidget_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    ThemeManager themeManager;
    themeManager.applyCurrentTheme();

    MainWindow w(&themeManager);
    w.show();
    return a.exec();
}
