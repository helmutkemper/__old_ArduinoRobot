<?php
	
	include "mapaFunctions.inc.php";
	include "../commun/connection.php";
	include "../commun/constants.php";
	include "../commun/smarty.php";
	include "../SQLs/usuario/usuario.inc.php";
	include "../SQLs/mapa/mapa.inc.php";
	include "../SQLs/modem/modem.inc.php";
	include "../SQLs/configuracoes/configuracoes.inc.php";
	include "../SQLs/contrato/contrato.inc.php";
	
	$vgaSystemData	 =  getMapDataByUserId ( $_GET["userId"] );
	
	/*
	foreach ( $vgaSystemData["MapIconDate"] as $vgnKey => &$vgaData )
	{
		$vgaData =  serialize ( $vgaData );
	}
	*/
	
	$vgaSystemData["MapIconDate"] =  implode ( "***,***", $vgaSystemData["MapIconDate"] );
	
	$vgoSmarty		 -> assign ( "mapTitle", $vgaSystemData["ConfigSystem"]["ConfiguracaoSistemas_TituloMapa"] );
	$vgoSmarty		 -> assign ( "mapZoom", $vgaSystemData["Config"]["Mapa_Zoom"] );
	$vgoSmarty		 -> assign ( "mapType", $vgaSystemData["Config"]["Mapa_Tipo"] );
	$vgoSmarty		 -> assign ( "mapAutoZoom", $vgaSystemData["Config"]["Mapa_AutoZoom"] );
	$vgoSmarty		 -> assign ( "mapSetAutoCenter", $vgaSystemData["Config"]["Mapa_CentralizarSempre"] );
	$vgoSmarty		 -> assign ( "mapInterval", $vgaSystemData["Config"]["Mapa_TempoAtualizacaoSegundos"] );
	$vgoSmarty		 -> assign ( "mapMarkersData", $vgaSystemData["MapIconDate"] ); //"[{latitude: -8.158584, longitude: -34.913936, content: 'Olá mundo', title: 'Teste', icon: 'http://www.kemper.com.br/modem/icons/status_ok.png'}, {latitude: -8.158084, longitude: -34.913036, content: 'Olá mundo', title: 'Teste', icon: 'http://www.kemper.com.br/modem/icons/status_ok.png'}, {latitude: -8.108584, longitude: -34.910936, content: 'Olá mundo', title: 'Teste', icon: 'http://www.kemper.com.br/modem/icons/status_ok.png'}]"
	$vgoSmarty		 -> assign ( "mapIdUser", 1 );
	$vgoSmarty		 -> assign ( "mapRelativeDataAddress", "latlong_carro.php" );
	
	$vgoSmarty		 -> display("Templates/mapa.tpl");
		