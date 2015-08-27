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
        $this->model = new Model($this->getEntityName());
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
     * @return string
     */
    public function getEntityName() {
        $params = Parameters::getInstance();
        $entity = strtolower($params->getUrlParamValue('entity') . '_' . __CLASS__);
        return $entity;
    }

    /**
     * Send action
     * @TODO ERROR TRTEATMENT
     */
    public function send() {
        $this->save();
        $params   = Parameters::getInstance();
        if ($bundleData = File::read(APP_ROOT . $params->get('bundlesPath') . $params->get('defaultBundle'))) {
            if ($bundle = json_decode($bundleData, true)) {
                $entities = (isset($bundle['entities'])) ? $bundle['entities'] : false;
                if ($entities) {
                    $mapping = array();
                    foreach ($entities as $entity) {
                        $entity = strtolower($params->getUrlParamValue('entity') . '_' . ucfirst($entity));
                        $model = new Model($entity);
                        $model->load();
                        $attributes = $model->getAttributes();
                        foreach ($attributes as $attr) {
                            $cdbName = $model->getTranslation($attr);
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
