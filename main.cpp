#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QStringList>
#include <QDebug>
#include <QRegExp>

#include "controller/Controller.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("CopyFinder");

    quint64 sizeBlock = 512;
    quint64 sizeFile = 1;
    QStringList pathArguments;
    QStringList upathArguments;
    QStringList maskArguments;

    QString currentFlag;
    QCommandLineParser parser;

    parser.addHelpOption();

    QCommandLineOption checkNestingDirectoryOption(
        QStringList() << "l",
        QCoreApplication::translate("main", "Check nesting directory")
    );

    QCommandLineOption pathForScanningOption(
        QStringList() << "p" << "path",
        QCoreApplication::translate("main", "Include check directory"),
        R"(path1, pathN)"
    );

    QCommandLineOption excludedDirectoriesOption(
        QStringList() << "up" << "upath",
        QCoreApplication::translate("main", "Exclude check directory"),
        R"(path1, pathN)"
    );

    QCommandLineOption masksFileOption(
        QStringList() << "mf" << "maskfile",
        QCoreApplication::translate("main", "Masks for filename"),
        R"(".*.py" "file_[0-9]+.txt")"
    );

    QCommandLineOption sizeBlockReadableOption(
            QStringList() << "sb" << "sizeblock",
            QCoreApplication::translate("main", "Size block readable"),
            R"(512)"
    );

    QCommandLineOption sizeMinFileOption(
            QStringList() << "sf" << "sizefile",
            QCoreApplication::translate("main", "Size min. for file"),
            R"(1)"
    );

    parser.addOptions({
          checkNestingDirectoryOption,
          pathForScanningOption,
          excludedDirectoriesOption,
          masksFileOption,
          sizeBlockReadableOption,
          sizeMinFileOption
    });

    parser.process(app);

    const QStringList args = parser.positionalArguments();

    for (int i = 1; i < argc; ++i){
        QString argument = QString(argv[i]);
        if (argument.startsWith("--")) currentFlag = argument;
        else if (argument.startsWith("-")) continue;
        else if (currentFlag.contains(QRegExp("--sb|--sizeblock"))) sizeBlock = argument.toULongLong();
        else if (currentFlag.contains(QRegExp("--sf|--sizefile"))) sizeFile = argument.toULongLong();
        else {
            if (currentFlag.contains(QRegExp("-p|--path"))) pathArguments.append(argument);
            if (currentFlag.contains(QRegExp("--up|--upath"))) upathArguments.append(argument);
            if (currentFlag.contains(QRegExp("--mf|--maskfile"))) maskArguments.append(argument);
        }
    }
    qDebug() << "Check nested dir: " << parser.isSet(checkNestingDirectoryOption);
    qDebug() << "Size block readable: " << sizeBlock;
    qDebug() << "Min. size file: " << sizeFile;
    qDebug() << "Include Path: " << pathArguments;
    qDebug() << "Exclude Path: " << upathArguments;
    qDebug() << "Masks: " << maskArguments;

    if (pathArguments.empty()){
        qDebug() << "Path for scanning not setup";
        return 0;
    }

    qDebug() << "\nScanning started:\n";

    Controller controller = Controller(
            pathArguments,
            maskArguments,
            upathArguments,
            parser.isSet(checkNestingDirectoryOption),
            (unsigned)sizeFile,
            (unsigned)sizeBlock
    );
    controller.handle_folders();

    qDebug() << "Scanning finished";
}