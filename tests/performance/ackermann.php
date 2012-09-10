<?php
function ack ($m, $n){
	if ($m ==  0){
		return ($n+1);
	}else if ($n == 0){
		return (ack ($m-1, 1));
	}else{
		return (ack ($m-1, ack($m, $n-1)));
	}
}

$start = microtime(true);
print (ack(3,5)."\n");
$stop = microtime(true);
print (($stop - $start)*1000);
?>
