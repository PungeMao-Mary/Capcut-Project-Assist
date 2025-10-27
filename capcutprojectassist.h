#ifndef CAPCUTPROJECTASSIST_H
#define CAPCUTPROJECTASSIST_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGroupBox>
#include <QFileDialog>
#include <QMessageBox>

// Forward declarations for cleaner header
class QProcess;

class CapcutProjectAssist : public QMainWindow
{
    Q_OBJECT

public:
    CapcutProjectAssist(QWidget *parent = nullptr);
    ~CapcutProjectAssist();

private slots:
    void showSenderMode();
    void showReceiverMode();
    void sendStart();
    void selectZip();
    void browseReceiverDir();
    void receiveStart();
    void refreshProjectList(); // 新增槽函数

private:
    void setupUI();
    QString getDefaultProjectsPath();
    bool compressFolder(const QString& sourceFolder, const QString& destZip);
    bool extractZip(const QString& zipPath, const QString& destDir);
    void loadProjectsFromPath(const QString& path); // 提取出的辅助函数

    QStackedWidget* stackedWidget;
    QWidget* mainPage;
    QWidget* senderPage;
    QWidget* receiverPage;

    // Main page widgets
    QPushButton* senderModeButton;
    QPushButton* receiverModeButton;

    // Sender page widgets
    QListWidget* projectList;
    QLineEdit* senderPathEdit;
    QPushButton* refreshPathButton; // 新增按钮
    QPushButton* senderStartButton;
    QPushButton* senderBackButton;

    // Receiver page widgets
    QPushButton* selectZipButton;
    QTextEdit* zipPathEdit;
    QLineEdit* receiverPathEdit;
    QPushButton* browseReceiverDirButton;
    QPushButton* receiverStartButton;
    QPushButton* receiverBackButton;

    QString selectedZipPath;
};

#endif // CAPCUTPROJECTASSIST_H
