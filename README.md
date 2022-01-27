# qt-fsarchiver-terminal
qt-fsarchiver-terminal is required for qt-fsarchiver (https://github.com/dieterbaum/qt-fsarchiver)to work correctly.
qt-fsarchiver: Back up and restore partitions, directories for Debian,Ubuntu, Linux-Mint, Suse and Fedora [http://wiki.ubuntuusers.de/qt4-fsarchiver]
qt-fsarchiver can clone and image hard disks too.

Both programs must be installed.

Copyright (C) 2008-2018 Francois Dupoux and Dieter Baum.  All rights reserved.
Copying the files is permitted with or without modifications. The code is without warranty of any kind. Use at your own risk.

François Dupoux has developed the basic program fsarchiver, Dieter Baum created the GUI and the code to use the GUI.

qt-fsarchiver a program with a graphical interface for easy operation the archiving program fsarchiver.
qt-fsarchiver has been split into a program with a graphical user interface (qt-fsarchiver)and a terminal program (qt-fsarchiver-terminal).
The graphical program can be started without root rights.
Thus the startup problems with gksu/gksudo, which is no longer installable, were solved with Wayland and Snap programs.

The source code can be installed on any Debian-based system on Suse and Fedora.
For Debian, Ubuntu and Linux Mint are deb packages for Suse and Fedora rpm packages are available.

Installing the program from the source files:
To install qt-fsarchiver and qt-fsarchiver-terminal the necessary dependencies for fsarchiver and the qt5 development environment must be installed.
Of Debian based distributions: This is the command:
sudo apt install libzip-dev libbz2-dev liblzma-dev liblzo2-2 liblzo2-dev libgcrypt11-dev e2fslibs-dev libblkid-dev libattr1-dev build-essential qtbase5-dev qttools5-dev-tools qt5-default btrfs-tools gdisk sshfs sshpass nmap samba nfs-kernel-server nfs-common smbclient liblz4-dev libzstd1-dev jfsutils xfsprogs sudo 

For some distributions, the /etc/sudoers file must be completed with these lines:
username ALL=(ALL) ALL 
%sudo	ALL=(ALL:ALL) ALL
The username has to be adjusted: for example peter.

Instead of libzst1-dev, libzst-dev is installed in some systems. btrfs-tools has recently been replaced by btrfs-progs. The above command has to be adapted accordingly.
 
The command for Suse: (you must be an administrator su -l) zypper in zypper in qt5-default libQt5Core5 libqt5-qttools libqt5-qtbase-devel make libzip-devel libbz2-devel xz-devel lzo-devel libgcrypt-devel e2fsprogs-devel libblkid-devel libattr-devel btrfsprogs gdisk sshfs nmap samba nfs-kernel-server xfsprogs liblz4-1 liblz4-devel libzstd1 libzstd-devel zlib-devel jfsutils 
If you use ssh (secure shell) want to access other computers in the network, you still need to install individually sshpass.

The command for Fedora: (you must be an administrator su -l) dnf install  gcc gcc-c++ zlib-devel bzip2-devel xz-devel lzo-devel libgcrypt-devel e2fsprogs-devel libblkid-devel libattr-devel qt5-default qt5-qtbase qt5-qtbase-devel gdisk sshfs sshpass nmap samba samba-client nfs-utils beesu lz4-devel libzstd-devel jfsutils xfsprogs
For a 64-bit system, you must also install lrelease: dnf install qt5-linguist.x86-64
32-bit systems are no longer supported.

You change in the terminal to the folder qt-fsarchiver-terminal (extracted from the sources).
This is the command to install the program with Debian, Ubuntu  and und Mint: /usr/lib/x86_64-linux-gnu/qt5/bin/qmake && make && sudo make install
In Debian you must instead sudo make install this: su -l, make install
This is the command for Fedora and Suse: qmake-qt5 && make && sudo make install.

Further information is contained in the doc files of qt-fsarchiver and qt-fsarchiver-terminal.




