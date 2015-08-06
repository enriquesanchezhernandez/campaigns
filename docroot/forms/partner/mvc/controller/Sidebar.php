<?php
/**
 * Sidebar.php
 * Controller for the sidebar
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Sidebar extends Controller implements IController {
    /**
     * @var array Form sections
     */
    private $sections;

    /**
     * Class controller
     * @param bool $directOutput
     */
    public function __construct($directOutput = false, $sections = false) {
        $this->directOutput = $directOutput;
        $this->sections = $sections;
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
        $renderer = new Renderer('sidebar', false);
        $contentArray = array(
            'appurl' => APP_URL . '?route=' . $params->get('route'),
            'title' => $params->get('title'),
            'sections' => $this->sections,
            'session_id' => $params->getUrlParamValue('session_id'),
        );
        $content = $renderer->render($contentArray);
        if ($this->directOutput) {
            print $content;
        } else {
            return $content;
        }
    }
}