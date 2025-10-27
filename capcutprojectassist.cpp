#include "capcutprojectassist.h"
#include <QDir>
#include <QProcess>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

CapcutProjectAssist::CapcutProjectAssist(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("剪映工程文件助手");
    resize(800, 600);
}

CapcutProjectAssist::~CapcutProjectAssist() {}

void CapcutProjectAssist::setupUI()
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Main page
    mainPage = new QWidget();
    auto mainLayout = new QHBoxLayout(mainPage);
    auto buttonLayout = new QVBoxLayout();
    buttonLayout->addStretch();
    senderModeButton = new QPushButton("发送端模式");
    senderModeButton->setMinimumSize(200, 50);
    buttonLayout->addWidget(senderModeButton, 0, Qt::AlignCenter);
    buttonLayout->addSpacing(20);
    receiverModeButton = new QPushButton("接收端模式");
    receiverModeButton->setMinimumSize(200, 50);
    buttonLayout->addWidget(receiverModeButton, 0, Qt::AlignCenter);
    buttonLayout->addStretch();
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    stackedWidget->addWidget(mainPage);

    // Sender page
    senderPage = new QWidget();
    auto senderLayout = new QHBoxLayout(senderPage);

    // Left side: project selector
    auto leftGroup = new QGroupBox("1. 选择工程文件夹");
    auto leftLayout = new QVBoxLayout(leftGroup);
    projectList = new QListWidget();
    leftLayout->addWidget(projectList);

    auto pathLayout = new QHBoxLayout();
    senderPathEdit = new QLineEdit();
    senderPathEdit->setPlaceholderText("默认或自定义工程路径");
    pathLayout->addWidget(senderPathEdit);
    refreshPathButton = new QPushButton("刷新");
    pathLayout->addWidget(refreshPathButton);
    leftLayout->addLayout(pathLayout);

    senderBackButton = new QPushButton("返回主菜单");
    leftLayout->addWidget(senderBackButton);
    senderLayout->addWidget(leftGroup, 2); // 左侧占比 2

    // Right side: start button
    auto rightGroup = new QGroupBox("2. 开始压缩");
    auto rightLayout = new QVBoxLayout(rightGroup);
    rightLayout->addStretch();
    senderStartButton = new QPushButton("开始");
    senderStartButton->setMinimumSize(150, 60);
    rightLayout->addWidget(senderStartButton, 0, Qt::AlignCenter);
    rightLayout->addStretch();
    senderLayout->addWidget(rightGroup, 1); // 右侧占比 1

    stackedWidget->addWidget(senderPage);

    // Receiver page
    receiverPage = new QWidget();
    auto receiverLayout = new QHBoxLayout(receiverPage);

    // Left side: select zip
    auto leftRGroup = new QGroupBox("1. 选择 ZIP 压缩包");
    auto leftRLayout = new QVBoxLayout(leftRGroup);
    leftRLayout->addStretch();
    selectZipButton = new QPushButton("选择文件");
    selectZipButton->setMinimumSize(150, 60);
    leftRLayout->addWidget(selectZipButton, 0, Qt::AlignCenter);
    zipPathEdit = new QTextEdit();
    zipPathEdit->setReadOnly(true);
    zipPathEdit->setMaximumHeight(80);
    zipPathEdit->setPlaceholderText("选择的ZIP文件路径将显示在此处...");
    leftRLayout->addWidget(zipPathEdit);
    leftRLayout->addStretch();
    receiverBackButton = new QPushButton("返回主菜单");
    leftRLayout->addWidget(receiverBackButton);
    receiverLayout->addWidget(leftRGroup, 1);

    // Right side: destination
    auto rightRGroup = new QGroupBox("2. 选择解压目标路径");
    auto rightRLayout = new QVBoxLayout(rightRGroup);
    auto destPathLayout = new QHBoxLayout();
    receiverPathEdit = new QLineEdit();
    destPathLayout->addWidget(receiverPathEdit);
    browseReceiverDirButton = new QPushButton("浏览...");
    destPathLayout->addWidget(browseReceiverDirButton);
    rightRLayout->addLayout(destPathLayout);
    rightRLayout->addStretch();
    receiverStartButton = new QPushButton("开始");
    receiverStartButton->setMinimumSize(150, 60);
    rightRLayout->addWidget(receiverStartButton, 0, Qt::AlignCenter);
    rightRLayout->addStretch();
    receiverLayout->addWidget(rightRGroup, 2);

    stackedWidget->addWidget(receiverPage);

    // Connect signals
    connect(senderModeButton, &QPushButton::clicked, this, &CapcutProjectAssist::showSenderMode);
    connect(receiverModeButton, &QPushButton::clicked, this, &CapcutProjectAssist::showReceiverMode);
    connect(senderBackButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentWidget(mainPage); });
    connect(receiverBackButton, &QPushButton::clicked, this, [this]() { stackedWidget->setCurrentWidget(mainPage); });

    // Sender connections
    connect(refreshPathButton, &QPushButton::clicked, this, &CapcutProjectAssist::refreshProjectList);
    connect(senderPathEdit, &QLineEdit::returnPressed, this, &CapcutProjectAssist::refreshProjectList);
    connect(senderStartButton, &QPushButton::clicked, this, &CapcutProjectAssist::sendStart);

    // Receiver connections
    connect(selectZipButton, &QPushButton::clicked, this, &CapcutProjectAssist::selectZip);
    connect(browseReceiverDirButton, &QPushButton::clicked, this, &CapcutProjectAssist::browseReceiverDir);
    connect(receiverStartButton, &QPushButton::clicked, this, &CapcutProjectAssist::receiveStart);

    // Set default paths
    QString defaultPath = getDefaultProjectsPath();
    senderPathEdit->setText(defaultPath);
    receiverPathEdit->setText(defaultPath);
}

