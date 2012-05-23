#
# fuzuli test framework 
# Copyright (C) 2012 Ismail Dogan <ismail@ismaildogan.com.tr>
# This file is a part of fuzuli project.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


#!/bin/bash
# changes; 
# changed variable names to easy understanding

echo "--------------------------------------------"
echo "|      testing all FUZULI script files.     |"
echo "--------------------------------------------"
echo ""

fzlList=`ls *.fzl`  # fzlList -> list of fzl files only in the test director
no=0                # no -> number of files
pass=0              # pass -> number of passed files
fail=0              # fail -> number of failed files

for cFzl in $fzlList; do        # cFzl -> current fzl for each loop circle
cResult=`fuzuli $cFzl`          # cResult -> current result for each loop circle
echo "$cFzl:"

i=1
for parca in $cResult; do

if `echo "$parca" | grep "PASSED!" 1>/dev/null 2>&1`
then
	(( pass += 1 ))
	echo "$i: PASS"
else
	(( fail += 1 ))
	echo "$i: FAIL"
fi
(( i += 1 ))
done
#echo "__________________________"
(( no += 1 ))
done

echo ""
echo "--------------------------------------------"
echo "|             Report of test               |"
echo "--------------------------------------------"
echo "|  $no files has been tested."
echo "|  $pass statements has been passed."
echo "|  $fail statements has been failed."
echo "--------------------------------------------"
