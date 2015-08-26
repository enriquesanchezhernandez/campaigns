<?php

/**
 * Class Debug
 *
 * @author     Janis Jekabsons     <jj@fcm-eu.com>
 * @copyright  2015 FCM GmbH
 * @version    1.0
 */
class Debug
{
    public function __construct()
    {
    }

    /**
     * Function dump
     *
     * @param            $data
     * @param bool|false $die
     */
    public static function dump($data, $die = false)
    {
        echo "<pre style='background-color: #F7BE81; border: 1px solid #3c3c3c; border-radius: 4px; padding: 50px;'>";
        var_dump($data);
        echo "</pre>";
        if ($die) {
            die;
        }
    }

}