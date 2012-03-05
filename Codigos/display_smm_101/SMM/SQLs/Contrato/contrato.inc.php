<?php
	
	function selectContractAndDevicesByUserId ( $vauiUserId, $vabContractInactived = 0 )
	{
		return "SELECT 
						UsuarioHasContrato.UsuarioHasContrato_Usuario_Id,
						UsuarioHasContrato.UsuarioHasContrato_Contrato_Id,
						Contrato.Contrato_DataInicial,
						Contrato.Contrato_DataExpiracao,
						Contrato.Contrato_CasoEspecial,
						Equipamento.Equipamento_Id,
						Equipamento.Equipamento_EquipamentoTipo_Id,
						EquipamentoTipo.EquipamentoTipo_Valor 
						
				FROM 
						UsuarioHasContrato,
						Contrato,
						ContratoHasEquipamento,
						Equipamento,
						EquipamentoTipo
						
				WHERE 
							UsuarioHasContrato.UsuarioHasContrato_Usuario_Id = {$vauiUserId} 
						AND UsuarioHasContrato.UsuarioHasContrato_Contrato_Id = Contrato.Contrato_Id
						AND Contrato.Contrato_Inativado = {$vabContractInactived}
						AND ContratoHasEquipamento.ContratoHasEquipamento_Contrato_Id = Contrato.Contrato_Id 
						AND ContratoHasEquipamento.ContratoHasEquipamento_Equipamento_Id = Equipamento.Equipamento_Id 
						AND Equipamento.Equipamento_EquipamentoTipo_Id = EquipamentoTipo.EquipamentoTipo_Id";
	}
	
	function selectContractAndDevicesByUserIdAndDays ( $vauiUserId, $vabContractInactived = 0, $vauiDaysToAttention = 90, $vauiDaysToCritical = 45, $vauiNewContractForDays = 30 )
	{
		return "SELECT 
						UsuarioHasContrato.UsuarioHasContrato_Usuario_Id,
						UsuarioHasContrato.UsuarioHasContrato_Contrato_Id,
						Contrato.Contrato_Id,
						Contrato.Contrato_DataInicial,
						Contrato.Contrato_DataExpiracao,
						Contrato.Contrato_CasoEspecial,
						IF( DATE_SUB( Contrato.Contrato_DataExpiracao, INTERVAL {$vauiDaysToAttention} DAY ) < NOW(), 1, 0 ) AS Contrato_AlertaCritico,
						IF( DATE_SUB( Contrato.Contrato_DataExpiracao, INTERVAL {$vauiDaysToCritical} DAY ) < NOW(), 1, 0 ) AS Contrato_AlertaAtencao,
						IF( DATE_ADD( Contrato.Contrato_DataInicial, INTERVAL {$vauiNewContractForDays} DAY ) > NOW(), 1, 0 ) AS Contrato_AlertaContratoNovo,
						Equipamento.Equipamento_Id,
						Equipamento.Equipamento_EquipamentoTipo_Id,
						EquipamentoTipo.EquipamentoTipo_Valor 
						
				FROM 
						UsuarioHasContrato,
						Contrato,
						ContratoHasEquipamento,
						Equipamento,
						EquipamentoTipo
						
				WHERE 
							UsuarioHasContrato.UsuarioHasContrato_Usuario_Id = {$vauiUserId} 
						AND UsuarioHasContrato.UsuarioHasContrato_Contrato_Id = Contrato.Contrato_Id
						AND Contrato.Contrato_Inativado = {$vabContractInactived}
						AND ContratoHasEquipamento.ContratoHasEquipamento_Contrato_Id = Contrato.Contrato_Id 
						AND ContratoHasEquipamento.ContratoHasEquipamento_Equipamento_Id = Equipamento.Equipamento_Id 
						AND Equipamento.Equipamento_EquipamentoTipo_Id = EquipamentoTipo.EquipamentoTipo_Id";
	}
	
	function selectContractDelayedByContractIdAndDaysToleranceToDelayedPayment ( $vauiContractId, $vauiDaysToleranceDelayedPayment = 5 )
	{
		return "SELECT 
						Parcelas_Id,
						Parcelas_AcertadoValor,
						Parcelas_AcertadoData
						
				FROM 
						ContratoHasParcelas,
						Parcelas
						
				WHERE 
							ContratoHasParcelas_Contrato_Id = {$vauiContractId} 
						AND ContratoHasParcelas_Parcelas_Id = Parcelas_Id 
						AND DATE_ADD( Parcelas_AcertadoData, INTERVAL {$vauiDaysToleranceDelayedPayment} DAY ) < NOW()
						AND Parcelas_PagoData IS NULL";
	}