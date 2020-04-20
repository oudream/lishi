#ifndef LISHI_CONFIG_H
#define LISHI_CONFIG_H

#include <ccxx/cxglobal.h>
#include <ccxx/cxdatabase.h>

#include <QUrl>

class Config {
public:
    static std::string mainDbFilePath();

    static std::string dbBackupPath();

    static QUrl defaultUrl();

    static CxDatabase * mainDb();

    static std::string imagePath();

    static std::string imageFilePath(const std::string &fn);

    static int maxManId();
    static void setMaxManId(int id);

    static int maxVehId();
    static void setMaxVehId(int id);

    static int currentLanID();

    static const std::vector<std::pair<int, std::string>> & langInfos();

};

#endif //LISHI_CONFIG_H
