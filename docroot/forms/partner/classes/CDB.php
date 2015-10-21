<?php

/**
 * Class CDB
 * @author  Juan Jose Arol Rosa <Juan.Jose.Arol.Rosa@everis.com>
 * @author  Eduardo Martos (eduardo.martos.gomez@everis.com)
 * @version 2.0
 */
final class CDB
{
    /** @var CDB Host */
    private $host;
    /** @var CDB port */
    private $port;
    /** @var string CDB resource string */
    private $resource;
    /** @var boolean Debug mode */
    private $debug;
    /** @var array Mapped fields */
    private $fields;
    /** @var array Mapped dropDowns */
    private $dropdowns;
    /** @var string Session ID */
    private $sessionID;
    /** @var array CDB map */
    private $cdbMap;

    /** Private class constructor so nobody else can instance it */
    private function __construct()
    {
    }

    /** Private class clone so nobody else can clone it */
    private function __clone()
    {
    }

    /**
     * Retrieve the persistent instance
     *
     * @param  array $cdbMap
     * @param string $sessionId
     *
     * @return $thi
     */
    public static function getInstance($cdbMap, $sessionId = '')
    {
        static $inst = null;
        if ($inst === null) {
            $class = __CLASS__;
            $inst  = new $class();
        }
        $inst->cdbMap = $cdbMap;
        $inst->initialize();
        if ($sessionId) {
            $inst->initializeSession($sessionId);
        }
        // Load the data of the dropDowns
        if ($inst->cdbMap) {
            $inst->loadDropdownsData();
        }

        return $inst;
    }

    /** Initialize the instance */
    private function initialize()
    {
        $params = Parameters::getInstance();
        $cdb    = $params->get('cdb');
        if ($cdb['debug'] == 'true') {
            $this->host     = APP_ROOT;
            $this->resource = $cdb['debug_folder'];
            $this->debug    = true;
        } else {
            $this->host     = $cdb['host'];
            $this->port     = $cdb['port'];
            $this->resource = $cdb['resource'];
        }
    }

    private function initializeSession($sessionId)
    {
        $this->sessionID = $sessionId;
        // Set the context
        $this->setContext();
        if ($this->cdbMap) {
            // Load the fields
            $this->getSessionData();
        }
    }

    /**
     * Retrieve the value of a regular field
     *
     * @param $key
     *
     * @return string|null
     */
    public function get($key)
    {
        $value = (! empty($key) && isset($this->fields[$key])) ? $this->fields[$key] : null;

        return $value;
    }

    /**
     * Retrieve the value of a dropDown field
     *
     * @param $key
     *
     * @return null
     */
    public function getDropdown($key)
    {
        $value = (! empty($key) && isset($this->dropdowns[$key])) ? $this->dropdowns[$key] : null;

        return $value;
    }

    /**
     * Retrieve the value of a image field
     *
     * @param $key
     *
     * @return array|bool
     */
    public function getImage($key)
    {
        $ret  = false;
        $data = (! empty($key) && isset($this->fields[$key])) ? $this->fields[$key] : null;
        if ($data) {
            $imgData = base64_decode($data);
            if (function_exists('finfo_open')) {
                $f        = finfo_open();
                $mimeType = finfo_buffer($f, $imgData, FILEINFO_MIME_TYPE);
            } else {
                $mimeType = 'application/octet-stream';
            }
            $ret = array(
                'mime'    => $mimeType,
                'content' => $data,
            );
        }

        return $ret;
    }

    /**
     * Set the value of a field
     *
     * @param $key
     * @param $value
     */
    public function set($key, $value)
    {
        if (isset($this->fields[$key])) {
            $this->fields[$key] = $value;
        }
    }

    /**
     * Retrieve data of a session
     *
     * @throws \CDBException
     */
    private function getSessionData()
    {
        $readMethod   = $this->getMethod('read', 'read_mf');
        $url          = $this->buildUrl($readMethod);
        $responseData = $this->getData($url);
        $response     = $responseData[$readMethod['response']];
        $countries    = $responseData['returnPaises'];

        if (! is_array($response)) {
            $response = json_decode($response, true);
        }
        if (! is_array($countries)) {
            $countries = json_decode($countries, true);
        }

        $params = Parameters::getInstance();
        if ($params->getUrlParamValue('maintenance_mode')) {
            $this->getSessionDataMF($response, $countries);
        } else {
            $this->getSessionDataAppForm($response, $countries);
        }
    }

