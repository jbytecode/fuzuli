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

 class PARSER {
    
    public $pathLocal   = ".";
    public $path        = "https://fuzuli.googlecode.com/hg/JFuzuli/JFuzuli/src/nfl/";
   public $fileList    = "nfl.list";
    public $file        = "string.nfl"; //for test
    public $extension   = "nfl";
    public $extension_w = "html";
    public $strip_tag   = "/*";
    public $strip_func  = "(function";
    public $strip_param = "(params";
    public $systemFiles = array();
    public $resultChars = array("(", ")", "/*", "*/", "function", "params");
    public $lineCount   = 5;
   public $loading     = "Please wait while loading files.....";
   public $fuzuli      = "Fuzuli Developer Team";
   public $noDesc      = "Description not found!";
   public $package     = "Package Functions";
   public $jquery      = "http://code.jquery.com/jquery-1.11.0.min.js";
   public $style       = "style.css";
    
    public function __construct () {
      
      return $this->fuzuli;   
         
    }
    
    public function getFilesLocal () {
       
       $folder = opendir ( $this->pathLocal );
       if ( $folder ) {
          while ( $file = readdir ( $folder ) )   {
             if (!is_dir ( $file )) {
                if ( substr ( $file, -3 )=="".$this->extension."" ) {
                   $this->systemFiles[] = $file;
                }
             }
          }
       }
       
       return $this->systemFiles;
       
    }
    
    public function getFiles () {
       
       $nflFileList = file_get_contents( $this->path.$this->fileList );
       return $this->setExplode( $nflFileList, "\n" );
       
    }
    
   public function setContent ( $fileName ) {
   
      $content = file_get_contents ( $this->path.$fileName );
      $output = fopen( $fileName, 'w' );
       fwrite ( $output , "".$content."" );
       fclose ( $output );
      
   }
    
    public function getLines ( $fileName ) {
      
       $this->setContent( $fileName );
       $file = @fopen ( $fileName, 'r' );
       while ( !feof( $file ) ){
          $content[] = fgets ( $file );
       }
       fclose($file);
       
       return $content;
       
    }
    
    public function controlComment ( $fileName, $line ) {
       
       $result = "";
       
       $content = $this->getLines( $fileName );
       for ( $t = ( $line - $this->lineCount ); $t < $line; $t++ ) {
          
          if( $this->getChar( $content[$t], 0, strlen ( $this->strip_tag ) ) == $this->strip_tag ) {
             
             for( $l = $t; $l < $line; $l++ ) {
                
                $result .= $content[$l];
                
             }
             
          }
          
       }
       return $result;
       
    }
   
   public function clearAll () {
   
      $fileList = $this->getFiles ();
      foreach ( $fileList as $file ) {
         
         $nfl  = trim ( $file );
         $html = str_replace ( ".".$this->extension."", ".".$this->extension_w."", trim ( $file ) );
         
         if (unlink ( $nfl ) && unlink ( $html ) ) { 
         
            echo "<b>".$file."</b> and <b>".$html."</b> files have been deleted now<br>";
            
         }
         
      }
      
   }
    
    public function setExplode ( $str, $chr ) {
       
       return explode ( "".$chr."", $str );

    }
    
    public function getChar ( $str, $min, $max ) {
       
      return substr ( $str, $min, $max );
       
    }
    public function getContent ( $myfile ) {
       
       $output = "";
       
       $content = $this->getLines ( $myfile );
       
       system ( touch ( str_replace( ".".$this->extension."", ".".$this->extension_w."", $myfile ) ) );
       system ( chmod ( str_replace( ".".$this->extension."", ".".$this->extension_w."", $myfile ), 0777 ) );
       echo $myfile." file has just been created by the system. Click <a href='".str_replace( ".".$this->extension."", ".".$this->extension_w."", $myfile )."' target='_blank'>here</a><br>";

       $output .= "<html>";
      $output .= "<head>";
       $output .= "<title>".ucwords ( $myfile )." ".$this->package."</title>";
      $output .= '<script src="'.$this->jquery.'"></script>';
      $output .= '<script type="text/javascript">';
      $output .= '$(document).ready(function() {';
      $output .= '$("table tr:even").css("background", "#ffffff");';
      $output .= '$("table tr:odd").css("background", "#f0f0f0");';
      $output .= '});';
      $output .= '</script>';
      $output .= '<link rel="stylesheet" href="'.$this->style.'" type="text/css" />';
       $output .= "</head>";
       $output .= "<body>";
      $output .= '<h1>'.ucwords ( $myfile ).' '.$this->package.'</h1>';
      $output .= '<div class="left">';
      $output .= '<ul>';
      $fileNames = $this->getFiles ();
      foreach ( $fileNames as $eachNames ) {
         if ( strlen ( $eachNames ) > 0 ) {
            $output .= '<li><a href="'.str_replace ( ".".$this->extension."", ".".$this->extension_w."", $eachNames ).'">'.ucwords ( $eachNames ).' '.$this->package.'</a></li>';
         }
      }
      $output .= '</ul>';
      $output .= '</div>';
       
       for ($i = 0; $i<=count($content); $i++) {
          
          if($this->getChar( $content[$i], 0, strlen ( $this->strip_func ) ) == "".$this->strip_func."" ) {
             
             $f = $this->setExplode( $content[$i], $this->strip_param );
             $functionName = trim( str_replace( $this->resultChars, "", $f[0] ) );
             $paramName    = "params ".trim( str_replace( $this->resultChars, "", $f[1] ) );
             
             if( strlen( $content[$i-1] ) >= 3 ) {
                
                $description  = trim( str_replace( $this->resultChars, "", $this->controlComment ( $myfile, $i ) ) );
                
             }
             else {
                
                $description  = $this->noDesc;
                
             }
            
            $output .= '<div class="right">';
            $output .= '<table width="100%" border="0" cellpadding="0" cellspacing="0">';
            $output .= '<tr>';
            $output .= '<td width="15%"><span>Function</span></td>';
            $output .= '<td width="85%">'.$functionName.'</td>';
            $output .= '</tr>';
            $output .= '<tr>';
            $output .= '<td width="15%"><span>Description</span></td>';
            $output .= '<td width="85%">'.$description.'</td>';
            $output .= '</tr>';
            $output .= '<tr>';
            $output .= '<td width="15%"><span>Params</span></td>';
            $output .= '<td width="85%">'.$paramName.'</td>';
            $output .= '</tr>';
            $output .= '</table>';
            $output .= '</div>';
                                       
          }
          
          $htmlFile = fopen( "".str_replace( ".".$this->extension."", ".".$this->extension_w."", $myfile )."", 'w' );
          fwrite ( $htmlFile , "".$output."<div class='info'>".$this->fuzuli."</div></body></html>" );
          fclose ( $htmlFile );
             
       }
       
    }

   
   public function load () {
   
      return $this->loading;
      
   }
    
    public function __destruct () {
       
       return $this->fuzuli;
       
    }
    
 }
?>