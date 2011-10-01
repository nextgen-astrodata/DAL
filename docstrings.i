
// File: index.xml

// File: classLDA_1_1Attribute.xml
%feature("docstring") LDA::Attribute "

Represents an attribute containing a scalar or a string.

Represents an attribute containing a vector of scalars or strings.

C++ includes: h5attribute.h ";

%feature("docstring")  LDA::Attribute::Attribute "LDA::Attribute< T
>::Attribute(const hid_gc &container, const std::string &name) ";

%feature("docstring")  LDA::Attribute::get "T LDA::Attribute< T
>::get() const

Returns the value of this attribute, retrieved from the HDF5 file. An
exception is thrown if the attribute does not already exist. ";

%feature("docstring")  LDA::Attribute::set "void LDA::Attribute< T
>::set(const T &value) const

Stores the value of this attribute in the HDF5 file. The attribute is
created if it does not already exist. ";


// File: classLDA_1_1Attribute_3_01std_1_1vector_3_01T_01_4_01_4.xml
%feature("docstring") LDA::Attribute< std::vector< T > > " ";

%feature("docstring")  LDA::Attribute< std::vector< T > >::Attribute "
LDA::Attribute< std::vector< T > >::Attribute(const hid_gc &container,
const std::string &name) ";

%feature("docstring")  LDA::Attribute< std::vector< T > >::get "
std::vector< T > LDA::Attribute< std::vector< T > >::get() const

Returns the value of this attribute, retrieved from the HDF5 file. An
exception is thrown if the attribute does not already exist. ";

%feature("docstring")  LDA::Attribute< std::vector< T > >::set " void
LDA::Attribute< std::vector< T > >::set(const std::vector< T > &value)
const

Stores the value of this attribute in the HDF5 file. The attribute is
created if it does not already exist. ";


// File: classLDA_1_1AttributeBase.xml
%feature("docstring") LDA::AttributeBase "

Represents core functionality for an attribute inside a group.

C++ includes: h5attribute.h ";

%feature("docstring")  LDA::AttributeBase::name "std::string
LDA::AttributeBase::name() const

Returns the name of this element in the HDF5 file. ";

%feature("docstring")  LDA::AttributeBase::exists "bool
LDA::AttributeBase::exists() const

Returns whether this element exists in the HDF5 file. ";

%feature("docstring")  LDA::AttributeBase::remove "void
LDA::AttributeBase::remove() const

Removes this element from the HDF5 file. Useful for porting,
repairing, or otherwise modifying files on a structural level. ";


// File: classLDA_1_1BeamFormedFile.xml
%feature("docstring") LDA::BeamFormedFile "

Interface for Beam-formed Data as described in ICD003.

C++ includes: BeamFormedFile.h ";

%feature("docstring")  LDA::BeamFormedFile::BeamFormedFile "LDA::BeamFormedFile::BeamFormedFile(const std::string &filename, enum
fileMode mode=READ) ";

%feature("docstring")  LDA::BeamFormedFile::createOfflineOnline "Attribute< string > LDA::BeamFormedFile::createOfflineOnline() ";

%feature("docstring")  LDA::BeamFormedFile::BFFormat "Attribute<
string > LDA::BeamFormedFile::BFFormat() ";

%feature("docstring")  LDA::BeamFormedFile::BFVersion "Attribute<
string > LDA::BeamFormedFile::BFVersion() ";

%feature("docstring")  LDA::BeamFormedFile::expTimeStartUTC "Attribute< string > LDA::BeamFormedFile::expTimeStartUTC() ";

%feature("docstring")  LDA::BeamFormedFile::expTimeStartMJD "Attribute< double > LDA::BeamFormedFile::expTimeStartMJD() ";

%feature("docstring")  LDA::BeamFormedFile::expTimeStartTAI "Attribute< string > LDA::BeamFormedFile::expTimeStartTAI() ";

%feature("docstring")  LDA::BeamFormedFile::expTimeEndUTC "Attribute<
string > LDA::BeamFormedFile::expTimeEndUTC() ";

