<?php /* Smarty version Smarty-3.1.8, created on 2012-03-05 11:15:14
         compiled from "Templates/mapa.tpl" */ ?>
<?php /*%%SmartyHeaderCode:1032143974f4bcb81d79304-00204078%%*/if(!defined('SMARTY_DIR')) exit('no direct access allowed');
$_valid = $_smarty_tpl->decodeProperties(array (
  'file_dependency' => 
  array (
    '589d7c8ae9df7b13270d853679f669f0fb580711' => 
    array (
      0 => 'Templates/mapa.tpl',
      1 => 1330956910,
      2 => 'file',
    ),
  ),
  'nocache_hash' => '1032143974f4bcb81d79304-00204078',
  'function' => 
  array (
  ),
  'version' => 'Smarty-3.1.8',
  'unifunc' => 'content_4f4bcb81dc3588_44095320',
  'variables' => 
  array (
    'mapTitle' => 0,
    'mapMarkersData' => 0,
    'mapZoom' => 0,
    'mapType' => 0,
    'mapAutoZoom' => 0,
    'mapInterval' => 0,
    'mapRelativeDataAddress' => 0,
    'mapIdUser' => 0,
    'mapSetAutoCenter' => 0,
  ),
  'has_nocache_code' => false,
),false); /*/%%SmartyHeaderCode%%*/?>
<?php if ($_valid && !is_callable('content_4f4bcb81dc3588_44095320')) {function content_4f4bcb81dc3588_44095320($_smarty_tpl) {?><html> 
<head> 
<meta name="viewport" content="initial-scale=1.0, user-scalable=no" /> 
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<title><?php echo $_smarty_tpl->tpl_vars['mapTitle']->value;?>
</title>
<script type="text/javascript" src="../JavaScript/utf8_encode.js"></script>
<script type="text/javascript" src="../JavaScript/utf8_decode.js"></script>
<script type="text/javascript" src="../JavaScript/serialize.js"></script>
<script type="text/javascript" src="../JavaScript/unserialize.js"></script>
<script src="http://www.google.com/jsapi"></script> 
<script type="text/javascript">google.load("jquery", "1");</script> 
<script type="text/javascript"> 
google.load("maps", "3", {other_params:"sensor=false"});
</script> 
<script>

	var vgbInfoWindowClosed	 =  true;
	var vgoInfoWindow		 =  new google.maps.InfoWindow();
	var vgoMarkerBounds		 =  new google.maps.LatLngBounds();
	var vgaMarkers			 =  [];
	var vgaMarkersData		 =  '<?php echo $_smarty_tpl->tpl_vars['mapMarkersData']->value;?>
';
	var vgoMainMap;
	var vgnTimeoutPointer;
	var temp = new Array ();
	
	vgaMarkersData =  vgaMarkersData.split ( "***,***" );
	
	for ( var i in vgaMarkersData )
	{
		var obj = {};
		var dados =  vgaMarkersData[i].split ("##,##");
		for ( var d in dados )
		{
			var campo = dados[d].split ('####');
			
			obj[ campo[0] ] = campo[1];
		}
		
		temp.push(obj);
		
	}
	vgaMarkersData = temp;
	
	function onInit()
	{
	 	var vloOptions			 =  {
										zoom: <?php echo $_smarty_tpl->tpl_vars['mapZoom']->value;?>
,
										center: new google.maps.LatLng(0, 0),
										mapTypeId: google.maps.MapTypeId.<?php echo $_smarty_tpl->tpl_vars['mapType']->value;?>

									};
			vgoMainMap			 =  new google.maps.Map( document.getElementById('map_canvas'), vloOptions );
						
									mapMakeMarkers (0);
									
		var vloCenter			 =  vgoMarkerBounds.getCenter ();
									vgoMainMap.setCenter( vloCenter );
									
									if ( <?php echo $_smarty_tpl->tpl_vars['mapAutoZoom']->value;?>
 )
									{
										vgoMainMap.fitBounds(vgoMarkerBounds);
									}
									
			vgnTimeoutPointer	 =  setInterval ( "onTimeToUpdateData()", <?php echo $_smarty_tpl->tpl_vars['mapInterval']->value;?>
000 );
	}
	
	function onAdd ( vaoForm )
	{
		var vlsSendToDisplay =  "";
		
		switch ( $('#command').attr('value') )
		{
			case '[H]':
			case '[D]':
			case '[T]':
			case '[L]':
			case '[Z]':
			case '[K]':	vlsSendToDisplay +=  $('#realCommand').attr ('value') + $('#command').attr('value');
						$('#realCommand').attr ( 'value', vlsSendToDisplay );
						break;
						
			case 'M':
			case 'B':
			case 'C':
			case 'E':
			case 'G':
			case 'J':
			case 'S':
			case 'R':	vlsSendToDisplay +=  $('#realCommand').attr ('value') + '[' + $('#command').attr('value') + $('#complementRoll').attr('value') + $('#textToDisplay').attr('value') + ']';
						$('#realCommand').attr ( 'value', vlsSendToDisplay );
						break;
			
			case 'I':	vlsSendToDisplay +=  $('#realCommand').attr ('value') + '[' + $('#command').attr('value') + $('#textToDisplay').attr('value') + ']';
						$('#realCommand').attr ( 'value', vlsSendToDisplay );
						break;
			
			case 'A':
			
			case '[P]':	vlsSendToDisplay +=  $('#realCommand').attr ('value') + '[P' + $('#complementPause').attr ('value') + ']';
						$('#realCommand').attr ( 'value', vlsSendToDisplay );
						break;
		}
	}
	
	function onChangeCommand ( vasValue )
	{
		$('#complementRoll').css('display','none');
		$('#complementPause').css('display','none');
		$('#textToDisplay').css('display','none');
		$('#labelText').css('display','none');
		
		switch ( vasValue )
		{
			case '[P]': $('#complementPause').show();
						break;
						
			case 'R':   $('#complementRoll').show();
						$('#textToDisplay').show();
						$('#labelText').show();
						break;
						
			case 'M':
			case 'B':
			case 'C':
			case 'E':
			case 'G':
			case 'J':
			case 'S':
			case 'I':	$('#textToDisplay').show();
						$('#labelText').show();
						break;
		}
	}
	
	function sendDataToDisplay( vaoForm )
	{
			vgoInfoWindow.close();
		var request = $.ajax	({
									url:		"sendToDevice.php",
									type:		"POST",
									contentType:"application/x-www-form-urlencoded; charset=iso-8859-1;",
									data:		{
													device_id:   vaoForm.device_id.value,
													user_id:     vaoForm.user_id.value,
													realCommand: "[L1]" + vaoForm.realCommand.value + "[F]"
												},
									dataType:	"html",
									success:    redraw
								});
	}
	
	function redraw ( vasData )
	{
		mapDestroyAllMarkers ();
		temp = new Array ();
		vgaMarkersData =  vasData.split ( "***,***" );
	
	for ( var i in vgaMarkersData )
	{
		var obj = {};
		var dados =  vgaMarkersData[i].split ("##,##");
		for ( var d in dados )
		{
			var campo = dados[d].split ('####');
			
			obj[ campo[0] ] = campo[1];
		}
		
		temp.push(obj);
		
	}
	vgaMarkersData = temp;
		mapMakeMarkers (1);
	}
	
	function mountCommandWindow ( vasTagId, vauiUserId )
	{
		$('#device_id_' + vasTagId ).html('<font face=\'verdana\' size=\'1\'>'+
										'<form name=\'newMessage\' action=\'sendToDevice.php\'>'+
											'<input type=\'hidden\' id=\'device_id\' name=\'device_id\' value=\''+vasTagId+'\'>'+
											'<input type=\'hidden\' id=\'user_id\' name=\'user_id\' value=\''+vauiUserId+'\'>'+
											'<label id=\'selectCommand\'><b>Comando para o display:</b></label><br><br>'+
											'<select id=\'command\' name=\'command\' onChange=\'onChangeCommand(this.value)\'>'+
												'<option value=\'[H]\'>Mostrar hora</option>'+
												'<option value=\'[D]\'>Mostrar data</option>'+
												'<option value=\'[T]\'>Mostrar temperatura</option>'+
												'<option value=\'[P]\'>Pausa</option>'+
												'<option value=\'[L]\'>Limpar display</option>'+
												'<option value=\'[Z]\'>Apagar memória</option>'+
												'<option value=\'M\'>Mensagem fixa</option>'+
												'<option value=\'B\'>Piscar mensagem</option>'+
												'<option value=\'C\'>Centro</option>'+
												'<option value=\'E\'>Abrir pelo lado esquerdo</option>'+
												'<option value=\'G\'>Abrir pelo lado direito</option>'+
												'<option value=\'J\'>Jogar mensagem</option>'+
												'<option value=\'[K]\'>Kome-Kome</option>'+
												'<option value=\'R\'>Rolar mensagem</option>'+
												'<option value=\'S\'>Subir mensagem</option>'+
												'<option value=\'I\'>Descer mensagem</option>'+
												'<option value=\'A\'>Acertar o relógio</option>'+
											'</select>'+
											'&nbsp;<select id=\'complementPause\' name=\'complementPause\' style=\'display:none;\'>'+
												'<option value=\'1\'>1 segundos</option>'+
												'<option value=\'2\'>2 segundos</option>'+
												'<option value=\'3\'>3 segundos</option>'+
												'<option value=\'4\'>4 segundos</option>'+
												'<option value=\'5\'>5 segundos</option>'+
												'<option value=\'6\'>6 segundos</option>'+
												'<option value=\'7\'>7 segundos</option>'+
												'<option value=\'8\'>8 segundos</option>'+
												'<option value=\'9\'>9 segundos</option>'+
											'</select>'+
											'<select id=\'complementRoll\' name=\'complementRoll\' style=\'display:none;\'>'+
												'<option value=\'R\'>Velocidade rápida</option>'+
												'<option value=\'M\'>Velocidade média</option>'+
												'<option value=\'L\'>Velocidade lenta</option>'+
											'</select>'+
											'<br><br><label id=\'labelText\' style=\'display:none;\'><b>Mesagem:</b> </label><input type=\'text\' id=\'textToDisplay\' name=\'textToDisplay\' size=\'40\' style=\'display:none;\'>'+
											'<br><input type=\'button\' id=\'addCommand\' value=\'Adicionar\' onClick=\'onAdd ( this.form )\'>'+
											'<br><br><label id=\'selectCommand\'><b>Comando real:</b></label><br><br>'+
											'<input type=\'text\' id=\'realCommand\' name=\'realCommand\' size=\'54\' style=\'display:none_;\'>'+
											'<br><input type=\'button\' id=\'sendCommand\' value=\'Enviar\' onClick=\'sendDataToDisplay( this.form )\'>'+
										'</form>'+
									'</font>');
	}

	function mapMakeMarkers (i)
	{
		var vloMapPin;
		
		for ( var vluiMarkeKey in vgaMarkersData )
		{
			vloMapPin =  makeMarker	({
										position:	new google.maps.LatLng(vgaMarkersData[ vluiMarkeKey ].latitude, vgaMarkersData[ vluiMarkeKey ].longitude),
  										content:	vgaMarkersData[ vluiMarkeKey ].content,
										icon:		vgaMarkersData[ vluiMarkeKey ].icon,
										width:		vgaMarkersData[ vluiMarkeKey ].width,
										height:		vgaMarkersData[ vluiMarkeKey ].height
									});
			vgaMarkers.push( vloMapPin );
		}
	}

	function mapDestroyAllMarkers ()
	{
		for ( var vluiMarkeKey in vgaMarkers )
		{
			vgaMarkers[ vluiMarkeKey ].setMap( null );
		}
	}
	
	function onTimeToUpdateData ()
	{
		if ( vgbInfoWindowClosed == false )
		{
			return;
		}
	
		$.ajax	({
	  				url:		"<?php echo $_smarty_tpl->tpl_vars['mapRelativeDataAddress']->value;?>
",
	  				type:		"POST",
	  				dataType:	"html",
					data:		<?php echo $_smarty_tpl->tpl_vars['mapIdUser']->value;?>
,
					success:	onUpdateDataDone
				});
	}
	
	function onUpdateDataDone ()
	{
		var vloCenter	 =  vgoMarkerBounds.getCenter ();
		
			if ( <?php echo $_smarty_tpl->tpl_vars['mapSetAutoCenter']->value;?>
 )
			{
				vgoMainMap.setCenter( vloCenter );
			}
									
			if ( <?php echo $_smarty_tpl->tpl_vars['mapAutoZoom']->value;?>
 )
			{
			//	vgoMainMap.fitBounds(vgoMarkerBounds);
			}
	}
	
	function makeMarker ( vaoOptions )
	{
		var vloIcon		 =  new google.maps.MarkerImage ( vaoOptions.icon, null, null, null, new google.maps.Size ( vaoOptions.width, vaoOptions.height ) );
							vaoOptions.icon =  vloIcon;
							
		var vloMapPin	 =  new google.maps.Marker( { map:vgoMainMap } );
							vloMapPin.setOptions( vaoOptions );
							
							google.maps.event.addListener( vloMapPin, "click", function()
							{
								vgbInfoWindowClosed	 =  false;
								vgoInfoWindow.setOptions( vaoOptions );
								vgoInfoWindow.open( vgoMainMap, vloMapPin );
								google.maps.event.addListener( vgoInfoWindow, 'closeclick', function()
								{
									vgbInfoWindowClosed =  true;
								});
	  						});
							vgoMarkerBounds.extend( vaoOptions.position );
							
							return vloMapPin;
	}
	
</script>
</head>
<body onload="onInit()">
  <div id="map_canvas" style="width:100%; height:100%;"></div>
</body>
</html><?php }} ?>