<?php

/**
 * Progressbar.php
 * Controller for the progress bar
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Progressbar extends Controller implements IController
{
    /* @var $percentage int Completion Percentage */
    private $percentage;
    /**
     * Class controller
     *
     * @param bool $directOutput
     */
    public function __construct($directOutput = false, $percentage)
    {
        $this->directOutput = $directOutput;
        $this->percentage   = $percentage;
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
        $contentArray = array(
            'appurl'     => APP_URL . '?route=' . $params->get('route'),
            'title'      => $params->get('title'),
            'percentage' => $this->percentage
        );
        $content      = $renderer->render($contentArray);
        if ($this->directOutput) {
            print $content;
        } else {
            return $content;
        }
    }
}