%feature("docstring")  LDA::BeamFormedFile::expTimeEndMJD "Attribute<
double > LDA::BeamFormedFile::expTimeEndMJD() ";

%feature("docstring")  LDA::BeamFormedFile::expTimeEndTAI "Attribute<
string > LDA::BeamFormedFile::expTimeEndTAI() ";

%feature("docstring")  LDA::BeamFormedFile::totalIntegrationTime "Attribute< double > LDA::BeamFormedFile::totalIntegrationTime() ";

%feature("docstring")  LDA::BeamFormedFile::observationDatatype "Attribute< string > LDA::BeamFormedFile::observationDatatype() ";

%feature("docstring")  LDA::BeamFormedFile::subArrayPointingDiameter "Attribute< double > LDA::BeamFormedFile::subArrayPointingDiameter() ";

%feature("docstring")  LDA::BeamFormedFile::bandwidth "Attribute<
double > LDA::BeamFormedFile::bandwidth() ";

%feature("docstring")  LDA::BeamFormedFile::beamDiameter "Attribute<
double > LDA::BeamFormedFile::beamDiameter() ";

%feature("docstring")  LDA::BeamFormedFile::weatherTemperature "Attribute< vector< double > >
LDA::BeamFormedFile::weatherTemperature() ";

%feature("docstring")  LDA::BeamFormedFile::weatherHumidity "Attribute< vector< double > > LDA::BeamFormedFile::weatherHumidity()
";

%feature("docstring")  LDA::BeamFormedFile::systemTemperature "Attribute< vector< double > > LDA::BeamFormedFile::systemTemperature()
";

%feature("docstring")  LDA::BeamFormedFile::nofSubArrayPointings "Attribute< unsigned > LDA::BeamFormedFile::nofSubArrayPointings() ";

%feature("docstring")  LDA::BeamFormedFile::subArrayPointing "BF_SubArrayPointing LDA::BeamFormedFile::subArrayPointing(unsigned nr)
";

%feature("docstring")  LDA::BeamFormedFile::sysLog "SysLog
LDA::BeamFormedFile::sysLog() ";


// File: classLDA_1_1BF__BeamGroup.xml
%feature("docstring") LDA::BF_BeamGroup "";

%feature("docstring")  LDA::BF_BeamGroup::nofStations "Attribute<
unsigned > LDA::BF_BeamGroup::nofStations() ";

%feature("docstring")  LDA::BF_BeamGroup::stationsList "Attribute<
vector< string > > LDA::BF_BeamGroup::stationsList() ";

%feature("docstring")  LDA::BF_BeamGroup::pointRA "Attribute< double
> LDA::BF_BeamGroup::pointRA() ";

%feature("docstring")  LDA::BF_BeamGroup::pointDEC "Attribute< double
> LDA::BF_BeamGroup::pointDEC() ";

%feature("docstring")  LDA::BF_BeamGroup::pointOffsetRA "Attribute<
double > LDA::BF_BeamGroup::pointOffsetRA() ";

%feature("docstring")  LDA::BF_BeamGroup::pointOffsetDEC "Attribute<
double > LDA::BF_BeamGroup::pointOffsetDEC() ";

%feature("docstring")  LDA::BF_BeamGroup::foldedData "Attribute< bool
> LDA::BF_BeamGroup::foldedData() ";

%feature("docstring")  LDA::BF_BeamGroup::foldPeriod "Attribute<
double > LDA::BF_BeamGroup::foldPeriod() ";

%feature("docstring")  LDA::BF_BeamGroup::foldPeriodUnit "Attribute<
string > LDA::BF_BeamGroup::foldPeriodUnit() ";

%feature("docstring")  LDA::BF_BeamGroup::dedispersion "Attribute<
string > LDA::BF_BeamGroup::dedispersion() ";

%feature("docstring")  LDA::BF_BeamGroup::dedispersionMeasure "Attribute< double > LDA::BF_BeamGroup::dedispersionMeasure() ";

