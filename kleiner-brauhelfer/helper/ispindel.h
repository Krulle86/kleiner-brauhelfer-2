#ifndef ISPINDEL_H
#define ISPINDEL_H

#include <QObject>
#include <QDebug>
#include <QTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariantMap>
#include <QSqlQueryModel>
#include <QSqlDriver>

#include "settings.h"

class Ispindel : public QObject
{
    Q_OBJECT
public:
    explicit Ispindel(QObject *parent = nullptr);
    ~Ispindel();

    void saveSettings();

    bool connectDatabaseIspindel(bool showMessage = false);
    bool isDatabaseOpen();
    QSqlError getLastSqlError();
    QSqlQuery* getQuery();
    QSqlRecord getRecordSetQuery(QString query);
    QStringList getStringListQuery(QString query);

    // Daten für andere Klassen
    QStringList getTablenames();
    QStringList getVerfuegbareSpindeln();
    int getAnzahlDatensaetze(QString NameSpindel);
    QList<QPair<QDateTime, QStringList> > getResetFlags(const QString NameSpindel);
    void setResetFlag(const QString NameSpindel, const int Recipe);
    QList<QVariantMap> getPlatoBetweenTimestamps(QString NameSpindel, QDateTime FirstDate, QDateTime LastDate);
    QSqlQueryModel *getPlatoBetweenTimestampsAsModel(QString NameSpindel, QDateTime DateNew, QDateTime DateOld);
    QStringList getCalibrationData(const QString NameSpindel);
    void setCalibrationData(const QString NameSpindel, const QStringList &Parameter0_2);
    void deleteDatabaseBetweenTimestamps(const QString NameSpindel, const QDateTime FirstDate, const QDateTime LastDate);

    QString getDbDriver() const;
    void setDbDriver(const QString &dbDriver);
    QString getDbServer() const;
    void setDbServer(const QString &dbServer);
    QString getDbDatabase() const;
    void setDbDatabase(const QString &dbDatabase);
    QString getDbUsername() const;
    void setDbUsername(const QString &dbUsername);
    QString getDbPwd() const;
    void setDbPwd(const QString &dbPwd);

    QString getDbTableCalibration() const;
    void setDbTableCalibration(const QString &dbTableCalibration);

    QString getDbTableData() const;
    void setDbTableData(const QString &dbTableData);

private:
    void loadSettings();
    QString buildConnectionString() const;
    void checkErrorDatabase();
    void execQueryAndCheckError();
    void execQueryAndCheckError(QString query);
    void execQuery(QString &query);

    template<class T>
    void error(T error);

    QString getQueryGetPlatoFromDb(
            QString &NameSpindel,
            QDateTime &DateNew,
            QDateTime &DateOld);

private:
    QSqlDatabase m_dbIspindel;
    QSqlQuery *m_dbIspindelQuery;

    QString mDbDriver, mDbServer, mDbDatabase, mDbUsername, mDbPwd;
    QString mDbTableCalibration, mDbTableData;

    QList<QVariantMap> mIdCalibrationDataDevice;
    //Return Type of SqlQueryModel
    QSqlQueryModel *mSqlModel;
};

#endif // ISPINDEL_H
