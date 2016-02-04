<?php 

$sql = "create database sample;";
$con = mysql_connect("mysql56:3306","root","123");
$q = mysql_query($sql);
$q = mysql_query("show databases;");
var_dump($q);
mysql_close($con);

while($l = mysql_fetch_assoc($q)){
	    var_dump($l);
}

