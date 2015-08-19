<?php

/**
 * InvolvementObject.php
 * Model the Involvement tab
 *
 * @author Eduardo Martos      (eduardo.martos.gomez@everis.com)
 * @author Juan Jose Arol Rosa (Juan.Jose.Arol.Rosa@everis.com)
 */
class InvolvementObject extends Model implements IModel
{
    /** Class constructor */
    public function __construct()
    {
        $this->attributes = array(
            'why_area'           => new Attribute('why_area'),
            'how_area'           => new Attribute('how_area'),
            'osh_campaignpledge' => new Attribute('osh_campaignpledge'),
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
    }
}