; intranet_nycc make file for local development
core = "7.x"
api = "2"

projects[drupal][version] = "7.x"
; include the d.o. profile base
includes[] = "drupal-org.make"

; +++++ TODO modules without versions +++++

projects[argfilters][subdir] = "custom"
projects[argfilters][type] = "module"
projects[argfilters][download][type] = "git"
projects[argfilters][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[Accordions for the policy pages][subdir] = "custom"
projects[Accordions for the policy pages][type] = "module"
projects[Accordions for the policy pages][download][type] = "git"
projects[Accordions for the policy pages][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[Forum Alerts Fix][subdir] = "custom"
projects[Forum Alerts Fix][type] = "module"
projects[Forum Alerts Fix][download][type] = "git"
projects[Forum Alerts Fix][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[Terms and conditions][subdir] = "custom"
projects[Terms and conditions][type] = "module"
projects[Terms and conditions][download][type] = "git"
projects[Terms and conditions][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[lync intergration][subdir] = "custom"
projects[lync intergration][type] = "module"
projects[lync intergration][download][type] = "git"
projects[lync intergration][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[mail url rewrite][subdir] = "custom"
projects[mail url rewrite][type] = "module"
projects[mail url rewrite][download][type] = "git"
projects[mail url rewrite][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc][subdir] = "custom"
projects[nycc][type] = "module"
projects[nycc][download][type] = "git"
projects[nycc][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc_content_validation][subdir] = "custom"
projects[nycc_content_validation][type] = "module"
projects[nycc_content_validation][download][type] = "git"
projects[nycc_content_validation][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc_social_icons][subdir] = "custom"
projects[nycc_social_icons][type] = "module"
projects[nycc_social_icons][download][type] = "git"
projects[nycc_social_icons][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc_user_profile][subdir] = "custom"
projects[nycc_user_profile][type] = "module"
projects[nycc_user_profile][download][type] = "git"
projects[nycc_user_profile][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[apachesolr_search_blocks][subdir] = "custom"
projects[apachesolr_search_blocks][type] = "module"
projects[apachesolr_search_blocks][download][type] = "git"
projects[apachesolr_search_blocks][download][url]="git@github.com:nicksmi/nyccintranet.git"

; +++++ Libraries +++++

; tinymce
libraries[tinymce][directory_name] = "tinymce"
libraries[tinymce][type] = "library"
libraries[tinymce][destination] = "libraries"
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "git@github.com:nicksmi/nyccintranet.git"

; +++++ Patches +++++

projects[redirect][patch][] = "redirect.circular-loops.1796596-146.patch" ; TODO add path to patch

