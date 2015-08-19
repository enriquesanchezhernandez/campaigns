<?php

/**
 * CompanyObject.php
 * Model the Company form
 * @author Eduardo Martos (eduardo.martos.gomez@everis.com)
 */
class CompanyObject extends Model implements IModel
{
    /** Class constructor */
    public function __construct()
    {
        $this->attributes = array(
            'org_name'                 => new Attribute('org_name', '', 'getOrganisationName'),
            'org_type'                 => new Attribute('org_type', '', 'getOrganisationTypes', '', Attribute::TYPE_DROPDOWN),
            'org_sector'               => new Attribute('org_sector', '', 'getBusinessSectors', '', Attribute::TYPE_DROPDOWN),
            'org_dialog'               => new Attribute('org_dialog', '', 'getSocialDialoguePartner'),
            'org_statement'            => new Attribute('org_statement', '', 'getMissionStatement'),
            'org_pub_type'             => new Attribute('org_pub_type', '', 'getPublicationsTypes'),
            'org_readership'           => new Attribute('org_readership', '', 'getReaderships'),
            'org_countries'            => new Attribute('org_countries', '', 'getCountries', '', Attribute::TYPE_DROPDOWN),
            'ceo_photo'                => new Attribute('ceo_photo', '', 'getCeoImage', '', Attribute::TYPE_IMAGE),
            'logo'                     => new Attribute('logo', '', 'getLogo', '', Attribute::TYPE_IMAGE),

            'osh_address'              => new Attribute('osh_address'),
            'osh_addressextra'         => new Attribute('osh_addressextra'),
            'osh_bussinessector'       => new Attribute('osh_bussinessector', '', 'getBusinessSectors', '', Attribute::TYPE_DROPDOWN),
            'osh_ceo'                  => new Attribute('osh_ceo'),
            'osh_city'                 => new Attribute('osh_city'),
            'osh_country'              => new Attribute('osh_country', '', '', '', Attribute::TYPE_DROPDOWN),
            'osh_emailrepresentative'  => new Attribute('osh_emailrepresentative', '', '', Validator::VALIDATION_EMAIL, Attribute::TYPE_EMAIL),
            'osh_generalemail'         => new Attribute('osh_generalemail', '', '', Validator::VALIDATION_EMAIL, Attribute::TYPE_EMAIL),
            'osh_generalphone'         => new Attribute('osh_generalphone'),
            'osh_phonerepresentative'  => new Attribute('osh_phonerepresentative'),

            'osh_yourmissionstatement' => new Attribute('osh_yourmissionstatement'),
            'osh_zipcode'              => new Attribute('osh_zipcode'),


        );
        $this->load();
    }

    /**
     * Filter specific values
     *
     * @param $attribute
     */
    public function filter($attribute)
    {
        // It's an example: adapt it if needed
        $value = $attribute->getValue();
        /*
        $params = Parameters::getInstance();
        if ($attribute->getName() == 'image') {
            $value = (file_exists(APP_ROOT . $params->get('imagePath') . $value)) ?
                APP_URL . $params->get('imagePath') . $value : APP_URL . $params->get('imagePath') . $params->get('defaultImg');
            $attribute->setValue($value);
        }
        */
    }
}