var $jqm = jQuery.noConflict();

$jqm(document).bind("mobileinit", function() {
  $jqm.mobile.ns = '';
  $jqm.mobile.autoInitializePage = 1;
  $jqm.mobile.subPageUrlKey = 'ui-page';
  $jqm.mobile.activePageClass = 'ui-page-active';
  $jqm.mobile.activeBtnClass = 'ui-btn-active'; 
  $jqm.mobile.ajaxEnabled = 1;
  $jqm.mobile.hashListeningEnabled = 1;
  $jqm.mobile.defaultPageTransition = 'slide';
  $jqm.mobile.defaultDialogTransition = 'pop';
  $jqm.mobile.minScrollBack = 150;
  $jqm.mobile.loadingMessage = 'loading';
  $jqm.mobile.pageLoadErrorMessage = 'Error';
  $jqm.mobile.linkBindingEnabled = 1;
  $jqm.mobile.pushStateEnabled = 1;
  $jqm.mobile.touchOverflowEnabled = 0;
});
