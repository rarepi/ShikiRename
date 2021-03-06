#ifndef SHIKIRENAME_SSD_H
#define SHIKIRENAME_SSD_H

#include <QDialog>
#include <QString>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
	class SeriesSelectionDialog;
}

class SeriesSelectionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SeriesSelectionDialog(QWidget *parent);
	~SeriesSelectionDialog();

signals:
	void closed(int id, QString name);

public slots:
	void setData(QJsonArray seriesData);

private slots:
	void on_buttonOK_clicked();
	void on_buttonCancel_clicked();


private:
	Ui::SeriesSelectionDialog *ui;
};

#endif // SHIKIRENAME_SSD_H
