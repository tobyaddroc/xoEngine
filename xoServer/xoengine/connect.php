<?php

$passwd = "547896321";

error_reporting(0);

if (isset($_GET['logintest'])) {
	echo "0x1: Welcome";
}
else {
	if ($_GET['usepassword'] == $passwd) {
		$handle = fopen("xo.bin", "w+");
		fwrite($handle, "00000000000000001");
		fclose($handle);
		echo "0x2: Connection allowed";
	}
	else {
		echo "0x391: Bad password";
	}
}

?>