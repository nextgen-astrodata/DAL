%include lofar/CommonTuples.h

%template( Coordinate3DDouble ) dal::Coordinate3D<double>;
AddAttributeAndVector( Coordinate3DDouble, %arg(dal::Coordinate3D<double>) );

