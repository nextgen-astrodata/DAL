
// File: index.xml

// File: classLDA_1_1Attribute.xml
%feature("docstring") LDA::Attribute "

Represents an attribute containing a scalar or a string.

C++ includes: h5attribute.h ";

%feature("docstring")  LDA::Attribute::Attribute "";

%feature("docstring")  LDA::Attribute::get "

Returns the value of this attribute, retrieved from the HDF5 file. An
exception is thrown if the attribute does not already exist. ";

%feature("docstring")  LDA::Attribute::set "

Stores the value of this attribute in the HDF5 file. The attribute is
created if it does not already exist. ";


// File: classLDA_1_1Attribute_3_01std_1_1vector_3_01T_01_4_01_4.xml
%feature("docstring") LDA::Attribute< std::vector< T > > "

Represents an attribute containing a vector of scalars or strings.

C++ includes: h5attribute.h ";

%feature("docstring")  LDA::Attribute< std::vector< T > >::Attribute "
";

%feature("docstring")  LDA::Attribute< std::vector< T > >::get "

Returns the value of this attribute, retrieved from the HDF5 file. An
exception is thrown if the attribute does not already exist. ";

%feature("docstring")  LDA::Attribute< std::vector< T > >::set "

Stores the value of this attribute in the HDF5 file. The attribute is
created if it does not already exist. ";


// File: classLDA_1_1AttributeBase.xml
%feature("docstring") LDA::AttributeBase "

Represents core functionality for an attribute inside a group.

C++ includes: h5attribute.h ";

%feature("docstring")  LDA::AttributeBase::name "

Returns the name of this element in the HDF5 file. ";

%feature("docstring")  LDA::AttributeBase::exists "

Returns whether this element exists in the HDF5 file. ";

%feature("docstring")  LDA::AttributeBase::remove "

Removes this element from the HDF5 file. Useful for porting,
repairing, or otherwise modifying files on a structural level. ";


// File: classLDA_1_1BeamFormedFile.xml
%feature("docstring") LDA::BeamFormedFile "

Interface for Beam-formed Data as described in ICD003.

C++ includes: BeamFormedFile.h ";

%feature("docstring")  LDA::BeamFormedFile::BeamFormedFile "";

%feature("docstring")  LDA::BeamFormedFile::createOfflineOnline "";

%feature("docstring")  LDA::BeamFormedFile::BFFormat "";

%feature("docstring")  LDA::BeamFormedFile::BFVersion "";

%feature("docstring")  LDA::BeamFormedFile::expTimeStartUTC "";

%feature("docstring")  LDA::BeamFormedFile::expTimeStartMJD "";

%feature("docstring")  LDA::BeamFormedFile::expTimeStartTAI "";

%feature("docstring")  LDA::BeamFormedFile::expTimeEndUTC "";

%feature("docstring")  LDA::BeamFormedFile::expTimeEndMJD "";

%feature("docstring")  LDA::BeamFormedFile::expTimeEndTAI "";

%feature("docstring")  LDA::BeamFormedFile::totalIntegrationTime "";

%feature("docstring")  LDA::BeamFormedFile::observationDatatype "";

%feature("docstring")  LDA::BeamFormedFile::subArrayPointingDiameter "";

%feature("docstring")  LDA::BeamFormedFile::bandwidth "";

%feature("docstring")  LDA::BeamFormedFile::beamDiameter "";

%feature("docstring")  LDA::BeamFormedFile::weatherTemperature "";

%feature("docstring")  LDA::BeamFormedFile::weatherHumidity "";

%feature("docstring")  LDA::BeamFormedFile::systemTemperature "";

%feature("docstring")  LDA::BeamFormedFile::nofSubArrayPointings "";

%feature("docstring")  LDA::BeamFormedFile::subArrayPointing "";

%feature("docstring")  LDA::BeamFormedFile::sysLog "";


// File: classLDA_1_1BF__BeamGroup.xml
%feature("docstring") LDA::BF_BeamGroup "";

