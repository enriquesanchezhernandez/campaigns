<?php
  if (isset($campaign_id)) {
    $url_query = array('pk_campaign' => $campaign_id);
  } else {
    $url_query = array();
  }
  ?>
<table border="0" cellpadding="28" cellspacing="0" width="800" class="blue-line">
  <tbody>
    <tr>
      <td style="padding-top: 0px; padding-bottom: 0px;">
        <table border="0" cellpadding="0" cellspacing="0" width="100%" class="blue-line">
          <tbody>
            <tr>
              <td style="background-color:#003399; width:800px; height: 4px;"></td>
            </tr>
          </tbody>
        </table>
      </td>
    </tr>
  </tbody>
</table>


<table border="0" cellpadding="0" cellspacing="0" width="800">
  <tbody>
    <tr>
      <td style="background-color: #B2B3B5; width:800px;">
        <table border="0" cellpadding="28" cellspacing="0" width="800">
          <tbody>
            <tr>
              <td class="social">
                <h2 style="color: #ffffff;">Follow us on:</h2>
                <?php
                  $social = array(
                    'twitter' => array(
                      'path' => 'https://twitter.com/eu_osha',
                      'alt' => t('Twitter')
                    ),
                    'linkedin' => array(
                      'path' => 'https://www.linkedin.com/company/european-agency-for-safety-and-health-at-work',
                      'alt' => t('LinkedIn')
                    ),
                    'face' => array(
                      'path' => 'https://www.facebook.com/EuropeanAgencyforSafetyandHealthatWork',
                      'alt' => t('Facebook')
                    ),
                    'youtube' => array(
                      'path' => 'https://www.youtube.com/user/EUOSHA',
                      'alt' => t('Youtube')
                    )
                  );

                  foreach ($social as $name => $options) {
                    $directory = drupal_get_path('module','osha_newsletter');
                    print l(theme('image', array(
                      'path' => $directory . '/images/' . $name . '.png',
                      'width' => 'auto',
                      'height' => 26,
                      'alt' => $options['alt'],
                      'attributes' => array('style' => 'border:0px;')
                    )), $options['path'], array(
                      'attributes' => array('style' => 'color:#144989;text-decoration:none;'),
                      'html' => TRUE,
                      'external' => TRUE
                    ));
					print ('&nbsp;&nbsp;&nbsp;&nbsp;');
                  }
                ?>
              </td>
            </tr>
          </tbody>
        </table>
      </td>
    </tr>
    <tr>
      <td style="text-align: center; width:800px;">
        <table border="0" cellpadding="28" cellspacing="0" width="800">
          <tbody>
            <tr>
              <td style="text-align: center; font-family: Arial, sans-serif; font-size: 13px;">
                <?php
                  print t('This is a disclaimer lorem ipsum.');
                  $url = url($base_url.'/en/oshmail-newsletter', array('query' => $url_query));
                ?>
                <a href="<?php echo $url; ?>" style="@style">Unsubscribe.</a>
              </td>
            </tr>
          </tbody>
        </table>
      </td>
    </tr>
  </tbody>
</table>
