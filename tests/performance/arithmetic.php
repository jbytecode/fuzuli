<?php
$start = microtime(true);
for ($i = 0; $i < 10000; $i++){
	$a = 1;
	$b = 2;
	$c =  ($a < $b) +  ($a > $b) +  ($a == $b) + ($a !=  $b) +  ($a <=  $b) + ($a >= $b);
	$c = $c << 2;
	$c = $c & 0xaaaaaa;
	$c = $c % 2;
	$c = $c ^ 0xffaa11;
	$c = $c << 2 << 2 << 2;
}
$stop = microtime(true);
print(($stop-$start)*1000);
?>