%feature("docstring")  LDA::BF_BeamGroup::dedispersionMeasureUnit "Attribute< string > LDA::BF_BeamGroup::dedispersionMeasureUnit() ";

%feature("docstring")  LDA::BF_BeamGroup::nofStokes "Attribute<
unsigned > LDA::BF_BeamGroup::nofStokes() ";

%feature("docstring")  LDA::BF_BeamGroup::stokesComponents "Attribute< vector< string > > LDA::BF_BeamGroup::stokesComponents() ";

%feature("docstring")  LDA::BF_BeamGroup::complexVoltages "Attribute<
bool > LDA::BF_BeamGroup::complexVoltages() ";

%feature("docstring")  LDA::BF_BeamGroup::signalSum "Attribute<
string > LDA::BF_BeamGroup::signalSum() ";

%feature("docstring")  LDA::BF_BeamGroup::stokes "BF_StokesDataset
LDA::BF_BeamGroup::stokes(unsigned nr) ";

%feature("docstring")  LDA::BF_BeamGroup::coordinates "CoordinatesGroup LDA::BF_BeamGroup::coordinates() ";


// File: classLDA_1_1BF__ProcessingHistory.xml
%feature("docstring") LDA::BF_ProcessingHistory "";

%feature("docstring")  LDA::BF_ProcessingHistory::parsetObs "Attribute< bool > LDA::BF_ProcessingHistory::parsetObs() ";

%feature("docstring")  LDA::BF_ProcessingHistory::logPresto "Attribute< bool > LDA::BF_ProcessingHistory::logPresto() ";

%feature("docstring")  LDA::BF_ProcessingHistory::parFile "Attribute<
bool > LDA::BF_ProcessingHistory::parFile() ";


// File: classLDA_1_1BF__StokesDataset.xml
%feature("docstring") LDA::BF_StokesDataset "";

%feature("docstring")  LDA::BF_StokesDataset::stokesComponent "Attribute< string > LDA::BF_StokesDataset::stokesComponent() ";

%feature("docstring")  LDA::BF_StokesDataset::nofChannels "Attribute<
vector< unsigned > > LDA::BF_StokesDataset::nofChannels() ";

%feature("docstring")  LDA::BF_StokesDataset::nofSubbands "Attribute<
unsigned > LDA::BF_StokesDataset::nofSubbands() ";

%feature("docstring")  LDA::BF_StokesDataset::nofSamples "Attribute<
unsigned > LDA::BF_StokesDataset::nofSamples() ";


// File: classLDA_1_1BF__SubArrayPointing.xml
%feature("docstring") LDA::BF_SubArrayPointing "";

%feature("docstring")  LDA::BF_SubArrayPointing::nofStations "Attribute< unsigned > LDA::BF_SubArrayPointing::nofStations() ";

%feature("docstring")  LDA::BF_SubArrayPointing::stationsList "Attribute< vector< string > > LDA::BF_SubArrayPointing::stationsList()
";

%feature("docstring")  LDA::BF_SubArrayPointing::pointRA "Attribute<
double > LDA::BF_SubArrayPointing::pointRA() ";

%feature("docstring")  LDA::BF_SubArrayPointing::pointDEC "Attribute<
double > LDA::BF_SubArrayPointing::pointDEC() ";

%feature("docstring")  LDA::BF_SubArrayPointing::clockRate "Attribute< double > LDA::BF_SubArrayPointing::clockRate() ";

%feature("docstring")  LDA::BF_SubArrayPointing::clockRateUnit "Attribute< string > LDA::BF_SubArrayPointing::clockRateUnit() ";

%feature("docstring")  LDA::BF_SubArrayPointing::nofSamples "Attribute< unsigned > LDA::BF_SubArrayPointing::nofSamples() ";

%feature("docstring")  LDA::BF_SubArrayPointing::samplingRate "Attribute< double > LDA::BF_SubArrayPointing::samplingRate() ";

%feature("docstring")  LDA::BF_SubArrayPointing::samplingRateUnit "Attribute< string > LDA::BF_SubArrayPointing::samplingRateUnit() ";

