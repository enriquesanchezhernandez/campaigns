<?php
/**
 * ContactObject.php
 * Model the OCP form
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class ContactObject extends Model implements IModel {
    /**
     * Class constructor
     */
    public function __construct() {
        $this->attributes = array(
            'confirm_email' => new Attribute('confirm_email', '', '', Validator::VALIDATION_EMAIL, Attribute::TYPE_EMAIL),
            'job_title' => new Attribute('job_title'),
            'captcha' => new Attribute('captcha'),

            'osh_maincontactperson' => new Attribute('osh_maincontactperson'),
            'osh_mainemail' => new Attribute('osh_mainemail', '', '', Validator::VALIDATION_EMAIL, Attribute::TYPE_EMAIL),
            'osh_mainphone' => new Attribute('osh_mainphone')

        );
        $this->load();
    }

    /**
     * Filter specific values
     * @param $attribute
     */
    public function filter($attribute) {}
}