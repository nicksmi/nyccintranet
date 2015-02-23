(function($){
	$(function(){
		$('#user-login > div').css('position', 'relative')

		$('#user-login').on('submit', function(e){
			var submit = submit ? e.preventDefault() : true;

			$('#edit-pass, #edit-name').attr('readonly', 'readonly')
				.css('backgroundColor', '#efefef');

			var opts = {
				lines: 17, // The number of lines to draw
				length: 0, // The length of each line
				width: 10, // The line thickness
				radius: 60, // The radius of the inner circle
				corners: 1, // Corner roundness (0..1)
				rotate: 90, // The rotation offset
				direction: 1, // 1: clockwise, -1: counterclockwise
				color: '#ff6634', // #rgb or #rrggbb or array of colors
				speed: 1.1, // Rounds per second
				trail: 50, // Afterglow percentage
				shadow: false, // Whether to render a shadow
				hwaccel: false, // Whether to use hardware acceleration
				className: 'spinner', // The CSS class to assign to the spinner
				zIndex: 2e9, // The z-index (defaults to 2000000000)
				top: '40%', // Top position relative to parent
				left: '50%' // Left position relative to parent
			};

			var spinner = $('#user-login > div').spin(opts);

			var $b = $('#edit-submit').hide().clone()
			    .attr('id', 'nycc-logging-in').attr('disabled', 'disabled')
			    .attr('value', 'Logging in...');

			$('#edit-actions').append($b.show());

		});


	});


}(jQuery));