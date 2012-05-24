%include lofar/CommonTuples.h

%template( Coordinate3DDouble ) DAL::Coordinate3D<double>;
AddAttributeAndVector( Coordinate3DDouble, %arg(DAL::Coordinate3D<double>) );

