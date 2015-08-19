<?php
/**
 * Validator.php
 * Validator for form fields
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class Validator {
    /**
     * Constant for NOT NULL validation
     */
    const VALIDATION_NOTNULL = 'not_null';
    /**
     * Constant for NOT NULL validation
     */
    const VALIDATION_NUMERIC = 'numeric';
    /**
     * Constant for SIZE validation
     */
    const VALIDATION_SIZE = 'size';
    /**
     * Constant for EMAIL validation
     */
    const VALIDATION_EMAIL = 'email';
    /**
     * @var array Validation types
     */
    private $validationTypes = array(
        self::VALIDATION_NOTNULL,
        self::VALIDATION_NUMERIC,
        self::VALIDATION_SIZE,
        self::VALIDATION_EMAIL,
    );

    /**
     * Validate a value
     * @param $attribute
     * @return bool
     */
    public function validate($attribute) {
        $ret = true;
        $validationType = $attribute->getValidator();
        if (in_array($validationType, $this->validationTypes)) {
            $params = Parameters::getInstance();
            $errorMessages = $params->get('errorMessages');
            $value = $attribute->getValue();
            switch($validationType) {
                case self::VALIDATION_NOTNULL:
                    if (!($ret = $this->validateNull($value))) {
                        $messageBus = MessageBus::getInstance();
                        $messageBus->put($attribute->getName(), $errorMessages[$validationType]);
                    }
                    break;
                case self::VALIDATION_NUMERIC:
                    if (!($ret = $this->validateNumeric($value))) {
                        $messageBus = MessageBus::getInstance();
                        $messageBus->put($attribute->getName(), $errorMessages[$validationType]);
                    }
                    break;
                case self::VALIDATION_SIZE:
                    $size = $attribute->getExtended('size');
                    if (!($ret = $this->validateSize($value, $size))) {
                        $messageBus = MessageBus::getInstance();
                        $messageBus->put($attribute->getName(), $errorMessages[$validationType] . $size);
                    }
                    break;
                case self::VALIDATION_EMAIL:
                    if (!($ret = $this->validateEmail($value))) {
                        $messageBus = MessageBus::getInstance();
                        $messageBus->put($attribute->getName(), $errorMessages[$validationType]);
                    }
                    break;
            }
        }
        return $ret;
    }

    /**
     * Sanitize an attribute
     * @param $attribute
     */
    public function sanitize($attribute) {
        switch($attribute->getType()) {
            case Attribute::TYPE_EMAIL:
                $attribute->setValue(filter_var($attribute->getValue(), FILTER_VALIDATE_EMAIL));
                break;
            case Attribute::TYPE_URL:
                $attribute->setValue(filter_var($attribute->getValue(), FILTER_SANITIZE_URL));
                break;
            default:
                $sanitizedString = filter_var($attribute->getValue(), FILTER_SANITIZE_STRING);
                $attribute->setValue(preg_replace("/[^A-Za-z0-9 ]/", '', $sanitizedString));
                break;
        }
    }

    /**
     * Validate the value is not null
     * @param $value
     * @return bool
     */
    private function validateNull($value) {
        return !empty($value);
    }

    /**
     * Validate the value is numeric
     * @param $value
     * @return bool
     */
    private function validateNumeric($value) {
        return is_numeric($value);
    }

    /**
     * Validate the value is less or equal than the specified size
     * @param $value
     * @return bool
     */
    private function validateSize($value, $size) {
        return (strlen($value) <= $size);
    }

    /**
     * Validate the value is an email address
     * @param $value
     * @return mixed
     */
    private function validateEmail($value) {
        return filter_var($value, FILTER_VALIDATE_EMAIL);
    }
}