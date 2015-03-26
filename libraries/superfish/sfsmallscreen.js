/*
 * sf-Smallscreen v1.0b - Provides small-screen compatibility for the jQuery Superfish plugin.
 *
 * Developer's note:
 * Built as a part of the Superfish project for Drupal (http://drupal.org/project/superfish)
 * Found any bug? have any cool ideas? contact me right away! http://drupal.org/user/619294/contact
 *
 * jQuery version: 1.3.x or higher.
 *
 * Dual licensed under the MIT and GPL licenses:
 *  http://www.opensource.org/licenses/mit-license.php
 *  http://www.gnu.org/licenses/gpl.html
 */

(function($){

  $.fn.sfsmallscreen = function(options){
    options = $.extend({
      mode: 'inactive',
      breakpoint: Drupal.settings.nyccIntranetTheme.responsive_menu_enable_width,
      useragent: '',
      title: '',
      addSelected: true,
      menuClasses: true,
      hyperlinkClasses: true,
      excludeClass_menu: '',
      excludeClass_hyperlink: '',
      includeClass_menu: '',
      includeClass_hyperlink: ''
    }, options);

    // We need to clean up the menu from anything unnecessary.
    function refine(menu){
      if ($('.sf-megamenu', menu).length > 0){
        var refined = menu.clone();
        refined.find('div.sf-megamenu-column > ol').each(function(){
          $(this).replaceWith('<ul>' + $(this).html() + '</ul>');
        });
        refined.find('div.sf-megamenu-column').each(function(){
          $(this).replaceWith($(this).html());
        }).end().find('.sf-megamenu-wrapper > ol').each(function(){
          $(this).replaceWith($(this).html());
        }).end().find('li.sf-megamenu-wrapper').each(function(){
          $(this).replaceWith($(this).html());
        });
      } else {
        var refined = menu.clone();
      }
      refined.find('.sf-smallscreen-remove').each(function(){
        $(this).replaceWith($(this).html());
      }).end().find('.sf-sub-indicator, .sf-description').each(function(){
        $(this).remove();
      });
      return refined;
    }

    // Currently the only available reaction is converting the menu into a <select> element;
    // In the next version there will be another reaction that will create a "compact" version of
    // the menu, using <ul> element hence easy to style with CSS and so on and so forth.
    function toSelect(menu, level){
      var items = '';
      $(menu).children('li').each(function(){
        var list = $(this);
        list.children('a, span').each(function(){
          var item = $(this),
          path = item.is('a') ? item.attr('href') : '',
          itemClone = item.clone(),
          classes = (options.hyperlinkClasses) ? ((options.excludeClass_hyperlink && itemClone.hasClass(options.excludeClass_hyperlink)) ? itemClone.removeClass(options.excludeClass_hyperlink).attr('class') : itemClone.attr('class')) : '',
          classes = (options.includeClass_hyperlink && !itemClone.hasClass(options.includeClass_hyperlink)) ? ((options.hyperlinkClasses) ? itemClone.addClass(options.includeClass_hyperlink).attr('class') : options.includeClass_hyperlink) : classes,
          classes = (classes) ? ' class="' + classes + '"' : '',
          disable = item.is('span') ? ' disabled="disabled"' : '',
          subIndicator = 1 < level ? Array(level).join('-') + ' ' : '';
          items += '<option value="' + path + '"' + classes + disable + '>' + subIndicator + $.trim(item.text()) +'</option>';
          list.find('> ul').each(function(){
            items += toSelect(this, level + 1);
          });
        });
      });
      return items;
    }

    // Create the new version, hide the original.
    function convert(menu){
      var menuClone = menu.clone(), classes = (options.menuClasses) ? ((options.excludeClass_menu && menuClone.hasClass(options.excludeClass_menu)) ? menuClone.removeClass(options.excludeClass_menu).attr('class') : menuClone.attr('class')) : '',
      classes = (options.includeClass_menu && !menuClone.hasClass(options.includeClass_menu)) ? ((options.menuClasses) ? menuClone.addClass(options.includeClass_menu).attr('class') : options.includeClass_menu) : classes,
      classes = (classes) ? ' class="' + classes + '"' : '';
      if ($('#' + menu.attr('id') + '-select').length == 0){
        var selectList = $('<select' + classes + ' id="' + menu.attr('id') + '-select"/>'),
        refinedMenu = refine(menu);
        console.log(refinedMenu);
        newMenu = toSelect(refinedMenu, 1);
        selectList.append('<option>' + options.title + '</option>').append(newMenu).change(function(){
          window.location = selectList.val();
        });
        if (options.addSelected) {
          selectList.find('.active').attr("selected", !0);
        }
        menu.before(selectList).hide();
      }
    }

    // Turn everything back to normal.
    function turnBack(menu){
      var id = '#' + menu.attr('id');
      $(id + '-select').remove();
      $(id).show();
    }


    function responsiveMenuShow(menu){
      if($('#' + $(menu).attr('id') + '-resp').length == 0){
        buildMenu = $([
          "<div id='" + $(menu).attr('id') + "-resp' class='sf-resp'>",
          " <a href='#' class='toggleMenu'>",
          "   <i class='fa fa-bars'></i>",
          " </a>",
          " <ul class='mobileNav'>",
          " </ul>",
          "</div>"
        ].join(""));

        buildMenu = $(buildMenu).children('ul').append(refine(menu).html()).parent('div');

        $('.mobileNav [style]', buildMenu).each(function(i, item){
          $(item).removeAttr('style');
        });

        $(menu).closest('.l-region--topmenu').hide().closest('.l-container').append(buildMenu);

        $('#' + $(menu).attr('id') + '-resp').on('click', '.toggleMenu', function(e){
            e.preventDefault();
            $(this).toggleClass('active');
            $('.mobileNav').slideToggle('slow');
        });

        $(".toggleMenu").css("display", "inline-block");
        if (!$(".toggleMenu").hasClass("active")) {
          $(".mobileNav").hide();
        } else {
          $(".mobileNav").show();
        }
        $(".mobileNav li").unbind('mouseenter mouseleave');
        $(".mobileNav li a.menuparent").unbind('click').bind('click', function (e) {
          // must be attached to anchor element to prevent bubbling
          e.preventDefault();
          $(this).parent("li").toggleClass("hover");
        });
      }

        /*


      var $refined = refine(menu);
      console.log($refined);
      var newMenu = $('<a href="#" class="toggleMenu"><i class="fa fa-bars"></i></a><ul class="mobileNav"></ul>');
      $(newMenu).children('ul:first').append($refined);

      console.log(newMenu);
      $($refined).prepend('<a href="#" class="toggleMenu"><i class="fa fa-bars"></i></a>').children('ul:first').addClass('mobileNav');
      $(menu).hide();
      //console.log($(menu).closest('.navbar'));
      $(menu).closest('.navbar').append(($refined).html());
      */
    }

    function responsiveMenuHide(menu){
      $('#' + menu.attr('id') + '-resp').remove();
      $('#' + menu.attr('id')).closest('.l-region--topmenu').show();

        $(".toggleMenu").css("display", "none");
        $(".mobileNav").show();
        $(".mobileNav li").removeClass("hover");
        $(".mobileNav li a").unbind('click');
        $(".mobileNav li").unbind('mouseenter mouseleave').bind('mouseenter mouseleave', function () {
            // must be attached to li so that mouseleave is not triggered when hover over submenu
            $(this).toggleClass('hover');
        });

    }
    

    // Return original object to support chaining.
    return this.each(function(){
      var menu = $(this),
      mode = options.mode;
      // The rest is crystal clear, isn't it? :)
      switch (mode){
        case 'always_active' :
          responsiveMenuShow(menu);
        break;
        case 'window_width' :
          if ($(window).width() < options.breakpoint){
            responsiveMenuShow(menu);
          }
          var timer;
          $(window).resize(function(){
            clearTimeout(timer);
            timer = setTimeout(function(){
              if ($(window).width() < options.breakpoint){
                responsiveMenuShow(menu);
              }
              else {
                responsiveMenuHide(menu);
              }
            }, 100);
          });
        break;
        case 'useragent_custom' :
          if (options.useragent != ''){
            var ua = RegExp(options.useragent, 'i');
            if (navigator.userAgent.match(ua)){
              responsiveMenuShow(menu);
            }
          }
        break;
        case 'useragent_predefined' :
          if (navigator.userAgent.match(/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od|ad)|iris|kindle|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i)){
            responsiveMenuShow(menu);
          }
        break;
      }
    });
  };
})(jQuery);



