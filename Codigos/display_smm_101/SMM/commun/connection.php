<?php
	
	include "../classes/mysql.php";
	
	$vgaDbSetup	 =  array	(
								"host"		=> "187.45.196.137",
								"username"	=> "rheda22",
								"password"	=> "SMMKemper",
								"dbname"	=> "rheda22"
							);
							
	$vgaDbSetup	 =  array	(
								"host"		=> "127.0.0.1",
								"username"	=> "root",
								"password"	=> "",
								"dbname"	=> "rheda22"
							);
	
	$vgoDb		 =  new mysql ();
					$vgoDb->setConnection ( $vgaDbSetup );