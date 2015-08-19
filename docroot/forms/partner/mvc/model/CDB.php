<?php
/**
 * Class CDB
 * @author Juan Jose Arol Rosa <Juan.Jose.Arol.Rosa@everis.com>
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 * @version 2.0
 */
final class CDB {
    /**
     * @var CDB Host
     */
    private $host;
    /**
     * @var CDB post
     */
    private $port;
    /**
     * @var CDB resource string
     */
    private $resource;
    /**
     * @var Mapped fields
     */
    private $fields;

    // TODO check if these are attributes or local variables
    private $userID;
    private $appForm;
    private $appFormType;

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
     * @param string $sessionId
     * @return CDB
     * @throws Exception
     */
    public static function getInstance($sessionId = '') {
        static $inst = null;
        if ($inst === null) {
            $class = __CLASS__;
            $inst = new $class();
        }
        $inst->initialize($sessionId);
        return $inst;
    }

    /**
     * Initialize the instance
     * @param $sessionId
     * @throws Exception
     */
    private function initialize($sessionId) {
        $params = Parameters::getInstance();
        $cdb = $params->get('cdb');
        $this->host = $cdb['host'];
        $this->port = $cdb['port'];
        $this->resource = $cdb['resource'];
        if ($cdb['debug'] != 'false') {
            foreach ($cdb['map'] as $key => $value) {
                $this->fields[$key] = $value;
            }
        } else {
            // Load the fields (only for logged-in users)
            if ($sessionId) {
                $this->userID = $sessionId;
                $this->getSessionData();
            }
            // Load the data of the dropdowns
            $this->loadDropdownsData();
        }
    }

    /**
     * Retrieve the value
     * of a regular field
     * @param $key
     * @return null
     */
    public function get($key) {
        $value = (!empty($key) && isset($this->fields[$key])) ? $this->fields[$key] : null;
        return $value;
    }

    /**
     * Retrieve the value of a dropdown field
     * @param $key
     * @return null
     */
    public function getDropdown($key) {
        // TODO get the array of values and the selected value
        // Maybe we need to refactor the configuration map to include the name of the method to retrieve the values of the dropdown
    }

    /**
     * Retrieve the value of a image field
     * @param $key
     * @return array|bool
     */
    public function getImage($key) {
        $ret = false;
        $data = (!empty($key) && isset($this->fields[$key])) ? $this->fields[$key] : null;
        if ($data) {
            $imgData = base64_decode($data);
            if (function_exists('finfo_open')) {
                $f = finfo_open();
                $mimeType = finfo_buffer($f, $imgData, FILEINFO_MIME_TYPE);
            } else {
                $mimeType = 'application/octet-stream';
            }
            $ret = array(
                'mime' => $mimeType,
                'content' => $data,
            );
        }
        return $ret;
    }

    /**
     * Set the value of a field
     * @param $key
     * @param $value
     */
    public function set($key, $value) {
        if (isset($this->fields[$key])) {
            $this->fields[$key] = $value;
        }
    }

    /**
     * Retrieve data of a session
     * @throws \CDBException
     * @throws \Exception
     */
    private function getSessionData() {
        // $this->userID = (! empty($_SESSION['userID'])) ? $_SESSION['userID'] : '74e95fd7-4705-e511-93f7-000c293f1c16'; // For testing
        $params = Parameters::getInstance();
        $url = (!empty($this->userID)) ? 'getAppForm?id=' . $this->userID : '';
        $response = $this->getData($url);
        $response = $response['getAppFormResult'];
        $cdbConfig = $params->get('cdb');
        if (!$cdbMap = $cdbConfig['map']) {
            throw new Exception('There is a problem with the configuration. Please contact Administrator', 301);
        }
        $cdbMap = $cdbConfig['map'];
        foreach ($cdbMap as $htmlName => $cdbName) {
            if (isset ($response[$cdbName])) {
                $this->fields[$htmlName] = $response[$cdbName];
            }
        }
    }

    /**
     * Load the data of the dropdown fields
     */
    private function loadDropdownsData() {
        $params = Parameters::getInstance();
        $dropdownMethods = $params->get('cdb')['dropdown_methods'];
        foreach ($dropdownMethods as $method) {
            $this->getDropdownData($method);
        }
    }

    /**
     * Load the data of a single dropdown field
     * @param $method
     * @throws \CDBException
     */
    private function getDropdownData($method) {
        if ($response = $this->getData($method['method'])) {
            $response = json_decode($response[$method['data']], true);
            foreach ($response as $field) {
                if (isset($field['Name'])) {
                    $fieldNameArray = array($field['Name']);
                    $values = $field['Values'];
                } else {
                    $fieldNameArray = $method['fields'];
                    $values = $response;
                }
                foreach ($fieldNameArray as $fieldName) {
                    $this->fields[$fieldName] = $values;
                    if (isset($this->appForm) && $this->appForm[$fieldName]) {
                        $this->fields[$fieldName]['selected'] = $this->appForm[$fieldName];
                    }
                }
            }
        }
    }

    /**
     * Execute a service and retrieve the data
     * @param $url
     * @return array|null
     * @throws \CDBException
     */
    private function getData($url) {
        $resource = $this->host . ':' . $this->port . $this->resource . $url;
        $response = null;
        if ($content = @file_get_contents($resource)) {
            $response = json_decode($content, true);
            if (intval($response['returnCode']) !== 1) {
                throw new CDBException($response['returnMessage'], $response['returnCode']);
            }
        } else {
            throw new CDBException('Resource could not be found or read', 404);
        }
        return $response;
    }

    // TODO define the logic of this method
    private function setData($method, $parameters) {
        $handle = fsockopen($this->host, $this->port);
        fputs($handle, 'POST ' . $method . ' HTTP/1.1\r\n');
        fputs($handle, 'Host: ' . $this->host . '\r\n');
        fputs($handle, 'Content-type: application/x-www-form-urlencoded\r\n');
        fputs($handle, 'Content-length: ' . strlen($parameters) . '"\r\n');
        fputs($handle, 'Connection: close\r\n\r\n');
        fputs($handle, $parameters);
        $response = '';
        while (! feof($handle)) {
            $response .= fgets($handle, 1024);
        }
        fclose($handle);
        return $response;
    }
}