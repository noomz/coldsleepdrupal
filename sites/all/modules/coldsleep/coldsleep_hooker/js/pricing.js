jQuery(document).ready(function($) {

  var showCreateForm = function() {
    $('.form-item-retype-password').show();
    $('#edit-create').show();
    $('#edit-login').hide();
  };

  var showLoginForm = function() {
    $('.form-item-retype-password').hide();
    $('#edit-create').hide();
    $('#edit-login').show();
  };

  var type = $('input[name=type]:checked').val();
  switch (type) {
    case 'create': showCreateForm(); break;
    case 'login': showLoginForm(); break;
  }

  $('input[name=type]').click(function(e) {
    switch (this.value) {
      case 'create': showCreateForm(); break;
      case 'login': showLoginForm(); break;
    }
  });
});
