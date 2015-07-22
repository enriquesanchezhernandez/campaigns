<?php

/**
 * Class MigrateOshaBlog migrates blog.txt contents. The data
 * is stored inside the <em>Blog</em> content type.
 */
class PartnerMigration extends HwcCrmMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    $source_file = PartnerMigrateListXml::getSourceFile($arguments);
    $this->source = new MigrateSourceList(
      new PartnerMigrateListXml($source_file),
      new PartnerContentItemXML(),
      $this->exposedFields()
    );
    parent::__construct($arguments);
  }

  protected function getManuallyMigratedFields() {
    return array();
  }

  public function exposedFields() {
    return array(
      'field_guid_organisation',
      'title',
      'title_field',
      'field_general_email',
      'field_general_phone',
      'field_website',
      'field_orgtype',
      'field_bussines_sector',
      'field_mission_statement',
      'field_logo',
      'field_general_email',
      'field_campaign_website',
      'field_ph_address',
      'field_ph_cp',
      'field_country',
      'field_ph_address_extra',
      'field_guid_main_contact',
      'field_main_contact',
      'field_main_contact_email',
      'field_ceo',
      'field_ceo_photo',
      'field_category',
      'field_social_dialog_partner',
      'field_quote',
      'field_partner_type',
      'field_organisation_rep',
      'field_position_identifier',
      'field_appform_status',
    );
  }
}


class PartnerMigrateListXml extends AbstractCrmMigrateListXml {

  protected function parseSourceFile() {
    self::$data = array();
    if (!is_readable($this->file)) {
      return;
    }
    if ($xml = simplexml_load_file($this->file, 'SimpleXMLElement', LIBXML_COMPACT | LIBXML_PARSEHUGE)) {
      // Contact fields are attributes of Detail.
      foreach ($xml->xpath('//Details') as $item) {
        $data = new stdClass();
        $attributes = $item->attributes();
        $data->field_guid_organisation = (string) $attributes['Table0_Details1'];
        $data->title = (string) $attributes['Textbox1'];
        $data->title_field = (string) $attributes['Textbox1'];
        $data->field_general_email = (string) $attributes['Textbox2'];
        $data->field_general_phone = (string) $attributes['Textbox3'];
        $data->field_website = (string) $attributes['Textbox4'];
        $data->field_orgtype = (string) $attributes['Textbox5'];
        $data->field_bussines_sector = (string) $attributes['Textbox6'];
        $data->field_mission_statement = (string) $attributes['Textbox7'];
        $data->field_logo = base64_decode((string) $attributes['Textbox8']);
        $data->field_logo_mime = (string) $attributes['Textbox9'];
        $data->field_logo_file = $data->title . '.jpg';
        $data->field_campaign_website = (string) $attributes['Textbox10'];
        $data->field_ph_address = (string) $attributes['Table0_Details2'];
        $data->field_ph_cp = (string) $attributes['Textbox11'];
        $data->field_country = (string) $attributes['Textbox12'];
        $data->field_ph_address_extra = (string) $attributes['Textbox13'];
        $data->field_guid_main_contact = (string) $attributes['Table0_Details3'];
        $data->field_main_contact = (string) $attributes['Textbox14'];
        $data->field_main_contact_email = (string) $attributes['Textbox15'];

        $data->field_ceo = (string) $attributes['Table0_Details4'];
        $data->field_ceo_photo = base64_decode((string) $attributes['Textbox16']);
        $data->field_ceo_photo_file = $data->field_ceo . '.jpg';
        if (empty($data->field_ceo)) {
          $data->field_ceo_photo_file = $data->title . '_ceo.jpg';
        }
        $data->field_ceo_photo_mime = (string) $attributes['Textbox17'];
        $data->field_partner_type = (string) $attributes['Table0_Details5'];

        $data->field_social_dialog_partner = (string) $attributes['Textbox18'];
        if (strtolower($data->field_social_dialog_partner) == 'false') {
          $data->field_social_dialog_partner = 0;
        }
        else {
          $data->field_social_dialog_partner = 1;
        }

        $data->field_quote = (string) $attributes['Textbox19'];
//        $data->field_quote = (string) $attributes['Textbox20'];
        $data->field_organisation_rep = (string) $attributes['Textbox21'];
        $data->field_position_identifier = (string) $attributes['Textbox22'];
        $data->field_appform_status = (string) $attributes['Textbox23'];
        if (empty(self::$data[$data->field_guid_organisation])) {
          self::$data[$data->field_guid_organisation] = $data;
        }
      }
    }
  }
}

class PartnerContentItemXML extends MigrateItem {

  /**
   * {@inheritdoc}
   */
  public function getItem($item_id) {
    if (array_key_exists($item_id, PartnerMigrateListXml::$data)) {
      return (object) PartnerMigrateListXml::$data[$item_id];
    }
    return NULL;
  }
}
