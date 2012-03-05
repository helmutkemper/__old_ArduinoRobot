<?php
	
	function selectSystemConfig ()
	{
		return "SELECT * FROM ConfiguracaoSistemas WHERE ConfiguracaoSistemas.ConfiguracaoSistemas_ConfigInicial >= NOW() AND ConfiguracaoSistemas.ConfiguracaoSistemas_ConfigFinal <= NOW()";
	}