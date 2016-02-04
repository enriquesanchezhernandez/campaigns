<?php
/**
 * @file
 * Social share widgets
 *
 * Available variables:
 * - $url: URL to the page
 * - $node: Current node / A false node with nid=0 if the widget is for a page
 * - $tweet_url: Twitter share URL
 * - $language: Current language
 * - $options: Additional configuration options
 *
 * Additional configuration options variables:
 * - rss_url: URL to the RSS feed
 * - rss_hide: Set to TRUE to hide the RSS link
 * @see template_process()
 */
?>
<?php
/** @var string $tweet_url */
/** @var array $options */
$rss_url = !empty($options['rss_url']) ? $options['rss_url'] : url('rss-feeds/latest/news.xml', array('absolute' => TRUE));
$rss_hide = !empty($options['rss_hide']);

// ToDo: make action and counter for facebook 'like' button
$fb_like_count = 0;

// FB share counter.
$api = file_get_contents('http://graph.facebook.com/?id=' . $url);
$count = json_decode($api);
$fb_share_count = isset($count->shares) ? $count->shares : 0;

// Twitter share counter.
$api = file_get_contents('https://cdn.api.twitter.com/1/urls/count.json?url=' . $url);
$count = json_decode($api);
$twitter_share_count = isset($count->count) ? $count->count : 0;

// LinkedIn share counter.
$api = file_get_contents('https://www.linkedin.com/countserv/count/share?url=' . $url . '&format=json');
$count = json_decode($api);
$linkedin_share_count = isset($count->count) ? $count->count : 0;

?>
<div class="hwc-share-widget">
  <ul>
    <li id="facebook-share-button-<?php print $node->nid; ?>"  class="hwc-share-widget-button hwc-share-widget-facebook" data-href="">
      <a href="<?php print $url ?>">Facebook</a>
    </li>
    <li class="label">
      <?php print t('Share'); ?> <span>(<?php print $fb_share_count ?>)</span>
    </li>
    <li id="facebook-like-button-<?php print $node->nid; ?>"  class="hwc-share-widget-button hwc-share-widget-facebook" data-href="">
      <a href="<?php print $url ?>">Facebook</a>
    </li>
    <li class="label">
      <?php print t('Like'); ?> <span>(<?php print $fb_like_count ?>)</span>
    </li>
    <li id="twitter-share-button-<?php print $node->nid; ?>" class="hwc-share-widget-button hwc-share-widget-twitter">
      <a href="<?php print $tweet_url; ?>">Twitter</a>
    </li>
    <li class="label">
      <?php print t('Tweet'); ?> <span>(<?php print $twitter_share_count ?>)</span>
    </li>
    <li id="linked-in-<?php print $node->nid; ?>" class="napo-share-widget-button napo-share-widget-linkedin">
      <a href="https://www.linkedin.com/shareArticle?mini=true&url=<?php print $url; ?>">Linked in</a>
    </li>
    <li class="label">
      <?php print t('Share'); ?> <span>(<?php print $linkedin_share_count ?>)</span>
    </li>
    <?php if (!$rss_hide): ?>
      <li class="label label-rss pull-right">
        <?php print t('RSS'); ?>
      </li>
    <li class="pull-right">
      <a href="<?php print $rss_url; ?>">RSS</a>
    </li>
    <?php endif; ?>
  </ul>
</div>
<script>
  window.fbAsyncInit = function() {
    FB.init({
      appId      : Drupal.settings.hwc.fb_app_key,
      xfbml      : true,
      version    : 'v2.3'
    });
  };

  (function(d, s, id){
    var js, fjs = d.getElementsByTagName(s)[0];
    if (d.getElementById(id)) {return;}
    js = d.createElement(s); js.id = id;
    js.src = "//connect.facebook.net/en_US/sdk.js";
    fjs.parentNode.insertBefore(js, fjs);
  }(document, 'script', 'facebook-jssdk'));

  (function($) {
    $('#facebook-share-button-<?php print $node->nid; ?> a').click(function(e) {
        e.preventDefault();
        FB.ui({
          method: 'share',
          href: this.href
        }, function (response) {
        });
      }
    );

    $('#twitter-share-button-<?php print $node->nid; ?> a').click(function(event) {
      var width  = 575,
        height = 400,
        left   = ($(window).width()  - width)  / 2,
        top    = ($(window).height() - height) / 2,
        opts   = 'status=1' +
          ',width='  + width  +
          ',height=' + height +
          ',top='    + top    +
          ',left='   + left;
      window.open(this.href, 'twitter', opts);
      return false;
    });

    $('#linked-in-<?php print $node->nid; ?> a').click(function() {
      var width  = 575,
        height = 400,
        left   = ($(window).width()  - width)  / 2,
        top    = ($(window).height() - height) / 2,
        opts   = 'status=1' +
          ',width='  + width  +
          ',height=' + height +
          ',top='    + top    +
          ',left='   + left;
      window.open(this.href, 'Linked In', opts);
      return false;
    });
  })(jQuery);
</script>
