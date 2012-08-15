#!/usr/bin/env python
import DAL

filename = 'test-auto-create-bf-fields.h5'
f = DAL.BF_File(filename, DAL.BF_File.CREATE)

telescope_attr = f.telescope()
if telescope_attr.get() != 'LOFAR':
  print 'TELESCOPE is not auto-created and set to LOFAR'

filedate_attr = f.fileDate()
if not filedate_attr.exists():
  print 'FILEDATE is not auto-created'

filetype_attr = f.fileType()
if filetype_attr.get() != 'bf':
  print 'FILETYPE is not auto-created and set to bf'

filename_attr = f.fileName()
if filename_attr.get() != filename:
  print 'FILENAME is not auto-created and set to ', filename

docversion_attr = f.docVersion()
if not docversion_attr.exists():
  print 'DOC_VERSION is not auto-created'

