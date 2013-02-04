<?php
function fibonacci ($x){
        if ($x <= 2) {
                return 1;
        }else{
                return fibonacci($x-1) + fibonacci($x-2);
        }
}

$start = microtime(true);
for ($i=0;$i<24;$i++){
        fibonacci($i);
}
$stop = microtime (true);
print (($stop - $start)*1000);
?>