%feature("docstring")  LDA::BF_BeamGroup::nofStations "";

%feature("docstring")  LDA::BF_BeamGroup::stationsList "";

%feature("docstring")  LDA::BF_BeamGroup::pointRA "";

%feature("docstring")  LDA::BF_BeamGroup::pointDEC "";

%feature("docstring")  LDA::BF_BeamGroup::pointOffsetRA "";

%feature("docstring")  LDA::BF_BeamGroup::pointOffsetDEC "";

%feature("docstring")  LDA::BF_BeamGroup::foldedData "";

%feature("docstring")  LDA::BF_BeamGroup::foldPeriod "";

%feature("docstring")  LDA::BF_BeamGroup::foldPeriodUnit "";

%feature("docstring")  LDA::BF_BeamGroup::dedispersion "";

%feature("docstring")  LDA::BF_BeamGroup::dedispersionMeasure "";

%feature("docstring")  LDA::BF_BeamGroup::dedispersionMeasureUnit "";

%feature("docstring")  LDA::BF_BeamGroup::nofStokes "";

%feature("docstring")  LDA::BF_BeamGroup::stokesComponents "";

%feature("docstring")  LDA::BF_BeamGroup::complexVoltages "";

%feature("docstring")  LDA::BF_BeamGroup::signalSum "";

%feature("docstring")  LDA::BF_BeamGroup::stokes "";

%feature("docstring")  LDA::BF_BeamGroup::coordinates "";


// File: classLDA_1_1BF__ProcessingHistory.xml
%feature("docstring") LDA::BF_ProcessingHistory "";

%feature("docstring")  LDA::BF_ProcessingHistory::parsetObs "";

%feature("docstring")  LDA::BF_ProcessingHistory::logPresto "";

%feature("docstring")  LDA::BF_ProcessingHistory::parFile "";


// File: classLDA_1_1BF__StokesDataset.xml
%feature("docstring") LDA::BF_StokesDataset "";

%feature("docstring")  LDA::BF_StokesDataset::stokesComponent "";

%feature("docstring")  LDA::BF_StokesDataset::nofChannels "";

%feature("docstring")  LDA::BF_StokesDataset::nofSubbands "";

%feature("docstring")  LDA::BF_StokesDataset::nofSamples "";


// File: classLDA_1_1BF__SubArrayPointing.xml
%feature("docstring") LDA::BF_SubArrayPointing "";

%feature("docstring")  LDA::BF_SubArrayPointing::nofStations "";

%feature("docstring")  LDA::BF_SubArrayPointing::stationsList "";

%feature("docstring")  LDA::BF_SubArrayPointing::pointRA "";

%feature("docstring")  LDA::BF_SubArrayPointing::pointDEC "";

%feature("docstring")  LDA::BF_SubArrayPointing::clockRate "";

%feature("docstring")  LDA::BF_SubArrayPointing::clockRateUnit "";

%feature("docstring")  LDA::BF_SubArrayPointing::nofSamples "";

%feature("docstring")  LDA::BF_SubArrayPointing::samplingRate "";

%feature("docstring")  LDA::BF_SubArrayPointing::samplingRateUnit "";

%feature("docstring")  LDA::BF_SubArrayPointing::channelsPerSubband "";

%feature("docstring")  LDA::BF_SubArrayPointing::subbandWidth "";

%feature("docstring")  LDA::BF_SubArrayPointing::subbandWidthUnit "";

%feature("docstring")  LDA::BF_SubArrayPointing::channelWidth "";

%feature("docstring")  LDA::BF_SubArrayPointing::channelWidthUnit "";

%feature("docstring")  LDA::BF_SubArrayPointing::nofBeams "";

%feature("docstring")  LDA::BF_SubArrayPointing::beam "";


// File: classLDA_1_1CommonAttributesFile.xml
%feature("docstring") LDA::CommonAttributesFile "

Wraps an HDF5 file implementing the Common LOFAR Attributes.

C++ includes: CommonAttributesFile.h ";

%feature("docstring")  LDA::CommonAttributesFile::CommonAttributesFile
"";

