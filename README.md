=========================================================================================================================================
qt-fsarchiver: Back up and restore partitions for Debian,Ubuntu, Linux-Mint, Suse and Fedora [http://wiki.ubuntuusers.de/qt-fsarchiver]
=========================================================================================================================================

Copyright (C) 2008-2024 Francois Dupoux and Dieter Baum.  All rights reserved.
Copying the files is permitted with or without modifications. The code is without warranty of any kind. Use at your own risk.

François Dupoux has developed the basic program fsarchiver, Hihin Ruslan has improved the program and tranlate to englisch und russian. Michael R. Lawrence and his team translated to Spanish and Italian, Zhenneng Li translated to Chinese, Dieter Baum created the GUI and the code to use the GUI.

qt-fsarchiver a program with a graphical interface for easy operation the archiving program fsarchiver.
The graphical program must be started with root rights

The source code can be installed on any Debian-based system on Suse and Fedora.
For Debian, Ubuntu and Linux Mint are deb packages for Suse and Fedora rpm packages are available.

From version 2.8.7-0 qt-fsarchiver is based on Qt6.

Installing the program from the source files:
To install qt-fsarchiver the necessary dependencies for fsarchiver and the qtt development environment must be installed.
Of Debian based distributions: This is the command:
sudo apt install libzip-dev libbz2-dev liblzma-dev liblzo2-2 liblzo2-dev libgcrypt20-dev e2fslibs-dev libblkid-dev libattr1-dev build-essential qt6-qmltooling-plugins qt6-base-dev qt6-tools-dev qt6-5compat-dev btrfs-progs gdisk liblz4-dev libzstd-dev jfsutils xfsprogs sudo 
For some distributions, the /etc/sudoers file must be completed with these lines:
username ALL=(ALL) ALL 
%sudo	ALL=(ALL:ALL) ALL
The username has to be adjusted: for example peter.

The command for Suse: (you must be an administrator su -l) zypper in qt6-qtbase-devel qt6-linguist qt6-qt5compat qt6-qt5compat-devel make libzip-devel libbz2-devel xz-devel lzo-devel libgcrypt-devel e2fsprogs-devel libblkid-devel libattr-devel btrfsprogs gdisk  xfsprogs liblz4-1 liblz4-devel libzstd1 libzstd-devel zlib-devel jfsutils update-desktop-files pkexec

The command for Fedora: (you must be an administrator su -l) dnf install  gcc gcc-c++ zlib-devel bzip2-devel xz-devel lzo-devel libgcrypt-devel e2fsprogs-devel libblkid-devel libattr-devel qt6-qtbase qt6-qtbase-devel gdisk lz4-devel libzstd-devel jfsutils xfsprogs libuuid-devel qt6-linguist qt6-qt5compat qt6-qt5compat-devel

You change in the terminal to the folder qt-fsarchiver (extracted from the sources).
This is the command to install the program with Debian, Ubuntu, Mint, Fedora und Suse: qmake6 && make && sudo make install
In Debian you must instead sudo make install this: su -l, make install

Installing the program from the DEB packages:
A double click on the deb file installs the program.
If the installation is unsuccessful you enter this command in a terminal(you must be administrator): apt install qt-fsarchiver-2.8.7-0.deb. The version number needs to be adjusted.

Installation of the program from a Launchpad:
With Ubuntu and Mint you can reach the installation with these commands:
sudo add-apt-repository ppa:dieterbaum/qt-fsarchiver
Confirm the command with Enter.
sudo apt update
sudo apt install qt-fsarchiver

With this installation variant, the updates are installed automatically

Program call:
Partial starters are installed. By double-qt5-fsarchiver is started.
Start qt-fsarchiver in a terminal: pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY /usr/sbin/qt-fsarchiver

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
When the backup over a network, an additional form is opened, in which the user name and password must be entered for the network. 

New from version 0.8.6-9:
When backing up partitions, a order list is created in the background. If the order name is the same, the older date is replaced by the current date in the order name.
A task can be selected under the menu item Actions>Task and the corresponding task can be carried out by pressing the button "Save partition" or "Restore partition".
Individual or all orders can be deleted under Actions>Edit order list.
With regular backups, many orders files accumulate. Older orders files can be deleted with the "Delete existing order" button. The number of most recent backups left can be selected from 2 to 5. The order data intended for deletion are displayed in a text window for prior checking.
Jobs with encryption and recovery jobs are not saved for security reasons.

New as of version 1.8.6-0: 
qt-fsarchiver can also be started without a graphical user interface.
If a job has been saved under this name: jj-home, then this job can be started like this: pkexec env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY /usr/sbin/qt-fsarchiver -jj-home.
If a corresponding desktop file is also created, this job can be processed very quickly.

Backups can also be done encrypted. Here, the key length between 6 and 64 characters. The archives splitting on DVD-size is possible.

The backup of mounted partitions is possible after asking for confirmation. Restoring partitions can only be made ​​if the partition is unmounted.
The restoration of a root or a home partition is possible with the live DVD-fsarchiver (http://sourceforge.net/projects/qt-fsarchiver/files/Live-CD/ ").
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

When starting qt-fsarchiver are not all unmounted partitions under /media/sda ... /media/sdb .../media/nvme1n.... mounted. The partitions are easily reachable on the desktop. The directory where the backup should be saved or the directory in which the secured partition is stored, can be selected in qt-fsarchiver under /media/sd ....or /media/nvme1n... 
Qt-fsarchiver can only be called once. The repeated start is prevented.

Further information can be found in the german websites http://wiki.ubuntuusers.de/qt-fsarchiver.
You can get information about fsarchiver on the English website of fsarchiver http://www.fsarchiver.org/Main_Page.


