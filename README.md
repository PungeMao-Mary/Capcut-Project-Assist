## Capcut Project Assist

[中文版本](#chinese-version)

A cross-platform Qt application to assist with transferring Jianying Pro (Capcut video editor) project files between different machines. Since Jianying is an absolute garbage piece of software that pretends to be professional but lacks basic project export and team collaboration features, this tool helps bridge that gap horribly.

### Features
- Cross-platform support for macOS (ARM) and Windows (x64)
- Simple GUI with sender and receiver modes
- Automatic scanning of Jianying project directories
- Project folder compression to ZIP
- ZIP extraction with proper folder structure creation
- Handles platform-specific paths automatically

### Limitations and Rant
**IMPORTANT:** This tool ONLY transfers the project structure and metadata. It does **NOT** transfer the actual media files (videos, images, audio, etc.) referenced in the project. You still need to manually copy/pack the assets and re-establish links within Jianying because... wait for it... Jianying doesn't have native project export functionality! 🤦‍♂️

Why Jianying? Why this absolute garbage? A software that positions itself as "professional video editing for creators" but lacks basic:
- Project export/import features
- Team collaboration capabilities
- Media file management
- Basic professional workflow support

It's 2025, and we're still dealing with software that acts like it's from 2010. Just copy your project folder with your assets to transfer work? How primitive! This is what beginners expect, not professional users. Absolute joke.

But since we're forced to use this garbage, here's a workaround tool to make your life slightly less miserable.

### Requirements
- Qt 6.10.0 (+ CMake 3.16+)
- On macOS: Command Line Tools, cmake via brew
- On Windows: Visual Studio 2019/2022 with C++ workload, cmake

### Build Instructions

#### macOS (ARM64)
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/Volumes/ExtremeSSD/Applications/Qt/6.10.0/macos
make
```

#### Windows (x64 with MSVC)
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/6.10.0/msvc2022_64
cmake --build .
```

### Usage
1. Run the application
2. Choose "Sender Mode" to export projects:
   - Select a project folder from the list
   - Choose output ZIP location
   - Click "Start" to compress
3. Choose "Receiver Mode" to import projects:
   - Select the project ZIP file
   - Set destination path
   - Click "Start" to extract

### Default Project Paths
- macOS: ~/Movies/JianyingPro/User Data/Projects/com.lveditor.draft
- Windows: %APPDATA%/Local/JianyingPro/User Data/Projects/com.lveditor.draft

### License
Whatever license you want, just use it.

---

<a name="chinese-version"></a>

## 剪映工程文件助手

一个跨平台的Qt应用程序，用于在不同机器之间转移剪映专业版（Capcut视频编辑）项目文件。由于剪映是一个绝对的垃圾软件，假装专业却缺少基本的项目导出和团队协作功能，这个工具帮忙填补这个巨大缺陷。

### 功能特性
- 跨平台支持macOS (ARM)和Windows (x64)
- 简洁的GUI界面，支持发送和接收模式
- 自动扫描剪映项目目录
- 项目文件夹压缩为ZIP
- ZIP提取并正确创建文件夹结构
- 自动处理平台特定路径

### 缺陷与吐槽
**重要警告：** 这个工具**仅转移项目结构和元数据**。它**不转移项目中引用的实际媒体文件**（视频、图片、音频等）。你仍然需要手动复制打包素材，并在剪映内重新建立链接，因为... 等等... 剪映居然没有原生项目导出功能！🤦‍♂️

为何是剪映？这个垃圾玩意算什么？一个把自己定位为"面向创作者的专业视频编辑"的软件，却缺少基本的：
- 项目导出/导入功能
- 团队协作能力
- 媒体文件管理
- 基本的专业工作流程支持

2025年了，我们还在用像2010年一样的软件。复制项目文件夹连带着素材来转移工作？太原始了！这只有初级用户才会期待，不是专业用户的需求。绝对是开玩笑。

但既然被迫用这个垃圾，这就是一个稍稍减轻你痛苦的变通工具。

### 系统要求
- Qt 6.10.0 (+ CMake 3.16+)
- macOS上：Command Line Tools, brew install cmake
- Windows上：Visual Studio 2019/2022 with C++ workload, cmake

### 编译指南

#### macOS (ARM64)
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=/Volumes/ExtremeSSD/Applications/Qt/6.10.0/macos
make
```

#### Windows (x64 with MSVC)
```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH=C:/Qt/6.10.0/msvc2022_64
cmake --build .
```

### 使用方法
1. 运行应用程序
2. 选择"发送端模式"导出项目：
   - 从列表中选择项目文件夹
   - 选择ZIP输出位置
   - 点击"开始"压缩
3. 选择"接收端模式"导入项目：
   - 选择项目ZIP文件
   - 设置目标路径
   - 点击"开始"提取

### 默认项目路径
- macOS: ~/Movies/JianyingPro/User Data/Projects/com.lveditor.draft
- Windows: %APPDATA%/Local/JianyingPro/User Data/Projects/com.lveditor.draft

### 许可证
随便用什么许可证，用就行。