%feature("docstring")  LDA::CommonAttributesFile::groupType "";

%feature("docstring")  LDA::CommonAttributesFile::fileName "";

%feature("docstring")  LDA::CommonAttributesFile::fileDate "";

%feature("docstring")  LDA::CommonAttributesFile::fileType "";

%feature("docstring")  LDA::CommonAttributesFile::telescope "";

%feature("docstring")  LDA::CommonAttributesFile::observer "";

%feature("docstring")  LDA::CommonAttributesFile::projectID "";

%feature("docstring")  LDA::CommonAttributesFile::projectTitle "";

%feature("docstring")  LDA::CommonAttributesFile::projectPI "";

%feature("docstring")  LDA::CommonAttributesFile::projectCOI "";

%feature("docstring")  LDA::CommonAttributesFile::projectContact "";

%feature("docstring")  LDA::CommonAttributesFile::observationID "";

%feature("docstring")  LDA::CommonAttributesFile::observationStartUTC
"";

%feature("docstring")  LDA::CommonAttributesFile::observationStartMJD
"";

%feature("docstring")  LDA::CommonAttributesFile::observationStartTAI
"";

%feature("docstring")  LDA::CommonAttributesFile::observationEndUTC "";

%feature("docstring")  LDA::CommonAttributesFile::observationEndMJD "";

%feature("docstring")  LDA::CommonAttributesFile::observationEndTAI "";

%feature("docstring")
LDA::CommonAttributesFile::observationNofStations "";

%feature("docstring")
LDA::CommonAttributesFile::observationStationsList "";

%feature("docstring")
LDA::CommonAttributesFile::observationNofBitsPerSample "";

%feature("docstring")  LDA::CommonAttributesFile::clockFrequency "";

%feature("docstring")  LDA::CommonAttributesFile::clockFrequencyUnit "";

%feature("docstring")  LDA::CommonAttributesFile::antennaSet "";

%feature("docstring")  LDA::CommonAttributesFile::filterSelection "";

%feature("docstring")  LDA::CommonAttributesFile::target "";

%feature("docstring")  LDA::CommonAttributesFile::systemVersion "";

%feature("docstring")  LDA::CommonAttributesFile::pipelineName "";

%feature("docstring")  LDA::CommonAttributesFile::pipelineVersion "";

%feature("docstring")  LDA::CommonAttributesFile::ICDNumber "";

%feature("docstring")  LDA::CommonAttributesFile::ICDVersion "";

%feature("docstring")  LDA::CommonAttributesFile::notes "";


// File: classLDA_1_1Coordinate.xml
%feature("docstring") LDA::Coordinate "";

%feature("docstring")  LDA::Coordinate::coordinateType "";

%feature("docstring")  LDA::Coordinate::storageType "";

%feature("docstring")  LDA::Coordinate::nofAxes "";

%feature("docstring")  LDA::Coordinate::axisNames "";

%feature("docstring")  LDA::Coordinate::axisUnits "";

%feature("docstring")  LDA::Coordinate::referenceValue "";

%feature("docstring")  LDA::Coordinate::referencePixel "";

%feature("docstring")  LDA::Coordinate::increment "";

%feature("docstring")  LDA::Coordinate::pc "";

%feature("docstring")  LDA::Coordinate::axisValuesPixel "";

%feature("docstring")  LDA::Coordinate::axisValuesWorld "";


// File: classLDA_1_1CoordinatesGroup.xml
%feature("docstring") LDA::CoordinatesGroup "";

%feature("docstring")  LDA::CoordinatesGroup::refLocationValue "";

%feature("docstring")  LDA::CoordinatesGroup::refLocationUnit "";

%feature("docstring")  LDA::CoordinatesGroup::refLocationFrame "";

%feature("docstring")  LDA::CoordinatesGroup::refTimeValue "";

%feature("docstring")  LDA::CoordinatesGroup::refTimeUnit "";

%feature("docstring")  LDA::CoordinatesGroup::refTimeFrame "";

