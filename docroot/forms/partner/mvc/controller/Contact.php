<?php
/**
 * Contact.php
 * Controller for the Contact form
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Contact extends Controller implements IController, IForm {
    /**
     * Class constructor
     * @param bool $directOutput
     */
    public function __construct($directOutput = true) {
        $this->directOutput = $directOutput;
        $this->model = new ContactObject();
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
        $this->load();
        $params = Parameters::getInstance();
        // Build the progressbar and the sidebar
        $sections = array(
            'PRIMARY_CONTACT' => 'Your Primary Contact',
        );
        $sidebar  = new Sidebar(false, $sections);
        $sidebarContent = $sidebar->execute();
        $progressbar = new Progressbar(false, 100);
        $progressbarContent = $progressbar->execute();
        $renderer = new Renderer(__CLASS__);
        $contentArray = array(
            'appurl' => APP_URL . '?route=' . $params->get('route'),
            'title' => $params->get('title'),
            'sidebar' => $sidebarContent,
            'progressbar' => $progressbarContent,
            'attributes' => $this->model->getAttributesValues(),
            'session_id' => $params->getUrlParamValue('session_id'),
            'mf' => $params->getUrlParamValue('manteinance_mode'),
            'disabled' => '',
        );
        if ($params->get('action') == 'pdf') {
            $contentArray['pdf'] = true;
            $content = $renderer->render($contentArray);
            $this->pdf($content, __CLASS__);
        } else {
            if ($params->get('action') == 'print') {
                $contentArray['print'] = true;
                $contentArray['disabled'] = ' disabled="disabled" ';
            }
            $content = $renderer->render($contentArray);
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
        $params = Parameters::getInstance();
        if ($sessionId = $params->getUrlParamValue('session_id')) {
            $_SESSION['session_id'] = $sessionId;
            $params->set('session_id', $sessionId);
            $this->model->load($sessionId);
        }
        if ($mf = $params->getUrlParamValue('manteinance_mode')) {
            $_SESSION['mf'] = $mf;
            $params->set('mf', $mf);
        }
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
        $this->model->saveSession();
        header('Location: ' . APP_URL . '?route=' . Congrats::getName());
        exit;
    }
}
