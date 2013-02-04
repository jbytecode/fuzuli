<?php
$start = microtime(true);
$n = 10;
$arr = range(1,$n);
$i = 0;
foreach ($arr as $a){
	foreach ($arr as $b){
		foreach ($arr as $c){
			foreach ($arr as $d){
				foreach ($arr as $e){
					$i++;
				}
			}
		}
	}
}
$stop = microtime(true);
print (($stop - $start) * 1000);
?>
