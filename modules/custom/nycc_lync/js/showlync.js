var nameCtrl = null;

jQuery(document).ready(function () {
    if(window.ActiveXObject) 
    {
      nameCtrl = new ActiveXObject("Name.NameCtrl");
    } 
    else 
    {
      try 
      {
        nameCtrl = new ActiveXObject("Name.NameCtrl");
      } 
      catch (e)
      {
        nameCtrl = (function(b){
          var c = null;
          try {
            c = document.getElementById(b);
            if (!Boolean(c) && (Boolean(navigator.mimeTypes) && navigator.mimeTypes[b] && navigator.mimeTypes[b].enabledPlugin)) {
              var a = document.createElement("object");
              a.id = b;
              a.type = b;
              a.width = "0";
              a.height = "0";
              a.style.setProperty("visibility", "hidden", "");
              document.body.appendChild(a);
              c = document.getElementById(b)
            }
          } catch (d) {
            c = null
          }
        
        return c
      })("application/x-sharepoint-uc");
    }
  }
});

function showLyncPresencePopup(userName, target) {
  if(nameCtrl && nameCtrl.PresenceEnabled){
    
    var eLeft = jQuery(target).offset().left;
    var x = eLeft - jQuery(window).scrollLeft();

    var eTop = jQuery(target).offset().top;
    var y = eTop - jQuery(window).scrollTop();
  
    nameCtrl.ShowOOUI(userName, 0, x, y);  
  }
}

function hideLyncPresencePopup() {
  if (window.ActiveXObject) {
    if (!nameCtrl) {
      return;
    }
  
    nameCtrl.HideOOUI();
  }
}