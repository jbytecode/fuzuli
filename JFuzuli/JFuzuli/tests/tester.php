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

$fuzuli_bin="java -jar ../dist/JFuzuli.jar ";

$fuzuli_temp=tempnam ("/temp", "fuzuli_result");


$total_passed=0;
$total_error=0;
$files_count=0;
$total_unknown=0;

print ("--------------------------------------------\n");
print ("|            Fuzuli Test Result            |\n");
print ("--------------------------------------------\n");

#list for .fzl files
$path=(".");
$folder=opendir ($path);
   if($folder) {
      while ($file=readdir ($folder))   {
         if (!is_dir ($file)) {
            if (substr ($file, -3)=="fzl") {
               $files[]=$file;
               $files_count++;
            }
         }
      }
   }
sort ($files);

   foreach ($files as $eachfile) {
      if (substr( $eachfile, -3)=="fzl") {
         $newfile=$eachfile;
         if ($newfile!=NULL) {
            $last_process=system(''.$fuzuli_bin.' '.$newfile.' > '.$fuzuli_temp.'', $process_result);
            print (trim ($newfile).":\n");
               if (!$process_result) {
                  print ("");
               } else {
                  print ("Error Code: ".$process_result."\n");            
                  $total_unknown=$total_unknown+1;
                  $error_files[]=$newfile;
               }
            $file_content=file_get_contents ($fuzuli_temp);
            print ($file_content);
            print ("--\n");
            $tests=explode ("\n", $file_content);
            foreach ($tests as $test) {
               if ($test=="PASSED!") {
                  $total_passed=$total_passed+1;   
               }
               elseif ($test=="ERROR") {
                  $total_error=$total_error+1;   
               }
            }
         }
      }
   }

print ("--------------------------------------------\n");
print ("|                Test Reports              |\n");
print ("--------------------------------------------\n");
print ("|  ".$files_count." files have been tested\n");
print ("|  ".$total_passed." statements have been passed.\n");
print ("|  ".$total_error." statements have been failed.\n");
print ("|  ".$total_unknown." files have been undefined:.\n");
   if ($total_unknown>"0") {
      foreach ($error_files as $error_file) {
         print ("|    -".$error_file." file\n");   
      }
   }
print ("--------------------------------------------\n");
?>

