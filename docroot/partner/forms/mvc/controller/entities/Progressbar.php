<?php

/**
 * Progressbar.php
 * Controller for the progress bar
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Progressbar extends Controller implements IController {
    /* @var $step int Current step */
    private $currentStep;

    /**
     * Class controller
     * @param bool $directOutput
     */
    public function __construct($directOutput = false) {
        $this->directOutput = $directOutput;
        $params = Parameters::getInstance();
        $routes = $params->get('routes');
        $currentRoute = $params->get('route');
        $this->currentStep = isset($routes[$currentRoute]['index']) ? $routes[$currentRoute]['index'] : 1;
        //Mostramos el progressbar relleno en la vista de congrats
        if($currentRoute=="congrats"){
            $this->currentStep = 3;
        }
    }

    /**
     * Retrieve the class name
     * @return string
     */
    public static function getName() {
        return strtolower(__CLASS__);
    }

    /**
     * Execute the controller
     */
    public function execute() {
        $params = Parameters::getInstance();
        $renderer = new Renderer('progressbar', false);
        $renderer->setViewPath($params->get('viewEntitiesPath'));
        $routes = $params->get('routes');
        if (is_array($routes) && count($routes) > 0) {
            $contentArray = array(
                'appurl' => APP_URL,
                'title' => $params->get('title'),
                'currentStep' => $this->currentStep,
                'current_Route' => $this->recuperaPrincipal($routes),
                'steps' => $routes,
                'totalSteps' => count($routes),
            );
            $content = $renderer->render($contentArray);
            if ($this->directOutput) {
                print $content;
            } else {
                return $content;
            }
        }
    }
    
    private function recuperaPrincipal($routes){
        foreach ($routes as $route) {
            if($route['index'] == $this->currentStep){
                return $route['internal'];
            }
        }
    }
}