%feature("docstring")  LDA::CoordinatesGroup::nofCoordinates "";

%feature("docstring")  LDA::CoordinatesGroup::nofAxes "";

%feature("docstring")  LDA::CoordinatesGroup::coordinateTypes "";

%feature("docstring")  LDA::CoordinatesGroup::coordinate "";


// File: classLDA_1_1HDF5DatasetBase.xml
%feature("docstring") LDA::HDF5DatasetBase "

Provides generic functionality for HDF5 Datasets.

C++ includes: HDF5DatasetBase.h ";

%feature("docstring")  LDA::HDF5DatasetBase::create "

Creates a new dataset with dimensions sized `dims` and can be scaled
up to `maxdims`. The rank of the dataset is dims.size() ==
maxdims.size(). A maximum of -1 represents an unbounded dimension.

If a `filename` is given, that file will be used to store the data.
The file can be provided by the user, or will be created upon the
first write. Note that the filename cannot be changed after the
dataset has been created (HDF5 1.8.7), so providing absolute paths
will make the dataset difficult to copy or move across systems.

`endianness` toggles whether the data is in big-endian format.
Typically: NATIVE: use the endianness of the current machine LITTLE:
use little-endian: ARM, x86, x86_64 BIG: use big-endian: MIPS, POWER,
PowerPC, SPARC ";

%feature("docstring")  LDA::HDF5DatasetBase::create "";

%feature("docstring")  LDA::HDF5DatasetBase::ndims "

Returns the rank of the dataset. ";

%feature("docstring")  LDA::HDF5DatasetBase::dims "

Returns the dimension sizes. ";

%feature("docstring")  LDA::HDF5DatasetBase::maxdims "

Returns the maximum dimension sizes to which this dataset can grow;
elements of -1 represent unbounded dimensions. ";

%feature("docstring")  LDA::HDF5DatasetBase::externalFiles "

Returns a list of the external files containing data for this dataset.
";

%feature("docstring")  LDA::HDF5DatasetBase::getMatrix "

Retrieves any matrix of data of sizes `size` from position `pos`.
`buffer` must point to a memory block large enough to hold the result.

Requires: pos.size() == size.size() == ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::setMatrix "

Stores any matrix of data of sizes `size` at position `pos`.

Requires: pos.size() == size.size() == ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::get2D "

Retrieves a 2D matrix of data from a 2D dataset from position `pos`.
`buffer` must point to a memory block large enough to hold the result.

pos: position of the first sample dim1, dim2, outbuffer2: 2D array,
the size of which determines the amount of data to retrieve dim1index,
dim2index: indices of the dimensions to query

Requires: ndims() >= 2 pos.size() == ndims() dim1index < dim2index <
ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::set2D "

Stores a 2D matrix of data from a 2D dataset at position `pos`.

pos: position of the first sample dim1, dim2, outbuffer2: 2D array,
the size of which determines the amount of data to write dim1index,
dim2index: indices of the dimensions to query

Requires: ndims() >= 2 pos.size() == ndims() dim1index < dim2index <
ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::get1D "

Retrieves a 1D matrix of data from a 1D dataset from position `pos`.
`buffer` must point to a memory block large enough to hold the result.

pos: position of the first sample dim1, outbuffer1: 1D array, the size
of which determines the amount of data to write dim1index: index of
the dimension to query

Requires: ndims() >= 1 pos.size() == ndims() dim1index < ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::set1D "

Stores a 1D matrix of data from a 1D dataset at position `pos`.

pos: position of the first sample dim1, outbuffer1: 1D array, the size
of which determines the amount of data to write dim1index: index of
the dimension to query

Requires: ndims() >= 1 pos.size() == ndims() dim1index < ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::getScalar "

Retrieves a single value from the dataset from position `pos`.

Requires: pos.size() == ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::setScalar "

Stores a single value into the dataset at position `pos`.

Requires: pos.size() == ndims() ";


// File: classLDA_1_1HDF5Exception.xml
%feature("docstring") LDA::HDF5Exception "";

