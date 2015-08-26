<?php
/**
 * Model.php
 * Abstract class for models
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
abstract class Model {
    /**
     * @var Array of attributes
     */
    protected $attributes;

    /**
     * Load the model
     * @param string $sessionId
     */
    public function load($sessionId = '') {
        $params = Parameters::getInstance();
        if ($params->get(Session::STORED_IN_SESSION)) {
            $this->loadFromSession();
        } else {
            $this->loadFromCDB($sessionId);
        }
    }

    /**
     * Load from session
     */
    private function loadFromSession() {
        $params = Parameters::getInstance();
        foreach ($this->attributes as &$attribute) {
            $attribute->setValue($params->get($attribute->getName()));
            $this->filter($attribute);
        }
    }

    /**
     * Load from the CDB
     * @param string $sessionId
     */
    private function loadFromCDB($sessionId = '') {
        $value = false;
        $cdb = CDB::getInstance($sessionId);
        foreach ($this->attributes as &$attribute) {
            // If a callback is defined, invoke the callback
            if ($callback = $attribute->getCallback()) {
                if (method_exists($cdb, $callback)) {
                    $value = $cdb->$callback();
                }
                // If no callback is defined, check the attribute type to determine the call
            } else {
                $name = $attribute->getName();
                $type = $attribute->getType();
                if ($type == Attribute::TYPE_DROPDOWN) {
                    $value = $cdb->getDropdown($name);
                } else if ($type == Attribute::TYPE_IMAGE) {
                    $value = $cdb->getImage($name);
                } else {
                    $value = $cdb->get($name);
                }
            }
            if ($value) {
                $attribute->setValue($value);
                $this->filter($attribute);
            }
        }
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
        foreach ($this->attributes as $attribute) {
            $values[$attribute->getName()] = $attribute->getValue();
        }
        return $values;
    }

    public function getSelectedValues()
    {
        $values = array();
        foreach ($this->attributes as $attribute) {
            $values[$attribute->getName()] = $attribute->getSelectedValues();
        }
        return $values;
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
     */
    public function set($attribute, $value) {
        if (isset($this->attributes[$attribute])) {
            $this->attributes[$attribute]->setValue($value);
        }
    }

    /**
     * Save the send values in session
     */
    public function saveSession() {
        $params = Parameters::getInstance();
        foreach($this->attributes as $attribute) {
            $name = $attribute->getName();
            $value = $params->get($name);
            $params->set($name, $value, true);
        }
        $params->set(Session::STORED_IN_SESSION, true, true);
    }
}