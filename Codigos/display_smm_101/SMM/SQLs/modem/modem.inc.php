<?php
	
	function insertGpdData ( $vauiDaviceId, $vauiMessageId, $vauiSignalQuality, $vauiPowerControl, $vasGpsDateTime, $vasGpsLatitude, $vasGpsLatitudeHemisphere, $vasGpsLongitude, $vasGpsLongitudeHemisphere, $vasGpsDadaValid )
	{
		return "INSERT INTO `DisplayLogRx` (`DisplayLogRx_Id`, `DisplayLogRx_Equipamento_Id`, `DisplayLogRx_Mensagem_Id`, `DisplayLogRx_SinalOperadora`, `DisplayLogRx_AlimentacaoDisplay`, `DisplayLogRx_GpsDataHora`, `DisplayLogRx_GpsLatitude`, `DisplayLogRx_GpsLatitudeHemisferio`, `DisplayLogRx_GpsLongitude`, `DisplayLogRx_GpsLongitudeHemisferio`, `DisplayLogRx_GpsValido`) VALUES ( NULL, {$vauiDaviceId}, {$vauiMessageId}, {$vauiSignalQuality}, {$vauiPowerControl}, '{$vasGpsDateTime}', '{$vasGpsLatitude}', '{$vasGpsLatitudeHemisphere}', '{$vasGpsLongitude}', '{$vasGpsLongitudeHemisphere}', '{$vasGpsDadaValid}')";
	}
	
	/*function getDeviceConfig ( $vanDeviceId )
	{
		return "SELECT EquipamentoParametro.EquipamentoParametro_RotuloEquipamento, EquipamentoParametro.EquipamentoParametro_Valor FROM EquipamentoParametro LEFT JOIN ( Equipamento, EquipamentoHasEquipamentoParametro, EquipamentoTipoHasEquipamentoParametro ) ON ( ( EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_Equipamento_Id = {$vanDeviceId} AND EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_EquipamentoParametro_Id = EquipamentoParametro.EquipamentoParametro_Id ) OR ( EquipamentoTipoHasEquipamentoParametro.EquipamentoTipoHasEquipamentoParametro_EquipamentoTipo_Id = Equipamento.Equipamento_EquipamentoTipo_Id AND Equipamento.Equipamento_Id = {$vanDeviceId} AND EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_EquipamentoParametro_Id = EquipamentoParametro.EquipamentoParametro_Id ) )";
	}*/
	
	function selectOnConnectMesage ( $vanDeviceId )
	{
		return "SELECT 
						Mensagem.Mensagem_Id, 
						Mensagem.Mensagem_Texto 
						
				FROM 
						Mensagem 
						
				WHERE 
							Mensagem_Equipamento_Id = {$vanDeviceId} 
						AND Mensagem_MensagemTipo_Id = (
															SELECT 
																	MensagemTipo_Id 
																	
															FROM 
																	MensagemTipo 
																	
															WHERE 
																	MensagemTipo.MensagemTipo_Valor = 'onConnect' 
														)";
	}
	
	function selectNormalMessage ( $vanDeviceId )
	{
		return "SELECT 
						Mensagem.*
						
				FROM 
						Mensagem 
						
				WHERE 
							Mensagem.Mensagem_Equipamento_Id = {$vanDeviceId} 
						AND Mensagem.Mensagem_MensagemTipo_Id = (
																	SELECT 
																			MensagemTipo.MensagemTipo_Id 
																
																	FROM 
																			MensagemTipo 
																
																	WHERE 
																			MensagemTipo.MensagemTipo_Valor = 'dateNormal'
														) 
						AND Mensagem.Mensagem_DataInicial <= NOW() 
						AND Mensagem.Mensagem_DataFinal > NOW() 
						
				ORDER BY 
						Mensagem.Mensagem_Id DESC LIMIT 1";
	}
	
	function selectOnDateErroMessage ( $vanDeviceId )
	{
		return "SELECT 
						Mensagem.Mensagem_Id, 
						Mensagem.Mensagem_Texto 
						
				FROM 
						Mensagem 
						
				WHERE 
							Mensagem_Equipamento_Id = {$vanDeviceId} 
						AND Mensagem_MensagemTipo_Id = (
														SELECT 
																MensagemTipo_Id 
																
														FROM 
																MensagemTipo 
																
														WHERE 
																MensagemTipo.MensagemTipo_Valor = 'dateError'
														)";
	}
	
	function selectDeviceConfigByDeviceIdAndDeviceType ( $vanDeviceId )
	{
		return "SELECT 
						EquipamentoParametro.EquipamentoParametro_RotuloEquipamento, 
						EquipamentoParametro.EquipamentoParametro_Valor 
						
				FROM 
						EquipamentoParametro 
						
				LEFT JOIN ( 
						Equipamento, 
						EquipamentoHasEquipamentoParametro, 
						EquipamentoTipoHasEquipamentoParametro 
						) 
						
				ON ( 
						( 
								EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_Equipamento_Id = {$vanDeviceId} 
							AND EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_EquipamentoParametro_Id = EquipamentoParametro.EquipamentoParametro_Id 
						) OR ( 
								EquipamentoTipoHasEquipamentoParametro.EquipamentoTipoHasEquipamentoParametro_EquipamentoTipo_Id = Equipamento.Equipamento_EquipamentoTipo_Id 
							AND Equipamento.Equipamento_Id = {$vanDeviceId} 
							AND EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_EquipamentoParametro_Id = EquipamentoParametro.EquipamentoParametro_Id 
							) 
					)";
	}
	
	function selectLogTxMessageByDeviceId ( $vauiDeviceId, $vauiLateSeconds = 120, $vauiCriticalSeconds = 600 )
	{
		return "SELECT 
						DeviceLogRx.*,
						IF( DATE_SUB( DeviceLogRx.DeviceLogRx_DateTimeServer, INTERVAL {$vauiLateSeconds} SECOND ) < NOW(), 1, 0 ) AS DeviceLogRx_AlertaAtrasado,
						IF( DATE_SUB( DeviceLogRx.DeviceLogRx_DateTimeServer, INTERVAL {$vauiCriticalSeconds} SECOND ) < NOW(), 1, 0 ) AS DeviceLogRx_AlertaCritico
						
				FROM 
						DeviceLogRx 
						
				WHERE 
						DeviceLogRx.DeviceLogRx_Equipamento_Id = {$vauiDeviceId}
						
				ORDER BY
						DeviceLogRx_Id DESC
						
				LIMIT 1";
	}