%feature("docstring")  LDA::HDF5Exception::HDF5Exception "";


// File: classLDA_1_1HDF5FileBase.xml
%feature("docstring") LDA::HDF5FileBase "";

%feature("docstring")  LDA::HDF5FileBase::flush "";


// File: classLDA_1_1HDF5GroupBase.xml
%feature("docstring") LDA::HDF5GroupBase "";

%feature("docstring")  LDA::HDF5GroupBase::HDF5GroupBase "";

%feature("docstring")  LDA::HDF5GroupBase::~HDF5GroupBase "";

%feature("docstring")  LDA::HDF5GroupBase::create "";

%feature("docstring")  LDA::HDF5GroupBase::exists "";

%feature("docstring")  LDA::HDF5GroupBase::remove "";

%feature("docstring")  LDA::HDF5GroupBase::set "";

%feature("docstring")  LDA::HDF5GroupBase::groupType "";


// File: classLDA_1_1HDF5Node.xml
%feature("docstring") LDA::HDF5Node "";

%feature("docstring")  LDA::HDF5Node::HDF5Node "";

%feature("docstring")  LDA::HDF5Node::name "";


// File: classLDA_1_1hid__gc.xml
%feature("docstring") LDA::hid_gc "";

%feature("docstring")  LDA::hid_gc::hid_gc "";

%feature("docstring")  LDA::hid_gc::hid_gc "";

%feature("docstring")  LDA::hid_gc::~hid_gc "";


// File: classLDA_1_1hid__gc__noref.xml
%feature("docstring") LDA::hid_gc_noref "";

%feature("docstring")  LDA::hid_gc_noref::hid_gc_noref "";

%feature("docstring")  LDA::hid_gc_noref::~hid_gc_noref "";


// File: classLDA_1_1SpectralCoordinate.xml
%feature("docstring") LDA::SpectralCoordinate "";


// File: classLDA_1_1SysLog.xml
%feature("docstring") LDA::SysLog "";


// File: classLDA_1_1TimeCoordinate.xml
%feature("docstring") LDA::TimeCoordinate "";


// File: namespaceLDA.xml
%feature("docstring")  LDA::h5scalar "";

%feature("docstring")  LDA::h5array "";

%feature("docstring")  LDA::h5stringType "";

%feature("docstring")  LDA::h5complexType< T > " ";

%feature("docstring")  LDA::h5nativeType "";

%feature("docstring")  LDA::h5nativeType< float > " ";

%feature("docstring")  LDA::h5nativeType< double > " ";

%feature("docstring")  LDA::h5nativeType< unsigned > " ";

%feature("docstring")  LDA::h5nativeType< int > " ";

%feature("docstring")  LDA::h5nativeType< bool > " ";

%feature("docstring")  LDA::h5writeType "";

%feature("docstring")  LDA::h5writeType< float > " ";

%feature("docstring")  LDA::h5writeType< double > " ";

%feature("docstring")  LDA::h5writeType< unsigned > " ";

%feature("docstring")  LDA::h5writeType< int > " ";

%feature("docstring")  LDA::h5writeType< bool > " ";

%feature("docstring")  LDA::h5dataType "";

%feature("docstring")  LDA::h5dataType< float > " ";


// File: namespacestd.xml


// File: BeamFormedFile_8cc.xml


// File: BeamFormedFile_8h.xml


// File: CommonAttributesFile_8cc.xml


// File: CommonAttributesFile_8h.xml


// File: h5attribute_8h.xml


// File: h5complex_8h.xml


// File: h5exception_8h.xml


// File: h5typemap_8h.xml


// File: hid__gc_8h.xml


// File: HDF5DatasetBase_8h.xml


// File: HDF5FileBase_8cc.xml


// File: HDF5FileBase_8h.xml


// File: HDF5GroupBase_8cc.xml


// File: HDF5GroupBase_8h.xml


// File: HDF5Node_8h.xml


// File: test_8cpp.xml
%feature("docstring")  main "";


// File: dir_e977623c22313efae7be34036cf05f12.xml

