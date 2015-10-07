<?php

/**
 * Controller.php
 * Abstract class for controllers
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
abstract class Controller
{
    /**
     * @var Model object
     */
    protected $model;
    /**
     * @var Direct output or return
     */
    protected $directOutput;

    /**
     * Execute an action defined in the specific controller
     */
    public function executeAction()
    {
        $params = Parameters::getInstance();
        $action = $params->get('action');
        if (method_exists($this, $action)) {
            $this->$action();
        }
    }

    /**
     * Execute the controller
     */
    public function execute()
    {
        // Load the entity
        $this->load();
        $params = Parameters::getInstance();
        // Build the progressbar and the sidebar
        $sidebar = new Sidebar(false);
        $sidebarContent = $sidebar->execute();
        $progressbar = new Progressbar(false);
        $progressbarContent = $progressbar->execute();
        // Build the form
        $route = $params->get('route');
        $submitText = isset($params->get('routes')[$route]['submitText']) ? $params->get('routes')[$route]['submitText'] : 'Next';
        $isPrintable = $this->isPrintable();
        $renderer = new Renderer($this->getEntityName());
        $renderer->setViewPath($params->get('viewEntitiesPath'));
        $contentArray = array(
            'appurl' => APP_URL . '?route=' . $params->get('route'),
            'title' => $params->get('title'),
            'nonce' => $params->get('nonce'),
            'sidebar' => $sidebarContent,
            'progressbar' => $progressbarContent,
            'attributes' => $this->transformAttributes(),
            'session_id' => $params->getUrlParamValue('session_id'),
            'mf' => $params->get('maintenance_mode'),
            'partner_type' => $params->getUrlParamValue('partner_type'),
            'submit_text' => $submitText,
            'printable' => $isPrintable,
            'show_print_version' => $params->get('print'),
            'show_pdf_version' => $params->get('pdf'),
            'locked' => $params->getUrlParamValue('locked'),
            'actionType' => $params->get('actionType'),
            'disabled' => '',
        );
        // PDF version
        if ($isPrintable) {
            $route = $params->get('route');
            $params->set('route', 'MaintenanceForm');
            $maintenanceForm = new MaintenanceForm(false);
            $content = $maintenanceForm->execute();
            $params->set('route', $route);
        } else {
            // Content rendering
            $content = $renderer->render($contentArray);
        }
        if ($this->directOutput) {
            print $content;
        } else {
            return $content;
        }
    }

    /**
     * Load an entity
     */
    public function load()
    {
        $params = Parameters::getInstance();
        if ($sessionID = $params->getUrlParamValue('session_id')) {
            $params->setUrlParamValue('session_id', $sessionID);
        }
        if ($mf = $params->get('maintenance_mode')) {
            $params->setUrlParamValue('maintenance_mode', $mf);
        }
        $this->model->load($sessionID);
    }

    /**
     * Determine whether the form is in printable mode or not
     * @return bool|string
     */
    protected function isPrintable()
    {
        $params = Parameters::getInstance();
        if ($params->get('action') == 'pdf' || $params->get('action') == 'printable') {
            $ret = ($params->get('action') == 'pdf') ? 'pdf' : 'printable';
        } else {
            $ret = false;
        }
        return $ret;
    }

    /**
     * Transform the attributes depending on its type of control
     * @return array
     */
    protected function transformAttributes()
    {
        $transformedAttributes = array();
        $params = Parameters::getInstance();
        $attributes = $this->model->getAttributes();
        $nonce = $params->get('nonce');
        foreach ($attributes as $id => $attribute) {
            if ($attribute->getName()) {
                // Render the attribute widget
                //$disabled = $params->getUrlParamValue('partner_type') == 'current' ? 'disabled' : '';
                $disabled = $params->getUrlParamValue('locked') ? 'disabled' : '';
                if (is_array(($attribute->getValidator()))) {
                    foreach ($attribute->getValidator() as $validator) {
                        $required = ($validator == Validator::VALIDATION_NOTNULL) ? 'required' : '';
                    }
                } else {
                    $required = ($attribute->getValidator() == Validator::VALIDATION_NOTNULL) ? 'required' : '';
                }

                if ($attribute->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                    $data = $attribute->getValue();
                    foreach ($data as $countryKey => $countryValue) {
                        if (is_array($attribute->getSelectedValues())) {
                            $selected = in_array($countryValue, $attribute->getSelectedValues());
                        } else {
                            $selected = $countryValue == $attribute->getSelectedValues();
                        }
                        $countries[] = array(
                            'id' => $countryKey,
                            'name' => $countryValue,
                            'selected' => $selected,
                        );
                    }
                    $countriesProcessed = array('values' => $countries);
                    $attribute->setValue($countriesProcessed);
                }

                $attributeContentArray = array(
                    'appurl' => APP_URL,
                    'nonce' => $nonce,
                    'fieldName' => $attribute->getName(),
                    'fieldLabel' => $attribute->getLabel(),
                    'fieldPlaceholder' => $attribute->getPlaceholder(),
                    'fieldPublicProfile' => $attribute->getPublicProfile(),
                    'fieldHelpText' => $attribute->getHelpText(),
                    'fieldSection' => $attribute->getSection(),
                    'fieldValue' => $attribute->getValue(),
                    'selectedValue' => $attribute->getSelectedValues(),
                    'required' => $required,
                    'locked' => $params->getUrlParamValue('locked'),
                    'disabled' => $disabled,
                );
                $attributeRendered = $this->renderWidget($attribute->getType(), $attributeContentArray);
                $transformedAttributes[$attribute->getName()] = $attributeRendered;
            }
        }
        return $transformedAttributes;
    }

    /**
     * Render a widget
     * @param $view
     * @param $contentArray
     * @return string
     */
    private function renderWidget($view, $contentArray)
    {
        $params = Parameters::getInstance();
        if ($this->isPrintable()) {
            if ($view == 'image') {
                $contentArray['image'] = true;
            }
            $view = $params->get('printableTpl');
        }
        $renderer = new Renderer('', false);
        $renderer->setViewPath($params->get('widgetsPath'));
        $renderer->setView($view);
        $content = $renderer->render($contentArray);
        return $content;
    }

    /**
     * Save action
     */
    public function save()
    {
        $this->saveToSession();
        // Perform the send to CDB
        $params = Parameters::getInstance();
        if (!$params->get('print') && !$params->get('pdf')) {
            $this->send(true);
        }
    }

    /**
     * Save the data into session
     */
    private function saveToSession()
    {
        $this->load();
        $params = Parameters::getInstance();
        $attributes = $this->model->getAttributes();
        if ($attributes) {
            foreach ($attributes as $attribute) {
                $name = $attribute->getName();
                if ($value = $params->get($name)) {
                    if ($attribute->getType() == Attribute::TYPE_DROPDOWN ||
                        $attribute->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE
                    ) {
                        if (intval($attribute->getSelectedValues()) === -1) {
                            $attribute->setSelectedValues(null);
                        } else {
                            $attribute->setSelectedValues($value);
                        }
                    } else {
                        $attribute->setValue($value);
                    }
                    $this->model->setWholeAttribute($attribute);
                }
            }
            $this->model->saveSession();
        }
    }

    /**
     * Save and Send action
     * @param bool $save
     * @param bool $updateMF
     */
    public function send($save = false, $updateMF = false)
    {
        if (!$save) {
            $this->saveToSession();
        }
        $params = Parameters::getInstance();
        if ($bundleData = File::read(APP_ROOT . $params->get('bundlesPath') . $params->get('defaultBundle'))) {
            if ($bundle = json_decode($bundleData, true)) {
                $entities = (isset($bundle['entities'])) ? $bundle['entities'] : false;
                if ($entities) {
                    $mapping = array();
                    $currentRoute = $params->get('route');
                    $currentModel = $this->model;
                    foreach ($entities as $entity) {
                        $this->model = new Model(strtolower($params->getUrlParamValue('entity') . '_' . ucfirst($entity)));
                        if ($updateMF) {
                            $this->model->setCdbMap(true);
                        }
                        $params->set('route', $entity);
                        $this->model->load();
                        $this->saveToSession();
                        $attributes = $this->model->getAttributes();
                        foreach ($attributes as $attr) {
                            $cdbName = $this->model->getTranslation($attr);
                            if ($cdbName) {
                                if ($attr->getType() == Attribute::TYPE_IMAGE) {
                                    //                                $image             = $attr->getValue();
                                    //                                $mapping[$cdbName] = $image['content'];
                                } else if ($attr->getType() == Attribute::TYPE_RADIO ||
                                    $attr->getType() == Attribute::TYPE_CHECKBOX
                                ) {
                                    $mapping[$cdbName] = (strtolower($attr->getValue()) == 'on' || strtolower($attr->getValue()) == 'yes') ? 'true' : 'false';
                                } elseif ($attr->getType() == Attribute::TYPE_DROPDOWN || $attr->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                                    $mapping[$cdbName] = $attr->getSelectedValues();
                                } else {
                                    $mapping[$cdbName] = $attr->getValue();
                                }
                            }
                        }
                    }

                    $params->set('route', $currentRoute);
                    $this->model = $currentModel;
                    $type = $save || $params->get('actionType') == 'next' ? 'save' : 'submit';
                    $paramRequest = $this->getBuiltURL($mapping, $type);
                    $this->model->saveToCDB($paramRequest);
                }
            }
        }
        if (!$save) {
            $route = $params->get('route');
            $nextRoute = isset($params->get('routes')[$route]['next']) ? $params->get('routes')[$route]['next'] : '';
            header('Location: ' . APP_URL . '?route=' . $nextRoute);
            exit;
        }
    }

    /**
     * Return the formed URL request data for the update method of CDB
     *  * @TODO: set the delimiter data in cdb.json and acces it generically through params:
     *      field delimiter: ','
     *      value delimiter: '|'
     *      enclosure start tag: '('
     *      enclosure end  tag: ')'
     *      fields delimiter: '&'
     *      etc
     *
     * @param array $fields
     * @param string $type
     *
     * @return array
     */
    protected function getBuiltURL(array $fields, $type)
    {
        $params = Parameters::getInstance();
        $updatedValues = '';
        $countries = '';
        $otherUsers = '';
        foreach ($fields as $key => $value) {
            // @FIXME remove this hack to send the images again
            if (empty($value) || strpos($key, 'image') !== false) {
                continue;
            }
            // @FIXME remove this hack to send contact fields again
            if (strpos($key, 'maincontact') !== false) {
                continue;
            }
            if (strpos($key, 'category') !== false || strpos($key, 'leads') !== false) {
                // Don't send neither category and osh_leads field.
                continue;
            } elseif (is_array($value)) {
                // Countries of Activities dropdown
                $countries .= implode(',', array_keys($value));
            } elseif (strpos($value, 'otheruser') === false) {
                //Normal fields
                if (isset($value)) {
                    $updatedValues .= '(' . $key . '|' . $value . '),';
                }
            } else {
                // Other Users
                $otherUsers .= '(' . $key . '|' . $value . '),';
            }
        }
        // $result .= ! empty ($updatedValues) ? 'id=' . $params->get('session_id') . '&option=SUBMIT&fields=' . substr($updatedValues, 0, -1) : '';
        //        $result = ! empty ($otherUsers) ? $result . 'otherusers=' . substr($updatedValues, 0, -1) : substr($result, 0, -1);
        $result = array(
            'id' => $params->get('session_id'),
            'fields' => substr($updatedValues, 0, -1)
        );
        if ($params->getUrlParamValue('no_session_id')) {
            unset($result['id']);
        }

        if (!empty($countries)) {
            $result['paises'] = $countries;
        }

        if (!$params->getUrlParamValue('maintenance_mode')) {
            $result['option'] = ($type == 'submit') ? 'SUBMIT' : 'SAVE';
        } else {
            $result['option'] = 'SUBMIT';
        }

        return $result;
    }

    /**
     * Function validateAttribute
     *
     * @return bool
     */
    protected function validateAttribute()
    {
        $ret = true;
        if ($this->model) {
            $param = Parameters::getInstance();
            $attribute = $param->get('attribute');
            $value = $param->get('value');
            $this->model->set($attribute, $value);
            $ret = $this->model->validate($attribute);
        }
        if ($param->get('ajax')) {
            $messageBus = MessageBus::getInstance();
            $response = array(
                'status' => $ret,
                'id' => $attribute,
                'message' => $messageBus->getMessage($attribute),
            );
            print json_encode($response);
            die;
        } else {
            return $ret;
        }
    }

    /**
     * Download a PDF file
     * @param string $content
     * @param string $controller
     */
    protected function downloadPdf($content = '', $controller = '')
    {
        if (!empty($content)) {
            $params = Parameters::getInstance();
            $pdf = new Pdf();
            $path = $pdf->render($content);
            File::download($params->get('pdfFilename') . '-' . date('d-m-Y_H-i'), $path, 'application/pdf');
            die;
        }
    }

    /**
     * Get Value based on type.
     *
     * @param Attribute $attribute
     * @return array|bool|null|string
     */
    protected function getValue(Attribute $attribute)
    {
        switch ($attribute->getType()) {
            case 'dropdown':
            case 'dropdown_multiple':
                return $attribute->getSelectedValues();
                break;
            case 'radio':
                return $attribute->getValue() === 'Yes' ? true : $attribute->getValue() === 'No' ? false : null;
                break;
            case 'checkbox':
                return $attribute->getValue() !== null ? (bool)$attribute->getValue() : null;
                break;
            case 'image':
                return $attribute->getValue() ? base64_encode($attribute->getValue()['content']) : '';
                break;
            default:
                // Rest: text, textarea
                return ($attribute->getValue() !== null) && (trim($attribute->getValue()) !== '') ? strval($attribute->getValue()) : null;
                break;
        }
    }
}