%feature("docstring")  LDA::BF_SubArrayPointing::channelsPerSubband "Attribute< unsigned > LDA::BF_SubArrayPointing::channelsPerSubband()
";

%feature("docstring")  LDA::BF_SubArrayPointing::subbandWidth "Attribute< double > LDA::BF_SubArrayPointing::subbandWidth() ";

%feature("docstring")  LDA::BF_SubArrayPointing::subbandWidthUnit "Attribute< string > LDA::BF_SubArrayPointing::subbandWidthUnit() ";

%feature("docstring")  LDA::BF_SubArrayPointing::channelWidth "Attribute< double > LDA::BF_SubArrayPointing::channelWidth() ";

%feature("docstring")  LDA::BF_SubArrayPointing::channelWidthUnit "Attribute< string > LDA::BF_SubArrayPointing::channelWidthUnit() ";

%feature("docstring")  LDA::BF_SubArrayPointing::nofBeams "Attribute<
unsigned > LDA::BF_SubArrayPointing::nofBeams() ";

%feature("docstring")  LDA::BF_SubArrayPointing::beam "BF_BeamGroup
LDA::BF_SubArrayPointing::beam(unsigned nr) ";


// File: classLDA_1_1CommonAttributesFile.xml
%feature("docstring") LDA::CommonAttributesFile "

Wraps an HDF5 file implementing the Common LOFAR Attributes.

C++ includes: CommonAttributesFile.h ";

%feature("docstring")  LDA::CommonAttributesFile::CommonAttributesFile
"LDA::CommonAttributesFile::CommonAttributesFile(const std::string
&filename, enum fileMode mode=READ) ";

%feature("docstring")  LDA::CommonAttributesFile::groupType "Attribute< string > LDA::CommonAttributesFile::groupType() ";

%feature("docstring")  LDA::CommonAttributesFile::fileName "Attribute< string > LDA::CommonAttributesFile::fileName() ";

%feature("docstring")  LDA::CommonAttributesFile::fileDate "Attribute< string > LDA::CommonAttributesFile::fileDate() ";

%feature("docstring")  LDA::CommonAttributesFile::fileType "Attribute< string > LDA::CommonAttributesFile::fileType() ";

%feature("docstring")  LDA::CommonAttributesFile::telescope "Attribute< string > LDA::CommonAttributesFile::telescope() ";

%feature("docstring")  LDA::CommonAttributesFile::observer "Attribute< string > LDA::CommonAttributesFile::observer() ";

%feature("docstring")  LDA::CommonAttributesFile::projectID "Attribute< string > LDA::CommonAttributesFile::projectID() ";

%feature("docstring")  LDA::CommonAttributesFile::projectTitle "Attribute< string > LDA::CommonAttributesFile::projectTitle() ";

%feature("docstring")  LDA::CommonAttributesFile::projectPI "Attribute< string > LDA::CommonAttributesFile::projectPI() ";

%feature("docstring")  LDA::CommonAttributesFile::projectCOI "Attribute< string > LDA::CommonAttributesFile::projectCOI() ";

%feature("docstring")  LDA::CommonAttributesFile::projectContact "Attribute< string > LDA::CommonAttributesFile::projectContact() ";

%feature("docstring")  LDA::CommonAttributesFile::observationID "Attribute< string > LDA::CommonAttributesFile::observationID() ";

%feature("docstring")  LDA::CommonAttributesFile::observationStartUTC
"Attribute< string > LDA::CommonAttributesFile::observationStartUTC()
";

%feature("docstring")  LDA::CommonAttributesFile::observationStartMJD
"Attribute< double > LDA::CommonAttributesFile::observationStartMJD()
";

%feature("docstring")  LDA::CommonAttributesFile::observationStartTAI
"Attribute< string > LDA::CommonAttributesFile::observationStartTAI()
";

%feature("docstring")  LDA::CommonAttributesFile::observationEndUTC "Attribute< string > LDA::CommonAttributesFile::observationEndUTC() ";

