(function($){
	$(function(){
		$('input, textarea').placeholder();

		userInfoWrapperToggle();

		$(document).on('blur', 'input, textarea', function() {
    			setTimeout(function() {
        			window.scrollTo($(document).scrollLeft(), $(document).scrollTop());
    			}, 0);
		});

	});


	var userInfoWrapperToggle = function(){
		var $tog = $('.user-info-wrapper-toggle');
	    var $e = $('.user-info-wrapper');
	    var down = 'fa-angle-double-down';
	    var up = 'fa-angle-double-up';

		var toggleWrapper = function(){
			if($e.attr('data-visible') == 'true'){
				// Hide the user info wrapper
				$e.animate({top:'-35px'}, 400, function(){
					switchIcon($('.fa', $tog));
					$tog.hide().removeClass('inline').slideDown('slow');
					})
				.attr('data-visible', 'false');

			}
			else{
				// Show the user-info-wrapper
				$tog.slideUp('fast', function(){
					$(this).addClass('inline').show();
					switchIcon($('.fa', $tog));
					$e.animate({top:'0'},400).attr('data-visible', 'true');
				});

			}
		};


		var switchIcon = function($ico){
			if($ico.attr('data-ico') === 'down'){
				$ico.removeClass(down).addClass(up).attr('data-ico', 'up');
			}
			else{
				$ico.removeClass(up).addClass(down).attr('data-ico', 'down');
			}
		};

		var toggleRegisterEvent = function(){
			$tog.unbind().on('click tap', function(){
				toggleWrapper();
			});
		};

		toggleRegisterEvent();
	};

}(jQuery));

