#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ThemeManager.h"
#include "ThemePreviewDialog.h"
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStyle>

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

    // Sample toolbar to showcase QToolButton hover/pressed styles
    QToolBar *tb = addToolBar(tr("Main Toolbar"));
    tb->setMovable(true);
    tb->setToolButtonStyle(Qt::ToolButtonIconOnly);

    auto mkStd = [this](QStyle::StandardPixmap sp, const QString &text){
        QAction *a = new QAction(style()->standardIcon(sp), text, this);
        return a;
    };

    QAction *aNew = mkStd(QStyle::SP_FileIcon, tr("New"));
    QAction *aOpen = mkStd(QStyle::SP_DirOpenIcon, tr("Open"));
    QAction *aSave = mkStd(QStyle::SP_DialogSaveButton, tr("Save"));
    QAction *aPrev = new QAction(QIcon::fromTheme("preview"), tr("Preview"), this);
    QAction *aToggle = new QAction(tr("Toggle"), this);
    aToggle->setCheckable(true);

    tb->addAction(aNew);
    tb->addAction(aOpen);
    tb->addAction(aSave);
    tb->addSeparator();
    tb->addAction(aPrev);
    tb->addSeparator();
    tb->addAction(aToggle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

