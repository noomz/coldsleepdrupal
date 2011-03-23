$ = jQuery;
$(document).ready(function() {
  $('.node-weight-slide-smile').slideSmile({
	'speed': parseInt(Drupal.settings.node_weight.smile.speed),
	'interval': parseInt(Drupal.settings.node_weight.smile.interval),
	'autoplay': Drupal.settings.node_weight.smile.autoplay,
	'pager': Drupal.settings.node_weight.smile.use_pager,
	'pager_position': Drupal.settings.node_weight.smile.pager_position,
	'navigation': Drupal.settings.node_weight.smile.navigation
  });
});
