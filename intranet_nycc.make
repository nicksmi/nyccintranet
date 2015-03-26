; nycc_intranet make file for local development
core = "7.x"
api = "2"

projects[drupal][version] = "7.x"
; include the d.o. profile base
includes[] = "drupal-org.make"

; +++++ TODO modules without versions +++++

projects[lync intergration][subdir] = "custom"
projects[lync intergration][type] = "module"
projects[lync intergration][download][type] = "git"
projects[lync intergration][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc][subdir] = "custom"
projects[nycc][type] = "module"
projects[nycc][download][type] = "git"
projects[nycc][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[apachesolr_search_blocks][subdir] = "custom"
projects[apachesolr_search_blocks][type] = "module"
projects[apachesolr_search_blocks][download][type] = "git"
projects[apachesolr_search_blocks][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc_content_types][subdir] = "custom"
projects[nycc_content_types][type] = "module"
projects[nycc_content_types][download][type] = "git"
projects[nycc_content_types][download][url]="git@github.com:nicksmi/nyccintranet.git"

projects[nycc_social][subdir] = "custom"
projects[nycc_social][type] = "module"
projects[nycc_social][download][type] = "git"
projects[nycc_social][download][url]="git@github.com:nicksmi/nyccintranet.git"

; +++++ Profile +++++
projects[nycc_intranet][type] = "profile"
projects[nycc_intranet][download][type] = "git"
projects[nycc_intranet][download][url]="git@github.com:nicksmi/nyccintranet.git"


; +++++ Patches +++++

; projects[redirect][patch][] = "redirect.circular-loops.1796596-146.patch" ; TODO add path to patch

