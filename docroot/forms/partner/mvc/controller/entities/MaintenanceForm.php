<?php
/**
 * MaintenanceForm.php
 * Controller for the Maintenance form
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class MaintenanceForm extends Controller implements IController, IForm {
    /**
     * Class constructor
     *
     * @param bool $directOutput
     */
    public function __construct($directOutput = true) {
        $this->directOutput = $directOutput;
    }

    /**
     * Retrieve the class name
     * @return string
     */
    public static function getName() {
        return strtolower(__CLASS__);
    }

    /**
     * Retrieve the entity name
     * @param $entity
     * @return string
     */
    public function getEntityName($entity) {
        $params = Parameters::getInstance();
        $entity = strtolower($params->getUrlParamValue('entity') . '_' . $entity);

        return $entity;
    }

    /**
     * Execute the controller
     * @return string
     * @throws OshException
     */
    public function execute() {
        // Load the bundle
        $params = Parameters::getInstance();
        $entities = false;
        if ($bundleData = File::read(APP_ROOT . $params->get('bundlesPath') . $params->get('route'))) {
            if ($bundle = json_decode($bundleData, true)) {
                $entities = (isset($bundle['entities'])) ? $bundle['entities'] : false;
            }
        }
        if (!$entities) {
            throw new OshException('bad_config', 500);
        }
        // Browse the entities of the bundle, call a new Model each time and collect the rendered body
        $content = '';
        $renderer = new Renderer('', false);
        foreach ($entities as $entity) {
            $this->model = new Model($this->getEntityName($entity));
            $this->load();
            // Build the form
            $renderer->setView($this->getEntityName($entity));
            $renderer->setViewPath($params->get('viewEntitiesPath'));
            $contentArray = array(
                'appurl' => APP_URL . '?route=' . $params->get('route'),
                'title' => $params->get('title'),
                'attributes' => $this->transformAttributes(),
                'session_id' => $params->getUrlParamValue('session_id'),
                'mf' => true,
                'disabled' => '',
            );
            $content .= $renderer->render($contentArray);
        }
        // Render the bundle
        $sidebar  = new Sidebar(false);
        $sidebarContent = $sidebar->execute();
        $renderer->setView($this->getName());
        $renderer->setIncludeHeaderFooter(true);
        $contentArray = array(
            'appurl' => APP_URL . '?route=' . $params->get('route'),
            'title' => $params->get('title'),
            'sidebar' => $sidebarContent,
            'content' => $content,
            'session_id' => $params->getUrlParamValue('session_id'),
            'mf' => true,
            'printable' => $this->isPrintable(),
            'submit_text' => 'Submit',
            'disabled' => '',
        );
        // PDF version
        if ($params->get('action') == 'pdf') {
            $content = $renderer->render($contentArray);
            $this->downloadPdf($content, __CLASS__);
        }
        // Content rendering
        $content = $renderer->render($contentArray);
        //print $content;die;
        if ($this->directOutput) {
            print $content;
        } else {
            return $content;
        }
    }

    /**
     * Send action
     */
    public function send() {
        $this->model = new Model('');
        $params = Parameters::getInstance();
        if ($bundleData = File::read(APP_ROOT . $params->get('bundlesPath') . $params->get('defaultBundle'))) {
            if ($bundle = json_decode($bundleData, true)) {
                $entities = (isset($bundle['entities'])) ? $bundle['entities'] : false;
                if ($entities) {
                    $mapping = array();
                    foreach ($entities as $entity) {
                        $entity = strtolower($params->getUrlParamValue('entity') . '_' . ucfirst($entity));
                        $this->model->setEntity($entity);
                        $this->save();
                        $this->model->load();
                        $attributes = $this->model->getAttributes();
                        foreach ($attributes as $attr) {
                            $cdbName = $this->model->getTranslation($attr);
                            $mapping[$cdbName] = $this->getValue($attr);
                        }
                    }
                    array_filter($mapping);
                    $paramRequest = $this->getBuiltURL($mapping);
                    $this->model->saveToCDB($paramRequest);
                }
            }
        }
        $route     = $params->get('route');
        $nextRoute = isset($params->get('routes')[$route]['next']) ? $params->get('routes')[$route]['next'] : '';
        header('Location: ' . APP_URL . '?route=' . $nextRoute);
        exit;
    }
}