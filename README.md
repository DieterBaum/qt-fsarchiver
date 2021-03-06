# qt-fsarchiver
qt-fsarchiver: Back up and restore partitions for Debian,Ubuntu, Linux-Mint, Suse and Fedora [http://wiki.ubuntuusers.de/qt-fsarchiver]

Copyright (C) 2008-2019 Francois Dupoux and Dieter Baum.  All rights reserved.
Copying the files is permitted with or without modifications. The code is without warranty of any kind. Use at your own risk.

François Dupoux has developed the basic program fsarchiver, Hihin Ruslan has improved the program and tranlate to englisch und russian. Michael R. Lawrence and his team translated to Spanish and Italian, Zhenneng Li translated to Chinese, Dieter Baum created the GUI and the code to use the GUI.

qt4-fsarchiver was translated QT5 environment and renamed in qt-fsarchiver.

qt-fsarchiver a program with a graphical interface for easy operation the archiving program fsarchiver.
qt-fsarchiver has been split into a program with a graphical user interface and a terminal program.
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

You change in the terminal to the folder qt5-fsarchiver (extracted from the sources).
This is the command to install the program with Debian, Ubuntu  and und Mint: /usr/lib/x86_64-linux-gnu/qt5/bin/qmake && make && sudo make install
In Debian you must instead sudo make install this: su -l, make install
This is the command for Fedora and Suse: qmake-qt5 && make && sudo make install.

Installing the program from the DEB packages:
A double click on the deb file installs the program.
If the installation is unsuccessful you enter this command in a terminal(you must be administrator): apt install qt-fsarchiver-0.8.5-1.deb. The version number needs to be adjusted.
In Debian is this the command: gpk-install-local-file qt5-fsarchiver-0.8.5-1.deb. The version number needs to be adjusted.
Is in Debian8 gpk is not installed, then you must enter: su -l dpkg-i, qt5-fsarchiver-0.8.5-1.deb und apt install -f. The output of dpkg error message can be ignored.

Installation of the program from a Launchpad:
With Ubuntu and Mint you can reach the installation with these commands:
sudo add-apt-repository ppa:/dieterbaum/qt-fsarchiver
Confirm the command with Enter.
sudo apt update
sudo apt install qt-fsarchiver

qt-fsarchiver-terminal is installed with the deb packages as well as with the launchpad installation.

Program call:
Partial starters are installed. By double-qt5-fsarchiver is started.
Start qt-fsarchiver in a terminal:
qt-fsarchiver

The handling of qt-fsarchiver is simple:

Using the menu option "Actions" from the toolbar or the following actions can be selected:
"Partition backup/restore partitions", "Partition backup/restore over a network", "MBR/GPT backup / restore your files", "Directories save/restore" and "clone HD, create oder restore an Image".
The program automatically detects if the Master Boot Record or GUID partition table must be secured.
Additionally, the menu item "Settings" basic settings such as number of cores or compression strength and can be adjusted further.
When backups of partitions can be used to determine whether the partition boot record (PBR) should be backed up. Grub does not support the PBR. With Grub, the backup is usually no significance.

The backup is always followed the same schema: You choose the name for the backup, the program automatically adds the name with a date stamp, then you choose the partition to be backed up or the directory to be backed up. Now the directory are selected in which the backup should be stored. then select the directory where the backup should be stored. the button "secure partition" button and begin the backup.
USB partitions are mounted under /media/user or under run/media/user.

The restoring is similar: In the backup directory the file name is selected to be restored. When restoring a partition to restore the partition is selected. It assesses whether the name of the restore partition (eg / dev/sda5), matches the name of the secured partition. After receiving the warning, the partition can be written back to any location. If exist a file with the partition boot sector as content, is asked if the PBR is to be restored.
When restoring a btrfs Partiiton you can choose whether the partition should be formatted or not. When you format a new UUID is generated when format is not the UUID get.

When restoring directories is selected, whether the directory should be restored to its original location or to another location. Press the  button "Restore Partition" and the partition or directory being restored.
Requisites for the work with the network:
When the backup over a network, an additional form is opened, in which the user name and password must be entered for the network. Of storing the password is not recommended outside of the private sector, because the encryption of the password is performed in a simple way.

With the protocoll samba:
If the network is used must be installed on both computers (Client and Server) Samba. Client is the computer that performs the backup/restore. Server is the computer where the data is stored.
The integration of the virtual file system "cifs vfs" must be possible on the Linux machine. Please refer to the Ubuntu wiki article "http://wiki.ubuntuusers.de/Samba_Client_cifs".
For access to a Windows 7 shared folder you must add group or user name "Everyone" in  Properties> Sharing> Advanced Sharing> Permissions. As permissions for "Everyone" should of "full access", "Change" and "reading" can be activated.

With the protocoll SSH (secure shared):
In the Linux area must be openssh-server installed on the computer on which the data is stored(server).To access the individual server may need to be entered once in the terminal to identify these commands:
sudo ssh user@Adresse des Servers. (Example: sudo ssh peter@192.168.2.10). The call must be made with administrative rights. Confirm the question of the RSA key fingerprint with yes. Enter the password for accessing the server. If this is successful you have with the terminal contacts to the server. This is indicated by the prompt changed. Leave the server with the command exit. This procedure needs to be performed once for all servers.
The first time access the program qt-fsarchiver on a server, the command sudo ssh username@serveraddress is entered directly into the terminal. In the basic settings of the program can be set if the automatic entry to access additional servers should be repeated or not. 
For mounting a ssh server, the terminal must be the password for access to the server to be entered. To avoid this, it is advisable to set up a public key. Important: The public key of the server (file:authorized_keys) needs in the /root/.ssh be copied.
In the basic settings can be determined whether the reference for setting the password to be displayed or not.
Note works with ssh: Some operating systems, the program must be started in a root-terminal. 

With the protocoll NFS (Network File System):
Only Linux machine as a client or server can be used. Must be installed on the server nfs-kernel-server. In the file /etc/exports to be released in addition to the directories listed. The name can not contain spaces. In the directory must have read and write can be accessed. The entry /home/user/images 192.168.2.0/255.255.255.0(rw) allows any computer with the IP address 192.168.2.0 through 192.168.2.255 a read-write access to the directory /home/user/pictures of the client.

After starting the live CD or the computer it may .ake a while to show up other computers on the network. 

Backups can also be done encrypted. Here, the key length between 6 and 64 characters. The archives splitting on DVD-size is possible.

The backup of mounted partitions is possible after asking for confirmation. Restoring partitions can only be made ​​if the partition is unmounted.
The restoration of a root or a home partition is possible with the live CD qt5-fsarchiver (http://sourceforge.net/projects/qt5-fsarchiver/files/Live-CD/ ").
On the SystemRescueCd is the program available fsarchiver. With fsarchiver it is posible root- and home-partitions can be restore​​.

When backing up the MBR/GPT only needs to select (with multiple hard drives), the hard disk and the backup directory. The hidden area of ​​the disk between the end of the MBR and the start of the first partition will be backed up. While restoring the MBR/GPT with multiple hard drives, the hard disk can be selected, the MBR/GPT will be written back. In addition, you can choose whether the boot loader area, the partition table or hidden area of ​​the disk to be restored.

qt-fsarchiver  can back up and restore with ecryptfs encrypted home directories. This is regardless of whether the user's home directory is stored in a separate partition or within the root directory.

With TrueCrypt encrypted partitions can not be backed up.

Securing and restore Windows FAT partitions is with Version 0.8.0.5 and later possible. It can be stored on a FAT partition. The backup file will be split if the file size is greater than 4GB.

Clone hard drive: You choose in the left list box, select the existing drive that is to be cloned, and the right list box, the hard drive, which is to be rebuilt. Click on the button "Clone disk".
Image of the hard disk/partition create:
Choose in the left list box of the existing hard drive/partition, from which an image is to be create. Choose a backup directory. In addition, select whether the image is compressed. Click on the button "Image create".
Image of the hard disk/partition restore:
Choose in the left list box from the hard drive/partiiton, from which an image is to be written back. Choose existing backup file (ending img.fsa or gz.fsa or gz.part.fsa or part.fsa). Click on the button "Image restore".

When starting qt-fsarchiver are not all unmounted partitions under / media / sda ... / media / sdb ... mounted. The partitions are easily reachable on the desktop. The directory where the backup should be saved or the directory in which the secured partition is stored, can be selected in qt-fsarchiver under / media / sd .... 
Qt-fsarchiver can only be called once. The repeated start is prevented.

Further information can be found in the german websites and http://wiki.ubuntuusers.de/qt-fsarchiver http://wiki.ubuntuusers.de/fsarchiver.
You can get information about fsarchiver on the English website of fsarchiver http://www.fsarchiver.org/Main_Page.
