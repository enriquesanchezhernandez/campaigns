<?php
/**
 * @file
 * OSHA's theme implementation to display a custom node view mode.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<?php if($node->title != NULL) {?>
<table id="node-<?php print $node->nid; ?>" border="0" cellpadding="0" cellspacing="0" width="100%">
  <tbody>
    <?php
    if (isset($field_publication_date) && $node->type != 'newsletter_article') {
      $date = strtotime($field_publication_date[0]['value']);
    ?>
      <tr>
        <td colspan="2" style="font-family: Arial, sans-serif; font-size: 14px; padding-left: 14px;">
          <span class="item-date"><?php print date('M d, Y',$date);?></span>
        </td>
      </tr>
    <?php
    } if ($node->type == 'events') {
      $date = (isset($field_start_date) && !empty($field_start_date)) ? strtotime($field_start_date[0]['value']) : '';
      $country_location = (isset($field_country_code) && !empty($field_country_code)) ? $field_country_code[0]['value'] : '';
      $city_location = (isset($field_city) && !empty($field_city)) ? $field_city[0]['safe_value'] : '';
      ?>
      <tr>
        <td colspan="2" style="font-family: Arial, sans-serif; font-size: 14px; padding-left: 14px;">
          <span class="item-date"><?php if (trim($country_location) != '' && trim($city_location) != '') { echo $country_location . ' ' . $city_location . ', ';} if (trim($date) != '') { print date('M d, Y',$date);}?></span>
        </td>
      </tr>
    <?php
    }
    ?>
    <tr>
      <td align="left" width="5%" style="padding-left: 0px; padding-right: 0px; vertical-align: top; padding-top: 5px;">
        <?php
          $directory = drupal_get_path('module','osha_newsletter');
          $site_url = variable_get('site_base_url', 'http://osha.europa.eu');
          print l(theme('image', array(
          'path' => $directory . '/images/link-arrow.png',
          'width' => 7,
          'height' => 11,
          'alt' => 'link arrow',
          'attributes' => array('style' => 'border: 0px;')
          )), $site_url, array(
          'html' => TRUE,
          'external' => TRUE
        ));
        ?>
      </td>
      <td align="right" width="95%" style="text-align: left; padding-top: 5px; padding-bottom: 10px;">
        <?php
        if ($node->type == 'publication') {
          print l($node->title, url('node/' . $node->nid . '/view', array('absolute' => TRUE)), array(
            'attributes' => array('style' => 'color: #003399; text-decoration: none; font-family:Arial, sans-serif; font-size: 12px; font-weight: bold;'),
            'external' => TRUE
          ));
        } else {
          print l($node->title, url('node/' . $node->nid, array('absolute' => TRUE)), array(
            'attributes' => array('style' => 'color: #003399; text-decoration: none; font-family:Arial, sans-serif; font-size: 12px; font-weight: bold;'),
            'external' => TRUE
          ));
        }
        ?>
      </td>
    </tr>
    <tr>
      <td colspan="2" style="border-bottom:2px dotted #CFDDEE;padding-top:0px;"></td>
    </tr>
    <tr>
      <td colspan="2" style="padding-bottom: 10px;" class="space-beyond-dotted-line"></td>
    </tr>
  </tbody>
</table>
<?php } ?>
