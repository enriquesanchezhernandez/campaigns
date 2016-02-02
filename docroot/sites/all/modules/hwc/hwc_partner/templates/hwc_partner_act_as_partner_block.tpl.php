<a class="btn btn-primary btn-lg" data-toggle="modal" data-target="#act-as-partner">
  <?php print t('Act as a partner'); ?>
</a>
<div id="act-as-partner" class="modal fade" tabindex="-1" role="dialog">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title"><?php t('Act as a partner'); ?></h4>
      </div>
      <div class="modal-body">
        <?php print $content; ?>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal"><?php print t('Cancel'); ?></button>
      </div>
    </div><!-- /.modal-content -->
  </div><!-- /.modal-dialog -->
</div><!-- /.modal -->