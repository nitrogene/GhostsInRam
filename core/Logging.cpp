#include "Logging.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QLoggingCategory>
#include <QSettings>
#include <QTextStream>

Q_LOGGING_CATEGORY(core, "core")

static QFile s_logFile;
static QTextStream s_logStream;

static const char *levelString(QtMsgType type)
{
    switch (type) {
    case QtDebugMsg: return "DEBUG";
    case QtInfoMsg: return "INFO";
    case QtWarningMsg: return "WARNING";
    case QtCriticalMsg: return "CRITICAL";
    case QtFatalMsg: return "FATAL";
    }
    return "UNKNOWN";
}

static void qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (!s_logFile.isOpen()) {
        const QString logFileName = QDir(QCoreApplication::applicationDirPath()).filePath("trace.log");
        s_logFile.setFileName(logFileName);
        if (!s_logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            fprintf(stderr, "Erreur d'ouverture du fichier de log : %s\n", qPrintable(logFileName));
            return;
        }
        s_logStream.setDevice(&s_logFile);
    }

    const QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    const QString typeName = levelString(type);
    const char* functionName = context.function ? context.function : "unknown_function";
    const QString contextInfo = QString("%1:%2 (%3)")
            .arg(context.file ? context.file : "unknown_file")
            .arg(context.line)
            .arg(functionName);
    
    const QString output = QString("%1 [%2] %3 (%4) %5")
            .arg(timestamp, typeName, context.category, contextInfo, msg);

    s_logStream << output << '\n';
    s_logStream.flush();

    fprintf(stderr, "%s\n", output.toLocal8Bit().constData());

    if (type == QtFatalMsg) {
        abort();
    }
}

static QString filterRulesForLevel(const QString &level)
{
    const QString normalized = level.trimmed().toLower();
    if (normalized == "debug") {
        return QStringLiteral("core.*=true");
    }
    if (normalized == "info") {
        return QStringLiteral("core.debug=false;core.info=true;core.warning=true;core.critical=true");
    }
    if (normalized == "warning") {
        return QStringLiteral("core.debug=false;core.info=false;core.warning=true;core.critical=true");
    }
    if (normalized == "critical") {
        return QStringLiteral("core.debug=false;core.info=false;core.warning=false;core.critical=true");
    }
    return QStringLiteral("core.*=true");
}

void initializeLogging()
{
    const QString iniPath = QDir(QCoreApplication::applicationDirPath()).filePath("core.ini");
    QSettings settings(iniPath, QSettings::IniFormat);
    QString level = settings.value("Logging/level", "debug").toString();

    QLoggingCategory::setFilterRules(filterRulesForLevel(level));
    qInstallMessageHandler(qtMessageHandler);
    qInfo(core) << "Initialisation du logging Qt. Niveau:" << level << "Fichier:" << QDir(QCoreApplication::applicationDirPath()).filePath("trace.log");
}
