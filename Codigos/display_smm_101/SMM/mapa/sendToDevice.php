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
	
	$vgoDb			 -> query	(
									array 	(
												"query" =>  "INSERT INTO Mensagem ( Mensagem_Id, Mensagem_Equipamento_Id, Mensagem_MensagemTipo_Id, _Mensagem_Usuario_Id, Mensagem_Texto, Mensagem_DataInicial, Mensagem_DataFinal ) VALUES ( NULL, {$_REQUEST["device_id"]}, 2, {$_REQUEST["user_id"]}, '{$_REQUEST["realCommand"]}', '2010-01-01', '2030-01-01' )",
												"line"	=>  __LINE__,
												"file"	=>  __FILE__
											)
								);
	
	$vgaSystemData	 =  getMapDataByUserId ( $_REQUEST["device_id"] );	
	$vgaSystemData["MapIconDate"] =  implode ( "***,***", $vgaSystemData["MapIconDate"] );
	
	$res  = fopen ( "teste2.txt", "a" );
			fwrite ( $res, $_REQUEST["realCommand"] . "\r\n");
			fwrite ( $res, $_REQUEST["user_id"] . "\r\n");
			fclose ( $res );
			
			print utf8_encode(str_replace ( "\\", "", $vgaSystemData["MapIconDate"] ) );