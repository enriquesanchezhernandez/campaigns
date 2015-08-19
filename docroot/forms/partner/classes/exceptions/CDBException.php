<?php

/**
 *
 * Class CDBException
 *
 *
 * @author      Juan Jose Arol Rosa <Juan.Jose.Arol.Rosa@everis.com>
 * @copyright   2015. Everis
 *
 * @version     1.0
 */
class CDBException extends Exception
{

    public function __construct($errorMessage, $errorCode)
    {
        $code    = empty($errorCode) ? -1 : $errorCode;
        $message = empty($errorMessage) ? 'Error contacting CDB' : $errorMessage;
        parent::__construct($message, $code);
    }
}