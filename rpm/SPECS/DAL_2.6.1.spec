Name:		DAL
Version:	2.6.1
Release:	2%{?dist}
Summary:	The DAL provides access to radio astronomy data produced by the LOFAR telescope, operated by ASTRON (Netherlands Institute for Radio Astronomy).

Group:		Software
License:	GNU Lesser General Public License (LGPL)
URL:		https://github.com/nextgen-astrodata/%{name}
Source0:	%{name}_v%{version}.tar.gz
Prefix:         /opt/%{name}

BuildRequires: cmake	
BuildRequires: make	
BuildRequires: gcc	
BuildRequires: swig	
BuildRequires: python-devel	
BuildRequires: hdf5-devel

%description
DAL is a reference implementation to access all HDF5 data fields with long-term compatibility in mind. DAL is written in C++ and offers Python bindings for all its functionality. It also comes with API documentation, a user manual, small example programs + data, and a test suite.


%prep
%setup -q 


%build
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=%{prefix} ..
make %{?_smp_mflags}
#echo "BUILDROOT = %{buildroot}"

%install
cd build
make install DESTDIR=%{buildroot}

%check
cd build
ctest -j 3 

%files
%dir /opt/DAL/
%dir /opt/DAL/bin/
%dir /opt/DAL/include/
%dir /opt/DAL/lib/
%dir /opt/DAL/lib64/
/opt/DAL/bin/*
/opt/DAL/include/dal/*
/opt/DAL/lib/*
/opt/DAL/lib64/python2.7/site-packages/dal/*

%changelog
* Tue Jan 30 2019 Reinoud Bokhorst <rbokhorst@astron.nl> - 2.6.1-1
- Initial DAL package
