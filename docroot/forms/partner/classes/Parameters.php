<?php
/**
 * Parameters.php
 * Parameters and configuration singleton
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
final class Parameters {
    /**
     * @var Array of parameters
     */
    private $params;

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
     * @return \Parameters
     */
    public static function getInstance() {
        static $inst = null;
        if ($inst === null) {
            $class = __CLASS__;
            $inst = new $class();
            // Load the configuration
            if ($config = file_get_contents(APP_CONFIG . 'config.json')) {
                $inst->params = json_decode($config, true);
            }
        }
        return $inst;
    }

    /**
     * Retrieve the value of a parameter
     * @param $name
     * @return bool
     */
    public function get($name) {
        if (isset($this->params[$name])) {
            $ret = $this->params[$name];
        } else if (isset($_REQUEST[$name])) {
            $ret = $_REQUEST[$name];
        } else if (isset($_SESSION[$name])) {
            $ret = $_SESSION[$name];
        } else {
            $ret = false;
        }
        return $ret;
    }

    /**
     * Retrieve the value of an URL parameter through its configuration key
     * @param $name
     * @return bool
     */
    public function getUrlParamValue($name) {
        $key = $this->get('url_params')[$name];
        return $this->get($key);
    }

    /**
     * Set the value of a parameter
     * @param $name
     * @param $value
     * @param $persistent
     */
    public function set($name, $value, $persistent = false) {
        $this->params[$name] = $value;
        if ($persistent) {
            $_SESSION[$name] = $value;
        }
    }
}