%feature("docstring")  LDA::CommonAttributesFile::observationEndMJD "Attribute< double > LDA::CommonAttributesFile::observationEndMJD() ";

%feature("docstring")  LDA::CommonAttributesFile::observationEndTAI "Attribute< string > LDA::CommonAttributesFile::observationEndTAI() ";

%feature("docstring")
LDA::CommonAttributesFile::observationNofStations "Attribute<
unsigned > LDA::CommonAttributesFile::observationNofStations() ";

%feature("docstring")
LDA::CommonAttributesFile::observationStationsList "Attribute<
vector< string > >
LDA::CommonAttributesFile::observationStationsList() ";

%feature("docstring")
LDA::CommonAttributesFile::observationNofBitsPerSample "Attribute<
unsigned > LDA::CommonAttributesFile::observationNofBitsPerSample() ";

%feature("docstring")  LDA::CommonAttributesFile::clockFrequency "Attribute< double > LDA::CommonAttributesFile::clockFrequency() ";

%feature("docstring")  LDA::CommonAttributesFile::clockFrequencyUnit "Attribute< string > LDA::CommonAttributesFile::clockFrequencyUnit() ";

%feature("docstring")  LDA::CommonAttributesFile::antennaSet "Attribute< string > LDA::CommonAttributesFile::antennaSet() ";

%feature("docstring")  LDA::CommonAttributesFile::filterSelection "Attribute< string > LDA::CommonAttributesFile::filterSelection() ";

%feature("docstring")  LDA::CommonAttributesFile::target "Attribute<
string > LDA::CommonAttributesFile::target() ";

%feature("docstring")  LDA::CommonAttributesFile::systemVersion "Attribute< string > LDA::CommonAttributesFile::systemVersion() ";

%feature("docstring")  LDA::CommonAttributesFile::pipelineName "Attribute< string > LDA::CommonAttributesFile::pipelineName() ";

%feature("docstring")  LDA::CommonAttributesFile::pipelineVersion "Attribute< string > LDA::CommonAttributesFile::pipelineVersion() ";

%feature("docstring")  LDA::CommonAttributesFile::ICDNumber "Attribute< string > LDA::CommonAttributesFile::ICDNumber() ";

%feature("docstring")  LDA::CommonAttributesFile::ICDVersion "Attribute< string > LDA::CommonAttributesFile::ICDVersion() ";

%feature("docstring")  LDA::CommonAttributesFile::notes "Attribute<
string > LDA::CommonAttributesFile::notes() ";


// File: classLDA_1_1Coordinate.xml
%feature("docstring") LDA::Coordinate "";

%feature("docstring")  LDA::Coordinate::coordinateType "Attribute<
string > LDA::Coordinate::coordinateType() ";

%feature("docstring")  LDA::Coordinate::storageType "Attribute<
vector< string > > LDA::Coordinate::storageType() ";

%feature("docstring")  LDA::Coordinate::nofAxes "Attribute< unsigned
> LDA::Coordinate::nofAxes() ";

%feature("docstring")  LDA::Coordinate::axisNames "Attribute< vector<
string > > LDA::Coordinate::axisNames() ";

%feature("docstring")  LDA::Coordinate::axisUnits "Attribute< vector<
string > > LDA::Coordinate::axisUnits() ";

%feature("docstring")  LDA::Coordinate::referenceValue "Attribute<
vector< double > > LDA::Coordinate::referenceValue() ";

%feature("docstring")  LDA::Coordinate::referencePixel "Attribute<
vector< double > > LDA::Coordinate::referencePixel() ";

%feature("docstring")  LDA::Coordinate::increment "Attribute< vector<
double > > LDA::Coordinate::increment() ";

%feature("docstring")  LDA::Coordinate::pc "Attribute< vector< double
> > LDA::Coordinate::pc() ";

%feature("docstring")  LDA::Coordinate::axisValuesPixel "Attribute<
vector< double > > LDA::Coordinate::axisValuesPixel() ";

%feature("docstring")  LDA::Coordinate::axisValuesWorld "Attribute<
vector< double > > LDA::Coordinate::axisValuesWorld() ";