void CapcutProjectAssist::showSenderMode()
{
    loadProjectsFromPath(senderPathEdit->text());
    stackedWidget->setCurrentWidget(senderPage);
}

void CapcutProjectAssist::refreshProjectList()
{
    loadProjectsFromPath(senderPathEdit->text());
}

void CapcutProjectAssist::loadProjectsFromPath(const QString& path)
{
    projectList->clear();
    QDir dir(path);
    if (!dir.exists()) {
        QMessageBox::warning(this, "路径无效", "指定的路径不存在！\n" + path);
        return;
    }
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Time); // 按时间排序，最新的在前面
    QStringList folders = dir.entryList();
    projectList->addItems(folders);
}


void CapcutProjectAssist::showReceiverMode()
{
    stackedWidget->setCurrentWidget(receiverPage);
}

void CapcutProjectAssist::sendStart()
{
    if (projectList->currentItem() == nullptr) {
        QMessageBox::warning(this, "操作无效", "请先在左侧列表中选择一个工程文件夹！");
        return;
    }

    QString sourceBasePath = senderPathEdit->text();
    QString projectName = projectList->currentItem()->text();
    QString sourceFolder = QDir(sourceBasePath).absoluteFilePath(projectName);

    QString defaultZipName = QDir::homePath() + "/" + projectName + ".zip";
    QString destZip = QFileDialog::getSaveFileName(this, "保存压缩文件", defaultZipName, "ZIP 文件 (*.zip)");

    if (destZip.isEmpty()) return;

    if (compressFolder(sourceFolder, destZip)) {
        QMessageBox::information(this, "成功", "工程文件夹已成功压缩到：\n" + destZip);
    } else {
        QMessageBox::critical(this, "错误", "压缩失败！请检查权限或路径是否正确。");
    }
}

void CapcutProjectAssist::selectZip()
{
    QString zipFile = QFileDialog::getOpenFileName(this, "选择工程压缩包", QDir::homePath(), "ZIP 文件 (*.zip)");
    if (!zipFile.isEmpty()) {
        selectedZipPath = zipFile;
        zipPathEdit->setText(zipFile);
    }
}

void CapcutProjectAssist::browseReceiverDir()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择解压目标目录", receiverPathEdit->text());
    if (!dir.isEmpty()) {
        receiverPathEdit->setText(dir);
    }
}

