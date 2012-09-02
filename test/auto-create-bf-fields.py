#!/usr/bin/env python
import sys
import DAL

exit_status = 0

filename = 'test-auto-create-bf-fields.h5'
f = DAL.BF_File(filename, DAL.BF_File.CREATE)

telescope_attr = f.telescope()
if telescope_attr.get() != 'LOFAR':
  print 'TELESCOPE is not auto-created and set to LOFAR'
  exit_status = 1

filedate_attr = f.fileDate()
if not filedate_attr.exists():
  print 'FILEDATE is not auto-created'
  exit_status = 1

filetype_attr = f.fileType()
if filetype_attr.get() != 'bf':
  print 'FILETYPE is not auto-created and set to bf'
  exit_status = 1

filename_attr = f.fileName()
if filename_attr.get() != filename:
  print 'FILENAME is not auto-created and set to ', filename
  exit_status = 1

docversion_attr = f.docVersion()
if not docversion_attr.exists():
  print 'DOC_VERSION is not auto-created'
  exit_status = 1

sys.exit(exit_status)

