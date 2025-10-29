#ifndef THEMEPREVIEWDIALOG_H
#define THEMEPREVIEWDIALOG_H

#include <QDialog>

class ThemeManager;

class ThemePreviewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ThemePreviewDialog(ThemeManager *themeManager, QWidget *parent = nullptr);
};

#endif // THEMEPREVIEWDIALOG_H


