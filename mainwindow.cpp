#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ThemeManager.h"
#include "ThemePreviewDialog.h"
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(ThemeManager *themeManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_themeManager(themeManager)
{
    ui->setupUi(this);

    auto themeMenu = menuBar()->addMenu(tr("Theme"));
    QAction *actLight = themeMenu->addAction(tr("Light"));
    QAction *actDark  = themeMenu->addAction(tr("Dark"));
    QAction *actAuto  = themeMenu->addAction(tr("Auto (System)"));
    themeMenu->addSeparator();
    QAction *actPreview = themeMenu->addAction(tr("Theme Preview…"));
    actPreview->setIcon(QIcon::fromTheme("preview"));

    connect(actLight, &QAction::triggered, this, [this]{ m_themeManager->setTheme(ThemeManager::Theme::Light); });
    connect(actDark,  &QAction::triggered, this, [this]{ m_themeManager->setTheme(ThemeManager::Theme::Dark);  });
    connect(actAuto,  &QAction::triggered, this, [this]{ m_themeManager->setTheme(ThemeManager::Theme::Auto);  });
    connect(actPreview, &QAction::triggered, this, [this]{ ThemePreviewDialog dlg(m_themeManager, this); dlg.exec(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

