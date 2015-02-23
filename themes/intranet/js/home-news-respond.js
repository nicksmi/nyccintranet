(function($){
    $(function(){
        var ww = document.body.clientWidth;
        var breakpoint = 780;
        var resizeTimeout;
        var tabs = [];

        var tabContent = $('div.l-region--home-news div.tab-content');

        function updateNews(){
            ww = document.body.clientWidth;
            var n = $('[id^=mobNews]');

            if(ww <= breakpoint && n.length ===0){
                showMobileNews();
            }
            else if(ww > breakpoint && n.length !== 0){
                hideMobileNews(n);
            }
        }

        function showMobileNews(){
            $('.tab-pane > div > div.view-content').each(function(i, div) {
               $(div).hide();
            });
            buildMobileNews();
        }

        function hideMobileNews(n){
            $('.tab-pane > div > div.view-content').each(function(i, div) {
                $(div).show();
            });
            $(n).remove();
        }

        $('.tab-pane', tabContent).each(function(tabIndex, tab){
            var thisTab = [];
            $('.views-row', tab).each(function(i, vr){
                var title = $('h3.node__title', vr).html();
                var subtext = $('div.field__item p', vr).html();
                var articleSrc = $('a' ,vr).attr('href');
                var imgSrc = $('.field--type-image img', vr).attr('src');

                var article = { title: title,
                    subtext: subtext,
                    articleSrc: articleSrc,
                    imgSrc: imgSrc
                };
                thisTab.push(article);
            });
            tabs.push(thisTab);
        });

        function buildMobileNews(){
            for(var i = 0; i < tabs.length; i++){
                var m = $('<div class="mobNews" id="mobNews' + i + '"></div>');

                for(var ti = 0; ti < tabs[i].length; ti++){
                    $(m).append('<div><div class="mobNewsContent"><h4>' + tabs[i][ti].title + '</h4><p>' + tabs[i][ti].subtext + '</p></div><a class="mobNewsBtn" href="' + tabs[i][ti].articleSrc + '">&raquo;</a></div>');
                }
                $('.tab-pane > div', tabContent).eq(i).prepend(m);
            }
        }

        // Bind to the size of our viewport changing
        $(window).bind('resize orientationchange', function(){
            clearTimeout(resizeTimeout);

            resizeTimeout = setTimeout(function(){
                updateNews();
            }, 300);
        });

        updateNews();
    });
})(jQuery);
