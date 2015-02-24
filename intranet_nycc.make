; intranet_nycc make file for local development
core = "7.x"
api = "2"

projects[drupal][version] = "7.x"
; include the d.o. profile base
includes[] = "drupal-org.make"

; +++++ TODO modules without versions +++++

projects[argfilters][version] = "" ; TODO add version
projects[argfilters][subdir] = "custom"

projects[Accordions for the policy pages][version] = "" ; TODO add version
projects[Accordions for the policy pages][subdir] = "custom"

projects[Forum Alerts Fix][version] = "" ; TODO add version
projects[Forum Alerts Fix][subdir] = "custom"

projects[Terms and conditions][version] = "" ; TODO add version
projects[Terms and conditions][subdir] = "custom"

projects[lync intergration][version] = "" ; TODO add version
projects[lync intergration][subdir] = "custom"

projects[mail url rewrite][version] = "" ; TODO add version
projects[mail url rewrite][subdir] = "custom"

projects[nycc][version] = "" ; TODO add version
projects[nycc][subdir] = "custom"

projects[nycc_content_validation][version] = "" ; TODO add version
projects[nycc_content_validation][subdir] = "custom"

projects[nycc_forms][version] = "" ; TODO add version
projects[nycc_forms][subdir] = "custom"

projects[nycc_forum_enhancements][version] = "" ; TODO add version
projects[nycc_forum_enhancements][subdir] = "custom"

projects[nycc_group_import][version] = "" ; TODO add version
projects[nycc_group_import][subdir] = "custom"

projects[nycc_social_icons][version] = "" ; TODO add version
projects[nycc_social_icons][subdir] = "custom"

projects[nycc_user_profile][version] = "" ; TODO add version
projects[nycc_user_profile][subdir] = "custom"

projects[apachesolr_search_blocks][version] = "" ; TODO add version
projects[apachesolr_search_blocks][subdir] = "custom"

; +++++ Libraries +++++

; tinymce
libraries[tinymce][directory_name] = "tinymce"
libraries[tinymce][type] = "library"
libraries[tinymce][destination] = "libraries"
libraries[tinymce][download][type] = "get"
libraries[tinymce][download][url] = "" ; TODO add download URI

; +++++ Patches +++++

projects[redirect][patch][] = "redirect.circular-loops.1796596-146.patch" ; TODO add path to patch

