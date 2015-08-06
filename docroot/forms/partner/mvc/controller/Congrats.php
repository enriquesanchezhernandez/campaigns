<?php
/**
 * Class Congrats
 * @author Joaquin Rua <joaquin.rua.conde@everis.com>
 * @version 1.0
 */
class Congrats extends Controller implements IController, IForm {
    /**
     * Class constructor
     * @param bool $directOutput
     */
    public function __construct($directOutput = true) {
        $this->directOutput = $directOutput;
        $this->model = new CongratsObject();
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
        $renderer = new Renderer(__CLASS__);
        $contentArray = array(
            'appurl' => APP_URL . '?route=' . $params->get('route'),
            'title' => $params->get('title'),
            'attributes' => $this->model->getAttributesValues(),
        );
        $content = $renderer->render($contentArray);
        if ($params->get('action') == 'pdf') {
            $this->pdf($content, __CLASS__);
        } else {
            if ($this->directOutput) {
                print $content;
            } else {
                return $content;
            }
        }
    }

    /**
     * Load an entity
     */
    public function load() {
    }

    /**
     * Save action
     */
    public function save() {
        // TODO: Implement save() method.
    }

    /**
     * Send action
     */
    public function send() {
        // TODO: Implement send() method.
        header('Location: ' . APP_URL);
        exit;
    }
}