#!/bin/bash
# Hinweis: keine Leerzeile zulässig, auch nicht am Ende!!, gegebenenfalls korrigieren. 
if [ $# -lt 1 ]; then
  echo "Fehler: Kein Passwort übergeben"
  exit
fi
# $1 = Auswahl
# $2 = zu mountende Partition, qt-fsarchiver Starter Verzeichnis /.config if=/dev
# $3 = Mountort of=/dev
# $4 = parameter für rm
ddif="$2"
ddof="$3"
sgdisk="$4"
dateiname="/.config/qt-fsarchiver/den.nfo.cpt"
testfile=$HOME$dateiname
if [ -f "$testfile" ];then 
/usr/bin/ccrypt -d -k ~/.local/share/.en.nfo ~/.config/qt-fsarchiver/den.nfo.cpt
URLFILE=~/.config/qt-fsarchiver/den.nfo
for i in `cat $URLFILE`; do
echo > .1 $i
done
if [ -f .1 ];then
rm .1
fi
# den.nfo.cpt wieder herstellen, den.nfo wird somit gelöscht
/usr/bin/ccrypt -e -k ~/.local/share/.en.nfo ~/.config/qt-fsarchiver/den.nfo
fi
if [ $1 -eq 1 ]; then
echo $i | sudo -S -b /usr/sbin/qt-fsarchiver-terminal $2
fi
if [ $1 -eq 2 ]; then
echo $i | sudo -S -b mount $2 $3
fi
if [ $1 -eq 3 ]; then
echo $i | sudo -S -b mkdir $2 $3 $4
fi
if [ $1 -eq 4 ]; then
echo $i | sudo -S -b umount $2 $3 $4 $5
fi
if [ $1 -eq 5 ]; then
cd /
cd $2
echo $i | sudo -S -b rm $3 $4 $5 $6
fi
if [ $1 -eq 6 ]; then
echo $i | sudo -S -b dd $2 $3 bs=512 count=1
fi
if [ $1 -eq 7 ]; then
echo $i | sudo -S -b mkfs.btrfs $2 $3 
fi
if [ $1 -eq 8 ]; then
echo $i | sudo -S -b rmdir $2 $3
fi
if [ $1 -eq 9 ]; then
echo $i | sudo -S -b fdisk $2 
fi
if [ $1 -eq 10 ]; then
echo $i | sudo -S -b $2 $3 $4 $5 $6 
fi
if [ $1 -eq 11 ]; then
echo $i | sudo -S -b  cp $2 $3
fi
if [ $1 -eq 12 ]; then
echo $i | sudo -S -b dd "$ddif" "$ddof" $4 $5 $6 $7
fi
if [ $1 -eq 13 ]; then
echo $i | sudo -S -b $2 $3 $4 $5
fi
if [ $1 -eq 14 ]; then
echo $i | sudo -S -b gunzip "$ddif" "$ddof" $4 $5 $6
fi
if [ $1 -eq 15 ]; then
cd /
cd $4
echo $i | sudo -S -b rm  $2 $3 $4 $5 $6
fi
if [ $1 -eq 16 ]; then
echo $i | sudo -S -b chmod $2 $3 $4 $5 $6
fi
if [ $1 -eq 17 ]; then
echo $i | sudo -S -b fusermount $2 $3 $4
fi
if [ $1 -eq 18 ]; then
echo $i | sudo -S -b nmap $2 $3 $4 $5 $6
fi
if [ $1 -eq 19 ]; then
echo $i | sudo -S -b mount $2 $3 $4 $5 "$6" $7 $8 
fi
if [ $1 -eq 20 ]; then
cd /
cd $2
echo $i | sudo -S -b  cp $3 $4
fi
if [ $1 -eq 21 ]; then
echo $i | sudo -S -b dd $2 $3 $4 $5 $6 $7
fi
if [ $1 -eq 22 ]; then
echo $i | sudo -S -b $3 "$ddof" "$sgdisk" $5
fi
if [ -f "$2" ];then 
  if [ $1 -eq 23 ]; then
  echo $i | sudo -S -b rm $2 
  fi
fi
if [ $1 -eq 24 ]; then
echo $i | sudo -S -b $2 "$3" $4 $5 $6
fi
if [ $1 -eq 25 ]; then
echo $i | sudo -S -b $2 $3 "$4" $5 $6
fi

