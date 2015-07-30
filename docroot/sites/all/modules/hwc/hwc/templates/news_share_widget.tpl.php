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
/** @var string $tweet_url */
/** @var array $options */
$rss_url = !empty($options['rss_url']) ? $options['rss_url'] : url('rss-feeds/latest/news.xml', array('absolute' => TRUE));
$rss_hide = !empty($options['rss_hide']);
?>
<div class="hwc-share-widget">
  <ul>
    <li id="fb-buttons"  class="hwc-share-widget-button hwc-share-widget-facebook" data-href="">
      <div class="fb-like" data-href="<?php print $url; ?>" data-layout="button_count" data-action="like" data-show-faces="true" data-share="true"></div>
    </li>
    <li id="twitter-share-button-<?php print $node->nid; ?>" class="hwc-share-widget-button hwc-share-widget-twitter">
      <a href="<?php print $tweet_url; ?>">Twitter</a>
    </li>
    <li id="linked-in-<?php print $node->nid; ?>" class="napo-share-widget-button napo-share-widget-linkedin">
      <a href="https://www.linkedin.com/shareArticle?mini=true&url=<?php print $url ?>">Linked in</a>
    </li>
    <?php if (!$rss_hide): ?>
    <li class="pull-right">
      <a href="<?print $rss_url; ?>">RSS</a>
    </li>
    <?php endif; ?>
  </ul>
</div>
<script>
  (function($) {
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
