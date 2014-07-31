<?php
/*
* Documentation System for Fuzuli Programming Language
* Copyright (C) 2014 A.Gokhan Satman <abgsatman@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


   set_time_limit(0);
   ini_set ( 'display_errors', FALSE );
   require "parser.php";
   
   $parser = new PARSER();
   $array = $parser->getFiles();
   
   if( $_REQUEST["process"] == "clearAll" ) {
         
      $parser->clearAll ();
         
   }
   else {
         
      foreach($array as $arr) {
         
         system( touch ( trim( $arr ) ) );
         system( chmod ( trim( $arr ), 0777 ) );
         
         $parser->getContent( trim ( $arr ) );
      
      }
      
      //$parser->getContent( "random.nfl" ); //test
   }
   
?>

