<?php
$start = microtime(true);
$n = 10;
$num = 0;

for ($a = 0; $a<$n; $a++){
	for ($b = 0; $b<$n; $b++){
		for ($c = 0; $c<$n; $c++){
			for ($d = 0; $d<$n; $d++){
				for ($e = 0; $e<$n; $e++){
					$num++;
				}
			}
		}
	}
}
$stop = microtime(true);
print(($stop - $start) * 1000);
?>

