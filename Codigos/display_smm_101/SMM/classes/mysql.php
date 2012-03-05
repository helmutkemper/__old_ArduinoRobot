<?php

	class mysql
	{
		private $vcoDbConnect;
		private $vcoQuery;
		
		function mysql ()
		{
			
		}
		
		public function setConnection ( $vaaSetup )
		{
			$this->vcoDbConnect	 =  mysql_connect ( $vaaSetup["host"], $vaaSetup["username"], $vaaSetup["password"] ) or die ( mysql_error () );
									mysql_select_db ( $vaaSetup["dbname"], $this->vcoDbConnect ) or die ( mysql_error () );
		}
		
		public function query ( $vaaSetup )
		{
			$this->vcoQuery		 =  mysql_query ( $vaaSetup["query"] ) or die ( $this->error( $vaaSetup ) );
		}
		
		public function fetch ()
		{
			$vlaReturn =  array ();
			
			while ( $vlaLinha =  mysql_fetch_array ( $this->vcoQuery, MYSQL_ASSOC ) )
			{
				$vlaReturn[] =  $vlaLinha;
			}
			
			return $vlaReturn;
		}
		
		private function error ( $vaaSetup )
		{
			print mysql_error ();
			print "<br><pre>";
			print_r ( $vaaSetup );
			print "</pre>";
			
		}
	}