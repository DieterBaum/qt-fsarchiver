#!/bin/bash
# Hinweis: keine Leerzeile zulässig, auch nicht am Ende!!, gegebenenfalls korrigieren. 
if [ $# -lt 1 ]; then
  echo "Fehler: Keine Kein Passwort übergeben"
  exit
fi
# $1 = Password
# $2 = Auswahl
# $3 = zu mountende Partition, qt-fsarchiver Starter Verzeichnis /.config if=/dev
# $4 = Mountort of=/dev
# $5 = parameter für rm
password=$1
auswahl=$2
if [ $2 -eq 1 ]; then
echo $1 | sudo -S -b /usr/sbin/qt-fsarchiver-terminal $3
fi
if [ $2 -eq 2 ]; then
echo $1 | sudo -S -b mount $3 $4 
fi
if [ $2 -eq 3 ]; then
echo $1 | sudo -S -b mkdir $3 $4 $5
fi
if [ $2 -eq 4 ]; then
echo $1 | sudo -S -b umount $3 $4 $5 $6
fi
if [ $2 -eq 5 ]; then
cd /
cd $3
echo $1 | sudo -S -b rm $4 $5 $6 $7
fi
if [ $2 -eq 6 ]; then
echo $1 | sudo -S -b dd $3 $4 bs=512 count=1
fi
if [ $2 -eq 7 ]; then
echo $1 | sudo -S -b mkfs.btrfs $3 $4 
fi
if [ $2 -eq 8 ]; then
echo $1 | sudo -S -b rmdir $3 $4
fi
if [ $2 -eq 9 ]; then
echo $1 | sudo -S -b fdisk $3 
fi
if [ $2 -eq 10 ]; then
echo $1 | sudo -S -b $3 $4 $5 $6 $7 
fi
if [ $2 -eq 11 ]; then
echo $1 | sudo -S -b  cp $3 $4
fi
if [ $2 -eq 12 ]; then
echo $1 | sudo -S -b dd $3 $4 $5 $6 $7 $8
fi
if [ $2 -eq 13 ]; then
echo $1 | sudo -S -b $3 $4 $5 $6
fi
if [ $2 -eq 14 ]; then
echo $1 | sudo -S -b gunzip $3 $4 $5 $6 $7
fi
if [ $2 -eq 15 ]; then
cd /
cd $5
echo $1 | sudo -S -b rm  $3 $4 $5 $6 $7
fi
if [ $2 -eq 16 ]; then
echo $1 | sudo -S -b chmod $3 $4 $5 $6 $7
fi
if [ $2 -eq 17 ]; then
echo $1 | sudo -S -b fusermount $3 $4 $5 
fi
if [ $2 -eq 18 ]; then
echo $1 | sudo -S -b nmap $3 $4 $5 $6 $7
fi
if [ $2 -eq 19 ]; then
echo $1 | sudo -S -b mount $3 $4 $5 $6 $7 $8 $9 
fi
if [ $2 -eq 20 ]; then
cd /
cd $3
echo $1 | sudo -S -b  cp $4 $5
fi
if [ $2 -eq 21 ]; then
echo $1 | sudo -S -b rm $4 $5 $6 $7
fi
