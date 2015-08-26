<?php
/**
 * Model.php
 * Class for models
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Model {
    /**
     * @var Array Array of attributes
     */
    protected $attributes;
    /**
     * @var Array CDB map of the current entity
     */
    protected $cdbMap;
    /**
     * @var Array Sections of the current entity
     */
    protected $sections;

    /**
     * Class constructor
     * @param $entity
     */
    public function __construct($entity) {
        if (isset($entity) && !empty($entity)) {
            $this->initializeAttributes($entity);
        }
    }

    /**
     * Load the model
     * @param string $sessionID
     */
    public function load($sessionID = '') {
        $session = Session::getInstance();
        if ($session->isSessionReady()) {
            $this->loadFromSession();
        } else {
            $this->loadFromCDB($this->cdbMap, $sessionID);
            $this->saveSession();
        }
    }

    /**
     * Load from session
     */
    private function loadFromSession() {
        $session = Session::getInstance();
        foreach ($this->attributes as $name => &$attribute) {
            $attribute->setValue($session->getAttribute($attribute->getName()));
            if ($attribute->getType() == Attribute::TYPE_DROPDOWN ||
                $attribute->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                $attribute->setSelectedValues($session->getAttribute($attribute->getName() . '_selected'));
            }
            //$this->filter($attribute);
        }
    }

    /**
     * Initialize the attributes of the current entity
     * @param $entity
     * @throws Exception
     */
    private function initializeAttributes($entity) {
        $params = Parameters::getInstance();
        $model = $params->get('entitiesPath');
            if ($entityDefinition = File::read(APP_ROOT . $model . $entity)) {
                $entityDefinition = json_decode($entityDefinition, true);
                if (isset($entityDefinition) && $entityDefinition !== false) {
                    foreach ($entityDefinition['attributes'] as $attributeDefinition) {
                        $this->attributes[$attributeDefinition['name']] = new Attribute($attributeDefinition);
                    }
                    if (! $params->getUrlParamValue('maintenance_mode')) {
                        $this->cdbMap = isset($entityDefinition['map']) ? $entityDefinition['map'] : false;
                    } else {
                        $this->cdbMap = isset($entityDefinition['map_mf']) ? $entityDefinition['map_mf'] : false;
                    }
                    $this->sections = isset($entityDefinition['sections']) ? $entityDefinition['sections'] : false;
                } else {
                    throw new OshException("data_unavailable", 500);
                }
            }
    }

    /**
     * Load from the CDB
     * @param $cdbMap
     * @param string $sessionId
     */
    private function loadFromCDB($cdbMap, $sessionId = '') {
        $value = false;
        $cdb = CDB::getInstance($cdbMap, $sessionId);
        foreach ($this->attributes as $name => &$attribute) {
            // If a callback is defined, invoke the callback
            if ($callback = $attribute->getCallback()) {
                if (method_exists($cdb, $callback)) {
                    $value = $cdb->$callback();
                }
                // If no callback is defined, check the attribute type to determine the call
            } else {
                $name = $attribute->getName();
                $type = $attribute->getType();
                if ($type == Attribute::TYPE_DROPDOWN || $type == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                    $value = $cdb->getDropdown($name);
                } else if ($type == Attribute::TYPE_IMAGE) {
                    $value = $cdb->getImage($name);
                } else {
                    $value = $cdb->get($name);
                }
            }
            if ($value) {
                $attribute->setValue($value);
            }
        }
    }

    /**
     * send the data to be updated in CDB
     * @TODO error treatment
     * @param $fields
     * @return bool
     */
    public function saveToCDB($fields)
    {
        $cdb = CDB::getInstance(null);
        $cdb->updateData($fields);

        return true;
    }

    /**
     * Retrieve all the attributes
     * @return Array
     */
    public function getAttributes() {
        return $this->attributes;
    }

    /**
     * Retrieve the values of all the attributes
     * @return Array
     */
    public function getAttributesValues() {
        $values = array();
        foreach ($this->attributes as $name => $attribute) {
            $values[$attribute->getName()] = $attribute->getValue();
        }
        return $values;
    }

    /**
     * Retrieve the selected values
     * @return Array
     */
    public function getSelectedValues() {
        $values = array();
        foreach ($this->attributes as $name => $attribute) {
            $values[$attribute->getName()] = $attribute->getSelectedValues();
        }
        return $values;
    }

    /**
     * Retrieve the loaded sections
     * @return Array
     */
    public function getSections() {
        return $this->sections;
    }

    /**
     * Validate the attributes
     * @param bool $attribute
     * @param bool $section
     * @return bool
     */
    public function validate($attribute = false, $section = false) {
        $ret = true;
        $validator = new Validator();
        if ($attribute) {
            // Single attribute validation
            if (isset($this->attributes[$attribute])) {
                $ret = $validator->validate($this->attributes[$attribute]);
            }
        } else {
            // Validation of all attributes
            foreach($this->attributes as $attribute) {
                if (!$section || ($section && $attribute->getSection() == $section)) {
                    $ret &= $validator->validate($attribute);
                }
            }
        }
        return $ret;
    }

    /**
     * Retrieve an attribute
     * @param $attribute
     * @return bool
     */
    public function get($attribute) {
        return (isset($this->attributes[$attribute])) ? $this->filter($this->attributes[$attribute->getValue()]) : false;
    }

    /**
     * Set an attribute
     * @param $attribute
     * @param $value
     * $param $persistence
     */
    public function set($attribute, $value, $persistence = false) {
        if (isset($this->attributes[$attribute])) {
            $this->attributes[$attribute]->setValue($value);
            if ($persistence) {
                $session = Session::getInstance();
                $session->setAttribute($attribute, $value);
            }
        }
    }

    /**
     * Save the send values in session
     */
    public function saveSession() {
        $session = Session::getInstance();
        foreach($this->attributes as $name => $attribute) {
            $session->setAttribute($attribute->getName(), $attribute->getValue());
            if ($attribute->getType() == Attribute::TYPE_DROPDOWN ||
                $attribute->getType() == Attribute::TYPE_DROPDOWN_MULTIPLE) {
                $session->setAttribute($attribute->getName() . '_selected', $attribute->getSelectedValues());
            }
        }
        $session->setAttribute(Session::STORED_IN_SESSION, true);
    }

    /**
     * Set the attribute with all its properties
     * @param $attribute
     */
    public function setWholeAttribute($attribute) {
        if (isset($this->attributes[$attribute->getName()])) {
            $this->attributes[$attribute->getName()] = $attribute;
        }
    }

    /**
     * Get the cdb name of an attribute, based on its html name
     *
     * @param $attribute
     *
     * @return null
     */
    public function getTranslation($attribute) {
        if (isset($this->cdbMap[$attribute->getName()])) {
            return $this->cdbMap[$attribute->getName()];
        }
        return null;
    }

    /**
     * Set the entity
     * @param $entity
     * @throws \OshException
     */
    public function setEntity($entity) {
        $this->initializeAttributes($entity);
    }
}