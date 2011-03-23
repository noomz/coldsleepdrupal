// $Id: i18n_node.js,v 1.1.2.1 2011/01/11 18:47:20 jareyero Exp $

/**
 * Rewrite autocomplete inputs to pass the language of the node currently being
 * edited in the path.
 *
 * This functionality ensures node autocompletes get suggestions for the node's
 * language rather than the current interface language.
 */
Drupal.behaviors.i18n = function (context) {
  if (Drupal.settings && Drupal.settings.i18n) {
    $('form[id^=node-form]', context).find('input.autocomplete[value^=' + Drupal.settings.i18n.interface_path + ']').each(function () {
      $(this).val($(this).val().replace(Drupal.settings.i18n.interface_path, Drupal.settings.i18n.content_path));
    });
  }
};

