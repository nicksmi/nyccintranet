(function ($) {

  /**
   * The recommended way for producing HTML markup through JavaScript is to write
   * theming functions. These are similiar to the theming functions that you might
   * know from 'phptemplate' (the default PHP templating engine used by most
   * Drupal themes including Omega). JavaScript theme functions accept arguments
   * and can be overriden by sub-themes.
   *
   * In most cases, there is no good reason to NOT wrap your markup producing
   * JavaScript in a theme function.
   */
  Drupal.theme.prototype.intranetExampleButton = function (path, title) {
    // Create an anchor element with jQuery.
    return $('<a href="' + path + '" title="' + title + '">' + title + '</a>');
  };

  /**
   * Behaviors are Drupal's way of applying JavaScript to a page. In short, the
   * advantage of Behaviors over a simple 'document.ready()' lies in how it
   * interacts with content loaded through Ajax. Opposed to the
   * 'document.ready()' event which is only fired once when the page is
   * initially loaded, behaviors get re-executed whenever something is added to
   * the page through Ajax.
   *
   * You can attach as many behaviors as you wish. In fact, instead of overloading
   * a single behavior with multiple, completely unrelated tasks you should create
   * a separate behavior for every separate task.
   *
   * In most cases, there is no good reason to NOT wrap your JavaScript code in a
   * behavior.
   *
   * @param context
   *   The context for which the behavior is being executed. This is either the
   *   full page or a piece of HTML that was just added through Ajax.
   * @param settings
   *   An array of settings (added through drupal_add_js()). Instead of accessing
   *   Drupal.settings directly you should use this because of potential
   *   modifications made by the Ajax callback that also produced 'context'.
   */

  Drupal.behaviors.intranetHoverNewsTab = {
    attach: function (context, settings) {



    $('.l-region--topbar', context).once('intranet', function(){



          Drupal.behaviors.intranetNewsCarouselCreateImageDiv();

          var speed = Drupal.settings.nyccIntranetTheme.carousel_speed;

          Drupal.behaviors.intranetNewsCarouselCheckActive();   
          run = setInterval('Drupal.behaviors.intranetNewsCarouselRotate()', speed);


          $('a[data-toggle="tab"]').on('shown.bs.tab', function (e) {

              Drupal.behaviors.intranetNewsCarouselCreateImageDiv();

              $('.tab-pane .news-summary-link.active').removeClass('active');
              Drupal.behaviors.intranetNewsCarouselCheckActive();   
          }); 


          $('.nav-tabs > li > a').hover( 
                function(){
                  var e = $(this);
                  intentDelay = setTimeout(function(){
                    $(e).tab('show');
                  }, 150);
                },
                
                function(){
                    clearTimeout(intentDelay);
                }                              
          );

          $('.news-summary-link').hover( function () { 
            clearInterval(run);
            Drupal.behaviors.intranetNewsCarouselShowImage(this) 
            }, function() 
            {
                run = setInterval('Drupal.behaviors.intranetNewsCarouselRotate()', speed);
            }
          );

          $('.tab-news-image').hover( function () { 
            clearInterval(run);
          },

            function() {
                run = setInterval('Drupal.behaviors.intranetNewsCarouselRotate()', speed);
            }
          );



     });
    }
  };


  Drupal.behaviors.intranetNewsCarouselCreateImageDiv = function (context, settings) {
    
    var imgDiv = "<div class='tab-news-image'></div>";
        
    if($('.tab-pane.active .view-content .tab-news-image').length == 0){ 

      $('.tab-pane.active .view-content').append(imgDiv);
    }

  };


  Drupal.behaviors.intranetNewsCarouselCheckActive = function (context, settings) {

      if($('.tab-pane.active .news-summary-link.active').length == 0){ 
          Drupal.behaviors.intranetNewsCarouselShowImage($('.tab-pane.active .news-summary-link:first'));
      }
  };



  Drupal.behaviors.intranetNewsCarouselRotate = function (context, settings) {
      var selector = $('.tab-pane.active .news-summary-link.active').parent(".views-row").next(".views-row").children(".news-summary-link");

      if(selector.length == 0)
      { 
        selector = $('.tab-pane.active .news-summary-link:first');
      }
      Drupal.behaviors.intranetNewsCarouselShowImage(selector);
  };




  Drupal.behaviors.intranetNewsCarouselShowImage = function(link) {

        $('.tab-pane .news-summary-link.active').removeClass('active');

        $(link).addClass('active');
        var imgDiv = $(link).next(".field--type-image").clone();

        imgDiv.css("display", "block");

        $('.tab-news-image').empty();
        $('.tab-news-image').append(imgDiv);

   };



  Drupal.behaviors.intranetExampleBehavior = {
    attach: function (context, settings) {
      // By using the 'context' variable we make sure that our code only runs on
      // the relevant HTML. Furthermore, by using jQuery.once() we make sure that
      // we don't run the same piece of code for an HTML snippet that we already
      // processed previously. By using .once('foo') all processed elements will
      // get tagged with a 'foo-processed' class, causing all future invocations
      // of this behavior to ignore them.
      $('.some-selector', context).once('foo', function () {
        // Now, we are invoking the previously declared theme function using two
        // settings as arguments.
        var $anchor = Drupal.theme('intranetExampleButton', settings.myExampleLinkPath, settings.myExampleLinkTitle);

        // The anchor is then appended to the current element.
        $anchor.appendTo(this);
      });
    }
  };



})(jQuery);
