<?php
/**
 * Session.php
 * Session management singleton
 * @author Juan José Arol Rosa <Juan.Jose.Arol.Rosa@everis.com>
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
final class Session {
    /**
     * Constant for the stored in session switch
     */
    const STORED_IN_SESSION = 'stored_in_session';
    /**
     * @var Session status
     */
    private $status = false;

    /**
     * Private class constructor so nobody else can instance it
     */
    private function __construct() {}

    /**
     * Private class clone so nobody else can clone it
     */
    private function __clone() {}

    /**
     * Retrieve the persistent instance
     * @return \Session
     */
    public static function getInstance() {
        static $inst = null;
        if ($inst === null) {
            $class = __CLASS__;
            $inst = new $class();
        }
        return $inst;
    }

    /**
     * Start a new session
     * @return bool|\Session
     */
    public function start() {
        if ($this->status === false && !headers_sent() && session_status() !== PHP_SESSION_ACTIVE) {
            $this->status = session_start();
        }
        return $this->status;
    }

    /**
     * Destroy an existing session
     * @return bool
     */
    public function destroy() {
        if ($this->status !== false) {
            $this->status = !session_destroy();
            unset($_SESSION);
            $ret = !$this->status;
        } else {
            $ret = false;
        }
        return $ret;
    }
}