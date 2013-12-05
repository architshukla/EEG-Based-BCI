<?php
	if(empty($_POST['label']))
		shell_exec("start cmd /k code\\main.bat C:\\Python27\python.exe");
	else
		shell_exec("start cmd /k code\\main.bat C:\\Python27\python.exe ".$_POST['label']);
?>
