AddVector( TBB_Station,       DAL::TBB_Station );
AddVector( TBB_DipoleDataset, DAL::TBB_DipoleDataset );

%include dal/lofar/TBB_File.h

%extend DAL::TBB_DipoleDataset {
  %pythoncode {
    def __len__(self):
      return self.dims()[0]
  }
}

