#include "ThemePreviewDialog.h"
#include "ThemeManager.h"

#include <QApplication>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTableView>
#include <QStandardItemModel>
#include <QProgressBar>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>

static QWidget* buildDemoPage(QWidget *parent = nullptr)
{
    auto *root = new QWidget(parent);
    auto *v = new QVBoxLayout(root);

    auto *box = new QGroupBox(QObject::tr("Controls"), root);
    auto *form = new QFormLayout(box);
    form->addRow(QObject::tr("Name"), new QLineEdit(box));
    auto *combo = new QComboBox(box);
    combo->addItems({"Alpha", "Beta", "Gamma"});
    form->addRow(QObject::tr("Type"), combo);
    form->addRow(QObject::tr("Count"), new QSpinBox(box));
    v->addWidget(box);

    auto *table = new QTableView(root);
    auto *model = new QStandardItemModel(5, 3, table);
    table->setModel(model);
    v->addWidget(table);

    auto *progress = new QProgressBar(root);
    progress->setValue(42);
    v->addWidget(progress);

    auto *h = new QHBoxLayout();
    auto *btn1 = new QPushButton(QObject::tr("Default"), root);
    auto *btn2 = new QPushButton(QObject::tr("Primary"), root);
    btn2->setObjectName("primary");
    auto *btn3 = new QPushButton(QObject::tr("Danger"), root);
    btn3->setObjectName("danger");
    h->addWidget(btn1);
    h->addWidget(btn2);
    h->addWidget(btn3);
    h->addStretch();
    v->addLayout(h);

    auto *checks = new QHBoxLayout();
    checks->addWidget(new QCheckBox(QObject::tr("Enabled"), root));
    checks->addWidget(new QRadioButton(QObject::tr("Choice A"), root));
    checks->addWidget(new QRadioButton(QObject::tr("Choice B"), root));
    checks->addStretch();
    v->addLayout(checks);

    v->addStretch();
    return root;
}

ThemePreviewDialog::ThemePreviewDialog(ThemeManager *themeManager, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Theme Preview"));
    resize(900, 600);
    auto *tabs = new QTabWidget(this);
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(tabs);

    QWidget *light = buildDemoPage();
    QWidget *dark = buildDemoPage();
    QWidget *darkPlus = buildDemoPage();
    QWidget *autoW = buildDemoPage();

    tabs->addTab(light, tr("Light"));
    tabs->addTab(dark, tr("Dark"));
    tabs->addTab(darkPlus, tr("Dark+"));
    tabs->addTab(autoW, tr("Auto"));

    // Build per-tab styles by asking ThemeManager for combined CSS
    // We avoid changing the global app stylesheet here.
    ThemeManager::Theme original = themeManager->currentTheme();
    themeManager->setTheme(ThemeManager::Theme::Light);
    const QString lightCss = qApp->styleSheet();
    themeManager->setTheme(ThemeManager::Theme::Dark);
    const QString darkCss = qApp->styleSheet();
    themeManager->setTheme(ThemeManager::Theme::DarkPlus);
    const QString darkPlusCss = qApp->styleSheet();
    themeManager->setTheme(ThemeManager::Theme::Auto);
    const QString autoCss = qApp->styleSheet();
    themeManager->setTheme(original);
    qApp->setStyleSheet(qApp->styleSheet());

    light->setStyleSheet(lightCss);
    dark->setStyleSheet(darkCss);
    darkPlus->setStyleSheet(darkPlusCss);
    autoW->setStyleSheet(autoCss);
}


