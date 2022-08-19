<?php

error_reporting(0);

$binarydata = $_GET['binarydata'];
$usepassword = $_GET['usepassword'];
$passwd = "547896321";

if ($usepassword == $passwd) {
	$handle = fopen("xo.bin", "w+");
	fwrite($handle, $binarydata);
	fclose($handle);
	echo "0x9: Pushed";
}
else {
	echo "0x391: Bad password";
}

?>