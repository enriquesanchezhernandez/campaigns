<?php
/**
 * Dispatcher.php
 * Front controller
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Dispatcher {
    /**
     * Route the execution
     */
    public function dispatch() {
        // Check the session ID
        $sessionID = $this->checkSessionID();
        // Set the route
        $route = $this->setRoute();
        if (class_exists($route) || class_exists(ucfirst(($route)))) {
            try {
                // Set the current partner category
                CDB::getInstance(null, $sessionID);
                // Execute the controller
                $controller = new $route();
                if (method_exists($controller, 'executeAction')) {
                    $controller->executeAction();
                }
                $controller->execute();
            } catch (CDBException $e) {
                print $e->getMessage();
            } catch (Exception $e) {
                print $e->getMessage();
            }
        }
    }

    /**
     * Check the session ID and retrieve it if defined
     * @return bool|string
     */
    private function checkSessionID() {
        // Check if session ID is defined
        $params = Parameters::getInstance();
        if ($params->get('cdb')['debug'] == 'true') {
            if (!$ret = $params->getUrlParamValue('session_id')) {
                $ret = uniqid();
                $params->setUrlParamValue('session_id', $ret, true);
            }
        } else {
            if (!$params->getUrlParamValue('session_id')) {
                $errorMessage = isset($params->get('errorMessages')['session_not_defined']) ?
                    $params->get('errorMessages')['session_not_defined'] : 'Fatal system error';
                print $errorMessage;
                die;
            }
            $ret = $params->getUrlParamValue('session_id');
        }
        return $ret;
    }

    /**
     * Set the route
     * @return bool
     */
    private function setRoute() {
        // Maintenance mode
        $params = Parameters::getInstance();
        if ($params->getUrlParamValue('maintenance_mode')) {
            $params->setUrlParamValue('maintenance_mode', true);
            $route = $params->get('maintenanceRoute');
            $params->set('route', $route);
        // Regular controller
        } else {
            $route = $this->getParamValue('route', 'defaultRoute');
        }
        return $route;
    }

    /**
     * Get a param value (with default if not defined)
     * @param $key
     * @param $defaultKey
     * @return bool
     */
    private function getParamValue($key, $defaultKey) {
        $params = Parameters::getInstance();
        if ($params->get($key)) {
            $value = strtolower($params->get($key));
        } else {
            $value = strtolower($params->get($defaultKey));
        }
        $params->set($key, $value);
        return $value;
    }
}