    /**
     * Function getSessionDataAppForm
     *
     * @param $response
     * @param $countries
     */
    private function getSessionDataAppForm($response, $countries)
    {
        $params      = Parameters::getInstance();
        $partnerType = $params->get('osh_category');
        $formType    = $params->get('osh_leads');
        $statusCode  = $params->get('statuscode');
        $sent        = intval($params->get('cdb')['sent']);

        $response['returnPaises'] = $countries;

        if (! ($partnerType === 'mp' && $formType === 'new' && $statusCode === $sent)) {
            foreach ($this->cdbMap as $htmlName => $cdbName) {
                if (isset ($response[$cdbName])) {
                    if (is_array($response[$cdbName]) && isset($response[$cdbName]['Name'])) {
                        $this->fields[$htmlName] = $response[$cdbName]['Name'];
                        /*} elseif (strpos($cdbName, 'profile') !== false) {
                            $this->fields['profiles'][$htmlName] = $response[$cdbName];*/
                    } elseif ($cdbName === "returnPaises") {
                        $this->fields[$htmlName] = $countries;
                    } else {
                        $this->fields[$htmlName] = $response[$cdbName];
                    }
                }
            }
        }
        // Debug::dump($this->fields, 'FIELDS', true);
    }

    /**
     * Get session data of Maintenance Forms
     *
     * @param $response
     *
     * @throws \CDBException
     */
    private function getSessionDataMF($response, $countries)
    {
        if (isset($response[0]['Fields'])) {
            $response = $response[0]['Fields'];
        } else {
            throw new CDBException('configuration_error', 500);
        }
        // Filter the response to clean the prefixes
        foreach ($response as $key => $value) {
            if (strpos($key, '.') !== false) {
                $key = explode('.', $key)[1];
            }
            $responseFixed[$key] = $value;
        }
        $response                 = $responseFixed;
        $response['returnPaises'] = $countries;
        foreach ($this->cdbMap as $htmlName => $cdbName) {
            if (isset ($response[$cdbName])) {
                if (is_array($response[$cdbName]) && isset($response[$cdbName]['Name'])) {
                    $this->fields[$htmlName] = $response[$cdbName]['Name'];
                } elseif ($cdbName === "returnPaises") {
                    $this->fields[$htmlName] = $countries;
                } else {
                    $this->fields[$htmlName] = isset($response[$cdbName]['Value']) ? $response[$cdbName]['Value'] : $response[$cdbName];
                }
            }
        }
    }

    /**
     * Set the context of the application via CDB
     *
     * @throws \CDBException
     * @throws \OshException
     */
    private function setContext()
    {
        $params = Parameters::getInstance();
        if ($this->debug) {
            $params->setUrlParamValue('entity', $params->get('entity') ? $params->get('entity') : $params->get('defaultEntity'));
            $params->setUrlParamValue('partner_type', $params->get('partner_type') ? $params->get('partner_type') : $params->get('defaultPartnerType'));
            $params->setUrlParamValue('status_code', $params->get('status_code'));
            $params->setUrlParamValue('maintenance_mode', $params->get('maintenance_mode'));
            $params->setUrlParamValue('locked', $params->get('locked'));

            return;
        }
        $readMethod = $this->getMethod('read', 'read_mf');
        $url        = $this->buildUrl($readMethod);
        $response   = $this->getData($url);
        $response   = $response[$readMethod['response']];
        if (! is_array($response)) {
            $response = json_decode($response, true);
        }
        if (! $params->getUrlParam('entity') || ! $params->getUrlParam('partner_type') || ! $params->getUrlParam('maintenance_mode') || ! $params->getUrlParam('locked')) {
            throw new OshException('bad_config', 500);
        } else {
            if ($params->getUrlParamValue('maintenance_mode')) {
                $this->setContextForMaintenanceForm($response);
            } else {
                $this->setContextForAppForm($response);
            }
        }
    }