void CapcutProjectAssist::receiveStart()
{
    if (selectedZipPath.isEmpty()) {
        QMessageBox::warning(this, "操作无效", "请先选择一个工程 ZIP 压缩包！");
        return;
    }

    QString destDir = receiverPathEdit->text();
    if (destDir.isEmpty()) {
        QMessageBox::warning(this, "操作无效", "请设置一个解压目标路径！");
        return;
    }

    QDir dir(destDir);
    if (!dir.exists()) {
        bool ok = dir.mkpath(".");
        if (!ok) {
            QMessageBox::critical(this, "错误", "无法创建目标目录，请检查权限！\n" + destDir);
            return;
        }
    }

    if (extractZip(selectedZipPath, destDir)) {
        QMessageBox::information(this, "成功", "工程文件已成功解压到：\n" + destDir);
    } else {
        QMessageBox::critical(this, "错误", "解压失败！请检查ZIP文件是否有效或目标路径权限。");
    }
}

QString CapcutProjectAssist::getDefaultProjectsPath()
{
#ifdef Q_OS_WIN
    // 正确的 Windows 实现
    // QStandardPaths::AppLocalDataLocation 会返回 C:\Users\<user>\AppData\Local\<AppName>
    // 我们需要的是它的父目录 C:\Users\<user>\AppData\Local
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir(appDataLocation);
    dir.cdUp(); // 返回上一级目录
    QString localPath = dir.path(); // 这就是 "C:\Users\<user>\AppData\Local"

    return QDir::toNativeSeparators(localPath + "/JianyingPro/User Data/Projects/com.lveditor.draft");

#elif defined(Q_OS_MAC)
    // macOS 的实现是正确的，保持不变
    QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return homePath + "/Movies/JianyingPro/User Data/Projects/com.lveditor.draft";

#else
    // 为 Linux 等其他平台提供一个备用路径
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#endif
}

bool CapcutProjectAssist::compressFolder(const QString& sourceFolder, const QString& destZip)
{
    QProcess process;
    QFileInfo sourceInfo(sourceFolder);

    // 工作目录设置为要压缩的文件夹的父目录
    process.setWorkingDirectory(sourceInfo.absolutePath());

    QString folderName = sourceInfo.fileName();

    // 使用 QDir::toNativeSeparators 保证路径分隔符正确
    QString nativeDestZip = QDir::toNativeSeparators(destZip);

#ifdef Q_OS_WIN
    // Windows: 使用 powershell 的 Compress-Archive
    // 为防止路径中带空格，用单引号包裹
    QString command = QString("Compress-Archive -Path '%1' -DestinationPath '%2' -Force").arg(folderName).arg(nativeDestZip);
    process.start("powershell", QStringList() << "-Command" << command);
#else
    // macOS/Linux: 使用系统 zip 命令
    // -r 递归, -y 保留符号链接
    process.start("zip", QStringList() << "-ry" << nativeDestZip << folderName);
#endif

    // 等待进程完成，超时时间30秒
    if (!process.waitForFinished(30000)) {
        qDebug() << "Compression process timed out.";
        process.kill();
        return false;
    }

    qDebug() << "Compression finished. Exit code: " << process.exitCode();
    qDebug() << "StdOut: " << process.readAllStandardOutput();
    qDebug() << "StdErr: " << process.readAllStandardError();

    return process.exitCode() == 0;
}

bool CapcutProjectAssist::extractZip(const QString& zipPath, const QString& destDir)
{
    QProcess process;

    // 确保路径分隔符正确
    QString nativeZipPath = QDir::toNativeSeparators(zipPath);
    QString nativeDestDir = QDir::toNativeSeparators(destDir);

#ifdef Q_OS_WIN
    // Windows: 使用 powershell 的 Expand-Archive
    QString command = QString("Expand-Archive -Path '%1' -DestinationPath '%2' -Force").arg(nativeZipPath).arg(nativeDestDir);
    process.start("powershell", QStringList() << "-Command" << command);
#else
    // macOS/Linux: 使用系统 unzip 命令
    // -o 覆盖文件不提示, -d 指定解压目录
    process.start("unzip", QStringList() << "-o" << nativeZipPath << "-d" << nativeDestDir);
#endif

    if (!process.waitForFinished(30000)) {
        qDebug() << "Extraction process timed out.";
        process.kill();
        return false;
    }

    qDebug() << "Extraction finished. Exit code: " << process.exitCode();
    qDebug() << "StdOut: " << process.readAllStandardOutput();
    qDebug() << "StdErr: " << process.readAllStandardError();

    // 只要zip包是正确地对整个文件夹打包（而不是文件夹里的内容），
    // 那么解压后就会自动创建那个文件夹。这个逻辑是符合你的需求的。
    return process.exitCode() == 0;
}
