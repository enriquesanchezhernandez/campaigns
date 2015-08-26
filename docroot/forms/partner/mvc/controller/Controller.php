<?php
/**
 * Controller.php
 * Abstract class for controllers
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
abstract class Controller {
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
    public function executeAction() {
        $params = Parameters::getInstance();
        $action  = $params->get('action');
        if (method_exists($this, $action)) {
            $this->$action();
        }
    }

    /**
     * Execute the controller
     */
    public function execute() {
        // Load the entity
        $this->load();
        $params = Parameters::getInstance();
        // Build the progressbar and the sidebar
        $sidebar  = new Sidebar(false);
        $sidebarContent = $sidebar->execute();
        $progressbar = new Progressbar(false);
        $progressbarContent = $progressbar->execute();
        // Build the form
        $route = $params->get('route');
        $submitText = isset($params->get('routes')[$route]['submitText']) ?
            $params->get('routes')[$route]['submitText'] : 'Next';
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
            'mf' => $params->getUrlParamValue('maintenance_mode'),
            'partner_type' => $params->getUrlParamValue('partner_type'),
            'submit_text' => $submitText,
            'printable' => $isPrintable,
            'locked' => $params->getUrlParamValue('locked'),
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
    public function load() {
        $params = Parameters::getInstance();
        if ($sessionID = $params->getUrlParamValue('session_id')) {
            $params->set($params->getUrlParamValue('session_id'), $sessionID, true);
        }
        if ($mf = $params->getUrlParamValue('maintenance_mode')) {
            $params->set($params->getUrlParamValue('maintenance_mode'), $mf, true);
        }
        $this->model->load($sessionID);
    }

    /**
     * Attributes validation
     */
    protected function validateAttribute() {
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
            //die;
        } else {
            return $ret;
        }
    }

    /**
     * Download a PDF file
     * @param string $content
     * @param string $controller
     */
    protected function downloadPdf($content = '', $controller = '') {
        if (!empty($content)) {
            $params = Parameters::getInstance();
            $pdf = new Pdf();
            $path = $pdf->render($content);
            File::download($params->get('pdfFilename') . '-' . date('d-m-Y_H-i'), $path, 'application/pdf');
            die;
        }
    }

    /**
     * Transform the attributes depending on its type of control
     * @return array
     */
    protected function transformAttributes() {
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
    private function renderWidget($view, $contentArray) {
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
    public function save() {
        $this->load();
        $params = Parameters::getInstance();
        $attributes = $this->model->getAttributes();
        foreach ($attributes as $attribute) {
            $name = $attribute->getName();
            if ($value = $params->get($name)) {
                if ($attribute->getType() == Attribute::TYPE_DROPDOWN ||
                    $attribute->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                    $attribute->setSelectedValues($value);
                } else {
                    $attribute->setValue($value);
                }
                $this->model->setWholeAttribute($attribute);
            }
        }
        $this->model->saveSession();
    }

    /**
     * Send action
     */
    public function send() {
        $this->save();
        $params = Parameters::getInstance();
        $route = $params->get('route');
        $nextRoute = isset($params->get('routes')[$route]['next']) ?
            $params->get('routes')[$route]['next'] : '';
        header('Location: ' . APP_URL . '?route=' . $nextRoute);
        exit;
    }

    /**
     * Determine whether the form is in printable mode or not
     * @return bool|string
     */
    protected function isPrintable() {
        $params = Parameters::getInstance();
        if ($params->get('action') == 'pdf' || $params->get('action') == 'printable') {
            $ret = ($params->get('action') == 'pdf') ? 'pdf' : 'printable';
        } else {
            $ret = false;
        }
        return $ret;
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
     *
     * @return string
     */
    protected function getBuiltURL(array $fields)
    {
        $updatedValues = '';
        $countries     = '';
        $otherUsers    = '';
        $result        = '';
        foreach ($fields as $key => $value) {
            if (is_array($value)) {
                // Countries of Activities dropdown
                $countries .= implode(',', $value);
            } elseif (strpos($value, 'otheruser') === false) {
                //Normal fields
                $updatedValues .= '(' . $key . '|' . $value . '),';
            } else {
                // Other Users
                $otherUsers .= '(' . $key . '|' . $value . '),';
            }
        }
        $result .= ! empty ($updatedValues) ? 'fields=' . substr($updatedValues, 0, -1) . '&' : '';
        $result .= ! empty ($countries) ? 'paises=' . $countries . '&' : '';
        $result = ! empty ($otherUsers) ? $result . 'otherusers=' . substr($updatedValues, 0, -1) : substr($result, 0, -1);

        return $result;
    }
}