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
        $params = Parameters::getInstance();
        $this->model = new Model(strtolower($params->getUrlParamValue('entity')));
        $params = Parameters::getInstance();
        $params->set('actionType', 'submit');
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
            $this->model = new Model(strtolower($params->getUrlParamValue('entity') . '_' . ucfirst($entity)));
            $params->set('route', $entity);
            $this->load();
            // Build the form
            $renderer->setView($this->getEntityName($entity));
            $renderer->setViewPath($params->get('viewEntitiesPath'));
            $contentArray = array(
                'appurl' => APP_URL . '?route=' . $params->get('route'),
                'title' => $params->get('title'),
                'attributes' => $this->transformAttributes(),
                'session_id' => $params->getUrlParamValue('session_id'),
                'locked' => $params->getUrlParamValue('locked'),
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
            'nonce' => $params->get('nonce'),
            'sidebar' => $sidebarContent,
            'content' => $content,
            'session_id' => $params->getUrlParamValue('session_id'),
            'mf' => true,
            'printable' => $this->isPrintable(),
            'show_print_version' => $params->get('print'),
            'show_pdf_version' => $params->get('pdf'),
            'submit_text' => 'Submit',
            'actionType' => $params->get('actionType'),
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
     * Function validateAttribute
     *
     * @return bool
     */
    protected function validateAttribute() {
        $params = Parameters::getInstance();
        if ($bundleData = File::read(APP_ROOT . $params->get('bundlesPath') . $params->get('defaultBundle'))) {
            if ($bundle = json_decode($bundleData, true)) {
                $entities = (isset($bundle['entities'])) ? $bundle['entities'] : false;
                if ($entities) {
                    $model = new Model('');
                    foreach ($entities as $entity) {
                        $entity = strtolower($params->getUrlParamValue('entity') . '_' . ucfirst($entity));
                        $model->setEntity($entity);
                        $model->load();
                        $attribute = $params->get('attribute');
                        $value     = $params->get('value');
                        $model->set($attribute, $value);
                        $ret = $model->validate($attribute);
                        if ($params->get('ajax')) {
                            $messageBus = MessageBus::getInstance();
                            $response   = array(
                                'status'  => $ret,
                                'id'      => $attribute,
                                'message' => $messageBus->getMessage($attribute),
                            );
                            print json_encode($response);
                            die;
                        } else {
                            return $ret;
                        }
                    }
                }
            }
        }
    }

    /**
     * Save action
     */
    public function save() {
        $params = Parameters::getInstance();
        if ($bundleData = File::read(APP_ROOT . $params->get('bundlesPath') . $params->get('defaultBundle'))) {
            if ($bundle = json_decode($bundleData, true)) {
                $entities = (isset($bundle['entities'])) ? $bundle['entities'] : false;
                if ($entities) {
                    $model = new Model('');
                    foreach ($entities as $entity) {
                        $entity = strtolower($params->getUrlParamValue('entity') . '_' . ucfirst($entity));
                        $model->setEntity($entity);
                        $model->load();
                        $attributes = $model->getAttributes();
                        foreach ($attributes as $attribute) {
                            $name = $attribute->getName();
                            if ($value = $params->get($name)) {
                                if ($attribute->getType() == Attribute::TYPE_DROPDOWN ||
                                    $attribute->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                                    $attribute->setSelectedValues($value);
                                } else {
                                    $attribute->setValue($value);
                                }
                                $model->setWholeAttribute($attribute);
                            }
                        }
                        $model->saveSession();
                    }
                    // Perform the send to CDB
                    if (! $params->get('print') && ! $params->get('pdf')) {
                        $this->send(true, true);
                    }
                }
            }
        }
    }

    /**
     * Send action
     *
     * @param string $type
     */
/*
    public function send($type = 'submit') {
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
                    $paramRequest = $this->getBuiltURL($mapping, $type);
                    $this->model->saveToCDB($paramRequest);
                }
            }
        }
        $route     = $params->get('route');
        $nextRoute = isset($params->get('routes')[$route]['next']) ? $params->get('routes')[$route]['next'] : '';
        header('Location: ' . APP_URL . '?route=' . $nextRoute);
        exit;
    }
*/
}