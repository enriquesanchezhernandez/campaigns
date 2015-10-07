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
    $this->source = new MigrateSourceList(
      new PartnerMigrateListXml(),
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
      'field_pledge',
      'field_quote',
      'field_partner_type',
      'field_organisation_rep',
      'field_position_identifier',
      'field_appform_status',
      'field_facebook_profile',
      'field_twitter_profile',
      'field_youtube_profile',
      'field_slideshare_profile',
      'field_linkedin_profile',
    );
  }
}


class PartnerMigrateListXml extends AbstractCrmMigrateListXml {

  public function __construct() {
    $file = variable_get('hwc_crm_data_dir', '') . '/PublicProfile.xml';
    parent::__construct($file);
  }

  protected function parseSourceFile() {
    self::$data = array();
    if (!is_readable($this->file)) {
      watchdog('hwc_crm_migration', 'Cannot find migration files: @file', array('@file' => $this->file), WATCHDOG_WARNING);
      return;
    }
    if ($xml = simplexml_load_file($this->file, 'SimpleXMLElement', LIBXML_COMPACT | LIBXML_PARSEHUGE)) {
      // Contact fields are attributes of Detail.
      foreach ($xml->xpath('//Details') as $item) {
        $data = new stdClass();
        $attributes = $item->attributes();
        $data->title = (string) $attributes['Textbox1'];
        $data->title_field = (string) $attributes['Textbox1'];
        $data->field_guid_organisation = (string) $attributes['Table0_Details1'];
        /** @var stdClass $term */
        if ($term = osha_workflow_get_partner_section_by_guid($data->field_guid_organisation)) {
          $data->workbench_access[$term->tid] = $term->tid;
        }
        else {
          watchdog('hwc_crm_migration', 'Creating new section with GUID: !guid for partner \'!partner\'',
            array('@guid' => $data->field_guid_organisation, '!organisation' => $data->title), WATCHDOG_INFO);
          if ($term = osha_workflow_create_section($data->title, $data->field_guid_organisation)) {
            $data->workbench_access[$term->tid] = $term->tid;
          }
          else {
            watchdog('hwc_crm_migration', 'Unable to create new section with GUID: !guid for partner \'!partner\'',
              array('@guid' => $data->field_guid_organisation, '!organisation' => $data->title), WATCHDOG_ERROR);
          }
        }

        $data->field_general_email = (string) $attributes['Textbox2'];
        $data->field_general_phone = (string) $attributes['Textbox3'];
        $data->field_website = (string) $attributes['Textbox4'];
        $data->field_orgtype = (string) $attributes['Textbox5'];
        $data->field_bussines_sector = (string) $attributes['Textbox6'];
        $data->field_mission_statement = (string) $attributes['Textbox7'];

        $logo_image = base64_decode((string) $attributes['Textbox8']);
        $logo_ext = (string) $attributes['Textbox9'];
        if (!empty($logo_image) && !empty($logo_ext)) {
          $data->field_logo = $logo_image;
          $data->field_logo_file = file_munge_filename($data->title . '.' . $logo_ext, '');
        }

        $data->field_logo_mime = (string) $attributes['Textbox9'];
        $data->field_logo_file = $data->title . '.jpg';
        $data->field_campaign_website = (string) $attributes['Textbox10'];

        $data->field_facebook_profile = (string) $attributes['Textbox11'];
        $data->field_twitter_profile = (string) $attributes['Textbox12'];
        $data->field_youtube_profile = (string) $attributes['Textbox13'];
        $data->field_slideshare_profile = (string) $attributes['Textbox14'];
        $data->field_linkedin_profile = (string) $attributes['Textbox15'];

        $data->field_ph_address = (string) $attributes['Textbox16'];
        $data->field_ph_cp = (string) $attributes['Textbox17'];
        $data->field_country = (string) $attributes['Textbox18'];
        $data->field_ph_address_extra = (string) $attributes['Textbox13'];
        $data->field_guid_main_contact = (string) $attributes['Textbox20'];
        $data->field_main_contact = trim((string) $attributes['Textbox21'] . ' ' . (string) $attributes['Textbox22']);
        $data->field_main_contact_email = (string) $attributes['Textbox23'];

        $data->field_ceo = trim((string) $attributes['Textbox24'] . ' ' . (string) $attributes['Textbox25']);
        $ceo_image = base64_decode((string) $attributes['Textbox26']);
        $ceo_image_ext = (string) $attributes['Textbox27'];
        if (!empty($ceo_image) && !empty($ceo_image_ext)) {
          $data->field_ceo_photo = $ceo_image;
          $data->field_ceo_photo_file = file_munge_filename($data->title . '_ceo.' . $ceo_image_ext, '');
        }

        // Try to assign a valid partner type term
        $partner_type = (string) $attributes['Textbox28'];
        $term = taxonomy_get_term_by_name($partner_type);
        if (!empty($term)) {
          $data->field_partner_type = (string) $attributes['Textbox28'];
        }
        else {
          watchdog('hwc_crm_migration', 'Could not find the partner type @type in the vocabulary for organisation @organisation',
            array('@type' => $partner_type, '@organisation' => $data->title), WATCHDOG_WARNING);
        }

        $data->field_social_dialog_partner = (string) $attributes['Textbox29'];
        if (strtolower($data->field_social_dialog_partner) == 'false') {
          $data->field_social_dialog_partner = 0;
        }
        else {
          $data->field_social_dialog_partner = 1;
        }

        $data->field_quote = (string) $attributes['Textbox30'];
        $data->field_pledge = (string) $attributes['Textbox31'];
        $data->field_organisation_rep = trim((string) $attributes['Textbox32'] . ' ' . (string) $attributes['Textbox33']);
        $data->field_position_identifier = (string) $attributes['Textbox34'];
        $data->field_appform_status = (string) $attributes['Textbox35'];
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
