<?php
#
# fuzuli test framework
# Copyright (C) 2012 A.Gokhan SATMAN <abgsatman@gmail.com>
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


$php_bin="/usr/bin/php";
$fuzuli_bin="/usr/lib/fuzuli/fuzuli";

$php_temp=tempnam("/temp", "php_output");
$fuzuli_temp=tempnam("/temp", "fuzuli_output");

$tests=file_get_contents("items.inc");
$files=explode("\n",$tests);

echo "--------------------------------------------------------------\n";
printf ("|%' -20.20s%' 20.20s%' 20.20s\n", "Files", "PHP Times", "FUZULI Times");
echo "--------------------------------------------------------------\n";

	foreach($files as $items) {
		!$items ? exit:
		system("".$php_bin." ".$items.".php > ".$php_temp."");
       		$php_content=round(file_get_contents($php_temp));

       		system("".$fuzuli_bin." ".$items.".fzl > $fuzuli_temp");
        	$fuzuli_content=round(file_get_contents($fuzuli_temp));

        	printf ("%' -20.20s%' 20.20s%' 20.20s\n", $items, $php_content, $fuzuli_content)."\n";		
	}
?>

