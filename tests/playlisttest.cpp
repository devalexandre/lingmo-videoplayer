#include "../src/playlistmodel.h"
#include <QtTest>
#include <QTemporaryDir>
#include <QAbstractItemModelTester>

class PlaylistTest : public QObject {
    Q_OBJECT
private slots:
    void sortAndRestore() {
        QTemporaryDir dir;
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, dir.path());
        QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, dir.path());
        QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, dir.path());
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, dir.path());
        QLocale::setDefault(QLocale("pt_BR"));
        PlayListModel model;
        QAbstractItemModelTester tester(&model, QAbstractItemModelTester::FailureReportingMode::QtTest);
        const auto ten = dir.filePath("Aula 10.mp4");
        const auto two = dir.filePath("aula 2.mp4");
        const auto one = dir.filePath("Aula 1.mp4");
        for (const auto &path : {ten, two, one}) {
            QFile file(path);
            QVERIFY(file.open(QIODevice::WriteOnly));
            model.addVideo(QUrl::fromLocalFile(path).toString());
            QCOMPARE(model.getPath(model.getPlayingVideo()), path);
        }
        QCOMPARE(model.getPath(0), one);
        QCOMPARE(model.getPath(1), two);
        QCOMPARE(model.getPath(2), ten);
        model.addVideo(ten);
        QCOMPARE(model.rowCount(), 3);
        QCOMPARE(model.getPlayingVideo(), 2);
        for (int i = 0; i < 3; ++i) {
            QCOMPARE(model.getItem(i)->index(), i);
            QCOMPARE(model.getItem(i)->isPlaying(), i == 2);
        }
        PlayListModel restored;
        QCOMPARE(restored.getPath(0), one);
        QCOMPARE(restored.getPath(1), two);
        QCOMPARE(restored.getPath(2), ten);
        model.clear();
        model.setPlayingVideo(0); // Empty models must be safe.
    }
};
int main(int argc, char **argv) {
    QTemporaryDir config;
    qputenv("XDG_CONFIG_HOME", config.path().toUtf8());
    qputenv("XDG_CONFIG_DIRS", config.path().toUtf8());
    QCoreApplication app(argc, argv);
    PlaylistTest test;
    return QTest::qExec(&test, argc, argv);
}
#include "playlisttest.moc"
