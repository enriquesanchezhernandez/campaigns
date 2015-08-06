<?php

/**
 * Dispatcher.php
 * Front controller
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Dispatcher
{
    /**
     * Route the execution
     */
    public function dispatch()
    {
        $params = Parameters::getInstance();
        if ($params->get('route')) {
            $route = $params->get('route');
        } else {
            $route = $params->get('defaultRoute');
            $params->set('route', $route);
        }
        if (class_exists($route) || class_exists(ucfirst(($route)))) {
            try {
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
}