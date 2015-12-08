<?php
/**
 * @file
 * Social share widgets
 *
 * Available variables:
 * - $url: URL to the page
 * - $node: Current node
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
$label = t('Share this article:');
if (!empty($node->nid) && $node->nid == 160) {
  $label = t('Share this video:');
}
?>
<div class="hwc-share-widget">
  <ul>
    <li class="share-this-article">
      <?php print $label; ?>
    </li>
    <li id="facebook-share-button-<?php print $node->nid; ?>"  class="hwc-share-widget-button hwc-share-widget-facebook" data-href="">
      <a href="<?php print $url ?>">Facebook</a>
    </li>
    <li id="twitter-share-button-<?php print $node->nid; ?>" class="hwc-share-widget-button hwc-share-widget-twitter">
      <a href="<?php print $tweet_url; ?>">Twitter</a>
    </li>
    <li id="linked-in-<?php print $node->nid; ?>" class="napo-share-widget-button napo-share-widget-linkedin">
      <a href="https://www.linkedin.com/shareArticle?mini=true&url=<?php print $url; ?>">Linked in</a>
    </li>
  </ul>
</div>
<script>
  (function($) {
    $(window).ready(function(){
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
    });
  })(jQuery);

</script>
