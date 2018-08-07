#!/bin/bash

#
# winetricksextract.sh
# of the 'WBottler' target in the 'WineBottler' project
#
# Copyright 2009-2017 Mike Kronenberg
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



##########     Merge our cutom verbs, then create plist  out of it     #########
################################################################################
w_metadata() {
    echo "\t<dict>\n\t\t<key>verb</key>\n\t\t<string>$1</string>\n\t\t<key>category</key>\n\t\t<string>$2</string>\n\t\t<key>status</key>\n\t\t<string>0</string>" >>"$WINETRICKS_TMP"
    shift
    shift
    for arg
    do
        echo "\t\t<key>${arg%%=*}</key>\n\t\t<string>${arg#*=}</string>" >>"$WINETRICKS_TMP"
    done
    echo "\t</dict>" >>"$WINETRICKS_TMP"
}
export -f w_metadata

export WINETRICKS_PLIST="$HOME/Library/Application Support/Wine/winetricks.plist"
export WINETRICKS_TMP="/tmp/winetricks.plist"

# add our custom verbs
cat "$HOME/Library/Application Support/Wine/winetricks" "$HOME/Library/Application Support/Wine/customverbs" > /tmp/winetricks_custom

# remove everything so that we can get the verbs
tr '\n' '^' < /tmp/winetricks_custom | sed -e "s/\$USERNAME/$USER/g" -e 's/\$W_PROGRAMS_X86_WIN/\%ProgramFiles\%/g' -e 's/\$W_SYSTEM32_DLLS_WIN/C:\/windows\/system32/g' -e 's/^.*# Runtimes//' -e 's/#---- Main Program ----.*WineBottler Custom Verbs//' | tr '^' '\n' > "/tmp/winetricks_verbs.sh"

#start plist
echo '<?xml version="1.0" encoding="UTF-8"?>\n<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">\n<plist version="1.0">\n<array>' >"$WINETRICKS_TMP"

# add verbs
source "/tmp/winetricks_verbs.sh"

#end plist
echo "</array>\n</plist>" >>"$WINETRICKS_TMP"

#fix special chars in plist
sed -e 's/\&/\&amp;/g' "$WINETRICKS_TMP" >"$WINETRICKS_TMP"2

#check if the plist validates
xmllint --noout "$WINETRICKS_TMP"2
if [ "$?" -ne "0" ]; then
    echo "\n***** Error:"
    exit
fi

#move the plist in the library
mv "$WINETRICKS_TMP"2 "$WINETRICKS_PLIST"

#cleanup
rm "$WINETRICKS_TMP"
rm /tmp/winetricks_custom
rm /tmp/winetricks_verbs.sh


exit 0
