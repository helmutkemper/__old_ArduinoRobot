<?php

	function selecUserTypeById ( $vauiUserId )
	{
		return "SELECT
						Usuario.*,
						ModuloTipo.* 
						
				FROM 
						Usuario, 
						ModuloTipo 
						
				WHERE 
							Usuario.Usuario_ModuloTipo_Id = ModuloTipo.ModuloTipo_Id 
						AND Usuario.Usuario_Id = {$vauiUserId}";
	}
	
	function selectUserDataByUserId ( $vauiUserId )
	{
		return "SELECT
						Usuario.*
						
				FROM
						Usuario
						
				WHERE
						Usuario.Usuario_Id = {$vauiUserId}";
	}