// File: classLDA_1_1CoordinatesGroup.xml
%feature("docstring") LDA::CoordinatesGroup "";

%feature("docstring")  LDA::CoordinatesGroup::refLocationValue "Attribute< vector< double > >
LDA::CoordinatesGroup::refLocationValue() ";

%feature("docstring")  LDA::CoordinatesGroup::refLocationUnit "Attribute< vector< string > > LDA::CoordinatesGroup::refLocationUnit()
";

%feature("docstring")  LDA::CoordinatesGroup::refLocationFrame "Attribute< string > LDA::CoordinatesGroup::refLocationFrame() ";

%feature("docstring")  LDA::CoordinatesGroup::refTimeValue "Attribute< double > LDA::CoordinatesGroup::refTimeValue() ";

%feature("docstring")  LDA::CoordinatesGroup::refTimeUnit "Attribute<
string > LDA::CoordinatesGroup::refTimeUnit() ";

%feature("docstring")  LDA::CoordinatesGroup::refTimeFrame "Attribute< string > LDA::CoordinatesGroup::refTimeFrame() ";

%feature("docstring")  LDA::CoordinatesGroup::nofCoordinates "Attribute< unsigned > LDA::CoordinatesGroup::nofCoordinates() ";

%feature("docstring")  LDA::CoordinatesGroup::nofAxes "Attribute<
unsigned > LDA::CoordinatesGroup::nofAxes() ";

%feature("docstring")  LDA::CoordinatesGroup::coordinateTypes "Attribute< vector< string > > LDA::CoordinatesGroup::coordinateTypes()
";

%feature("docstring")  LDA::CoordinatesGroup::coordinate "Coordinate
LDA::CoordinatesGroup::coordinate(unsigned nr) ";


// File: classLDA_1_1HDF5DatasetBase.xml
%feature("docstring") LDA::HDF5DatasetBase "

Provides generic functionality for HDF5 Datasets.

C++ includes: HDF5DatasetBase.h ";

