<?php
/**
 * Attribute.php
 * Class for storing attribute values
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Attribute {
    /**
     * Constant for dropdown type
     */
    const TYPE_DROPDOWN = 'dropdown';
    /**
     * Constant for dropdown multiple type
     */
    const TYPE_DROPDOWN_MULTIPLE = 'dropdown_multiple';
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
     * @var Label of the field
     */
    protected $label;
    /**
     * @var Placeholder of the text
     */
    protected $placeholder;
    /**
     * @var Public Profile of the element
     */
    protected $publicProfile;
    /**
     * @var Help text for the field
     */
    protected $helpText;
    /**
     * @var Value
     */
    protected $value;
    /**
     * @var $extended Extended attributes
     */
    protected $extended;
    /**
     * @var $selectedValues array
     */
    protected $selectedValues;
    /**
     * @var $validation Switch to show/hide the validation widget
     */
    protected $validation;

    /**
     * Class constructor
     *
     * @param string $attribute
     */
    public function __construct($attribute)
    {
        $this->name          = $this->assignProperty($attribute, 'name');
        $this->section       = $this->assignProperty($attribute, 'section');
        $this->callback      = $this->assignProperty($attribute, 'callback');
        $this->validator     = $this->assignProperty($attribute, 'validator');
        $this->type          = $this->assignProperty($attribute, 'type');
        $this->label         = $this->assignProperty($attribute, 'label');
        $this->placeholder   = $this->assignProperty($attribute, 'placeholder');
        $this->publicProfile = $this->assignProperty($attribute, 'publicProfile');
        $this->helpText      = $this->assignProperty($attribute, 'helpText');
        $this->validation    = $this->assignProperty($attribute, 'validator');
    }

    /**
     * Safe assignment of properties
     * @param $container
     * @param $name
     * @return string
     */
    private function assignProperty($container, $name) {
        return isset($container[$name]) ? $container[$name] : '';
    }

    /**
     * Retrieve the selected values
     * @return array
     */
    public function getSelectedValues() {
        return $this->selectedValues;
    }

    /**
     * Set the selected values
     * @param array $selectedValues
     */
    public function setSelectedValues($selectedValues) {
        $this->selectedValues = $selectedValues;
    }

    /**
     * Retrieve the name of the attribute
     * @return Name
     */
    public function getName() {
        return $this->name;
    }

    /**
     * Set the name of the attribute
     * @param Name $name
     */
    public function setName($name) {
        $this->name = $name;
    }

    /**
     * Retrieve the section of the attribute
     * @return Section
     */
    public function getSection() {
        return $this->section;
    }

    /**
     * Set the section of the attribute
     * @param Section $section
     */
    public function setSection($section) {
        $this->section = $section;
    }

    /**
     * Retrieve the callback of the attribute
     * @return callable
     */
    public function getCallback() {
        return $this->callback;
    }

    /**
     * Set the callback of the attribute
     * @param callable $callback
     */
    public function setCallback($callback) {
        $this->callback = $callback;
    }

    /**
     * Retrieve the validator of the attribute
     * @return Validator
     */
    public function getValidator() {
        return $this->validator;
    }

    /**
     * Set the validator of the attribute
     * @param Validator $validator
     */
    public function setValidator($validator) {
        $this->validator = $validator;
    }

    /**
     * Retrieve the type of the attribute
     * @return Type
     */
    public function getType() {
        return $this->type;
    }

    /**
     * Set the type of the attribute
     * @param Type $type
     */
    public function setType($type) {
        $this->type = $type;
    }

    /**
     * Retrieve the value of the attribute
     * @return Value
     */
    public function getValue() {
        return $this->value;
    }

    /**
     * Set the value of the attribute
     * @param Value $value
     */
    public function setValue($value) {
        if (is_array($value)) {
            if (array_key_exists('selected', $value)) {
                $this->selectedValues = $value['selected'];
            }
            if (array_key_exists('values', $value)) {
                $value = $value['values'];
            }
        } else {
            $value = trim($value);
        }
        $this->value = $value;
    }

    /**
     * Retrieve an extended attribute
     * @param $key
     * @return string
     */
    public function getExtended($key) {
        return isset($this->extended[$key]) ? $this->extended[$key] : '';
    }

    /**
     * Set extended attributes
     * @param $key
     * @param $value
     */
    public function setExtended($key, $value) {
        $this->extended[$key] = $value;
    }

    /**
     * @return Label
     */
    public function getLabel() {
        return $this->label;
    }

    /**
     * @param Label $label
     */
    public function setLabel($label) {
        $this->label = $label;
    }

    /**
     * @return Placeholder
     */
    public function getPlaceholder() {
        return $this->placeholder;
    }

    /**
     * @param Placeholder $placeholder
     */
    public function setPlaceholder($placeholder) {
        $this->placeholder = $placeholder;
    }

    /**
     * @return PublicProfile
     */
    public function getPublicProfile() {
        return $this->publicProfile;
    }

    /**
     * @param PublicProfile $publicProfile
     */
    public function setPublicProfile($publicProfile) {
        $this->publicProfile = $publicProfile;
    }

    /**
     * @return Help
     */
    public function getHelpText() {
        return $this->helpText;
    }

    /**
     * @param Help $helpText
     */
    public function setHelpText($helpText) {
        $this->helpText = $helpText;
    }

    /**
     * @return Help
     */
    public function getValidation() {
        return $this->validation;
    }

    /**
     * @param Help $validation
     */
    public function setValidation($validation) {
        $this->validation = $validation;
    }
}