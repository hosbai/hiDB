<?php
 class HiDB{
 	// config DB
	private static $server  = "localhost"; // enter your server name here
	private static $db_name = "DB_NAME"; // Enter your database name
	private static $db_user = "root"; // Enter your username
	private static $db_pass = ""; // Enter your password

	public static $con;
	public static $res;

	public static $count = array();


	// initialize:
	public static function hi(){
		static::$con = mysqli_connect(static::$server, static::$db_user, static::$db_pass, static::$db_name) or die("Could not connect to server!");
		static::$con->set_charset("utf8");
	}




	// basec query do
	public static function que($mySQLstr){
		static::$res = static::$con->query($mySQLstr);
		return static::$res;
		// return $res->fetch_array();
	}


	/*
	 * SELECT
	 */

	// get all of a table 
	public static function table($tableName){
	 	return static::que("SELECT * FROM `$tableName`");
	}

	// public static function table1Col($tableName, $colName){
	//  	return static::que("SELECT $colName FROM $tableName");
	// }
	// public static function isUnq($tableName, $colName, $val){
	// 	// $arr : ['']
	//  	return static::que("SELECT * FROM $tableName WHERE $colName=$val");
	// }

	public static function fch(){
		return static::$con->fetch_array(static::$res);
	}


	// select random row from my table
	public static function tableRand($tableName){
		// sure there is row count of table is exist
		if(!isset(static::$count[$tableName])) static::updateCountTable($tableName);

		// create random selection:
		$offset = rand(0,static::$count[$tableName]-.001);
		return static::que("SELECT * FROM $tableName LIMIT 1 OFFSET $offset")->fetch_array();
	}


	// check count of table rows and update $count
	public static function updateCountTable($tableName){
		static::$count[$tableName] = intval(static::que("SELECT COUNT(*) FROM $tableName")->fetch_row()[0]);
	}




	// insert to table
	public static function ins($tableName, $arr){
		// $array = ['field1'=>'value of field 1', ...]
		$col = "`";
		$val = "'";
		foreach ($arr as $key => $value) {

			// scaping here:

			$col .= $key."`,`";
			$val .= $value."','";
		}
		$col = substr($col, 0, -2);  
		$val = substr($val, 0, -2);

		return static::que("INSERT INTO `$tableName`($col) VALUES ($val);");
	}

	// 



	// for escape input values
	public static function esc($str2esc){
		return static::$con->real_escape_string($str2esc);
	}

	// close db
	public static function bye(){
		static::$con->close();
	}
}

?>