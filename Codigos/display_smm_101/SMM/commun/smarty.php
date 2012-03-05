<?php
	
	include "../classes/smart/libs/Smarty.class.php";
	
	$vgoSmarty		 =  new Smarty;
	
	$vgoSmarty		 -> caching			 =  false;
	$vgoSmarty		 -> left_delimiter	 =  "<!--{";
	$vgoSmarty		 -> right_delimiter	 =  "}-->";
	$vgoSmarty		 -> compile_dir		 =  "../classes/smart/libs/templates_c/";
	$vgoSmarty		 -> config_dir		 =  "../classes/smart/libs/configs/";
	$vgoSmarty		 -> cache_dir		 =  "../classes/smart/libs/cache/";