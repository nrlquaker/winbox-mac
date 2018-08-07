#!/usr/bin/env bash

#
# icon.sh
# of the 'WBottler' target in the 'WineBottler' project
#
# Copyright 2009 Mike Kronenberg
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
#



##########        Grab Icon out of exe and convert it to png           #########
################################################################################
PATH_TO_EXECUTABLE=$(echo "$PATH_TO_EXECUTABLE" | sed s'/\\/\//g')
MAINICON=$(echo $(./wrestool -l --type=group_icon "$PATH_TO_EXECUTABLE") | awk '{print $2}' | sed 's/--name=//')
MAINICON=$(echo $MAINICON | sed s/\'//g)
TMPICON=$(echo "$(date +%s)$RANDOM")


./wrestool -x --type=group_icon --output=/tmp/$TMPICON.ico --name=$MAINICON "$PATH_TO_EXECUTABLE"

./icotool -x -i "$(./icotool --list /tmp/$TMPICON.ico | awk '{
    ci=int(substr($2,index($2,"=") + 1)); cw=int(substr($3,index($3,"=") + 1)); cb=int(substr($5,index($5,"=") + 1));
    if ((cw > w) || (cw == w && cb > b)) {b = cb;w = cw;i = ci;}} END {print i;}')" /tmp/$TMPICON.ico -o /tmp/$TMPICON.png

sips -s format icns --resampleHeightWidth 256 256 /tmp/$TMPICON.png --out "$PATH_TO_ICON"

if [ -d "/Users/mike/Sites/winebottler/icons" ]; then
    cp /tmp/$TMPICON.png "/Users/mike/Sites/winebottler/icons/$TMPICON.png"
fi

rm /tmp/$TMPICON.ico &>/dev/null
rm /tmp/$TMPICON.png &>/dev/null