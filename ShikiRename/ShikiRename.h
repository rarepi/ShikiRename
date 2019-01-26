#ifndef SHIKIRENAME_H
#define SHIKIRENAME_H

#include <QMainWindow>
#include <QString>
#include <QStringBuilder>
#include <QFileInfo>
#include <limits>
#include <QFutureWatcher>
#include <QtNetwork/QNetworkReply>
#include <SeriesSelectionDialog.h>
#include <RenameConfirmationDialog.h>
#include <QList>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <regex>
#include "MediaInfoDLL/MediaInfoDLL.h" //Dynamicly-loaded library (.dll or .so)
#include <DirWatcher.h>
#include <TVDB.h>

namespace Ui {
	class ShikiRenameClass;
}

class ShikiRename : public QMainWindow
{
	Q_OBJECT

public:
	const enum MetaDB { None = 0, TheTVDB = 1 };
	const int MAX_INT = (std::numeric_limits<int>::max)();
	explicit ShikiRename(QWidget *parent = 0);
	~ShikiRename();

private slots:
	void on_tabWidget_currentChanged(const int &index);
	void on_editDirectory_returnPressed();

	void on_editRemoveRight_textChanged(const QString &arg1);
	void on_editRemoveLeft_textChanged(const QString &arg1);
	void on_editReplace1_textChanged(const QString &arg1);
	void on_editReplace2_textChanged(const QString &arg1);
	void on_editInsert1_textChanged(const QString &arg1);
	void on_editInsert2_textChanged(const QString &arg1);
	void on_editRemoveAt1_textChanged(const QString &arg1);
	void on_editRemoveAt2_textChanged(const QString &arg1);
	void on_editPrefix_textChanged(const QString &arg1);
	void on_editSuffix_textChanged(const QString &arg1);
	void on_editNumIdx_textChanged(const QString &arg1);
	void on_editNumInitV_textChanged(const QString &arg1);
	void on_editNumInc_textChanged(const QString &arg1);
	void on_editNumDigits_textChanged(const QString &arg1);

	void on_buttonCustomFileNameReset_clicked();
	void on_checkboxCustomFileName_toggled(const bool &checked);
	void on_editCustomFileName_textChanged(const QString &arg1);
	void on_editName_textChanged(const QString &arg1);
	void on_editSeasonNrPrefix_textChanged(const QString &arg1);
	void on_editEpisodeNrPrefix_textChanged(const QString &arg1);
	void on_editSeasonNrDigits_textChanged(const QString &arg1);
	void on_editEpisodeNrDigits_textChanged(const QString &arg1);
	void on_checkboxNoSeason_toggled(const bool &checked);
	void on_comboEpisodeNameSrc_currentIndexChanged(const int &index);
	void on_comboEpisodeNameLang_currentIndexChanged(const int &index);
	void comboEpisodeNameLang_addItems(QStringList items);
	void on_checkboxOnlySelected_toggled(const bool &checked);
	void on_currentList_itemSelectionChanged();
	void on_renamePreview_finished();

	void on_actionOpen_triggered();
	void on_actionRefresh_triggered();
	void on_actionQuit_triggered();
	void on_actionUndo_triggered();
	void on_actionRedo_triggered();

	void on_buttonRename_clicked();

	void openDialogSeriesSelection(QJsonArray seriesData);
	void on_seriesSelectedDialog_closed(const int &id, const QString &name);

	void on_dirWatcherFW_finished();
	void watchFileChanges();

	void findSeries();
	void previewRename();

	void on_tvdb_authTimeout();
	void on_tvdb_loggedIn();

private:
	Ui::ShikiRenameClass *ui;
	SeriesSelectionDialog *seriesSelectionDialog;
	RenameConfirmationDialog *renameConfirmationDialog;

	const QString DEFAULT_MEDIA_FILENAME_STRUCTURE = "<NAME> - <SEASON PREFIX><SEASON><EPISODE PREFIX><EPISODE> - [<EPISODE ABSOLUTE>] <EPISODE NAME> - [<YEAR> <LANGUAGE> <AUDIO> <RESOLUTION> <SOURCE> <VIDEO> - <SCENE GROUP>]";
	QString invalidFnCharset_win;
	QStringList fileTypes_video;

	MediaInfoDLL::MediaInfo MI;
	QMap<QString, QMap<QString, QString>> mediaInfoCache;

	void resizeEvent(QResizeEvent * event);
	void changeEvent(QEvent * event);
	void fixGridLayoutWidth();

	bool isSelectedInList(QString filename);

	void open(QDir dir);
	void addToHistory(int id, QString o, QString n);
	void buildPreview();
	void cacheMediaInfo(QFileInfo fileInfo);

	QString zerofy(QString string, int digits);

	std::pair<int, int> searchSeasonAndEpisode(QString filename_qs);
	int searchEpisode(QString filename_qs);
	int searchEpisode_startIdx;

	bool onlineDbAvailable();

	DirWatcher dirWatcher;
	TVDB tvdb;
	QString curDir = "";
	QFileInfoList infoList;
	QStringList filenames;
	QStringList fileextensions;
	QStringList selectedFilenames;
	std::vector<std::tuple<int, QString, QString>> hist_undo; //id, old, new
	std::vector<std::tuple<int, QString, QString>> hist_redo; //id, new, old

	//tab 1
	int input_remLeft = 0;
	int input_remRight = 0;
	QString input_replace1;
	QString input_replace2;
	int input_insert_idx = -1;
	QString input_insert_string;
	int input_removeAt_amount = 0;
	int input_removeAt_idx = -1;
	bool input_onlySelected = false;
	QString input_prefix;
	QString input_suffix;
	int input_num_idx = -1;
	int input_num_init = 1;
	int input_num_inc = 1;
	int input_num_digits = 1;
	//tab 2
	QString input_vid_customFileNameRaw;
	QString input_vid_name;
	QString input_vid_sPrefix = "s";
	int input_vid_sDigits = 2;
	QString input_vid_ePrefix = "e";
	int input_vid_eDigits = 2;
	bool input_vid_noSeason = false;
	MetaDB input_vid_eNameSrc;
	QString input_vid_eNameLang = "en";
	QString releaseDataSuffix;
	bool input_epDetection = false;
	bool ongoingSeriesSelection = false;
	QFutureWatcher<void> previewFW;
	QFutureWatcher<int> dirWatcherFW;
	QTimer *tvdbSearchDelayTimer;
};

#endif // SHIKIRENAME_H