%feature("docstring")  LDA::HDF5DatasetBase::create "void
LDA::HDF5DatasetBase< T >::create(const std::vector< ssize_t > &dims,
const std::vector< ssize_t > &maxdims, const std::string
&filename=\"\", enum Endianness endianness=NATIVE)

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

%feature("docstring")  LDA::HDF5DatasetBase::create "virtual void
LDA::HDF5DatasetBase< T >::create() const ";

%feature("docstring")  LDA::HDF5DatasetBase::ndims "size_t
LDA::HDF5DatasetBase< T >::ndims()

Returns the rank of the dataset. ";

%feature("docstring")  LDA::HDF5DatasetBase::dims "std::vector<
ssize_t > LDA::HDF5DatasetBase< T >::dims()

Returns the dimension sizes. ";

%feature("docstring")  LDA::HDF5DatasetBase::maxdims "std::vector<
ssize_t > LDA::HDF5DatasetBase< T >::maxdims()

Returns the maximum dimension sizes to which this dataset can grow;
elements of -1 represent unbounded dimensions. ";

%feature("docstring")  LDA::HDF5DatasetBase::externalFiles "std::vector< std::string > LDA::HDF5DatasetBase< T >::externalFiles()

Returns a list of the external files containing data for this dataset.
";

%feature("docstring")  LDA::HDF5DatasetBase::getMatrix "void
LDA::HDF5DatasetBase< T >::getMatrix(const std::vector< size_t > &pos,
const std::vector< size_t > &size, T *buffer)

Retrieves any matrix of data of sizes `size` from position `pos`.
`buffer` must point to a memory block large enough to hold the result.

Requires: pos.size() == size.size() == ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::setMatrix "void
LDA::HDF5DatasetBase< T >::setMatrix(const std::vector< size_t > &pos,
const std::vector< size_t > &size, const T *buffer)

Stores any matrix of data of sizes `size` at position `pos`.

Requires: pos.size() == size.size() == ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::get2D "void
LDA::HDF5DatasetBase< T >::get2D(const std::vector< size_t > &pos, int
dim1, int dim2, T *outbuffer2, unsigned dim1index=0, unsigned
dim2index=1)

Retrieves a 2D matrix of data from a 2D dataset from position `pos`.
`buffer` must point to a memory block large enough to hold the result.

pos: position of the first sample dim1, dim2, outbuffer2: 2D array,
the size of which determines the amount of data to retrieve dim1index,
dim2index: indices of the dimensions to query

Requires: ndims() >= 2 pos.size() == ndims() dim1index < dim2index <
ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::set2D "void
LDA::HDF5DatasetBase< T >::set2D(const std::vector< size_t > &pos, int
dim1, int dim2, const T *inbuffer2, unsigned dim1index=0, unsigned
dim2index=1)

Stores a 2D matrix of data from a 2D dataset at position `pos`.

pos: position of the first sample dim1, dim2, outbuffer2: 2D array,
the size of which determines the amount of data to write dim1index,
dim2index: indices of the dimensions to query

Requires: ndims() >= 2 pos.size() == ndims() dim1index < dim2index <
ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::get1D "void
LDA::HDF5DatasetBase< T >::get1D(const std::vector< size_t > &pos, int
dim1, T *outbuffer1, unsigned dim1index=0)

Retrieves a 1D matrix of data from a 1D dataset from position `pos`.
`buffer` must point to a memory block large enough to hold the result.

pos: position of the first sample dim1, outbuffer1: 1D array, the size
of which determines the amount of data to write dim1index: index of
the dimension to query

Requires: ndims() >= 1 pos.size() == ndims() dim1index < ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::set1D "void
LDA::HDF5DatasetBase< T >::set1D(const std::vector< size_t > &pos, int
dim1, const T *inbuffer1, unsigned dim1index=0)

Stores a 1D matrix of data from a 1D dataset at position `pos`.

pos: position of the first sample dim1, outbuffer1: 1D array, the size
of which determines the amount of data to write dim1index: index of
the dimension to query

Requires: ndims() >= 1 pos.size() == ndims() dim1index < ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::getScalar "T
LDA::HDF5DatasetBase< T >::getScalar(const std::vector< size_t > &pos)

Retrieves a single value from the dataset from position `pos`.

Requires: pos.size() == ndims() ";

%feature("docstring")  LDA::HDF5DatasetBase::setScalar "void
LDA::HDF5DatasetBase< T >::setScalar(const std::vector< size_t > &pos,
const T &value)

Stores a single value into the dataset at position `pos`.

Requires: pos.size() == ndims() ";


// File: classLDA_1_1HDF5Exception.xml
%feature("docstring") LDA::HDF5Exception "";

%feature("docstring")  LDA::HDF5Exception::HDF5Exception "LDA::HDF5Exception::HDF5Exception(const std::string &msg) ";


// File: classLDA_1_1HDF5FileBase.xml
%feature("docstring") LDA::HDF5FileBase "";

%feature("docstring")  LDA::HDF5FileBase::flush "void
LDA::HDF5FileBase::flush() const ";


// File: classLDA_1_1HDF5GroupBase.xml
%feature("docstring") LDA::HDF5GroupBase "";

%feature("docstring")  LDA::HDF5GroupBase::HDF5GroupBase "LDA::HDF5GroupBase::HDF5GroupBase(const HDF5GroupBase &other) ";

%feature("docstring")  LDA::HDF5GroupBase::~HDF5GroupBase "LDA::HDF5GroupBase::~HDF5GroupBase() ";

%feature("docstring")  LDA::HDF5GroupBase::create "void
LDA::HDF5GroupBase::create() ";

%feature("docstring")  LDA::HDF5GroupBase::exists "bool
LDA::HDF5GroupBase::exists() const ";

%feature("docstring")  LDA::HDF5GroupBase::remove "void
LDA::HDF5GroupBase::remove() const ";

%feature("docstring")  LDA::HDF5GroupBase::set "void
LDA::HDF5GroupBase::set(const HDF5GroupBase &other, bool deepcopy) ";

%feature("docstring")  LDA::HDF5GroupBase::groupType "Attribute<
string > LDA::HDF5GroupBase::groupType() ";


// File: classLDA_1_1HDF5Node.xml
%feature("docstring") LDA::HDF5Node "";

%feature("docstring")  LDA::HDF5Node::HDF5Node "LDA::HDF5Node::HDF5Node(const std::string &name) ";

%feature("docstring")  LDA::HDF5Node::name "std::string
LDA::HDF5Node::name() const ";


// File: classLDA_1_1hid__gc.xml
%feature("docstring") LDA::hid_gc "";

%feature("docstring")  LDA::hid_gc::hid_gc "LDA::hid_gc::hid_gc(hid_t
hid, hid_t(*closefunc)(hid_t), const std::string &errordesc=\"\") ";

%feature("docstring")  LDA::hid_gc::hid_gc "LDA::hid_gc::hid_gc(const
hid_gc &other) ";

