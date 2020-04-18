#include "config.h"

#include <ccxx/cxappenv.h>
#include <ccxx/cxinterinfo.h>

using namespace std;

std::string Config::mainDbFilePath()
{
    static string s = CxFileSystem::normalize(CxFileSystem::mergeFilePath(CxAppEnv::applicationDeployPath(), "../alignerchen/lsmasterlite.db"));
    return s;
}

std::string Config::dbBackupPath()
{
    static string s = CxFileSystem::normalize(CxFileSystem::mergeFilePath(CxAppEnv::dataPath(), "backup"));
    return s;
}

QUrl Config::defaultUrl()
{
    static QUrl u(QStringLiteral("http://news.baidu.com/"));
    return u;
}

CxDatabase *Config::mainDb()
{
    static CxDatabase * db = CxDatabaseManager::createDatabase(Config::mainDbFilePath());
    if (! db->isOpen()){
        db->openDatabase();
        cxPrompt() << "sqlite db open: " << Config::mainDbFilePath() << "; status: " << db->isOpen();
    }

    return db;
}

std::string Config::imagePath()
{
    static string s = CxFileSystem::normalize(CxFileSystem::mergeFilePath(CxAppEnv::applicationDeployPath(), "res/images"));
    return s;
}

std::string Config::imageFilePath(const string &fn)
{
    return CxFileSystem::mergeFilePath(imagePath(), fn);
}

static int _maxManId = -1;
int Config::maxManId()
{
    if (_maxManId == -1)
    {
        string sMaxId;
        sMaxId = mainDb()->queryValue("SELECT MAX(ManID) FROM Man;");
        if (CxString::toInt32(sMaxId) > 0)
        {
            _maxManId = CxString::toInt32(sMaxId);
        }
    }
    return _maxManId;
}

static int _maxVehId = -1;
int Config::maxVehId()
{
    if (_maxVehId == -1)
    {
        string sMaxId;
        sMaxId = mainDb()->queryValue("SELECT MAX(VehID) FROM Vehicle;");
        if (CxString::toInt32(sMaxId) > 0)
        {
            _maxVehId = CxString::toInt32(sMaxId);
        }
    }
    return _maxVehId;
}
void Config::setMaxManId(int id)
{
    _maxManId = id;
}
void Config::setMaxVehId(int id)
{
    _maxVehId = id;
}

static std::map<int, std::string> _langInfos;
std::map<int, std::string> Config::langInfos()
{
    if (_langInfos.size()==0)
    {
        string fp = CxFileSystem::normalize(CxFileSystem::mergeFilePath(CxAppEnv::resPath(), "lang/langs.csv"));
        string ls = CxFile::getLineString(fp);
        vector<string> ss;
        CxFile::load(fp, ss, ls);
        for (int i = 0; i < ss.size(); ++i)
        {
            const string & s = ss[i];
            vector<string> ss1 = CxString::split(s, ',');
            if (ss1.size()>1)
            {
                _langInfos[CxString::toInt32(ss1[0])] = s;
            }
        }
    }
    return _langInfos;
}
