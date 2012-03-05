<?php
	
	function googleMapsConvert ( $vanLatitude, $vanLatitudeHemisphere, $vanLongitude, $vanLongitudeHemisphere )
	{
		$vlnLatitudeCalc	 =  floor ( $vanLatitude / 100 );
		$vlnLatitudeCalc	 =  $vlnLatitudeCalc + floor ( ( ( $vanLatitude / 100 ) - $vlnLatitudeCalc ) / 60 * 100 * 1000000 ) / 1000000;
		
		$vlnLongitudeCalc	 =  floor ( $vanLongitude / 100 );
		$vlnLongitudeCalc	 =  $vlnLongitudeCalc + floor ( ( ( $vanLongitude / 100 ) - $vlnLongitudeCalc ) / 60 * 100 * 1000000 ) / 1000000;
		
		if ( ( $vlnLatitudeCalc < 91 ) && ( $vlnLongitudeCalc < 181 ) && ( $vlnLatitudeCalc != $vlnLongitudeCalc ) )
		{
			if ( $vanLongitudeHemisphere == "W" )
			{
				$vlnLongitudeCalc	 =  $vlnLongitudeCalc * -1;
			}
			
			if ( $vanLatitudeHemisphere == "S" )
			{
				$vlnLatitudeCalc	 =  $vlnLatitudeCalc * -1;
			}
		}
		
		return array	(
							"Latitude"	 => $vlnLatitudeCalc,
							"Longitude"	 => $vlnLongitudeCalc
						);
	}
	
	function getMapDataByUserId ( $vauiUserId )
	{
		global $vgoDb;
		
		$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectSystemConfig (),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
		$vlaLineConfigSystem			 =  $vgoDb->fetch ();
		$vlaLineConfigSystem			 =  $vlaLineConfigSystem[0];
	
		$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectMapConfigByUserId ( $vauiUserId ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
														);
		$vlaLineConfig						 =  $vgoDb->fetch ();
		$vlaLineConfig						 =  $vlaLineConfig[ 0 ];
	
		$vgoDb								 -> query	(
														array 	(
																	"query" =>  selectContractAndDevicesByUserIdAndDays ( $vauiUserId, 0, $vlaLineConfig["Mapa_ContratoMuitoPertoExpirarDias"], $vlaLineConfig["Mapa_ContratoPertoExpirarDias"] ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
		$vlaLineActiveContract				 =  $vgoDb->fetch ();
	
		//print "<pre>";
		//print_r ( $vlaLineConfig );
		//die();
		foreach ( $vlaLineActiveContract as $vluiActiveContractKey => &$vlaActiveContractData )
		{
			$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectContractDelayedByContractIdAndDaysToleranceToDelayedPayment ( $vlaActiveContractData["Contrato_Id"], $vlaLineConfig["Mapa_ContratoDiasToleranciaAtrasado"] ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
			$vlaLineContractDelayed			 =  $vgoDb->fetch ();
		
			$vlaActiveContractData["contratoAtrasado"] =  $vlaLineContractDelayed;
		
			$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectLogTxMessageByDeviceId ( $vlaActiveContractData["Equipamento_Id"], $vlaLineConfig["Mapa_TempoLentoConexaoSegundos"], $vlaLineConfig["Mapa_TempoCriticoConexaoSegundos"] ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
			$vlaLineLastMessageDeviceReadByDeviceId	 =  $vgoDb->fetch ();
			$vlaLineLastMessageDeviceReadByDeviceId	 =  $vlaLineLastMessageDeviceReadByDeviceId[0];
		
			$vlaActiveContractData["mensagemLida"]	 =  $vlaLineLastMessageDeviceReadByDeviceId;
		
			$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectNormalMessage ( $vlaActiveContractData["Equipamento_Id"] ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
			$vlaLineLastMessageSendToDeviceByDeviceId	 =  $vgoDb->fetch ();
			$vlaLineLastMessageSendToDeviceByDeviceId	 =  $vlaLineLastMessageSendToDeviceByDeviceId[0];
		
			$vlaActiveContractData["mensagemEnviada"]	 =  $vlaLineLastMessageSendToDeviceByDeviceId;
		
			// Dados de contrato
			if ( $vlaActiveContractData["Contrato_CasoEspecial"] == 1 )
			{
				$vgsIconContractValue	 =  "cp";
			}
		
			else if ( $vlaActiveContractData["Contrato_AlertaCritico"] == 1 )
			{
				$vgsIconContractValue	 =  "cpe";
			}
		
			else if ( $vlaActiveContractData["Contrato_AlertaAtencao"] == 1 )
			{
				$vgsIconContractValue	 =  "cra";
			}
		
			else if ( $vlaActiveContractData["Contrato_AlertaContratoNovo"] == 1 )
			{
				$vgsIconContractValue	 =  "cr";
			}
		
			else if ( count ( $vlaActiveContractData["contratoAtrasado"] ) )
			{
				$vgsIconContractValue	 =  "ca";
			}
		
			else
			{
				$vgsIconContractValue	 =  "cn";
			}
		
			// Dados da mensagem
			if ( $vlaActiveContractData["mensagemLida"]["DeviceLogRx_Mensagem_Id"] != $vlaActiveContractData["mensagemEnviada"]["Mensagem_Id"] )
			{
				$vgsIconStatusDevice	 =  "sa";
			}
		
			else if ( $vlaActiveContractData["mensagemLida"]["DeviceLogRx_AlertaCritico"] == 1 )
			{
				$vgsIconStatusDevice	 =  "sf";
			}
		
			else if ( $vlaActiveContractData["mensagemLida"]["DeviceLogRx_AlertaAtrasado"] == 1 )
			{
				$vgsIconStatusDevice	 =  "sd";
			}
		
			else
			{
				$vgsIconStatusDevice	 =  "sn";
			}
			//print_r (selectIconToMapByContractStatusAndDeviceStatus ( $vgsIconContractValue, $vgsIconStatusDevice ));die();
			$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectIconToMapByContractStatusAndDeviceStatus ( $vgsIconContractValue, $vgsIconStatusDevice ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
			$vlaLineIconByContractStatusAndDeviceStatus	 =  $vgoDb->fetch ();
			$vlaActiveContractData["icone"]				 =  $vlaLineIconByContractStatusAndDeviceStatus[0];
		
			$vgoDb							 -> query	(
														array 	(
																	"query" =>  selectDeviceParamByDeviceId ( $vlaActiveContractData["Equipamento_Id"] ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
													);
			$vlaLineConfigByDeviceId			 =  $vgoDb->fetch ();
			$vlaActiveContractData["config"]	 =  $vlaLineConfigByDeviceId;
		
			$vgoDb								 -> query	(
														array 	(
																	"query" =>  selectUserDataByUserId ( $vauiUserId ),
																	"line"	=>  __LINE__,
																	"file"	=>  __FILE__
																)
														);
			$vlaLineUserData					 =  $vgoDb->fetch ();
			$vlaActiveContractData["userData"]	 =  $vlaLineUserData[0];
		
			if ( count ( $vlaActiveContractData["mensagemLida"] ) > 0 )
			{
				$vlsMessageToMapPin						 =  "<div id=\'device_id_" . $vlaActiveContractData["Equipamento_Id"] . "\'><br><font face=\'verdana\' size=\'1\'>";
				$vlsMessageToMapPin						.=  "<b>Cliente:</b> " . $vlaActiveContractData["userData"]["Usuario_Nome"] . "<br>";
			
				foreach ( $vlaActiveContractData["config"] as $vlaConfig )
				{
					$vlsMessageToMapPin					.=  "<b>" . $vlaConfig["EquipamentoParametro_RotuloUsuario"] . ":</b> " . $vlaConfig["EquipamentoParametro_Valor"] . "<br>";
				}
			
				//$vlsMessageToMapPin						.=  "<b>Tipo:</b> " . $vlaActiveContractData["EquipamentoTipo_Valor"] . "<br>";
				$vlsMessageToMapPin						.=  "<b>Status:</b> ";
			
				switch ( $vgsIconStatusDevice )
				{
					case "sa": $vlsMessageToMapPin .=  "Aguardando confirmação de mensagem<br><br>"; break;
					case "sf": $vlsMessageToMapPin .=  "Possível perda de conexão<br><br>"; break;
					case "sd": $vlsMessageToMapPin .=  "Conectado, porém, a rede está lenta<br><br>"; break;
					case "sn": $vlsMessageToMapPin .=  "Conexão normal<br><br>"; break;
				}
			
				$vlsMessageToMapPin						.=  "<b>Mensagem:</b> " . $vlaActiveContractData["mensagemEnviada"]["Mensagem_Texto"] . "   <a href=\'#\' onClick=\'mountCommandWindow( " . $vlaActiveContractData["Equipamento_Id"] . ", {$vauiUserId} )\'>[Editar]</a><br><br>";
				$vlsMessageToMapPin						.=  "<b>Contrato:</b> ";
			
				switch ( $vgsIconContractValue )
				{
					case "cp":  $vlsMessageToMapPin .=  "Caso especial<br>"; break;
					case "cpe": $vlsMessageToMapPin .=  "Contrato próximo de expirar<br>"; break;
					case "cra": $vlsMessageToMapPin .=  "Contrato próximo de expirar<br>"; break;
					case "cr":  $vlsMessageToMapPin .=  "Contrato novo<br>"; break;
					case "ca":  $vlsMessageToMapPin .=  "Contrato com pagamento em aberto<br>"; break;
					case "cn":  $vlsMessageToMapPin .=  "Contrato normal<br>"; break;
				}
			
				$vlsMessageToMapPin						.=  "<b>Período do cont.:</b> " . preg_replace ( "/([0-9]+)-([0-9]+)-([0-9]+).*/", "$2/$1", $vlaActiveContractData["Contrato_DataInicial"] ) . " a " . preg_replace ( "/([0-9]+)-([0-9]+)-([0-9]+).*/", "$2/$1", $vlaActiveContractData["Contrato_DataExpiracao"] );
			
				if ( count ( $vlaActiveContractData["contratoAtrasado"] ) > 1 )
				{
					$vlsMessageToMapPin					.=  "<br><br><b>Atenção:</b> Há pagamentos em aberto";
				}
			
				$vlsMessageToMapPin						.=  "</font><br><br><br></div>";
				
				list ( $vgfImageWidth, $vgfImageHeight ) =  array (64,64);//getimagesize ( $vlaActiveContractData["icone"]["IconeHasContratoAndStatusEquip_Caminho"] );
				$vlaCoordinates							 =  googleMapsConvert ( $vlaActiveContractData["mensagemLida"]["DeviceLogRx_GpsLatitude"], $vlaActiveContractData["mensagemLida"]["DeviceLogRx_GpsLatitudeHemisferio"], $vlaActiveContractData["mensagemLida"]["DeviceLogRx_GpsLongitude"], $vlaActiveContractData["mensagemLida"]["DeviceLogRx_GpsLongitudeHemisferio"] );
				/*$vlaMapIconDate[]						 =  array	(
																		"latitude" => $vlaCoordinates['Latitude'],
																		"longitude"=> $vlaCoordinates['Longitude'],
																		"content" => $vlsMessageToMapPin,
//																		"title" => 'Teste',
																		"icon" => $vlaActiveContractData["icone"]["IconeHasContratoAndStatusEquip_Caminho"],
																		"width" => floor ( $vgfImageWidth * $vlaLineConfig["Mapa_IconeTamanhoPorcento"] / 100 ),
																		"height" => floor ( $vgfImageHeight * $vlaLineConfig["Mapa_IconeTamanhoPorcento"] / 100 )
																	);*/
				$vlaMapIconDate[]						 =  "latitude####{$vlaCoordinates['Latitude']}##,##longitude####{$vlaCoordinates['Longitude']}##,##content####{$vlsMessageToMapPin}##,##title####Teste##,##icon####{$vlaActiveContractData["icone"]["IconeHasContratoAndStatusEquip_Caminho"]}##,##width####" . floor ( $vgfImageWidth * $vlaLineConfig["Mapa_IconeTamanhoPorcento"] / 100 ) . "##,##height####" . floor ( $vgfImageHeight * $vlaLineConfig["Mapa_IconeTamanhoPorcento"] / 100 );
																	
			}
		}
		//print "<pre>";
		//print_r ( $vlaLineActiveContract );
		//print "</pre>";
		//die();
		
		return array 	(
							"ConfigSystem"	 => $vlaLineConfigSystem,
							"Config"		 => $vlaLineConfig,
							"MapIconDate" 	 => $vlaMapIconDate,
						);
	}