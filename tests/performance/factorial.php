<?php
function factorial ($x){
        if ($x <= 1) {
                return 1;
        }else{
                return $x * factorial($x-1);
        }
}

$start = microtime(true);
for ($i=0;$i<1000;$i++){
       	factorial(25);
}
$stop = microtime (true);
print (($stop - $start)*1000);
?>

