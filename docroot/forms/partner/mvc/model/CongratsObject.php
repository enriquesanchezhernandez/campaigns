<?php
/**
 * ContactObject.php
 * Model the OCP form
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class CongratsObject extends Model implements IModel {
    /**
     * Class constructor
     */
    public function __construct() {
        $this->attributes = array(
            'name' => new Attribute('name'),
            'phone' => new Attribute('phone'),
            'email' => new Attribute('email'),
            'job_title' => new Attribute('job_title'),
        );
        $this->load();
    }

    /**
     * Filter specific values
     * @param $attribute
     */
    public function filter($attribute) {}
}