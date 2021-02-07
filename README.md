# Terminal Finances
This software is suitable for those who want to have control of their personal accounts in an easy and simple way. Available for Linux and Windows.

## ![Terminal Finances - Personal Financial Management](terminal-finances.png) Terminal Finances - Personal Financial Management

![Terminal Finances running](screenshot.png)

# Installation
If you want to use Terminal Finances without compiling choose one of the options below to download:
- [AppImage Linux x86_64](https://github.com/terroo/terminal-finances/releases/download/v1.0.0/Terminal_Finances-x86_64.AppImage)
How to install:
```sh
wget https://github.com/terroo/terminal-finances/releases/download/v1.0.0/Terminal_Finances-x86_64.AppImage
chmod +x Terminal_Finances-x86_64.AppImage
./Terminal_Finances-x86_64.AppImage
```
Alternatively, you can use the [app-get](https://github.com/terroo/app-get). What makes it different is that it creates an icon on your Dashboard and makes it easier to access and update or remove. Example:
```sh
app-get terminal-finances
```

- [Windows 10 64-bit](https://github.com/terroo/terminal-finances/releases/download/v1.0.0/TerminalFinances_installer_Win10_64.rar)
  - Download it by [clicking on this link](https://github.com/terroo/terminal-finances/releases/download/v1.0.0/TerminalFinances_installer_Win10_64.rar)
  - Unzip the **.rar** file
  - Double-click the installation file to install
  - And after the installation is finished, access the program through the start menu

# Building the Terminal Finances
First of all you will need the dependencies
  - [qmake](https://en.wikipedia.org/wiki/Qmake)
  - [g++](https://gcc.gnu.org/)
  - [GNU Make](https://www.gnu.org/software/make/)
  - libQt5Widgets
  - libQt5Gui
  - libQt5Core
  - libQt5Sql
  - libQt5PrintSupport

For example, on Ubuntu, Linux Mint, Debian and derivatives the command would be:
```sh
sudo apt install qmake g++ make libqt5widgets5 libqt5gui5 libqt5core5a libqt5sql libqt5printsupport5
```

Then clone the repository and compile as follows:
```sh
git clone https://github.com/terroo/terminal-finances
cd terminal-finances
qmake -qt=qt5 src/TerminalFinances.pro
make
sudo make install
```

# Use
I am still developing the Wiki, but while it is not ready you can see how to use it through this video:
> Activate subtitles and choose the language according to yours.

## <https://youtu.be/BF809OoXfjM>

If you find a bug or want a feature to be implemented for the new versions use the [issues](https://github.com/terroo/terminal-finances/issues) to inform.

# License
[GNU GPLv3](LICENSE)

---

# Uninstall
- Compiled version 
Clone the repository if you don't have
```sh
cd terminal-finances
sudo make uninstall
```

- Windows
Access the Control Panel and Add/Remove Programs and uninstall

- [app-get](https://github.com/terroo/app-get)/Linux
```sh
app-get --remove terminal-finances
```

