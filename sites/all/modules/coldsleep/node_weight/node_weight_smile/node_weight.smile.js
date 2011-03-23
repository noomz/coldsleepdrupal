(function($) {
  $.fn.extend({
    slideSmile: function(options) {
      var timer = null;
	  var isMoving = false;
      var size = 0;
	  var defaults = {
	    interval: 3000,
		speed: 500,
		pager: true,
		navigation: true,
		pager_position: 'top-right',
        activeIndex: 0,
        width: 960,
        height: 350,
        autoplay: true
      };
	  var options = $.extend(defaults, options);
	  return this.each(function() {
		var self = this;
		// Reset css prevent lost css style.
        $(this).css({'height': options.height, 'overflow': 'hidden', 'position': 'relative'});
		  
        // Should set on stylesheet.
        $('.node-weight-slides', this).css({
          'overflow': 'hidden',
		  'width': options.width,
		  'height': options.height
		});

        $('.node-weight-slide-wrapper', this).css({
          'position': 'relative'
        });

		if (options.navigation) {
		  // Previous.
		  $('.node-weight-prev', this).click(function(e) {
		    e.preventDefault();
		    previous();
		    if (options.autoplay) {
		      clearInterval(timer);
		      play();
		    }
		  });

		  // Next.
		  $('.node-weight-next', this).click(function(e) {
		    e.preventDefault();
		    // Reset timer.
		    next();
		    if (options.autoplay) {
		      clearInterval(timer);
		      play();
		    }
		  });
		}

        $('.node-weight-slides', this).children().each(function(i, item) {
          size++;
          $(item).css({
            'position': 'absolute',
            'top': 0,
            'left': 0,
            'z-index': 1
          });
          if (i == options.activeIndex) {
            $(item)
              .show()
              .css('z-index', 6);
          }
          else {
            $(item).hide();
          }

		  if (options.pager) {
		    // Add pager.
			if (i == 0) $('.node-weight-slide-pager', self).addClass('node-weight-slide-pager-'+options.pager_position);
		    var a = $('<a></a>').attr('href', '#').html(i+1).click(function(e) {
		      e.preventDefault();
		      go(i);
		    });
		    if (i == options.activeIndex) {
		      a.addClass('active');
		    }
		    $('.node-weight-slide-pager', self).append(a);
		  }
        });

		function go(i) {
		  if (i > options.activeIndex) {
			next(i);
		  }
		  else if (i < options.activeIndex) {
			previous(i);
		  }
		}
        
        function next(i) {
		  if (!isMoving) {
			isMoving = true;
		    var item;
            var old = $('.node-weight-slides', self).children().get(options.activeIndex);
            if (options.activeIndex >= size - 1) {
              item = $('.node-weight-slides', self).children().get(0);
		      options.activeIndex = 0;
            }
			else if (i != undefined && i != options.activeIndex) {
		      item = $('.node-weight-slides', self).children().get(i);
		      options.activeIndex = i;
			}
            else {
		      item = $('.node-weight-slides', self).children().get(options.activeIndex + 1);
		      options.activeIndex++;
            }
		    if (item) {
		      $(item).show().css({
		        'left': options.width,
		        'top': 0
		      }).animate({
		        'left': 0
		      }, options.speed, function() {
		        $(this).css('z-index', 6);
				isMoving = false;
				if (options.autoplay) {
			      clearInterval(timer);
				  play();
				}
		      });

		      $(old).animate({
		        'left': options.width * -1,
		      }, options.speed, function() {
		        $(this).hide().css('z-index', 1);
		      });

			  // Set active to pager.
			  $('.node-weight-slide-pager a', self).removeClass('active').eq(options.activeIndex).addClass('active');
		    }
		  }
        }

        function previous(i) {
		  if (!isMoving) {
			isMoving = true;
			clearInterval(timer);
		    var item;
            var old = $('.node-weight-slides', self).children().get(options.activeIndex);
            if (options.activeIndex <= 0) {
              item = $('.node-weight-slides', self).children().get(size - 1);
		      options.activeIndex = size - 1;
            }
			else if (i != undefined && i != options.activeIndex) {
		      item = $('.node-weight-slides', self).children().get(i);
		      options.activeIndex = i;
			}
            else {
		      item = $('.node-weight-slides', self).children().get(options.activeIndex - 1);
		      options.activeIndex--;
            }
		    if (item) {
		      $(item).show().css({
		        'left': options.width * -1,
		        'top': 0
		      }).animate({
		        'left': 0
		      }, options.speed, function() {
		        $(this).css('z-index', 6);
				isMoving = false;
				if (options.autoplay) {
			      clearInterval(timer);
				  play();
				}
		      });

		      $(old).animate({
		        'left': options.width
		      }, options.speed, function() {
		        $(this).hide().css('z-index', 1);
		      });
			  
			  // Set active to pager.
			  $('.node-weight-slide-pager a', self).removeClass('active').eq(options.activeIndex).addClass('active');
		    }
		  }
        }

        function play() {
          timer = setInterval(function() {
			next();
          }, options.interval);
        }

        if (options.autoplay) {
          play();
        }

	    var self = this;
	  });
	}
  });
})(jQuery);
