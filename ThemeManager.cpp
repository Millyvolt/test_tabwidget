#include "ThemeManager.h"

#include <QApplication>
#include <QFile>
#include <QSettings>
#include <QTextStream>
#include <QStyle>
#include <QIcon>

static QString readResource(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }
    const QByteArray bytes = f.readAll();
    return QString::fromUtf8(bytes);
}

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent)
    , m_theme(loadPersistedTheme())
{
}

void ThemeManager::applyCurrentTheme()
{
    applyStylesheetText(combinedQssFor(m_theme));
}

void ThemeManager::setTheme(ThemeManager::Theme theme)
{
    if (m_theme == theme)
        return;
    m_theme = theme;
    persistTheme(theme);
    applyCurrentTheme();
    emit themeChanged(m_theme);
}

ThemeManager::Theme ThemeManager::currentTheme() const
{
    return m_theme;
}

bool ThemeManager::isSystemLight() const
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
    const int val = reg.value("AppsUseLightTheme", 1).toInt();
    return val == 1;
#else
    // Fallback heuristic: check palette base brightness
    const auto base = QApplication::palette().base().color();
    const int luminance = qRound(0.2126 * base.red() + 0.7152 * base.green() + 0.0722 * base.blue());
    return luminance > 128;
#endif
}

QString ThemeManager::loadQssResource(const QString &resourcePath) const
{
    return readResource(resourcePath);
}

void ThemeManager::applyStylesheetText(const QString &qssText)
{
    QApplication::setStyle("Fusion");
    QApplication::setPalette(QApplication::style()->standardPalette());
    qApp->setStyleSheet(qssText);

    // Ensure themed icons resolve from our resources
    static bool pathsSet = false;
    if (!pathsSet) {
        QStringList paths = QIcon::themeSearchPaths();
        paths.prepend(":/icons");
        QIcon::setThemeSearchPaths(paths);
        pathsSet = true;
    }
    const bool light = (m_theme == Theme::Light) || (m_theme == Theme::Auto && isSystemLight());
    QIcon::setThemeName(light ? "light" : "dark");
}

QString ThemeManager::combinedQssFor(ThemeManager::Theme theme) const
{
    const QString common = loadQssResource(":/styles/styles/common.qss");
    const bool light = (theme == Theme::Light) || (theme == Theme::Auto && isSystemLight());
    const QString specific = light
        ? loadQssResource(":/styles/styles/light.qss")
        : loadQssResource(":/styles/styles/dark.qss");
    return common + "\n\n" + specific;
}

void ThemeManager::persistTheme(ThemeManager::Theme theme) const
{
    QSettings s;
    s.setValue("theme", static_cast<int>(theme));
}

ThemeManager::Theme ThemeManager::loadPersistedTheme() const
{
    QSettings s;
    const int stored = s.value("theme", static_cast<int>(Theme::Auto)).toInt();
    switch (stored) {
    case 0: return Theme::Light;
    case 1: return Theme::Dark;
    case 2: default: return Theme::Auto;
    }
}


