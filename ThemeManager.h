#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QString>

class ThemeManager : public QObject
{
    Q_OBJECT
public:
    enum class Theme { Light, Dark, Auto };
    Q_ENUM(Theme)

    explicit ThemeManager(QObject *parent = nullptr);

    void applyCurrentTheme();
    void setTheme(Theme theme);
    Theme currentTheme() const;

signals:
    void themeChanged(ThemeManager::Theme theme);

private:
    Theme m_theme;

    bool isSystemLight() const;
    QString loadQssResource(const QString &resourcePath) const;
    void applyStylesheetText(const QString &qssText);
    QString combinedQssFor(Theme theme) const;
    void persistTheme(Theme theme) const;
    Theme loadPersistedTheme() const;
};

#endif // THEMEMANAGER_H


