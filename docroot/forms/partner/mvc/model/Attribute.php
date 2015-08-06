<?php

/**
 * Attribute.php
 * Class for storing attribute values
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Attribute
{
    /**
     * Constant for dropdown type
     */
    const TYPE_DROPDOWN = 'dropdown';
    /**
     * Constant for email type
     */
    const TYPE_EMAIL = 'email';
    /**
     * Constant for URL type
     */
    const TYPE_URL = 'url';
    /**
     * Constant for image type
     */
    const TYPE_IMAGE = 'image';
    /**
     * @var Name
     */
    protected $name;
    /**
     * @var Section this attribute belongs to
     */
    protected $section;
    /**
     * @var Callback method associated to this attribute
     */
    protected $callback;
    /**
     * @var Validator associated to this attribute
     */
    protected $validator;
    /**
     * @var Type of field
     */
    protected $type;
    /**
     * @var Value
     */
    protected $value;
    /**
     * @var $extended Extended attributes
     */
    protected $extended;
    /** @var $selectedValues array */
    protected $selectedValues;

    /**
     * @param string $name
     * @param string $section
     * @param string $callback
     * @param string $validator
     * @param string $type
     * @param string $value
     * @param array  $extended
     */
    public function __construct($name = '', $section = '', $callback = '', $validator = '', $type = '', $value = '', $extended = array())
    {
        $this->name      = $name;
        $this->section   = $section;
        $this->callback  = $callback;
        $this->validator = $validator;
        $this->type      = $type;
        $this->value     = $value;
        $this->extended  = $extended;
    }

    /**
     * @return array
     */
    public function getSelectedValues()
    {
        return $this->selectedValues;
    }

    /**
     * @param array $selectedValues
     */
    public function setSelectedValues($selectedValues)
    {
        $this->selectedValues = $selectedValues;
    }

    /**
     * @return Name
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @param Name $name
     */
    public function setName($name)
    {
        $this->name = $name;
    }

    /**
     * @return Section
     */
    public function getSection()
    {
        return $this->section;
    }

    /**
     * @param Section $section
     */
    public function setSection($section)
    {
        $this->section = $section;
    }

    /**
     * @return callable
     */
    public function getCallback()
    {
        return $this->callback;
    }

    /**
     * @param callable $callback
     */
    public function setCallback($callback)
    {
        $this->callback = $callback;
    }

    /**
     * @return Validator
     */
    public function getValidator()
    {
        return $this->validator;
    }

    /**
     * @param Validator $validator
     */
    public function setValidator($validator)
    {
        $this->validator = $validator;
    }

    /**
     * @return Type
     */
    public function getType()
    {
        return $this->type;
    }

    /**
     * @param Type $type
     */
    public function setType($type)
    {
        $this->type = $type;
    }

    /**
     * @return Value
     */
    public function getValue()
    {
        return $this->value;
    }

    /**
     * @param Value $value
     */
    public function setValue($value)
    {
        if (is_array($value)) {
            if (array_key_exists('selected', $value)) {
                $this->selectedValues = $value['selected'];
                unset ($value['selected']);
            }
        }
        $this->value = $value;
    }

    /**
     * @param $key
     *
     * @return string
     */
    public function getExtended($key)
    {
        return isset($this->extended[$key]) ? $this->extended[$key] : '';
    }

    /**
     * @param $key
     * @param $value
     */
    public function setExtended($key, $value)
    {
        $this->extended[$key] = $value;
    }
}