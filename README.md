###qt-fsarchiver
 
Back up and restore partitions for Debian, Ubuntu, Linux-Mint, SUSE and Fedora [http://wiki.ubuntuusers.de/qt-fsarchiver]
 
**qt-fsarchiver** is a program with a graphical interface for easy operation of the archiving program _fsarchiver_.
 
qt-fsarchiver has been split into a program with a graphical user interface and a terminal program.
Both programs must be installed.
The graphical program can be started without superuser rights.
Thus startup problems with gksu/gksudo, (which is no longer installable) were solved with Wayland and Snap packages.

The source code can be installed on any Debian-based system via DEB packages, and on SUSE and Fedora with RPM.
 
###Installation from source files:
To install qt-fsarchiver and qt-fsarchiver-terminal the necessary dependencies for fsarchiver and the
Qt 5 development environment must be installed.
 

####Debian based installations:
1. "sudo apt install libzip-dev libbz2-dev liblzma-dev liblzo2-2 liblzo2-dev libgcrypt20-dev e2fslibs-dev libblkid-dev libattr1-dev build-essential qtbase5-dev qttools5-dev-tools qt5-default btrfs-tools gdisk sshfs sshpass nmap samba nfs-kernel-server nfs-common smbclient liblz4-dev libzstd1-dev jfsutils xfsprogs sudo"
2. If that, grant yourself superuser privileges with "su"
 
On some distributions, the /etc/sudoers file must be completed with these lines:
 username ALL=(ALL) ALL 
 %sudo	ALL=(ALL:ALL) ALL
 The username has to be adjusted: for example peter.
 
Instead of libzst1-dev, libzst-dev is installed in some systems. btrfs-tools has recently been replaced by btrfs-progs.
The above command has to be adapted accordingly.
  
####SUSE:
1. Grant yourself superuser priviliges: "su -l"
2. Install required packages "zypper in zypper in qt5-default libQt5Core5 libqt5-qttools libqt5-qtbase-devel make libzip-devel libbz2-devel xz-devel lzo-devel libgcrypt-devel e2fsprogs-devel libblkid-devel libattr-devel btrfsprogs gdisk sshfs nmap samba nfs-kernel-server xfsprogs liblz4-1 liblz4-devel libzstd1 libzstd-devel zlib-devel jfsutils"
If you use SSH (secure shell) and want to access other computers in the network, you also need "sshpass".

####Fedora:
1. Grant yourself superuser priviliges: "su -l"
2. Install required packages "dnf install gcc gcc-c++ zlib-devel bzip2-devel xz-devel lzo-devel libgcrypt-devel e2fsprogs-devel libblkid-devel libattr-devel qt5-default qt5-qtbase qt5-qtbase-devel gdisk sshfs sshpass nmap samba samba-client nfs-utils lz4-devel libzstd-devel jfsutils xfsprogs"
For a 64-bit system, you must also install lrelease: "dnf install qt5-linguist.x86-64"
With Fediora30 you still have to install "make".
(32-bit systems are no longer supported.)
 
You change in the terminal to the folder qt5-fsarchiver (extracted from the sources).

####Install the program
**Debian, Ubuntu and Mint** with this command:
"/usr/lib/x86_64-linux-gnu/qt5/bin/qmake && make && sudo make install"
**Debian**: Instead use sudo make install like this:
1. "su -l"
2. "make install"
**Fedora and SUSE**:
"qmake-qt5 && make && sudo make install."

## DEB package installation:
1. Double click the DEB file to install it.
2. If the installation is unsuccessful, you can enter this command in a terminal (as superuser): 
"apt install qt-fsarchiver-0.8.5-1.deb" (adjust 0.8.5-1 to what you have downloaded).
In Debian:
1. "gpk-install-local-file qt5-fsarchiver-0.8.5-1.deb"(adjust 0.8.5-1 to what you have downloaded).
If in Debian 8 "gpk" is not installed, you must enter:
1. "su -l dpkg-i, qt5-fsarchiver-0.8.5-1.deb" (adjust 0.8.5-1 to what you have downloaded).
2. "apt install -f". (The output of the dpkg error message can be ignored.)

### PPA installation:
 With Ubuntu and Mint you can reach the installation with these commands:

1. "sudo add-apt-repository ppa:/dieterbaum/qt-fsarchiver"
2. Confirm the command with ⏎.
3. "sudo apt update && sudo apt install qt-fsarchiver"
 
qt-fsarchiver-terminal is installed with the DEB packages, as well as with the PPA installation.
The version of qt-fsarchiver-terminal is checked. If the version is incorrect, the program is terminated.
 
 Program call:
 Partial starters are installed. By double-qt-fsarchiver is started.

Start qt-fsarchiver in a terminal:
1. "/usr/sbin/qt-fsarchiver"

### Using qt-fsarchiver:

1. Start it.
2. Enter your superuser password in the dialog window when requested.
Please note: If the superuser password is incorrect, a hint to terminate the program is given.
The program will be forcefully terminated. An empty password is detected and an error message is displayed.
2. Optionally select whether the password is shown on or not under
"Settings" → "Basic Settings" by marking the checkbox "Password"
3. Select one of the following from "Actions" in the toolbar:
* "Partition backup/restore partitions"
* "Partition backup/restore over a network"
* "MBR/GPT backup / restore your files"
* "Directories save/restore"
* "Clone HD"
* "Create or restore an image".

The program automatically detects whether the master boot record (MBR) or GUID partition table must be secured.

3+. Additionally, from the menu item "Settings",
basic settings such as the number of cores or compression strength can be adjusted further.
When backups of partitions can be used to determine whether the partition boot record (PBR) should be backed up.
GRUB does not support the PBR. With GRUB, the backup is usually no significance.

### Making backups:
1. Choose the name for the backup, the program automatically adds the name with a date stamp.
2. Choose the partition or the directory to be backed up.
3. Select the directory to store the backup in.
4. Click the "secure partition" button to begin the backup.
 
The restoring is similar: In the backup directory the file name is selected to be restored.
When restoring a partition to restore the partition is selected.
It assesses whether the name of the restore partition (e.g. /dev/sda5),
matches the name of the secured partition.
After receiving the warning, the partition can be written back to any location.
If a file with the partition boot sector content exist,
a question will be presented of whether the PBR is to be restored.
When restoring a Btrfs partition, you can choose whether the partition should be formatted or not.
When you format a new UUID is generated when format is not the UUID get.

When restoring directories is selected,
whether the directory should be restored to its original location or to another location.
Press the "Restore Partition" button and the partition or directory will be restored.

### Requisites for the work with the network:

When performing a backup over a network, an additional form is opened, in which the username and password for the network must be entered. Storing the password outside of local storage is not recommended, since encryption of the password is performed in a much too simple way.
 
 Prerequisites for working with the network: 
 The computer name may contain a maximum of 15 characters.

The names of the backup directories can not contain any spaces.

### With the Samba (SMB) protocol:
If the same local network is used, Samba must be installed on both computers (client and server). 
The client is the computer that performs the backup/restoration.
The server is the computer where the data is stored.
Integration of the virtual file system "CIFS VFS" must be possible on the Linux machine.
Please refer to this Ubuntu wiki article "https://wiki.ubuntuusers.de/Samba_Client_cifs".
For access to a shared folder on Windows 7 you must add a group- or username
"Everyone" in "Properties" → "Sharing" → "Advanced Sharing" → "Permissions".
To grant permissions to "Everyone", "Full access", "Change" and "Reading" should be activated.
 
### With the secure shell (SSH) protocol:
On the Linux side, openssh-server must installed on the computer the data is stored on (server).
To access the individual server, you may need authenticate by entering these commands in a terminal:
"sudo ssh user@server-address". (Example: sudo ssh peter@192.168.2.10).
Confirm the question of the RSA key fingerprint addition with "Yes".
Enter the password for accessing the server. If this is successful, you have made a connection to the server.
This is indicated by the prompt changing. Leave the server with the "exit" command.
This procedure needs to be performed once for all servers.
 
For first time access to a server with qt-fsarchiver, enter the command "sudo ssh username@serveraddress" in a the terminal.
In the basic settings of the program you can select whether automatic access additional servers should be repeated or not. 
For mounting a SSH server, you must enter the password to access it in a terminal.
To avoid this, (or in addition to it) it is strongly advisable to set up a public key to avoid automated guesses.
 
**Important**: The public key of the server (file:authorized_keys) needs to be copied into /root/.ssh.
 
n the basic settings it can be determined whether the reference for setting the password should be displayed or not.
Note on working with SSH: On some operating systems, the program must be started in a terminal with the command: "qt-fsarchiver"
 
#### With the network file system (NFS) protocol:
Only Linux machines as client or server can be used. nfs-kernel-server must be installed on the server.
In the file /etc/exports to be released in addition to the directories listed. The name can not contain spaces.
Read and write access must be granted so it can be accessed.
The entry /home/user/images 192.168.2.0/255.255.255.0(rw) grants any computer within the IP address range 192.168.2.0 through 192.168.2.255 read-write access to the /home/user/pictures folder of the client.
 
After starting the live CD or the computer, it may take a while for other computers on the network to show up. 
 
Backups can also be made in encrypted form. Use a key-length of between 6 and 64 characters to do so.
Archive splitting to DVD size is possible.
 
The backup of mounted partitions is possible after asking for confirmation.
Restoring partitions can only be done if the partition is unmounted.
Restoring root or home partitions is possible with the qt5-fsarchiver image (http://sourceforge.net/projects/qt5-fsarchiver/files/Live-CD/ ").
On the SystemRescueCd, you will find the program fsarchiver. With fsarchiver it is possible to restore root- and home partitions.
 
If you have multiple hard-drives, only the hard disk and the backup directory needs to be selected when backing up the MBR/GPT. The hidden area of the disk between the end of the MBR and the start of the first partition will be backed up.
While restoring the MBR/GPT with multiple hard drives, the hard disk to write the MBR/GPT to can be selected.
In addition, you can choose whether the boot loader area, the partition table, or a hidden area of the disk is to be restored.
 
qt-fsarchiver can back up and restore encrypted home directories with eCryptfs,
regardless of whether the user's home directory is stored in a separate partition, or within the root directory.
 
Partitions encrypted with TrueCrypt can not be backed up.
 
Securing and restore Windows FAT partitions is possible with version 0.8.0.5 and later. It can be stored on a FAT partition.
The backup file will be split if the file size is greater than 4GB.
 
### Clone hard drive:
 
1. Select an existing drive to be cloned in the list on the left.
2. Select the hard drive to rebuild from the list on the right.
3. Click the "Clone disk" button.
 
### Create an image of the hard disk/partition:

1. Choose the hard drive/partition from the list on the left, from which an image is to be written back.
2. Choose a backup directory.
3. elect whether the image should be compressed.
4. Click the "Image create" button.

### Restore image of the hard disk/partition:

1. Choose the hard drive/partition from the list on the left, from which an image is to be written back.
2. Choose existing backup file (ending in img.fsa or gz.fsa or gz.part.fsa or part.fsa).
3. Click on the button "Image restore".

When starting qt-fsarchiver, unmounted partitions under "/media/sda*" and "/media/sdb*" are not mounted.
The partitions are easily reachable from the desktop.
The "/media/sd*" can be used to save secured partitions or saving backups by using qt-fsarchiver to select it.

Qt-fsarchiver can only be called once. Thus concurrently running copies is prevented.

Further info can be found on the German website https://wiki.ubuntuusers.de/qt-fsarchiver.
You can get info about fsarchiver on the English website of fsarchiver https://www.fsarchiver.org/.

* _François Dupoux_, development of fsarchiver.
* _Hihin Ruslan_, program improvements, English and Russian translation.
* _Michael R. Lawrence and his team_, Spanish and Italian translation.
* _Zhenneng Li_, Chinese translation.
* _Dieter Baum_, GUI and code to use it.
* _Allan Nordhøy_, editing and Norwegian Bokmål translation.

qt4-fsarchiver was translated to the Qt 5 environment and renamed qt-fsarchiver.

Qt-fsarchiver is Licensed GPLv3+
Copyright © 2008–2020 Francois Dupoux and Dieter Baum. All rights reserved.
Copying the files is permitted with or without modifications. The code is without warranty of any kind. Use at your own risk.

