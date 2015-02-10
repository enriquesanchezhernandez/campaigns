<?php

$site = $_GET['site'];
$s = curl_init();
curl_setopt($s, CURLOPT_URL, $site);
curl_setopt($s, CURLOPT_RETURNTRANSFER, TRUE);
print curl_exec($s);