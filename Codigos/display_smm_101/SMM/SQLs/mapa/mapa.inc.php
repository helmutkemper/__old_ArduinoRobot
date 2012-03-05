<?php

	function selectMapConfigByUserId ( $vanUserId )
	{
		return "SELECT
						Mapa.*
						
				FROM 
						Mapa 
						
				WHERE 
						Mapa.Mapa_Usuario_Id = {$vanUserId} 
						
				ORDER BY 
						Mapa.Mapa_Id DESC LIMIT 1";
	}
	
	function selectDeviceTypeByDeviceId ( $vanDeviceId )
	{
		return "SELECT 
						Equipamento.Equipamento_Id,
						EquipamentoTipo.EquipamentoTipo_Valor 
						
				FROM 
						Equipamento,
						EquipamentoTipo
						
				WHERE 
							EquipamentoTipo.EquipamentoTipo_Id = Equipamento.Equipamento_EquipamentoTipo_Id 
						AND Equipamento.Equipamento_Id = {$vanDeviceId}";
	}
	
	function selectDeviceParamByDeviceId ( $vanDeviceId )
	{
		return "SELECT 
						EquipamentoParametro.EquipamentoParametro_Id, 
						EquipamentoParametro.EquipamentoParametro_RotuloUsuario, 
						EquipamentoParametro.EquipamentoParametro_Valor 
						
				FROM 
						EquipamentoParametro 
						
				WHERE 
						EquipamentoParametro.EquipamentoParametro_Id IN
						(
							SELECT 
									EquipamentoHasEquipamentoParametro.EquipamentoHasEquipamentoParametro_EquipamentoParametro_Id 
									
							FROM 
									EquipamentoHasEquipamentoParametro 
							
							WHERE 
									EquipamentoHasEquipamentoParametro_Equipamento_Id = {$vanDeviceId} ) 
									
							UNION
							SELECT 
									EquipamentoParametro.EquipamentoParametro_Id,
									EquipamentoParametro.EquipamentoParametro_RotuloUsuario,
									EquipamentoParametro.EquipamentoParametro_Valor 
									
							FROM 
									Equipamento, 
									EquipamentoParametro, 
									EquipamentoTipoHasEquipamentoParametro 
									
							WHERE 
										Equipamento.Equipamento_EquipamentoTipo_Id = EquipamentoTipoHasEquipamentoParametro.EquipamentoTipoHasEquipamentoParametro_EquipamentoTipo_Id 
									AND EquipamentoParametro.EquipamentoParametro_Id = EquipamentoTipoHasEquipamentoParametro.EquipamentoTipoHasEquipamentoParametro_EquipamentoParametro_Id 
									AND Equipamento.Equipamento_Id = {$vanDeviceId}";
	}
	
	function selectContractDataByUserId ( $vauiUserId, $vabActive = 0 )
	{
		return "SELECT 
						Contrato.Contrato_Id,
						Contrato.Contrato_DataInicial,
						Contrato.Contrato_DataExpiracao,
						Contrato.Contrato_CasoEspecial,
						Contrato.Contrato_Comentario,
						Contrato.Contrato_TotalParcelas,
						Parcelas.Parcelas_AcertadoValor,
						Parcelas.Parcelas_AcertadoData, 
						Parcelas.Parcelas_PagoValor, 
						Parcelas.Parcelas_PagoData 
						
				FROM 
						Contrato, 
						UsuarioHasContrato, 
						ContratoHasParcelas, 
						Parcelas 
						
				WHERE 
							UsuarioHasContrato.UsuarioHasContrato_Usuario_Id = {$vauiUserId} 
						AND UsuarioHasContrato.UsuarioHasContrato_Contrato_Id = Contrato.Contrato_Id 
						AND ContratoHasParcelas.ContratoHasParcelas_Contrato_Id = Contrato.Contrato_Id 
						AND ContratoHasParcelas.ContratoHasParcelas_Parcelas_Id = Parcelas.Parcelas_Id
						AND Contrato.Contrato_Inativado = {$vabActive}";
	}
	
	function selectMessageByUserId ( $vauiUserId )
	{
		return "SELECT 
						Mensagem.Mensagem_Id, 
						Mensagem.Mensagem_Equipamento_Id, 
						Mensagem.Mensagem_MensagemTipo_Id, 
						Mensagem.Mensagem_Texto, 
						Mensagem.Mensagem_DataInicial, 
						Mensagem.Mensagem_DataFinal 
						
				FROM
						Mensagem,
						UsuarioHasContrato,
						Contrato,
						ContratoHasEquipamento
						
				WHERE
							UsuarioHasContrato.UsuarioHasContrato_Usuario_Id = {$vauiUserId}
						AND UsuarioHasContrato.UsuarioHasContrato_Contrato_Id = Contrato_Id
						AND ContratoHasEquipamento.ContratoHasEquipamento_Contrato_Id = Contrato_Id
						AND ContratoHasEquipamento.ContratoHasEquipamento_Equipamento_Id = Mensagem_Equipamento_Id
						AND Mensagem.Mensagem_MensagemTipo_Id = (
															SELECT 
																	MensagemTipo.MensagemTipo_Id 
																	
															FROM 
																	MensagemTipo 
																	
															WHERE 
																	MensagemTipo.MensagemTipo_Valor = 'dateNormal'
														)
						AND Mensagem.Mensagem_DataInicial <= NOW()
						AND Mensagem.Mensagem_DataFinal >= NOW()
						
				ORDER BY
						Mensagem.Mensagem_Id DESC";
	}
	
	function selectMessageByDeviceId ( $vauiDeviceId )
	{
		return "SELECT 
						Mensagem.Mensagem_Id, 
						Mensagem.Mensagem_Equipamento_Id, 
						Mensagem.Mensagem_MensagemTipo_Id, 
						Mensagem.Mensagem_Texto, 
						Mensagem.Mensagem_DataInicial, 
						Mensagem.Mensagem_DataFinal 
						
				FROM
						Mensagem,
						UsuarioHasContrato,
						Contrato,
						ContratoHasEquipamento
						
				WHERE
							UsuarioHasContrato.UsuarioHasContrato_Equipamento_Id = {$vauiDeviceId}
						AND UsuarioHasContrato.UsuarioHasContrato_Contrato_Id = Contrato_Id
						AND ContratoHasEquipamento.ContratoHasEquipamento_Contrato_Id = Contrato_Id
						AND ContratoHasEquipamento.ContratoHasEquipamento_Equipamento_Id = Mensagem_Equipamento_Id
						AND Mensagem.Mensagem_MensagemTipo_Id = (
															SELECT 
																	MensagemTipo.MensagemTipo_Id 
																	
															FROM 
																	MensagemTipo 
																	
															WHERE 
																	MensagemTipo.MensagemTipo_Valor = 'dateNormal'
														)
						AND Mensagem.Mensagem_DataInicial <= NOW()
						AND Mensagem.Mensagem_DataFinal >= NOW()
						
				ORDER BY
						Mensagem.Mensagem_Id DESC";
	}
	
	function selectIconToMapByContractStatusAndDeviceStatus ( $vasIconContractValue, $vasIconStatusDevice )
	{
		return "SELECT 
						IconeHasContratoAndStatusEquip.IconeHasContratoAndStatusEquip_Caminho 
						
				FROM 
						IconeContrato,
						IconeStatusEquipamento,
						IconeHasContratoAndStatusEquip,
						EquipamentoTipo
						
				WHERE
				 			IconeHasContratoAndStatusEquip.IconeHasContratoAndStatusEquip_IconeContrato_Id = IconeContrato.IconeContrato_Id
						AND IconeHasContratoAndStatusEquip.IconeHasContratoAndStatusEquip_IconeStatusEquipamento_Id = IconeStatusEquipamento.IconeStatusEquipamento_Id
						AND IconeHasContratoAndStatusEquip.IconeHasContratoAndStatusEquip_EquipamentoTipo_Id = EquipamentoTipo.EquipamentoTipo_Id
						AND IconeContrato.IconeContrato_Valor = '{$vasIconContractValue}'
						AND IconeStatusEquipamento.IconeStatusEquipamento_Valor = '{$vasIconStatusDevice}'";
	}