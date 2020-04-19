#!/bin/bash
yum -y install epel-release; yum -y install git vim rpm-build rpmdevtools
mkdir -p ~/rpmbuild/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
# git clone repo
spectool -g -R contrib/rpm/digibyte.spec
yum-builddep contrib/rpm/digibyte.spec