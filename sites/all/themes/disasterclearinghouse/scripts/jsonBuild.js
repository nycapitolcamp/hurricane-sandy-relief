(function ($) {
	$(document).ready(function() {
		var postedData = '';
		postedData += '<div class="header">Warming Centers and Shelters</div>';
		if($('#node-20').length > 0)
		{
			$('#node-20 .content').append('<div class="jsonData"></div>');
			var eoCheck = 0;
			var setEO;
			$.ajax({
				url: '/sites/all/data/all_warming.json',
				dataType: 'json',
				success: function(data, status, XMLHttpRequest) {
					$.each(data, function() {
				     var subData = this;
						$.each(subData, function() {
							var jsonExport = this;
							eoCheck++;

							if(eoCheck % 2)
							{	
								setEO = 'even';
							}
							else {
								setEO = 'odd';
							}
								var shelter = jsonExport.SHELTER_NAME;
								var loCity = jsonExport.CITY;
								postedData += '<div class="json-row '+setEO+'">';
								postedData += '<div class="shelterName">'+shelter.toLowerCase()+'</div>';
								postedData += '<div class="address">'+jsonExport.ADDRESS+'</div>';
								postedData += '<div class="cityState">'+loCity+', '+jsonExport.STATE+'</div>';
								postedData += '<div class="openToClose">'+jsonExport.HOURS_OPEN+' - '+jsonExport.HOURS_CLOSE+'</div>';
								postedData += '</div>';
						});
					});
					$('#node-20 .jsonData').html(postedData);
				}
			});
		}
	});
}(jQuery));