%feature("docstring")  LDA::hid_gc::~hid_gc "LDA::hid_gc::~hid_gc()
";


// File: classLDA_1_1hid__gc__noref.xml
%feature("docstring") LDA::hid_gc_noref "";

%feature("docstring")  LDA::hid_gc_noref::hid_gc_noref "LDA::hid_gc_noref::hid_gc_noref(hid_t hid, hid_t(*closefunc)(hid_t),
const std::string &errordesc=\"\") ";

%feature("docstring")  LDA::hid_gc_noref::~hid_gc_noref "LDA::hid_gc_noref::~hid_gc_noref() ";


// File: classLDA_1_1SpectralCoordinate.xml
%feature("docstring") LDA::SpectralCoordinate "";


// File: classLDA_1_1SysLog.xml
%feature("docstring") LDA::SysLog "";


// File: classLDA_1_1TimeCoordinate.xml
%feature("docstring") LDA::TimeCoordinate "";


// File: namespaceLDA.xml
%feature("docstring")  LDA::h5scalar "hid_t LDA::h5scalar() ";

%feature("docstring")  LDA::h5array "hid_t LDA::h5array(hsize_t
count) ";

%feature("docstring")  LDA::h5stringType "hid_t LDA::h5stringType()
";

%feature("docstring")  LDA::h5complexType< T > " hid_gc
LDA::h5complexType< T >() ";

%feature("docstring")  LDA::h5nativeType "hid_t LDA::h5nativeType()
";

%feature("docstring")  LDA::h5nativeType< float > " hid_t
LDA::h5nativeType< float >() ";

%feature("docstring")  LDA::h5nativeType< double > " hid_t
LDA::h5nativeType< double >() ";

%feature("docstring")  LDA::h5nativeType< unsigned > " hid_t
LDA::h5nativeType< unsigned >() ";

%feature("docstring")  LDA::h5nativeType< int > " hid_t
LDA::h5nativeType< int >() ";

%feature("docstring")  LDA::h5nativeType< bool > " hid_t
LDA::h5nativeType< bool >() ";

%feature("docstring")  LDA::h5writeType "hid_t LDA::h5writeType() ";

%feature("docstring")  LDA::h5writeType< float > " hid_t
LDA::h5writeType< float >() ";

%feature("docstring")  LDA::h5writeType< double > " hid_t
LDA::h5writeType< double >() ";

%feature("docstring")  LDA::h5writeType< unsigned > " hid_t
LDA::h5writeType< unsigned >() ";

%feature("docstring")  LDA::h5writeType< int > " hid_t
LDA::h5writeType< int >() ";

%feature("docstring")  LDA::h5writeType< bool > " hid_t
LDA::h5writeType< bool >() ";

%feature("docstring")  LDA::h5dataType "hid_t LDA::h5dataType(bool
bigEndian) ";

%feature("docstring")  LDA::h5dataType< float > " hid_t
LDA::h5dataType< float >(bool bigEndian) ";


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
%feature("docstring")  main "int main() ";


// File: dir_e977623c22313efae7be34036cf05f12.xml