/*
jQuery(document).ready(function(){
  var $ = jQuery;
  var ww = document.body.clientWidth;

  function adjustMenu(){
        if (ww < 960) {
            console.log('show responsive');
        $(".toggleMenu").css("display", "inline-block");
        if (!$(".toggleMenu").hasClass("active")) {
            $(".mobileNav").hide();
        } else {
            $(".mobileNav").show();
        }
        $(".mobileNav li").unbind('mouseenter mouseleave');
        $(".mobileNav li a.menuparent").unbind('click').bind('click', function (e) {
            // must be attached to anchor element to prevent bubbling
            e.preventDefault();
            $(this).parent("li").toggleClass("hover");
        });
    }
    else if (ww >= 960) {
            console.log('hide responsive');
        $(".toggleMenu").css("display", "none");
        $(".mobileNav").show();
        $(".mobileNav li").removeClass("hover");
        $(".mobileNav li a").unbind('click');
        $(".mobileNav li").unbind('mouseenter mouseleave').bind('mouseenter mouseleave', function () {
            // must be attached to li so that mouseleave is not triggered when hover over submenu
            $(this).toggleClass('hover');
        });
    }
  }

/*
  $('.toggleMenu').click(function(e){
    e.preventDefault();
    $(this).toggleClass('active');
    $('.mobileNav').toggle();
  });
*/
/*
  $(window).bind('resize orientationchange', function(){
      ww = document.body.clientWidth;
      adjustMenu();
  });


  adjustMenu();



});
 */