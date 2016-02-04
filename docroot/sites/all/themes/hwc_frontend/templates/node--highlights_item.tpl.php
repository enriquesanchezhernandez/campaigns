<?php
/**
 * @file
 * EU-OSHA's theme implementation to display a newsletter item in Newsletter Highlights view mode.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<style>
	.container-ppal a:before{
		content: ">";
		padding-right: 5px;
	}
</style>
<table id="node-<?php print $node->nid; ?>" class="container-ppal" border="0" cellpadding="0" cellspacing="0" width="100%" style="padding-top: 0px; margin-left: 10px;">
  <tbody>
    <tr>
      <td>
        <table border="0" cellpadding="0" cellspacing="0" class="item-thumbnail-and-title" width="100%">
          <tbody>
            <tr>
              <td width="67%" valign="top" style="color: #003399; padding-bottom: 10px; padding-left: 0px; padding-right: 0px; font-family: Oswald, Arial, sans-serif; font-size: 18px; vertical-align: top;">
                <?php
                if (isset($variables['elements']['#campaign_id'])) {
                  $url_query = array('pk_campaign' => $variables['elements']['#campaign_id']);
                } else {
                  $url_query = array();
                }
                if ($node->type == 'publication') {
                  print l($title, url('node/' . $node->nid . '/view', array('absolute' => TRUE)), array(
                    'attributes' => array('style' => 'color: #003399; text-decoration: none;'),
                    'query' => $url_query,
                    'external' => TRUE
                  ));
                } else {
                  print l($title, url('node/' . $node->nid, array('absolute' => TRUE)), array(
                    'attributes' => array('style' => 'color: #003399; text-decoration: none;'),
                    'query' => $url_query,
                    'external' => TRUE
                  ));
                }
                ?>
              </td>
            </tr>
            <tr>
              <td style="font-size: 12px; padding-bottom: 10px;">
                <?php
                $date = (isset($field_publication_date) && !empty($field_publication_date)) ? strtotime($field_publication_date[0]['value']) : '';
                print format_date($date, 'custom', 'M d, Y');
                ?>
              </td>
            </tr>
          </tbody>
        </table>
        <table border="0" cellpadding="0" cellspacing="0" class="item-summary" width="100%" style="margin-bottom: 20px; border-bottom: 1px dotted #749b00;">
          <tbody>
            <tr>
              <td style="padding-bottom: 10px; width: 100%; font-size: 13px; font-family: Arial, sans-serif; color: #000000;">
                <?php
                print l(theme('image_style', array(
                  'style_name' => 'thumbnail',
                  'path' => (isset($field_image) && !empty($field_image)) ? $field_image[0]['uri'] : '',
                  'width' => 150,
                  'alt' => (isset($field_image) && !empty($field_image)) ? $field_image[0]['alt'] : '',
                  'attributes' => array('style' => 'border: 0px; width: 150px; float: left; margin-right: 20px; margin-bottom: 20px;')
                )), url('node/' . $node->nid, array('absolute' => TRUE)), array(
                  'html' => TRUE,
                  'external' => TRUE
                ));
                ?>

                <?php if (isset($body) && is_array($body)) {
                  if (!empty($body)) {
                    // dpm($body);
                    if (isset($body[0]['safe_value'])) {
                      print($body[0]['safe_value']);
                    }
                  }
                }?>
              </td>
            </tr>
          </tbody>
        </table>
      </td>
    </tr>
  </tbody>
</table>