    /**
     * Set the context for AppForms
     * @throws \CDBException
     */
    private function setContextForAppForm($response)
    {
        $params      = Parameters::getInstance();
        $categoryKey = $params->getUrlParam('entity');
        if (! isset($response[$categoryKey]['Name']) || ! isset($params->get('cdb')['category'])) {
            throw new CDBException("no_partner_type", 500);
        } else {
            $category    = $response[$categoryKey]['Name'];
            $categoryMap = $params->get('cdb')['category'];
            $locked      = $params->get('cdb')['locked'];
            $statusCode  = $params->getUrlParam('status_code');
            $statusCode  = intval($response[$statusCode]);
            $gracePeriod = $params->get('cdb')['graceperiod'];
            if (array_search($statusCode, $gracePeriod) !== false) {
                $params->setUrlParamValue('graceperiod', true);
            }
            $params->set('statuscode', $statusCode);
            foreach ($categoryMap as $categoryPattern => $categoryName) {
                if (strpos(strtolower($category), $categoryPattern) !== false) {
                    $categoryTranslated = $categoryMap[$categoryPattern];
                    if ($categoryTranslated != 'pcp') {
                        $params->setUrlParamValue('entity', $categoryTranslated);
                    } else {
                        $params->setUrlParamValue('entity', 'ocp');
                    }

                    if ($categoryTranslated === 'fop') {
                        $params->setUrlParamValue('partner_type', 'current');
                        //$params->setUrlParamValue('maintenance_mode', 'mf');
                    } elseif ($categoryTranslated === 'pcp') {
                        $params->setUrlParamValue('partner_type', 'new');
                        $params->setUrlParamValue('locked', false);
                        $params->setUrlParamValue('potential', true);
                        $params->setUrlParamValue('maintenance_mode', false);
                    } else {
                        $partnerType      = $params->getUrlParam('partner_type');
                        $partnerTypeValue = isset($response[$partnerType]) ? 'new' : 'current';
                        $params->setUrlParamValue('partner_type', $partnerTypeValue);
                        if (array_search($statusCode, $locked) !== false) {
                            $params->setUrlParamValue('locked', true);
                        }
                    }
                }
            }
        }
    }

    /**
     * Set the context for maintenance forms
     * @throws \CDBException
     */
    private function setContextForMaintenanceForm($response)
    {
        $params      = Parameters::getInstance();
        $categoryKey = $params->getUrlParam('entity_mf');
        if (isset($response[0]['Fields'])) {
            $response = $response[0]['Fields'];
        } else {
            throw new CDBException('configuration_error', 500);
        }
        if (! isset($response[$categoryKey]['Value']['Name']) || ! isset($params->get('cdb')['category'])) {
            throw new CDBException("no_partner_type", 500);
        } else {
            $category    = $response[$categoryKey]['Value']['Name'];
            $categoryMap = $params->get('cdb')['category'];
            $statusCode  = $params->getUrlParam('status_code');
            $statusCode  = intval($response[$statusCode]);
            $gracePeriod = $params->get('cdb')['graceperiod'];
            if (array_search($statusCode, $gracePeriod) !== false) {
                $params->setUrlParamValue('graceperiod', true);
            }
            foreach ($categoryMap as $categoryPattern => $categoryName) {
                if (strpos(strtolower($category), $categoryPattern) !== false) {
                    $categoryTranslated = $categoryMap[$categoryPattern];
                    $params->setUrlParamValue('entity', $categoryTranslated);
                    if ($categoryTranslated === 'fop') {
                        $params->setUrlParamValue('partner_type', 'current');
                    } else {
                        $partnerType      = $params->getUrlParam('partner_type');
                        $partnerTypeValue = isset($response[$partnerType]) ? 'new' : 'current';
                        $params->setUrlParamValue('partner_type', $partnerTypeValue);
                    }
                }
            }
        }
    }

    /**
     * Retrieve the correct method regarding on the context
     *
     * @return string
     * @throws \CDBException
     */
    private function getMethod($key, $keyMf)
    {
        $params     = Parameters::getInstance();
        $readMethod = null;
        if ($key == 'update' || $keyMf == 'update_mf') {
            if (isset($params->get('cdb')['regular_methods'])) {
                if ($params->getUrlParamValue('maintenance_mode')) {
                    if (isset($params->get('cdb')['regular_methods'][$keyMf])) {
                        $readMethod = $params->get('cdb')['regular_methods'][$keyMf];
                    }
                } else {
                    if (isset($params->get('cdb')['regular_methods'][$key])) {
                        $readMethod = $params->get('cdb')['regular_methods'][$key];
                    }
                }
            }
        } else {
            if (isset($params->get('cdb')['regular_methods'])) {
                if ($params->getUrlParamValue('maintenance_mode')) {
                    if (isset($params->get('cdb')['regular_methods'][$keyMf])) {
                        $readMode = 'read_mf';
                    }
                } else {
                    if (isset($params->get('cdb')['regular_methods'][$key])) {
                        $readMode = 'read';
                    }
                }
            }
            if (! isset($params->get('cdb')['regular_methods'][$readMode]) || ! isset($params->get('cdb')['regular_methods'][$readMode]['name']) || ! isset($params->get('cdb')['regular_methods'][$readMode]['idParam']) || ! isset($params->get('cdb')['regular_methods'][$readMode]['response'])) {
                throw new CDBException('configuration_error', 500);
            } else {
                $readMethod = $params->get('cdb')['regular_methods'][$readMode];
            }
        }

        return $readMethod;
    }

