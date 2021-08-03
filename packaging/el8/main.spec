Name: ::package_name::
Version: ::package_version::
Release: ::package_build_version::%{?dist}
Summary: ::package_description_short::
License: ::package_licence::
URL: ::package_url::
Source0: %{name}-%{version}.tar.gz
BuildArch: ::package_architecture_el::

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root

%description
::package_title::
::package_description_long::

%prep
%setup -q

%build
make

%install
make DESTDIR=%{buildroot} install

%files
/opt/45drives/*
/etc/ld.so.conf.d/45drives.conf

%changelog
* Fri Jul 30 2021 Joshua Boudreau <jboudreau@45drives.com> 0.1.0-1
- First autopackage build