    /**
     * Build the URL
     */
    private function buildUrl($method)
    {
        if ($this->debug) {
            $url = $method['name'];
        } else {
            $url = (! empty($this->sessionID)) ? $method['name'] . '?' . $method['idParam'] . '=' . $this->sessionID : '';
        }

        return $url;
    }

    /**
     * Load the data of the dropDown fields
     */
    private function loadDropdownsData()
    {
        $params          = Parameters::getInstance();
        $dropDownMethods = $params->get('cdb')['dropdown_methods'];
        foreach ($dropDownMethods as $method) {
            $this->getDropdownData($method);
        }
    }

    /**
     * Load the data of a single dropDown field
     *
     * @param $method
     *
     * @throws \CDBException
     */
    private function getDropdownData($method)
    {
        if ($response = $this->getData($method['method'])) {
            $response = $response[$method['data']];
            if (! is_array($response)) {
                $response = json_decode($response, true);
            }
            // Combined response (more than one dropdown)
            if (is_array($response) && count($response) && isset($response[0]['Name'])) {
                $this->getCombinedDropdown($response);
                // Single dropDown
            } else {
                $this->getSingleDropdown($method, $response);
            }
        }
    }

    /**
     * Retrieve a combined dropDown
     *
     * @param $response
     */
    private function getCombinedDropdown($response)
    {
        foreach ($response as $field) {
            if (($key = array_search($field['Name'], $this->cdbMap)) !== false) {
                $values = $field['Values'];
                if (isset($this->fields[$key])) {
                    $this->dropdowns[$key]['selected'] = $this->fields[$key];
                }
                $this->dropdowns[$key]['values'] = $values;
            }
        }
    }

    /**
     * Retrieve a single dropDown (i.e. countries)
     *
     * @param $method
     * @param $response
     */
    private function getSingleDropdown($method, $response)
    {
        $fieldNameArray = $method['fields'];
        $values         = $response;
        foreach ($fieldNameArray as $fieldName) {
            if (isset($this->fields[$fieldName])) {
                $this->dropdowns[$fieldName]['selected'] = $this->fields[$fieldName];
            }
            $this->dropdowns[$fieldName]['values'] = $values;
        }
    }

    /**
     * Execute a service and retrieve the data
     *
     * @param $url
     *
     * @return array|null
     *
     * @throws \CDBException
     */
    private function getData($url)
    {
        $resource = $this->host . $this->port . $this->resource . $url;
        $response = null;
        if ($content = @file_get_contents($resource)) {
            $response = json_decode($content, true);
            if (! $this->debug && intval($response['returnCode']) !== 1) {
                throw new CDBException($response['returnMessage'], $response['returnCode']);
            }
        } else {
            throw new CDBException('resource_not_found', 404);
        }

        return $response;
    }

    /**
     * Update CDB User
     *
     * @param array $data
     */
    public function updateData($data)
    {
        $this->setData($data);
    }

    /**
     * Send the data to the CDB
     *
     * @param $parameters
     */
    /*
        private function setData($parameters)
        {
            $updateMethod = $this->getMethod('update', 'update_mf');
            $url          = $this->host . $this->port . $this->resource . $updateMethod;
            $ch           = curl_init($url);
            curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
            //curl_setopt($ch, CURLOPT_POST, true);
            curl_setopt($ch, CURLOPT_POSTFIELDS, $parameters);
            $server_output = curl_exec($ch);
            curl_close($ch);
        }
    */
    /**
     * @param string $parameters
     *
     * @throws \CDBException
     */
    private function setData($parameters)
    {
        $updateMethod = $this->getMethod('update', 'update_mf');
        $url          = $this->host . $this->port . $this->resource . $updateMethod . '?' . http_build_query($parameters);
        $ch           = curl_init($url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        $server_output = curl_exec($ch);
        $this->processResponse($server_output);
        curl_close($ch);
    }

    /**
     * Process the response of the CDB
     *
     * @param $response
     */
    private function processResponse($response)
    {
        if ($processedResponse = json_decode($response, true)) {
            if (isset($processedResponse['newId']) && $processedResponse['newId']) {
                $params = Parameters::getInstance();
                $params->setUrlParamValue('session_id', $processedResponse['newId']);
                $params->setUrlParamValue('no_session_id', false);
            }
        }
    }
}
